#pragma once
#include "lib/imgui/imgui.h"
#include "lib/imgui/imgui_impl_glfw.h"
#include "lib/imgui/imgui_impl_opengl3.h"

class GLFWwindow;

class GuiManager {
public:
	GuiManager(GLFWwindow* window, const int& x, const int& y);
	~GuiManager();

	void update();
	void draw();

	bool shouldDrawGui;
private:
	GLFWwindow* window;
	const int& screenX, screenY;
	void setColorGui();
};
