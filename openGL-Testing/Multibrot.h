#pragma once
#include "Renderer.h"
#include <vector>

class Multibrot {
private:
	const std::string shader_path = "resources/shaders/simulation_engine/fractals/multibrot.shader";
	VertexBuffer* vbo;
	VertexArray* vao;
	ShaderProgram* shader;
	glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f);
	int multibrot_power;
	int max_iterations;
	float escape_radius;
	float zoom_value;
	glm::vec2 center_offset;
	int color_transition;
	float transition_exponent;
public:
	Multibrot(int power, glm::vec3 color, int max_iterations = 1000);
	VertexBuffer* GetVertexBuffer();
	ShaderProgram* GetShader();
	void ZoomInto(glm::vec2 center, float time);
	void SetZoom(float zoom);
	void SetCenterOffset(glm::vec2 offset);
	void SetMultibrotPower(int power);
	void SetMaxIterationsCount(int max_iterations);
	void SetColor(glm::vec3 color);
	void SetEscapeRadius(float radius);
	void SetColorTransition(int index);
	void SetTransitionExponent(float exp);
	void Draw();
	~Multibrot();
};