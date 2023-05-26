#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h"

enum Type;

class DrawComponent;
class ObjModel;

class TileComponent : public Component {
public:
	TileComponent(DrawComponent*, Type type, glm::vec3 position, bool visited);
	~TileComponent();

	void setGameobject(DrawComponent*);
	void setModel(ObjModel*);

	bool visited;
	Type type;
	inline glm::vec3 GetPosition() const { return position; }
private:
	ObjModel* model = nullptr;
	glm::vec3 position;

	DrawComponent* drawComponent;
};