#pragma once


namespace Imp
{
	class VertexArray
	{
	public:
		virtual ~VertexArray(){}
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static VertexArray* Create();
	};
}