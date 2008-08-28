#include <Sound/BruteTransitionMode.h>

#include <Sound/ISound.h>

#include <Utils/Timer.h>

namespace OpenEngine {
namespace Sound {

BruteTransitionMode::BruteTransitionMode(Time newintime, Time newoutime) {
    intime = newintime;
    outtime = newoutime;
    done = true;
    timer.Reset();
}

BruteTransitionMode::~BruteTransitionMode() {
}

void BruteTransitionMode::InitFade(ISound* from, ISound* to) {
	fromsound = from;
	tosound = to;
    done = false;
    timer.Reset();
}


Time BruteTransitionMode::GetInTime() {
    return intime;
}

Time BruteTransitionMode::GetOutTime() {
    return outtime;
}

void BruteTransitionMode::Process() {
    /*
    unsigned int timeToEnd =
        fromsound->GetLengthInMicroseconds() -
        fromsound->GetCurrentPositionInMicroseconds();
    */
    /*
    //fade out logic
    if (timeToEnd == 0) {
        fromsound->SetGain(0.0f);
        fromsound->Stop();
    }
    else if (timeToEnd < outtime)
        from->SetGain(timeToEnd/outtime);

    if (inStart >= 0)
        if (timeToEnd < -inStartTime) {
            tosound->Play();
        }
    else
        throw Exception("time between fade - not implemented yet");

    //fade in logic
    unsigned int runningTime =
        tosound->GetCurrentPositionInMicroseconds();
    if (runningTime < intime)
        tosound->SetGain(runningTime/intime);
    else
        tosound->SetGain(1.0f);
*/
    if (true) {//timeToEnd == 0) */{
	fromsound->Stop();
	tosound->Play();
	done = true;
  }

}

bool BruteTransitionMode::IsDone() {
	return done;
}

void BruteTransitionMode::Start() {
    timer.Reset();
    done = false;

}

}
}
