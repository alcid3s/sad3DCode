#pragma once
#include "lib/imgui/imgui.h"
#include "lib/imgui/imgui_impl_glfw.h"
#include "lib/imgui/imgui_impl_opengl3.h"

class GLFWwindow;

enum MenuType {
	MainMenu,
	Options,
	Loading,
	None
};

class GuiManager {
public:
	GuiManager(GLFWwindow* window, const int& x, const int& y);
	~GuiManager();

	void update();
	void draw();

	void init();

	bool bShouldDrawGui = true;
	bool bLoadingScreen = false;
private:
	GLFWwindow* window;
	const int& screenX, screenY;

	MenuType menuType;
private:
	void drawMainMenu();
	void setColorGui();
};
