#include "PlaneComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.h"

PlaneComponent::PlaneComponent(glm::vec3 transform, Texture* texture, int textureMultiplier)
	: textureMultiplier(textureMultiplier), texture(texture) {
	if (texture) {
		verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, 0, -transform.z / 2), glm::vec2(0, 0)));
		verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, 0, -transform.z / 2), glm::vec2(1 * textureMultiplier, 0)));
		verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, 0, transform.z / 2), glm::vec2(0, 1 * textureMultiplier)));
		verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, 0, transform.z / 2), glm::vec2(1 * textureMultiplier, 1 * textureMultiplier)));
	}
	else {
		verts.push_back(Vertex::PC(glm::vec3(-transform.x / 2, 0, -transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
		verts.push_back(Vertex::PC(glm::vec3(transform.x / 2, 0, -transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
		verts.push_back(Vertex::PC(glm::vec3(transform.x / 2, 0, transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
		verts.push_back(Vertex::PC(glm::vec3(-transform.x / 2, 0, transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
	}
}

PlaneComponent::~PlaneComponent() {

}

void PlaneComponent::draw() {

	tigl::shader->enableColor(true);
	if (texture) {
		texture->bind();
		tigl::shader->enableTexture(true);
		tigl::drawVertices(GL_QUADS, verts);
		tigl::shader->enableTexture(false);
		texture->unbind();
	}
	else
		tigl::drawVertices(GL_QUADS, verts);
	tigl::shader->enableColor(false);
}