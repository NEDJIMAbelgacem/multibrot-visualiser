#pragma once
#include "Test.h"
#include <map>

class MultibrotParam : public Test {
private:
	int multibrot_power = 2;
	int max_itertions = 130;
	glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f);
	float escape_radius = 2.0f;
	int selected = 0;
	float zoom_value;
	float transition_exponent = 1.0f;
public:
	MultibrotParam();
	void Display();
	void Render();
	int GetMultibrotPower();
	int GetMaxIterations();
	float GetEscapeRadius();
	int GetColorTransition();
	float GetTransitionExponent();
	void SetZoomValue(float zoom);
	glm::vec3 GetColor();
	~MultibrotParam();
};