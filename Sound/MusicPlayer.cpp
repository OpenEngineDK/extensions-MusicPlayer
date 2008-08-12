
#include <Sound/MusicPlayer.h>

namespace OpenEngine {
namespace Sound {

MusicPlayer::MusicPlayer(Camera* inicam, ISoundSystem* inisystem) {
	cam = inicam;
	system = inisystem;
	current = 0;
	nextid = -1;
	first = true;
}

MusicPlayer::~MusicPlayer() {

}

IMonoSound* MusicPlayer::GetBackGroundSound(int id) {
	return backgroundlist.at(id);
}

void MusicPlayer::SetCurrentBackgroundSound(int id) {
	current = id;
}

int MusicPlayer::AddBackGroundSound(string filename) {

	ISoundResourcePtr backsoundres = ResourceManager<ISoundResource>::Create(filename);
	IMonoSound* backsound = system->CreateMonoSound(backsoundres);
	backgroundlist.push_back(backsound);
	nextid++;
	return nextid;

}

void MusicPlayer::RemoveBackGroundSound(int id) {

	backgroundlist.erase(backgroundlist.begin()+id,backgroundlist.begin()+id+1);

}

void MusicPlayer::Initialize() {

}

void MusicPlayer::Deinitialize() {

}

void MusicPlayer::Process(const float deltaTime, const float percent) {

	if (!backgroundlist.empty()) {

		IMonoSound* currentsound = backgroundlist.at(current);
		
		if (first) {

			first = false;
			currentsound->Play();

		}
		else if (currentsound->GetPlaybackState() == ISound::STOPPED) {
	
			current++;
			if (current == backgroundlist.size())
				current = 0;
			currentsound = backgroundlist.at(current);
			currentsound->Play();

		}

		Vector<3, float> pos = cam->GetPosition();
		currentsound->SetPosition(pos);

	}

}

}
}