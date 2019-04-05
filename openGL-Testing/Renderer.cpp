#include "pch.h"
#include "Renderer.h"

#define PI 3.14159f

void GLClearError() {
	while (glGetError());
}

bool GLPrintErrors(std::string function_name, std::string file, int line) {
	bool has_errors = false;
	while (GLenum err = glGetError()) {
		has_errors = true;
		std::cout << "[OpenGL error] : " << err << " " << function_name << " in " << file << ":" << line << std::endl;
	}
	return has_errors;
}

Renderer::Renderer() {
	glCall(glEnable(GL_MULTISAMPLE));
	glCall(glEnable(GL_BLEND));
	glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	glCall(glEnable(GL_DEPTH_TEST));
	glCall(glEnable(GL_CULL_FACE));
	glCall(glCullFace(GL_BACK));
	//glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}


void Renderer::UpdateShaderMatrices(ShaderProgram* shader) {
	shader->FillUniformMat4f("u_view", view_matrix);
	shader->FillUniformMat4f("u_proj", proj_matrix);
}

void Renderer::SetMatrices(glm::mat4 view, glm::mat4 proj) {
	view_matrix = view;
	proj_matrix = proj;
}

void Renderer::DrawIndexes(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader, GLenum type) const {
	shader.Bind();
	va.Bind();
	ib.Bind();
	glCall(glDrawElements(type, ib.GetCount(), GL_UNSIGNED_INT, 0));
	ib.Unbind();
	va.Unbind();
	shader.Unbind();
}

void Renderer::DrawArrays(unsigned int vertices_count, const VertexArray& va, const ShaderProgram& shader, GLenum type) const {
	shader.Bind();
	va.Bind();
	glCall(glDrawArrays(type, 0, vertices_count));
	va.Unbind();
	shader.Unbind();
}

void Renderer::DrawInstancedArrays(unsigned int vertices_count, unsigned int instances_count, const VertexArray& va, const ShaderProgram& shader, GLenum type) const {
	shader.Bind();
	va.Bind();
	glCall(glDrawArraysInstanced(type, 0, vertices_count, instances_count));
	va.Unbind();
	shader.Unbind();
}

void Renderer::DrawInstancedIndexes(unsigned int instances_count, const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader, GLenum type) const {
	shader.Bind();
	va.Bind();
	ib.Bind();
	glCall(glDrawElementsInstanced(type, ib.GetCount(), GL_UNSIGNED_INT, 0, instances_count));
	ib.Unbind();
	va.Unbind();
	shader.Unbind();
}

void Renderer::ClearScr() const {
	glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}