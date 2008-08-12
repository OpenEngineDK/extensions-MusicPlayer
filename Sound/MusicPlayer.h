
#ifndef _SOUND_MUSICPLAYER_H_
#define _SOUND_MUSICPLAYER_H_

#include <Core/IModule.h>
#include <Display/Camera.h>
#include <Sound/IMonoSound.h>
#include <Sound/ISoundSystem.h>
#include <Resources/ISoundResource.h>
#include <Resources/ResourceManager.h>
#include <vector>

namespace OpenEngine {
namespace Sound {

using OpenEngine::Core::IModule;
using OpenEngine::Display::Camera;
using namespace OpenEngine::Scene;
using namespace std;

class MusicPlayer : public IModule {

private:
	int current, nextid;
	bool first;
	Camera* cam;
	ISoundSystem* system;
	vector<IMonoSound*> backgroundlist;

public:
	MusicPlayer(Camera* inicam, ISoundSystem* system);
	~MusicPlayer();

	int AddBackGroundSound(string filename);
	void RemoveBackGroundSound(int id);
	IMonoSound* GetBackGroundSound(int id);

	void SetCurrentBackgroundSound(int id);

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