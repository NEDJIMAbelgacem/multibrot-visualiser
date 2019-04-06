#include "pch.h"
#include "Multibrot.h"

Multibrot::Multibrot(int power, glm::vec3 color, int max_iterations) : 
	color(color), multibrot_power(power), max_iterations(max_iterations){
	
	shader = new ShaderProgram(shader_path);
	shader->FillUniform1i("u_multibrot_power", power);
	shader->FillUniform1i("u_max_iteration", max_iterations);
	shader->FillUniformVec3("u_hsv_color", color);

	float vertices[]{
		1.0f, 1.0f,
		-1.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f
	};
	vbo = new VertexBuffer(vertices, 4 * 2 * sizeof(float));
	vao = new VertexArray();
	BufferLayout layout;
	layout.AddElement<float>(2, 0);
	vao->AddBuffer(*vbo, layout);
}

void Multibrot::Draw() {
	glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	shader->Bind();
	vao->Bind();
	glCall(glDrawArrays(GL_TRIANGLE_FAN, 0, 4));
	vao->Unbind();
	shader->Unbind();
}

void Multibrot::SetMultibrotPower(int power) {
	if (this->multibrot_power != power) {
		this->multibrot_power = power;
		shader->FillUniform1i("u_multibrot_power", power);
	}
}

void Multibrot::SetMaxIterationsCount(int max_iterations) {
	if (this->max_iterations != max_iterations) {
		this->max_iterations = max_iterations;
		shader->FillUniform1i("u_max_iteration", max_iterations);
	}
}

void Multibrot::SetZoom(float zoom) {
	if (this->zoom_value != zoom) {
		zoom_value = zoom;
		shader->FillUniform1f("u_zoom", zoom);
	}
}

void Multibrot::SetCenterOffset(glm::vec2 offset) {
	if (offset.x != this->center_offset.x || offset.y != this->center_offset.y) {
		center_offset = offset;
		shader->FillUniformVec("u_center_offset", offset);
	}
}

void Multibrot::ZoomInto(glm::vec2 center, float time) {
	SetZoom(time);
	SetCenterOffset(center);
}

void Multibrot::SetColor(glm::vec3 color) {
	if (this->color != color) {
		this->color = color;
		shader->FillUniformVec3("u_hsv_color", color);
	}
}

void Multibrot::SetEscapeRadius(float radius) {
	if (this->escape_radius != radius) {
		this->escape_radius = radius;
		shader->FillUniform1f("u_escape_radius", radius);
	}
}

void Multibrot::SetColorTransition(int index) {
	if (index != color_transition) {
		color_transition = index;
		shader->FillUniform1i("u_color_transition", color_transition);
	}
}


void Multibrot::SetTransitionExponent(float exp) {
	if (exp != transition_exponent) {
		transition_exponent = exp;
		shader->FillUniform1f("u_transition_exponent", exp);
	}
}

VertexBuffer* Multibrot::GetVertexBuffer() {
	return vbo;
}

ShaderProgram* Multibrot::GetShader() {
	return shader;
}

Multibrot::~Multibrot() {
	delete vbo;
}