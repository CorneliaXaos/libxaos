/**
 *  @file Test_IEntityController.cpp
 *  @brief Tests: libxaos-game:IEntityController.h
 *
 *  Constructs several IEntity instances and controls them via testing
 *  controllers.
 */

 #include <string>

#include "IEntity.h"
#include "IEntityController.h"
#include "Vector.h"

#include "catch.hpp"

// Define a few types
using IntVector3 = libxaos::maths::Vector<int, 3>;
using Entity = libxaos::game::IEntity<int, 3>;
using IEntityController = libxaos::game::IEntityController<int, 3>;

// Create a simple controller class
// This class updates an entity to have a particular name and position.
class Controller : public IEntityController {
    public:
        Controller() : IEntityController() {}
        Controller(Entity* entPtr) : IEntityController(entPtr) {}
        ~Controller() {}
        void update() const override final {
            Entity* entity = getEntity();
            entity->setName("NAME UPDATED");
            entity->setPosition(IntVector3{1, 1, 1});
        }
};

TEST_CASE("GAME:IEntityController | Can Create Controllers", "[game]") {
    // Make some controllers.
    volatile Controller controller1 {};
    Entity ent {};
    Controller controller2 {&ent};

    REQUIRE(controller2.getEntity() == &ent);
}

TEST_CASE("GAME:IEntityController | Can Attach and Access Entity", "[game]") {
    Controller controller {};
    Entity ent {};
    controller.setEntity(&ent);

    REQUIRE(controller.getEntity() == &ent);
}

TEST_CASE("GAME:IEntityController | Can Update Attached Entity", "[game]") {
    Controller controller {};
    Entity ent {};
    controller.setEntity(&ent);
    controller.update();

    REQUIRE(ent.getName() == "NAME UPDATED");
    REQUIRE((ent.getPosition() == IntVector3{1, 1, 1}));
}
