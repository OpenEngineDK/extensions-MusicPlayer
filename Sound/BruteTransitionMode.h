

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
	float intime, outtime;

public:
    BruteTransitionMode(float newintime, float newouttime);
    ~BruteTransitionMode();
    void InitFade(ISound* from, ISound* to);
    void SetInTime(float newintime);
    float GetInTime();
    void SetOutTime(float newouttime);
    float GetOutTime();
    void process(float deltatime);
    bool isDone();
    void Start();

};

} // NS Sound
} // NS OpenEngine

#endif
