
#ifndef _SOUND_MUSICPLAYER_H_
#define _SOUND_MUSICPLAYER_H_

#include <Core/IListener.h>
#include <Core/EngineEvents.h>
#include <Display/Camera.h>
#include <Sound/ISound.h>
#include <Sound/ISoundSystem.h>
#include <Resources/ISoundResource.h>
#include <Resources/ResourceManager.h>
#include <vector>
#include <Sound/ITransitionMode.h>
#include <Utils/Timer.h>

namespace OpenEngine {
namespace Sound {

using OpenEngine::Core::IListener;
using OpenEngine::Core::ProcessEventArg;
using OpenEngine::Display::Camera;
using namespace OpenEngine::Utils;
using namespace OpenEngine::Scene;
using namespace std;

class MusicPlayer : public IListener<ProcessEventArg> {

private:
    float gain;
	unsigned int current, previous;
	bool random, stopped;
	Camera* cam;
	ISoundSystem* system;
	vector<ISound*> backgroundlist;
	ITransitionMode* tran;
	int starttime;
	Timer* mytime;
	IMonoSound* monoreftype;
	IStereoSound* stereoreftype;

	void RandomNext();

public:
	MusicPlayer(Camera* inicam, ISoundSystem* system);
	~MusicPlayer();

	void AddMonoBackGroundSound(string filename);
	void AddStereoBackGroundSound(string filename);
	void RemoveBackGroundSound(int tracknumber);
	ISound* GetBackGroundSound(int tracknumber);

	void Previous();
	void Next();
	void SwitchTo(int tracknumber);
	void Play();
	void Stop();
	void Pause();
	void Shuffle();
	void Fade(int fromtracknumber, int totracknumber, float intime, float outtime);
	void SetTransitionMode(ITransitionMode* newtran);
	ITransitionMode* GetTransitionMode();
    void SetGain(float gain);
    float GetGain();

	void Handle(ProcessEventArg arg);
};

} // NS Sound
} // NS OpenEngine

#endif
