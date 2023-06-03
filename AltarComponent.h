#pragma once
#include "DrawComponent.h"
#include <string>

class ObjModel;

class AltarComponent : public DrawComponent {
public:
	AltarComponent(std::string path = "resource/models/altar/Altar.obj");
	~AltarComponent();

	void update(float deltaTime) override;
	void draw() override;
private:
	ObjModel *model;
};