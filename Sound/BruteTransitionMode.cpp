
#include <Sound/BruteTransitionMode.h>

namespace OpenEngine {
namespace Sound {

BruteTransitionMode::BruteTransitionMode(float newintime, float newoutime) {
    intime = newintime;
    outtime = newoutime;
    done = true;
}

BruteTransitionMode::~BruteTransitionMode() {
}

void BruteTransitionMode::InitFade(ISound* from, ISound* to) {
	fromsound = from;
	tosound = to;
}

void BruteTransitionMode::SetInTime(float newintime) {
    intime = newintime;
}

float BruteTransitionMode::GetInTime() {
    return intime;
}

void BruteTransitionMode::SetOutTime(float newouttime) {
    outtime = newouttime;
}
	
float BruteTransitionMode::GetOutTime() {
    return outtime;
}

void BruteTransitionMode::process(float deltatime) {
  if (deltatime >= intime) {
	fromsound->Stop();
	tosound->Play();
	done = true;
  }

}

bool BruteTransitionMode::isDone() {
	return done;
}

void BruteTransitionMode::Start() {
  
    done = false;

}

}
}
