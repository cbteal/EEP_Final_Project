#ifndef __FINISH__AGENT_H
#define __FINISH__AGENT_H

#include "enviro.h"

using namespace enviro;

class FinishController : public Process, public AgentInterface {

public:
    FinishController() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    inline void update() { }
    void stop() {}

};

class Finish : public Agent {
public:
    Finish(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
private:
    FinishController c;
};

DECLARE_INTERFACE(Finish)

#endif