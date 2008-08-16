
#ifndef _SOUND_MUSICPLAYER_H_
#define _SOUND_MUSICPLAYER_H_

#include <Core/IModule.h>
#include <Display/Camera.h>
#include <Sound/ISound.h>
#include <Sound/ISoundSystem.h>
#include <Resources/ISoundResource.h>
#include <Resources/ResourceManager.h>
#include <vector>
#include <Sound/ITransitionMode.h>

namespace OpenEngine {
namespace Sound {

using OpenEngine::Core::IModule;
using OpenEngine::Display::Camera;
using namespace OpenEngine::Scene;
using namespace std;

class MusicPlayer : public IModule {

private:
	int current;
	bool first, random, stopped;
	Camera* cam;
	ISoundSystem* system;
	vector<ISound*> backgroundlist;
	ITransitionMode* tran;

public:
	MusicPlayer(Camera* inicam, ISoundSystem* system);
	~MusicPlayer();

	void AddMonoBackGroundSound(string filename);
	void AddStereoBackGroundSound(string filename);
	void RemoveBackGroundSound(int tracknumber);
	ISound* GetBackGroundSound(int tracknumber);

	void Next();
	void SwitchTo(int tracknumber);
	void Play();
	void Stop();
	void Pause();
	void Suffle();
	void Fade(int fromtracknumber, int totracknumber, float intime, float outtime);
	void SetTransitionMode(ITransitionMode* newtran);
	ITransitionMode* GetTransitionMode();

	void Initialize();
    void Process(const float deltaTime, const float percent);
    void Deinitialize();
	
	bool IsTypeOf(const std::type_info& inf) { 
        return typeid(MusicPlayer) == inf; 
    }
};

} // NS Sound
} // NS OpenEngine

#endif