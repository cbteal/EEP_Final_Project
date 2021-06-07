#ifndef __COORDINATOR_AGENT__H
#define __COORDINATOR_AGENT__H 

#include "enviro.h"
#include "mazegenerator.h"
#include <time.h>

using namespace enviro;

class CoordinatorController : public Process, public AgentInterface {

public:
    CoordinatorController() : Process(), AgentInterface() {}

    void init() {
        

        
        MazeGenerator m = MazeGenerator();
        auto start = std::make_pair(0.0, 0.0);
        m.generate_maze(start);
        auto v = m.visited();

        for (auto iter : v) {
            add_agent("Block", iter.first, iter.second, 0, { {"fill", "blue"} });
        }


    }
    void start() {}
    void update() {}
    void stop() {}

};

class Coordinator : public Agent {
public:
    Coordinator(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
private:
    CoordinatorController c;
};

DECLARE_INTERFACE(Coordinator)

#endif