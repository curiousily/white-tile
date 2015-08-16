#include "SoundManager.h"

static SoundManager *soundManager = NULL;

const char* SoundManager::SOUND_ENABLED_KEY = "sound_enabled";
const char* SoundManager::MUSIC_ENABLED_KEY = "music_enabled";

SoundManager::SoundManager() {
}

void SoundManager::onAppStarting() {

	float soundVolume = isSoundEnabled() ? SOUND_EFFECTS_VOLUME : 0.0f;
	setEffectsVolume(soundVolume);

	float musicVolume = isMusicEnabled() ? BACKGROUND_MUSIC_VOLUME : 0.0f;
	setBackgroundVolume(musicVolume);
}

void SoundManager::loadEffect(const char *name) {
	SimpleAudioEngine::getInstance()->preloadEffect(
			String::createWithFormat("Sound/Effects/%s.wav", name)->getCString());
}

void SoundManager::setEffectsVolume(float newVolume) {
	SimpleAudioEngine::getInstance()->setEffectsVolume(newVolume);
}

bool SoundManager::isMusicEnabled() {
	auto db = UserDefault::getInstance();
	return db->getBoolForKey(MUSIC_ENABLED_KEY, true);
}

bool SoundManager::isSoundEnabled() {

	auto db = UserDefault::getInstance();
	return db->getBoolForKey(SOUND_ENABLED_KEY, true);
}

void SoundManager::setBackgroundVolume(float newVolume) {
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(newVolume);
}

void SoundManager::playLoopingBackground(const char *name) {
	SimpleAudioEngine::getInstance()->playBackgroundMusic(
			String::createWithFormat("Sound/%s.mp3", name)->getCString(),
			true);
}

void SoundManager::playSoundEffect(const char *name) {
	SimpleAudioEngine::getInstance()->playEffect(
			String::createWithFormat("Sound/Effects/%s.wav", name)->getCString());
}

void SoundManager::unmuteMusic() {
	auto db = UserDefault::getInstance();
	db->setBoolForKey(MUSIC_ENABLED_KEY, true);
    db->flush();
	setBackgroundVolume(BACKGROUND_MUSIC_VOLUME);
}

void SoundManager::unmuteSound() {
	auto db = UserDefault::getInstance();
	db->setBoolForKey(SOUND_ENABLED_KEY, true);
    db->flush();
	setEffectsVolume(SOUND_EFFECTS_VOLUME);
}

void SoundManager::muteSound() {
	auto db = UserDefault::getInstance();
	db->setBoolForKey(SOUND_ENABLED_KEY, false);
    db->flush();
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
}

void SoundManager::muteMusic() {
	auto db = UserDefault::getInstance();
	db->setBoolForKey(MUSIC_ENABLED_KEY, false);
    db->flush();
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
}

SoundManager::~SoundManager() {
}

SoundManager *SoundManager::sharedSoundManager() {
	if (soundManager == NULL) {
		soundManager = new SoundManager();
	}
	return soundManager;
}
