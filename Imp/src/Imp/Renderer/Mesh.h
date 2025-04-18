#pragma once
#include "Texture.h"

namespace Imp
{
	struct MeshVertex
	{
		glm::vec4 Position;
		glm::vec3 TextureCoords;
		glm::vec3 Normal;
	};

	class Mesh
	{
	public:
		Mesh() = default;

		void SetMesh(std::string const& meshPath);
		void SetTexture(Ref<Texture2D> const& texture) { m_Texture = texture; }

	private:
		void LoadMesh();

	private:
		std::string m_MeshPath;
		Ref<Texture2D> m_Texture;
		std::vector<MeshVertex> m_Vertices;
		std::vector<uint32_t> m_Indices;
	};
}
