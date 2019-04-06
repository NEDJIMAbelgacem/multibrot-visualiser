#include "pch.h"
#include "MultibrotParam.h"

MultibrotParam::MultibrotParam() { }

void MultibrotParam::Display() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Multibrot set parameters");
	ImGui::InputInt("multibrot power p", &multibrot_power, 1, 2);;
	ImGui::InputInt("max iteration per pixel", &max_itertions, 1, 2);
	ImGui::InputFloat("escape radius", &escape_radius, 0.1, 0.2, 1);
	ImGui::ColorEdit3("color", &this->color.x);
	static const char * items[]{ "hue", "saturation", "value" };
	ImGui::Combo("color transition", &this->selected, items, 3);
	ImGui::SliderFloat("expopnent stop 1", &exponent_stop_1, 0.01, exponent_stop_2);
	ImGui::SliderFloat("expopnent stop 2", &exponent_stop_2, exponent_stop_1, 6.0f);
	ImGui::SliderFloat("transition ratio", &color_transition_ratio, 0.0f, 5.0f);
	ImGui::Text("Image zoomed in %.3f times", zoom_value);
	ImGui::Text("Exponent : %.3f", transition_exponent);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

int MultibrotParam::GetMultibrotPower() {
	return this->multibrot_power;
}

int MultibrotParam::GetMaxIterations() {
	return this->max_itertions;
}

glm::vec3 MultibrotParam::GetColor() {
	glm::vec3 res;
	ImGui::ColorConvertRGBtoHSV(color.x, color.y, color.z, res[0], res[1], res[2]);
	return res;
}

float MultibrotParam::GetEscapeRadius() {
	return escape_radius;
}

float MultibrotParam::GetTransitionExponent() {
	return transition_exponent;
}

int MultibrotParam::GetColorTransition() {
	return selected;
}

void MultibrotParam::SetZoomValue(float zoom) {
	this->zoom_value = zoom;
}

void MultibrotParam::Update(float time_delta) {
	transition_exponent += color_transition_sign * color_transition_ratio * time_delta;
	if (transition_exponent > exponent_stop_2 || transition_exponent < exponent_stop_1)
		color_transition_sign *= -1.0f;
	if (transition_exponent < exponent_stop_1) transition_exponent = exponent_stop_1;
	if (transition_exponent > exponent_stop_2) transition_exponent = exponent_stop_2;
}

void MultibrotParam::Render() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

MultibrotParam::~MultibrotParam() { }