#pragma once
#include "Component.h"
#include "SFML/Audio.hpp"
#include <vector>
#include <tuple>
enum AudioType {
	AudioPlayer,
	AudioEnemy,
	Ambience
};

class AudioComponent : public Component {
public:
	AudioComponent(AudioType type);
	~AudioComponent();

	void update(float deltaTime) override;

	bool bIsRunning = false;
	bool bIsMoving = false;

	bool bPlayOutOfBreathSound = false;

protected:
	virtual void playFootsteps();
	virtual void playOutOfBreathSound();

	sf::Music* ambience = nullptr;
	std::vector<std::tuple<sf::Sound, sf::SoundBuffer>> soundsList;
private:
	AudioType type;
	int soundPosition = 0;

	const int amountOfFootsteps = 7;
	const int amountOfOutOfBreathSounds = 1;
};