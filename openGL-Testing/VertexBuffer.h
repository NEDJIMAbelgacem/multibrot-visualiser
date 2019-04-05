#pragma once
#include "Renderer.h"

class VertexBuffer {
private:
	unsigned int id;
public:
	VertexBuffer(const void* data, int size);

	void Bind() const;

	void Unbind() const;

	unsigned int GetId() const;

	~VertexBuffer();
};