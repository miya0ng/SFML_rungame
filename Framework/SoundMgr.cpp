#include "stdafx.h"
#include "SoundMgr.h"

void SoundMgr::Init(int totalChannels)
{
	for (int i = 0; i < totalChannels; ++i)
	{
		sf::Sound* sound = new sf::Sound();
		sound->setVolume(sfxVolume);
		waiting.push_back(sound);
	}
}

void SoundMgr::Release()
{
	for (auto sound : waiting)
	{
		delete sound;
	}
	waiting.clear();
	for (auto sound : playing)
	{
		delete sound;
	}
	playing.clear();
}

void SoundMgr::Update(float dt)
{
	auto it = playing.begin();
	while (it != playing.end())
	{
		if ((*it)->getStatus() == sf::Sound::Stopped)
		{
			waiting.push_back(*it);
			it = playing.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void SoundMgr::PlayBgm(std::string id, bool loop)
{
	PlayBgm(SOUNDBUFFER_MGR.Get(id), loop);
}

void SoundMgr::PlayBgm(sf::SoundBuffer& buffer, bool loop)
{
	bgm.stop();
	bgm.setLoop(loop);
	bgm.setBuffer(buffer);
	bgm.play();
}

void SoundMgr::StopBgm()
{
	bgm.stop();
}

sf::Sound* SoundMgr::PlaySsfx(const std::string& id, bool loop)
{
	if (waiting.empty()) return nullptr;

	sf::Sound* sfx = waiting.back();
	waiting.pop_back();

	sfx->setBuffer(SOUNDBUFFER_MGR.Get(id));
	sfx->setLoop(loop);
	sfx->play();

	playing.push_back(sfx);  // 매 프레임 Update()에서 회수
	return sfx;
}

void SoundMgr::PlaySfx(std::string id, bool loop)
{
	PlaySfx(SOUNDBUFFER_MGR.Get(id), loop);
}

void SoundMgr::PlaySfx(sf::SoundBuffer& buffer, bool loop)
{
	sf::Sound* sound = nullptr;

	if (!waiting.empty())
	{
		sound = waiting.front();
		waiting.pop_front();
	}
	else if (!playing.empty())
	{
		sound = playing.front();
		playing.pop_front();
		sound->stop();
	}
	else
	{
		sound = new sf::Sound();
		sound->setVolume(sfxVolume);
	}

	sound->setBuffer(buffer);
	sound->setLoop(loop);
	sound->play();
	playing.push_back(sound);
}

void SoundMgr::SetSfxVolume(float v)
{
	sfxVolume = v;
	for (auto sound : playing)
	{
		sound->setVolume(sfxVolume);
	}
	for (auto sound : waiting)
	{
		sound->setVolume(sfxVolume);
	}
}

void SoundMgr::StopAllSfx()
{
	for (auto sound : playing)
	{
		sound->stop();
		waiting.push_back(sound);
	}
	playing.clear();
}