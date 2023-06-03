#include "AudioComponent.h"
#include "GameObject.h"
#include <tuple>

AudioComponent::AudioComponent(AudioType type) : type(type)
{
	switch (type) {
	case AudioType::AudioPlayer:
		for (int i = 1; i <= amountOfOutOfBreathSounds; i++) {
			sf::Sound* sound = new sf::Sound();
			sf::SoundBuffer* buffer = new sf::SoundBuffer();

			std::string file = "resource/sounds/characterSounds/outOfBreath" + std::to_string(i) + ".wav";

			buffer->loadFromFile(file);
			sound->setBuffer(*buffer);
			sound->setMinDistance(5.f);
			sound->setAttenuation(0.5f);

			this->soundsList.push_back(std::make_tuple(*sound, *buffer));
		}

		for (int i = 1; i <= amountOfFootsteps; i++) {
			sf::Sound* sound = new sf::Sound();
			sf::SoundBuffer* buffer = new sf::SoundBuffer();

			std::string file = "resource/sounds/footsteps/wav/footstep" + std::to_string(i) + ".wav";

			buffer->loadFromFile(file);
			sound->setBuffer(*buffer);
			sound->setMinDistance(5.f);
			sound->setAttenuation(0.5f);

			this->soundsList.push_back(std::make_tuple(*sound, *buffer));
		}
		break;
	case AudioType::AudioEnemy:
		break;
	case AudioType::Ambience:
		this->ambience = new sf::Music();
		this->ambience->openFromFile("resource/sounds/ambience.wav");
		this->ambience->setVolume(5.f);
		this->ambience->setPitch(1.f);
		break;
	}
}

AudioComponent::~AudioComponent()
{
}

void AudioComponent::update(float deltaTime) {
	switch (type) {
	case AudioType::AudioPlayer:
		if (bPlayOutOfBreathSound) {
			playOutOfBreathSound();
		}

		if (bIsMoving) {
			playFootsteps();
		}
		break;
	case AudioType::AudioEnemy:
		break;
	case AudioType::Ambience:
		if (ambience && ambience->getStatus() != sf::Sound::Playing) {
			ambience->play();
		}
		break;
	}
	

}

void AudioComponent::playOutOfBreathSound() {
	sf::Sound* sound = &std::get<sf::Sound>(soundsList[soundPosition]);

	sf::Listener::setDirection(gameObject->position.x, gameObject->position.y, gameObject->position.z);

	// get random outOfBreath sound
	this->soundPosition = rand() % (soundsList.size() - amountOfFootsteps);

	// set pitch and volume of this sound
	sound->setPitch(1.f);
	sound->setVolume(40.f);

	// give sound the data for the sound from buffer in tuple.
	sound->setBuffer(std::get<sf::SoundBuffer>(soundsList[soundPosition]));

	// set origin from the sound
	sound->setPosition(gameObject->position.x, gameObject->position.y, gameObject->position.z);

	// play the sound
	sound->play();
}

void AudioComponent::playFootsteps()
{
	// gettings sound from tuple
	sf::Sound* sound = &std::get<sf::Sound>(soundsList[soundPosition]);

	// check if sound is playing
	if (sound->getStatus() != sf::Sound::Playing) {

		sf::Listener::setDirection(gameObject->position.x, gameObject->position.y, gameObject->position.z);

		// get random walk sound, but because out of breath sounds was first. It needs to exclude those from the footsteps
		this->soundPosition = (rand() % (soundsList.size() - amountOfOutOfBreathSounds)) + amountOfOutOfBreathSounds;

		if (bIsRunning) {
			sound->setVolume(sound->getVolume() + 10.f);
			sound->setPitch(1.5f);
		}
		else {
			sound->setVolume(20.f);
			sound->setPitch(1.f);
		}

		// give sound the data for the sound from buffer in tuple.
		sound->setBuffer(std::get<sf::SoundBuffer>(soundsList[soundPosition]));

		// set origin from the sound (on the feet of the player).
		sound->setPosition(gameObject->position.x, gameObject->position.y - 1, gameObject->position.z);

		// play the sound
		sound->play();
	}
}
