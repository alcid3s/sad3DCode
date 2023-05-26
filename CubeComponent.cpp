#include "CubeComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.h"

CubeComponent::CubeComponent(glm::vec3 transform, Texture* texture, int textureMultiplier)
    : textureMultiplier(textureMultiplier), texture(texture)
{
    if (texture) {
        // achterkant z
        verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec2(0, 0)));
        verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec2(0, 1 * textureMultiplier)));
        verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec2(1 * textureMultiplier, 0)));
        verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec2(1 * textureMultiplier, 1 * textureMultiplier)));

        // voorkant z
        verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec2(0, 0)));
        verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec2(0, 1 * textureMultiplier)));
        verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, transform.y / 2, transform.z / 2), glm::vec2(1 * textureMultiplier, 0)));
        verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, transform.y / 2, transform.z / 2), glm::vec2(1 * textureMultiplier, 1 * textureMultiplier)));

        // onderkant y
        verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec2(0, 0)));
        verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec2(1 * textureMultiplier, 0)));
        verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec2(0, 1 * textureMultiplier)));
        verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec2(1 * textureMultiplier, 1 * textureMultiplier)));

        // bovenkant y
        verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec2(0, 0)));
        verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec2(1 * textureMultiplier, 0)));
        verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, transform.y / 2, transform.z / 2), glm::vec2(0, 1 * textureMultiplier)));
        verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, transform.y / 2, transform.z / 2), glm::vec2(1 * textureMultiplier, 1 * textureMultiplier)));

        // linkerkant x
        verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec2(0, 0)));
        verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec2(1 * textureMultiplier, 0)));
        verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, transform.y / 2, transform.z / 2), glm::vec2(0, 1 * textureMultiplier)));
        verts.push_back(Vertex::PT(glm::vec3(-transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec2(1 * textureMultiplier, 1 * textureMultiplier)));

        // rechterkant x
        verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec2(0, 0)));
        verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec2(1 * textureMultiplier, 0)));
        verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, transform.y / 2, transform.z / 2), glm::vec2(0, 1 * textureMultiplier)));
        verts.push_back(Vertex::PT(glm::vec3(transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec2(1 * textureMultiplier, 1 * textureMultiplier)));
    }
    else {
        // achterkant z
        verts.push_back(Vertex::PC(glm::vec3(-transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(-transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

        // voorkant z
        verts.push_back(Vertex::PC(glm::vec3(-transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(transform.x / 2, transform.y / 2, transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(-transform.x / 2, transform.y / 2, transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

        // onderkant y
        verts.push_back(Vertex::PC(glm::vec3(-transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(-transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

        // bovenkant y
        verts.push_back(Vertex::PC(glm::vec3(-transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec4(1.0f, 0.8f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(transform.x / 2, transform.y / 2, transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(-transform.x / 2, transform.y / 2, transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

        // linkerkant x
        verts.push_back(Vertex::PC(glm::vec3(-transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(-transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(-transform.x / 2, transform.y / 2, transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(-transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

        // rechterkant x
        verts.push_back(Vertex::PC(glm::vec3(transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(transform.x / 2, transform.y / 2, transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        verts.push_back(Vertex::PC(glm::vec3(transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    }
}

CubeComponent::~CubeComponent()
{
}

void CubeComponent::draw()
{
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
