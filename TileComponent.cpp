#include "TileComponent.h"
#include "ObjModel.h"
#include "Component.h"
#include "CubeComponent.h"
#include "enumType.h"

TileComponent::TileComponent(DrawComponent* drawComponent, Type type, glm::vec3 position, bool visited) :
	drawComponent(drawComponent), type(type), position(position), visited(visited)
{

}

TileComponent::~TileComponent() {

}

void TileComponent::setGameobject(DrawComponent* drawComponent) {
	this->drawComponent = drawComponent;
}

void TileComponent::setModel(ObjModel* model) {
	this->model = model;
}