
#include <Sound/MusicPlayer.h>
#include <Sound/BruteTransitionMode.h>
#include <Sound/IMonoSound.h>

namespace OpenEngine {
namespace Sound {

MusicPlayer::MusicPlayer(Camera* inicam, ISoundSystem* inisystem) {
	cam = inicam;
	system = inisystem;
	current = 0;
	random = false;
	stopped = true;
	tran = new BruteTransitionMode();
}

MusicPlayer::~MusicPlayer() {

}

void MusicPlayer::AddMonoBackGroundSound(string filename) {

	ISoundResourcePtr backsoundres = ResourceManager<ISoundResource>::Create(filename);
	ISound* backsound = (ISound*) system->CreateMonoSound(backsoundres);
	backgroundlist.push_back(backsound);

}

void MusicPlayer::AddStereoBackGroundSound(string filename) {

	ISoundResourcePtr backsoundres = ResourceManager<ISoundResource>::Create(filename);
	ISound* backsound = (ISound*) system->CreateStereoSound(backsoundres);
	backgroundlist.push_back(backsound);

}

void MusicPlayer::RemoveBackGroundSound(int tracknumber) {

	backgroundlist.erase(backgroundlist.begin()+tracknumber,backgroundlist.begin()+tracknumber+1);

}
	
ISound* MusicPlayer::GetBackGroundSound(int tracknumber) {
	return backgroundlist.at(tracknumber);
}

void MusicPlayer::Next() {

}

void MusicPlayer::SwitchTo(int tracknumber) {

}

void MusicPlayer::Play() {
	(backgroundlist.at(current))->Play();
	stopped = false;
}

void MusicPlayer::Stop() {
	(backgroundlist.at(current))->Stop();
	stopped = true;
}

void MusicPlayer::Pause() {
	(backgroundlist.at(current))->Pause();
}

void MusicPlayer::Suffle() {
	random = !random;
}

void MusicPlayer::Fade(int fromtracknumber, int totracknumber, float intime, float outtime) {
        
}

void MusicPlayer::SetTransitionMode(ITransitionMode* newtran) {
	tran = newtran;
}

ITransitionMode* MusicPlayer::GetTransitionMode() {
	return tran;
}

void MusicPlayer::Handle(ProcessEventArg arg) {

	if (!backgroundlist.empty() || stopped) {

		ISound* currentsound = backgroundlist.at(current);		
		
		if (!(tran->isDone())) {
		  int curtime = (mytime.GetTime()).AsInt();
		  tran->process(curtime-starttime);
		}
		else {

		  if (typeid(currentsound) == typeid(IMonoSound)) {

		    IMonoSound* cursound = (IMonoSound*) currentsound;

		    //		    if (cursound)

		  }

		}



		/*		else if (currentsound->GetPlaybackState() == ISound::STOPPED) {
	
			current++;
			if (current == backgroundlist.size())
				current = 0;
			currentsound = backgroundlist.at(current);
			currentsound->Play();

		}

		Vector<3, float> pos = cam->GetPosition();
		currentsound->SetPosition(pos);*/

	}

}

}
}
