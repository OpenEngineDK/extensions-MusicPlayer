
#ifndef _SOUND_ITRANSITIONMODE_H_
#define _SOUND_ITRANSITIONMODE_H_

#include <Sound/ISound.h>

namespace OpenEngine {
namespace Sound {

class ITransitionMode {

public:
	virtual ~ITransitionMode() {}
	virtual void initfade(ISound* from, ISound* to, float intime, float outtime) = 0;
	virtual void process(float deltatime) = 0;
	virtual bool isDone() = 0;
	virtual float GetInTime() = 0;
};

} // NS Sound
} // NS OpenEngine

#endif
