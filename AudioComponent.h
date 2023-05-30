#pragma once
#include "Component.h"
#include "SFML/Audio.hpp"
#include <vector>
#include <tuple>
enum AudioType {
	Footsteps,
	Player,
	Enemy,
	Ambience
};

class AudioComponent : public Component {
public:
	AudioComponent(AudioType type);
	~AudioComponent();

	void update(float deltaTime) override;

	bool bIsRunning = false;
	bool bIsMoving = false;

protected:
	void playFootsteps();
	std::vector<std::tuple<sf::Sound, sf::SoundBuffer>> footsteps;
private:
	AudioType type;
	int soundPosition = 0;
};