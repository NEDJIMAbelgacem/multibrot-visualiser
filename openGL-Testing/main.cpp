// openGL-Testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Test.h"
#include "Multibrot.h"
#include "MultibrotParam.h"

void InitImGui(GLFWwindow* window, const char* glsl_version);

void DestroyImGui();

int main()
{
	// initialization context
	GLFWwindow* window;
	{
		// initialise glfw
		if (!glfwInit()) return -1;

		// set opengl version to 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		// Create a windowed mode window and its OpenGL context
		window = glfwCreateWindow(800, 600, "Multibrot", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}

		// Make the window's context current
		glfwMakeContextCurrent(window);

		// initialise glew
		if (glewInit() != GLEW_OK) {
			std::cout << "glew initialisation error" << std::endl;
			return -1;
		}
		//glfwSwapInterval(1);

		// Display opengl current version
		std::cout << "opengl version : " << glGetString(GL_VERSION) << std::endl;
	}

	// ImGui context
	{
		ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

		InitImGui(window, "#version 130");

		MultibrotParam debugTest;
		float zoom_value = 2.0f;
		glm::vec2 center_offset(0.0f);

		Multibrot mb(5, debugTest.GetColor());
		
		glCall(glEnable(GL_CULL_FACE));
		glCall(glCullFace(GL_BACK));
		float camera_step_ratio = 10.0f;
		float time1 = ImGui::GetTime();
		float time2 = ImGui::GetTime();
		float delta = 0.0f;

		auto draw_frame_fun = [&]() -> void {
			debugTest.Update(delta);
			mb.SetTransitionExponent(debugTest.GetTransitionExponent());

			mb.SetColor(debugTest.GetColor());
			mb.SetCenterOffset(center_offset);
			mb.SetZoom(zoom_value);
			mb.SetMultibrotPower(debugTest.GetMultibrotPower());
			mb.SetMaxIterationsCount(debugTest.GetMaxIterations());
			mb.SetEscapeRadius(debugTest.GetEscapeRadius());
			mb.SetColorTransition(debugTest.GetColorTransition());
			mb.Draw();
		};

		// Loop until the user closes the window
		while (!glfwWindowShouldClose(window))
		{
			float sensitivity = 100.0f;
			time1 = time2;
			time2 = ImGui::GetTime();
			delta = time2 - time1;
			// Poll for and process events
			glfwPollEvents();

			bool up_key_pressed = ImGui::IsKeyPressed(GLFW_KEY_UP) || ImGui::IsKeyPressed(GLFW_KEY_W);
			bool down_key_pressed = ImGui::IsKeyPressed(GLFW_KEY_DOWN) || ImGui::IsKeyPressed(GLFW_KEY_S);
			bool left_key_pressed = ImGui::IsKeyPressed(GLFW_KEY_LEFT) || ImGui::IsKeyPressed(GLFW_KEY_A);
			bool right_key_pressed = ImGui::IsKeyPressed(GLFW_KEY_RIGHT) || ImGui::IsKeyPressed(GLFW_KEY_D);
			bool zoom_in_pressed = ImGui::IsKeyPressed(GLFW_KEY_E) || ImGui::IsKeyPressed(GLFW_KEY_KP_ADD);
			bool zoom_out_pressed = ImGui::IsKeyPressed(GLFW_KEY_Q) || ImGui::IsKeyPressed(GLFW_KEY_KP_SUBTRACT);

			if (zoom_in_pressed) {
				zoom_value *= 0.9f;
			}
			if (zoom_out_pressed) {
				zoom_value /= 0.9f;
			}

			if (up_key_pressed) {
				center_offset.y += zoom_value / camera_step_ratio;
			}
			if (down_key_pressed) {
				center_offset.y -= zoom_value / camera_step_ratio;
			}
			if (left_key_pressed) {
				center_offset.x -= zoom_value / camera_step_ratio;
			}
			if (right_key_pressed) {
				center_offset.x += zoom_value / camera_step_ratio;
			}
			glCall(glEnable(GL_DEPTH_TEST));

			// main frame buffer
			draw_frame_fun();

			// update debug data	
			debugTest.SetZoomValue(1.0f / zoom_value);
			debugTest.Display();
			debugTest.Render();
			// Swap front and back buffers
			glfwSwapBuffers(window);
		}
		DestroyImGui();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

float lastX, lastY;

void InitImGui(GLFWwindow* window, const char* glsl_version) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void DestroyImGui() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}