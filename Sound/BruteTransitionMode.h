

#ifndef _SOUND_BRUTETRANSITIONMODE_H_
#define _SOUND_BRUTETRANSITIONMODE_H_

#include <Sound/ITransitionMode.h>
#include <Sound/ISound.h>

namespace OpenEngine {
namespace Sound {

class BruteTransitionMode : public ITransitionMode {

private:
	ISound* fromsound;
	ISound* tosound;
	bool done;
	float myintime;

public:
	BruteTransitionMode();
	~BruteTransitionMode();
	void initfade(ISound* from, ISound* to, float intime, float outtime);
	void process(float deltatime);
	bool isDone();
        float GetInTime();

};

} // NS Sound
} // NS OpenEngine

#endif
