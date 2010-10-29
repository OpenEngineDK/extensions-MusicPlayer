
#ifndef _SOUND_MUSICPLAYER_H_
#define _SOUND_MUSICPLAYER_H_

#include <Core/IListener.h>
#include <Core/EngineEvents.h>
#include <Display/Camera.h>
#include <Math/RandomGenerator.h>
#include <Resources/ISoundResource.h>
#include <Resources/IStreamingSoundResource.h>
#include <Resources/ResourceManager.h>
#include <Sound/ISound.h>
#include <Sound/ISoundSystem.h>
#include <Sound/ITransitionMode.h>

#include <vector>

namespace OpenEngine {
namespace Sound {

using OpenEngine::Core::IListener;
using OpenEngine::Core::ProcessEventArg;
using OpenEngine::Display::Camera;
using OpenEngine::Math::RandomGenerator;
using namespace OpenEngine::Scene;
using std::string;

class MusicPlayer : public IListener<ProcessEventArg> {

private:
    float gain;
	unsigned int current, nextTrackNumber;
	bool random, stalled, switchToNextNumber;
	Camera* cam;
	ISoundSystem* system;
	vector<ISound*> playlist;
	ITransitionMode* tran;
	int starttime;
    /*
	IMonoSound* monoreftype;
	IStereoSound* stereoreftype;
    */
	unsigned int PreviousNumber();
	unsigned int NextNumber();
	unsigned int RandomNumber();

    RandomGenerator* randGen;

public:
	MusicPlayer(Camera* inicam, ISoundSystem* system);
	~MusicPlayer();

	void AddSound(string filename);
	//void RemoveBackGroundSound(int tracknumber);
	//ISound* GetBackGroundSound(int tracknumber);

	void Previous();
	void Next();
	void SwitchTo(unsigned int trackNumber);
    unsigned int NumberOfTracks();
	void Play();
	void Stop();
	void Pause();
	void Shuffle(bool shuffle);
	//void Fade(int fromtracknumber, int totracknumber, float intime, float outtime);
	void SetTransitionMode(ITransitionMode* mode);
	//ITransitionMode* GetTransitionMode();
    void SetGain(float gain);
    float GetGain();

	void Handle(ProcessEventArg arg);
};

} // NS Sound
} // NS OpenEngine

#endif
