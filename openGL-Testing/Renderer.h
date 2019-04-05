#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/matrix_decompose.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();
#define glCall(x) GLClearError();\
	x;\
	ASSERT(!GLPrintErrors(#x, __FILE__, __LINE__))

void GLClearError();

bool GLPrintErrors(std::string function_name, std::string file, int line);

class VertexArray;
class IndexBuffer;
class ShaderProgram;

class Renderer {
private:
	glm::mat4 view_matrix = glm::mat4(1.0f);
	glm::mat4 proj_matrix = glm::mat4(1.0f);
public:
	Renderer();
	void UpdateShaderMatrices(ShaderProgram* shader);
	void SetMatrices(glm::mat4 view, glm::mat4 proj);
	void ClearScr() const;
private:
	void DrawIndexes(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader, GLenum type = GL_TRIANGLES) const;
	void DrawArrays(unsigned int vertices_count, const VertexArray& va, const ShaderProgram& shader, GLenum type = GL_TRIANGLES) const;
	void DrawInstancedArrays(unsigned int vertices_count, unsigned int instances_count, const VertexArray& va, const ShaderProgram& shader, GLenum type = GL_TRIANGLES) const;
	void DrawInstancedIndexes(unsigned int instances_count, const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader, GLenum type = GL_TRIANGLES) const;
};