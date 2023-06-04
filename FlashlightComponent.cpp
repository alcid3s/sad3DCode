#include "FlashlightComponent.h"
#include "ObjModel.h"
#include "GameObject.h"
#include <GLFW/glfw3.h>
#include "tigl.h"

FlashlightComponent::FlashlightComponent(std::string path) : obj(new ObjModel(path)), bIsRunning(false)
{

}

FlashlightComponent::~FlashlightComponent()
{
}

void FlashlightComponent::update(float deltaTime)
{
	updateFlashlight();
}

void FlashlightComponent::draw()
{
	if (obj) {
		tigl::shader->setModelMatrix(this->mat);
		obj->draw();
		drawLight();
	}
}

void FlashlightComponent::updateFlashlight() {
	if (obj) {
		glm::mat4 ret(1.0f);
		glm::vec3 flashPos = -gameObject->position;

		ret = glm::translate(ret, flashPos);

		// rotate camera in right direction.
		ret = glm::rotate(ret, -gameObject->rotation.y + 2.7f, glm::vec3(0, 1, 0));

		// place camera a bit in front of camera
		glm::vec3 pos;
		if (bIsRunning) {
			pos = glm::vec3(-.03f, -.1, 0.12f);
		}
		else {
			pos = glm::vec3(0.f, -.1, 0.15f);
		}
		ret = glm::translate(ret, pos);

		// rotate camera to point in the right direction
		ret = glm::rotate(ret, .5f, glm::vec3(0, 1, 0));

		this->mat = ret;
	}
}

void FlashlightComponent::drawLight() {

	// placing the light a bit in front of the flashlight for better effects.
	glm::vec3 position = glm::vec3(-gameObject->position.x, gameObject->position.y + 1.f, -gameObject->position.z - .75f);

	// setting light, play with parameters as you like.
	tigl::shader->enableLighting(true);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightDirectional(1, true);
	tigl::shader->setLightPosition(0, position);
	tigl::shader->setLightAmbient(0, glm::vec3(0.1f, 0.1f, 0.15f));
	tigl::shader->setLightDiffuse(0, glm::vec3(1.f, 1.f, 1.f));
	tigl::shader->setLightSpecular(0, glm::vec3(0, 0, 0));
	tigl::shader->setShinyness(1.f);
}
