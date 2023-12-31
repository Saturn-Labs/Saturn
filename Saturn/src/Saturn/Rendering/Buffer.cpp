#include "SaturnPch.h"
#include "Saturn/Rendering/Buffer.h"
#include "Saturn/Rendering/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Saturn
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, UInt32 size, Int32 drawMode)
	{
		ST_PROFILE_FUNCTION();
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::API::OpenGL:
				return Ref<VertexBuffer>(new OpenGLVertexBuffer(vertices, size, drawMode));
				break;
		}
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(UInt32 size, Int32 drawMode)
	{
		ST_PROFILE_FUNCTION();
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::API::OpenGL:
				return Ref<VertexBuffer>(new OpenGLVertexBuffer(size, drawMode));
				break;
		}
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(UInt32* indices, UInt32 size, Int32 drawMode)
	{
		ST_PROFILE_FUNCTION();
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::API::OpenGL:
				return Ref<IndexBuffer>(new OpenGLIndexBuffer(indices, size, drawMode));
				break;
		}
		return nullptr;
	}
}