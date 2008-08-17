
#ifndef _SOUND_ITRANSITIONMODE_H_
#define _SOUND_ITRANSITIONMODE_H_

#include <Sound/ISound.h>

namespace OpenEngine {
namespace Sound {

class ITransitionMode {

public:
    virtual ~ITransitionMode() {}
    virtual void InitFade(ISound* from, ISound* to) = 0;
    virtual void SetInTime(float newintime) = 0;
    virtual float GetInTime() = 0;
    virtual void SetOutTime(float newouttime) = 0;
    virtual float GetOutTime() = 0;
    virtual void process(float deltatime) = 0;
    virtual bool isDone() = 0;
    virtual void Start() = 0;

};

} // NS Sound
} // NS OpenEngine

#endif
