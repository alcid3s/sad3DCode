#include "AudioComponent.h"
#include "GameObject.h"
#include <tuple>

const int amountOfFootsteps = 7;
AudioComponent::AudioComponent(AudioType type) : type(type)
{
	switch (type) {
	case AudioType::Footsteps:
		for (int i = 1; i <= amountOfFootsteps; i++) {
			sf::Sound* sound = new sf::Sound();
			sf::SoundBuffer* buffer = new sf::SoundBuffer();

			std::string file = "resource/sounds/footsteps/wav/footstep" + std::to_string(i) + ".wav";

			buffer->loadFromFile(file);
			sound->setPitch(1.f);
			sound->setVolume(20.f);
			sound->setBuffer(*buffer);
			sound->setMinDistance(5.f);
			sound->setAttenuation(0.5f);

			this->footsteps.push_back(std::make_tuple(*sound, *buffer));
		}
		break;
	case AudioType::Enemy:
		break;
	case AudioType::Ambience:
		break;
	}
}

AudioComponent::~AudioComponent()
{
}

void AudioComponent::update(float deltaTime) {
	switch (type) {
	case AudioType::Footsteps:
		if (bIsMoving) {
			playFootsteps();
		}
		break;
	}
}

void AudioComponent::playFootsteps()
{
	// gettings sound from tuple
	sf::Sound* sound = &std::get<sf::Sound>(footsteps[soundPosition]);

	// check if sound is playing
	if (sound->getStatus() != sf::Sound::Playing) {

		sf::Listener::setDirection(gameObject->position.x, gameObject->position.y, gameObject->position.z);

		// get random walk sound
		this->soundPosition = rand() % footsteps.size();

		if (bIsRunning) {
			sound->setVolume(sound->getVolume() + 10.f);
			sound->setPitch(1.5f);
		}
		else {
			sound->setVolume(20.f);
			sound->setPitch(1.f);
		}

		// give sound the data for the sound from buffer in tuple.
		sound->setBuffer(std::get<sf::SoundBuffer>(footsteps[soundPosition]));

		// set origin from the sound
		sound->setPosition(gameObject->position.x, gameObject->position.y - 1, gameObject->position.z);

		// play the sound
		sound->play();
	}
}
