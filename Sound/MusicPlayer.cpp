#include <Sound/MusicPlayer.h>

#include <Sound/BruteTransitionMode.h>
#include <Sound/IMonoSound.h>
#include <Sound/IStereoSound.h>
#include <typeinfo>

namespace OpenEngine {
namespace Sound {

MusicPlayer::MusicPlayer(Camera* inicam, ISoundSystem* inisystem) {
	cam = inicam;
	system = inisystem;
	current = nextTrackNumber = 0;
	random = stalled = switchToNextNumber = false;
	tran = new BruteTransitionMode(Time(0,0), Time(0,0));
    gain = 1.0;

    randGen = new RandomGenerator();
    randGen->SeedWithTime();
}

MusicPlayer::~MusicPlayer() {
    delete randGen;
}

void MusicPlayer::AddSound(string filename) {
	ISoundResourcePtr resource =
        ResourceManager<ISoundResource>::Create(filename);
	ISound* sound = system->CreateSound(resource);
    
    // @todo: ugly cast only for testing
    if (sound->IsStereoSound()) {
        IMonoSound* left = ((IStereoSound*)sound)->GetLeft();
        left->SetRelativePosition(true);
        left->SetPosition(Vector<3,float>(-10.0,0.0,0.0));
        
        IMonoSound* right = ((IStereoSound*)sound)->GetRight();
        right->SetRelativePosition(true);
        right->SetPosition(Vector<3,float>(10.0,0.0,0.0));
    }
    else if (sound->IsMonoSound()) {
        IMonoSound* mono = ((IMonoSound*)sound);
        mono->SetRelativePosition(true);
        mono->SetPosition(Vector<3,float>(0.0,0.0,0.0));
    }
    
    playlist.push_back((ISound*) sound);
    sound->SetGain(gain);

    // if we are playing the last number and insert a new
    // one, then update which number should be next
    nextTrackNumber = NextNumber();

    //@todo: set the sound to be relative to the listener i openal
}

void MusicPlayer::SetGain(float gain) {
    //@todo: is this done right? I think there is a main gain!
    // maybe check all other methods for this error!!!

    if (gain < 0) gain = 0;
    else if (gain > 1) gain = 1;
    
    for (vector<ISound*>::iterator itr = playlist.begin();
         itr != playlist.end(); itr++) {
        (*itr)->SetGain(gain);
    }

    this->gain = gain;
}

float MusicPlayer::GetGain() {
    return gain;
}


unsigned int MusicPlayer::RandomNumber() {
    unsigned int switchTo = randGen->UniformInt(0,NumberOfTracks()-1);
    if (switchTo == current && NumberOfTracks() > 1)
        return NextNumber();
    return switchTo;
}

unsigned int MusicPlayer::PreviousNumber() {
    if (current == 0) 
        return NumberOfTracks()-1;
    else
        return current-1;
}

unsigned int MusicPlayer::NextNumber() {
    unsigned int switchTo = current+1;
    return switchTo %= NumberOfTracks();
}

void MusicPlayer::Previous() { 
    if (playlist.size() == 0) return;
    if (random)
        SwitchTo(RandomNumber());
    else
        SwitchTo(PreviousNumber());
}

void MusicPlayer::Next() {
    if (playlist.size() == 0) return;
    if (random)
        SwitchTo(RandomNumber());
    else
        SwitchTo(NextNumber());
}

void MusicPlayer::SwitchTo(unsigned int trackNumber) {
    if (playlist.at(current)->IsPlaying()) {
        nextTrackNumber = trackNumber;
        switchToNextNumber = true;
    }
    else {
        current = trackNumber;
        nextTrackNumber = NextNumber();
    }
    logger.info << "Switching to song number: " << trackNumber+1;
    logger.info << " out of " << NumberOfTracks() << logger.end;
}

unsigned int MusicPlayer::NumberOfTracks() {
    return playlist.size();
}

void MusicPlayer::Play() {
    if (playlist.size() == 0) return;
    (playlist.at(current))->Play();
    stalled = false;
}

void MusicPlayer::Stop() {
    (playlist.at(current))->Stop();
    stalled = true;
}

void MusicPlayer::Pause() {
    (playlist.at(current))->Pause();
    //stalled = true;
}

void MusicPlayer::Shuffle(bool shuffle) {
    random = shuffle;
}

void MusicPlayer::SetTransitionMode(ITransitionMode* transitionMode) {
    tran = transitionMode;
}

void MusicPlayer::Handle(ProcessEventArg arg) {
    if (!playlist.empty() && !stalled) {

        ISound* currentSound = playlist.at(current);

//         logger.info << "time left: " << 
//             currentSound->GetTimeLeft().ToString() << logger.end;

        if(currentSound->GetTimeLeft() <= tran->GetInTime()) {
            if (switchToNextNumber == false) Next();
            switchToNextNumber = true;
        }

        if (switchToNextNumber) {
            tran->InitFade(currentSound,
                           playlist.at(nextTrackNumber));
            tran->Start();
            current = nextTrackNumber;
            switchToNextNumber = false;
        }

        if (!tran->IsDone()) {
            tran->Process();
        }

        /*
        Vector<3, float> pos = cam->GetPosition();

        //set the position of the current
        if (monoreftype && (typeid(*currentsound).name() ==  
                            typeid(*monoreftype).name())) {
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
        if (monoreftype && (typeid(*previoussound).name() ==
                            typeid(*monoreftype).name())) {
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
        */
    }
}

} // NS Sound
} // NS OpenEngine
