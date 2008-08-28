#ifndef _SOUND_ITRANSITIONMODE_H_
#define _SOUND_ITRANSITIONMODE_H_

namespace OpenEngine {
    namespace Sound {
        class ISound;
    }
    namespace Utils {
        class Time;
    }
}

using OpenEngine::Utils::Time;

namespace OpenEngine {
namespace Sound {

class ITransitionMode {

public:
    virtual ~ITransitionMode() {}
    virtual void InitFade(ISound* from, ISound* to) = 0;
    virtual Time GetInTime() = 0;
    virtual Time GetOutTime() = 0;
    virtual void Process() = 0;
    virtual bool IsDone() = 0;
    virtual void Start() = 0;
};

} // NS Sound
} // NS OpenEngine

#endif
