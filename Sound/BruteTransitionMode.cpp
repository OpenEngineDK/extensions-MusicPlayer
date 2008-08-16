
#include <Sound/BruteTransitionMode.h>

namespace OpenEngine {
namespace Sound {

BruteTransitionMode::BruteTransitionMode() {
	done = true;
}

BruteTransitionMode::~BruteTransitionMode() {
}

void BruteTransitionMode::initfade(ISound* from, ISound* to, float intime, float outtime) {
	fromsound = from;
	tosound = to;
	done = false;
	myintime = intime;
}
	
void BruteTransitionMode::process(float deltatime) {
  if (deltatime >= myintime) {
	fromsound->Stop();
	tosound->Play();
	done = true;
  }
}

bool BruteTransitionMode::isDone() {
	return done;
}

float BruteTransitionMode::GetInTime() {

  return myintime;

}

}
}
