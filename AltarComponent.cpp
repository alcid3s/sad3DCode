#include "AltarComponent.h"
#include "ObjModel.h"

AltarComponent::AltarComponent(std::string path) : model(new ObjModel(path))
{

}

AltarComponent::~AltarComponent()
{

}

void AltarComponent::update(float deltaTime)
{
	
}

void AltarComponent::draw()
{
	if (model)
		model->draw();
}
