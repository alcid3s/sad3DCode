#pragma once
#include "lib/imgui/imgui.h"
#include "lib/imgui/imgui_impl_glfw.h"
#include "lib/imgui/imgui_impl_opengl3.h"

class GLFWwindow;

enum MenuType {
	MainMenu,
	Loading,
	Options,
	Playing,
	None
};

class GuiManager {
public:
	GuiManager(GLFWwindow* window, const int& x, const int& y);
	~GuiManager();

	void update();
	void draw();

	void init();

	MenuType menuType;
private:
	GLFWwindow* window;
	const int& screenX, screenY;

	
private:
	void drawLoadingScreen();
	void drawMainMenu();
	void setColorGui();
};
