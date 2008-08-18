
#include <Sound/MusicPlayer.h>
#include <Sound/BruteTransitionMode.h>
#include <Sound/IMonoSound.h>
#include <Sound/IStereoSound.h>
#include <typeinfo>

namespace OpenEngine {
namespace Sound {

void MusicPlayer::SetGain(float gain) {
    this->gain = gain;
    if (this->gain < 0) 
        this->gain = 0;
    previous = current;
    
    for (vector<ISound*>::iterator itr = backgroundlist.begin();
         itr != backgroundlist.end();
         itr++) {
        (*itr)->SetGain(this->gain);
    }
}

float MusicPlayer::GetGain() {
    return gain;
}


void MusicPlayer::RandomNext() {
    
    previous = current;
    srand(time(NULL));
    current = (int((rand()/(float)RAND_MAX)*backgroundlist.size()));
    
    if (current == backgroundlist.size()) 
        current = 0;

    tran->InitFade(backgroundlist.at(previous), backgroundlist.at(current));
    tran->Start();    

}

MusicPlayer::MusicPlayer(Camera* inicam, ISoundSystem* inisystem) {
	cam = inicam;
	system = inisystem;
	current = 0;
	previous = 0;
	random = false;
	stopped = true;
	tran = new BruteTransitionMode(0.0, 0.0);
	mytime = new Timer();
	monoreftype = NULL;
	stereoreftype = NULL;
    gain = 1.0;
}

MusicPlayer::~MusicPlayer() {

}

void MusicPlayer::AddMonoBackGroundSound(string filename) {

	ISoundResourcePtr backsoundres = ResourceManager<ISoundResource>::Create(filename);
	monoreftype = system->CreateMonoSound(backsoundres);
	backgroundlist.push_back((ISound*) monoreftype);
    monoreftype->SetGain(gain);

}

void MusicPlayer::AddStereoBackGroundSound(string filename) {

	ISoundResourcePtr backsoundres = ResourceManager<ISoundResource>::Create(filename);
	stereoreftype = system->CreateStereoSound(backsoundres);
	backgroundlist.push_back((ISound*) stereoreftype);
    stereoreftype->SetGain(gain);
}

void MusicPlayer::RemoveBackGroundSound(int tracknumber) {

	backgroundlist.erase(backgroundlist.begin()+tracknumber,backgroundlist.begin()+tracknumber+1);

}
	
ISound* MusicPlayer::GetBackGroundSound(int tracknumber) {
	return backgroundlist.at(tracknumber);
}

void MusicPlayer::Previous() {

    previous = current;

    current--;
    if (current == -1) 
        current = (backgroundlist.size())-1;

    tran->InitFade(backgroundlist.at(previous), backgroundlist.at(current));
    tran->Start();

}

void MusicPlayer::Next() {
    if (random) {
        RandomNext();
        return;
    }

    previous = current;

    current++;
    if (current == backgroundlist.size()) 
        current = 0;

    tran->InitFade(backgroundlist.at(previous), backgroundlist.at(current));
    tran->Start();    
}

void MusicPlayer::SwitchTo(int tracknumber) {
    previous = current;
    current = tracknumber;

    tran->InitFade(backgroundlist.at(previous), backgroundlist.at(current));
    tran->Start();
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

  //TODO make this count
void MusicPlayer::Shuffle() {
    random = !random;
}

void MusicPlayer::Fade(int fromtracknumber, int totracknumber, float newintime, float newouttime) {
    tran->InitFade(backgroundlist.at(fromtracknumber), backgroundlist.at(totracknumber));
    tran->SetInTime(newintime);
    tran->SetOutTime(newouttime);
    tran->Start();
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
	ISound* previoussound = backgroundlist.at(previous);

        if (!(tran->isDone())) {
	    int curtime = (mytime->GetTime()).AsInt32();
	    tran->process(curtime-starttime);
	}
	else {

	    float timeleft = 0.0;

	    //set the timeleft right
	    if (monoreftype && (typeid(*currentsound).name() ==  typeid(*monoreftype).name())) {

	        IMonoSound* cursound = (IMonoSound*) currentsound;
		timeleft = cursound->GetTotalLength()-cursound->GetTimeOffset();
	
	    }
	    else {

	        IStereoSound* cursound = (IStereoSound*) currentsound;
		timeleft = ((cursound->GetLeft())->GetTotalLength()) - ((cursound->GetLeft())->GetTimeOffset());
		float temp = ((cursound->GetRight())->GetTotalLength()) - ((cursound->GetRight())->GetTimeOffset());

		if (temp < timeleft)
		    timeleft = temp;
	    }
	      
	    if (timeleft <= tran->GetInTime()) {

	        starttime = (mytime->GetTime()).AsInt32();

		if (random)
		  RandomNext();
		else
		  Next();
	    }

	}

	Vector<3, float> pos = cam->GetPosition();
	
	//set the position of the current
	if (monoreftype && (typeid(*currentsound).name() ==  typeid(*monoreftype).name())) {

	        IMonoSound* cursound = (IMonoSound*) currentsound;
		cursound->SetPosition(pos);
	
	}
	else {

	        IStereoSound* cursound = (IStereoSound*) currentsound;
		IMonoSound* left = cursound->GetLeft();
		IMonoSound* right = cursound->GetRight();
		pos[0] = pos[0] - 1;
		left->SetPosition(pos);
		pos[0] = pos[0] + 1;
		right->SetPosition(pos);
	}
	
	//set the position of the old if initialize
	if (monoreftype && (typeid(*previoussound).name() ==  typeid(*monoreftype).name())) {

	    IMonoSound* presound = (IMonoSound*) previoussound;
	    presound->SetPosition(pos);
	
	} 
	else {
	  
	    IStereoSound* presound = (IStereoSound*) previoussound;
	    IMonoSound* left = presound->GetLeft();
	    IMonoSound* right = presound->GetRight();
	    pos[0] = pos[0] - 1;
	    left->SetPosition(pos);
	    pos[0] = pos[0] + 1;
	    right->SetPosition(pos);
	}
	
    }
}

}
}
