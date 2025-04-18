#include "ImpPCH.h"
#include "Imp/Renderer/Mesh.h"

#include <algorithm>
#include <regex>
#include <sstream>

#include "glm/ext/matrix_projection.hpp"

namespace Imp
{
	void Mesh::SetMesh(std::string const& meshPath)
	{
		m_MeshPath = meshPath;

		LoadMesh();
	}

	void Mesh::LoadMesh()
	{
		m_Indices.clear();
		m_Vertices.clear();

		std::ifstream input{ m_MeshPath };

		if (!input) return;

		std::string line;

		std::vector<glm::vec4> vertices;
		std::vector<glm::vec4> vertexNormals;
		std::vector<glm::vec3> vertexTextureCoords;

		while (std::getline(input, line))
		{
			std::string const identifier = line.substr(0, line.find_first_of(' '));
			std::stringstream lineData{ line.substr(line.find_first_of(' ') + 1) };

			switch (identifier)
			{
			case "v":
			{
				glm::vec4 vertex;
				lineData >> vertex.x >> vertex.y >> vertex.z;
				vertex.w = 1.f;
				vertices.push_back(vertex);
			}
			break;
			case "vn":
			{
				glm::vec4 vertexNormal;
				lineData >> vertexNormal.x >> vertexNormal.y >> vertexNormal.z;
				vertexNormal.w = 1.f;
				vertexNormals.push_back(vertexNormal);
			}
			break;
			case "vt":
			{
				glm::vec3 vertexTextureCoord;
				lineData >> vertexTextureCoord.x >> vertexTextureCoord.y >> vertexTextureCoord.z;
				vertexTextureCoords.push_back(vertexTextureCoord);
			}
			break;
			case "f":
			{

				uint32_t const countOfSlashes = static_cast<uint32_t>(std::count_if(lineData.str().begin(), lineData.str().end(), [](char const& c) { return c == '/'; }));

				for (int i = 0; i < 3; ++i)
				{
					MeshVertex vertex;
					char temp;

					switch (countOfSlashes)
					{
					case 0:
					{
						uint32_t v{};
						lineData >> v;
						vertex.Position = vertices[v];
					}
					break;
					case 3:
					{
						uint32_t v{}, vt{};
						lineData >> v;
						lineData.get(&temp, 1);
						lineData >> vt;

						vertex.Position = vertices[v];
						vertex.TextureCoords = vertexTextureCoords[vt];
					}
					break;
					case 6:
					{
						uint32_t v{}, vn{};
						int32_t vt{ -1 };

						lineData >> v;
						lineData.get(&temp, 1);

						//check if the next character is also a slash to see if we skip texture coordinates or not
						lineData.get(&temp, 1);

						if (temp != '/')
						{
							lineData.unget();
							lineData >> vt;
							lineData.get(&temp, 1);
						}

						lineData >> vn;

						vertex.Position = vertices[v];

						if (vt >= 0)
							vertex.TextureCoords = vertexTextureCoords[vt];

						vertex.Normal = vertexNormals[vn];
					}
					break;
					default:
						break;
					}

					auto iter = std::ranges::find_if(m_Vertices, [vertex](MeshVertex const& v)
					{
						float epsilon = 0.000001f;

						return std::abs(vertex.Position.x - v.Position.x) < epsilon && std::abs(vertex.Position.y - v.Position.y) < epsilon && std::abs(vertex.Position.x - v.Position.z) < epsilon;
					});

					if (iter == m_Vertices.end())
					{
						m_Vertices.push_back(vertex);
						m_Indices.push_back(static_cast<uint32_t>(m_Vertices.size() - 1));
					}
					else
					{
						m_Indices.push_back(static_cast<uint32_t>(std::distance(m_Vertices.begin(), iter)));
					}
				}
			}
			break;
			default:
				break;
			}
		}

		//TODO: Add tangent calculation here

	}
}
