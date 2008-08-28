#ifndef _SOUND_BRUTETRANSITIONMODE_H_
#define _SOUND_BRUTETRANSITIONMODE_H_

#include <Sound/ITransitionMode.h>

#include <Utils/Timer.h>

namespace OpenEngine {
    namespace Sound {
        class ISound;
    }
}

using OpenEngine::Utils::Time;
using OpenEngine::Utils::Timer;

namespace OpenEngine {
namespace Sound {

class BruteTransitionMode : public ITransitionMode {

private:
	ISound* fromsound;
	ISound* tosound;
	bool done;
	Time intime, outtime;
    Timer timer;

public:
    BruteTransitionMode(Time newintime, Time newouttime);
    ~BruteTransitionMode();
    void InitFade(ISound* from, ISound* to);
    Time GetInTime();
    Time GetOutTime();
    void Process();
    bool IsDone();
    void Start();
};

} // NS Sound
} // NS OpenEngine

#endif
