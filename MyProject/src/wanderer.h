#ifndef __WANDERER_AGENT__H
#define __WANDERER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class WandererController : public Process, public AgentInterface {

    public:
    WandererController() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    inline void update() { track_velocity(10, 0.15); }
    void stop() {}

};

class Wanderer : public Agent {
    public:
    Wanderer(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    WandererController c;
};

DECLARE_INTERFACE(Wanderer)

#endif