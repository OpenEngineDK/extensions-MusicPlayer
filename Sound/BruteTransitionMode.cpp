
#include <Sound/BruteTransitionMode.h>

namespace OpenEngine {
namespace Sound {

BruteTransitionMode::BruteTransitionMode() {
}

BruteTransitionMode::~BruteTransitionMode() {
}

void BruteTransitionMode::initfade(ISound* from, ISound* to, float intime, float outtime) {
	fromsound = from;
	tosound = to;
	done = false;
}
	
void BruteTransitionMode::process(float starttime, float deltatime) {
	fromsound->Stop();
	tosound->Play();
	done = true;
}

bool BruteTransitionMode::isDone() {
	return done;
}

}
}