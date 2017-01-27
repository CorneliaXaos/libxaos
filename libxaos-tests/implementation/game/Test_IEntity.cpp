/**
 *  @file Test_IEntity.cpp
 *  @brief Tests: libxaos-game:IEntity.h
 *
 *  Constructs an IEntity object (generic) and tests its functions.
 */

 #include <string>

 #include "IEntity.h"
 #include "Vector.h"

 #include "catch.hpp"

 // Define a few types
 using IntVector3 = libxaos::maths::Vector<int, 3>;
 using FloatVector4 = libxaos::maths::Vector<float, 4>;

 using ThreeDEntity = libxaos::game::IEntity<int, 3>;
 using FourDEntity = libxaos::game::IEntity<float, 4>;

 TEST_CASE("GAME:IEntity | Can Create Entities", "[game]") {
    // Make some entities.
    ThreeDEntity ent1 {};
    ThreeDEntity ent2 {"I AM ENTITY"};
    ThreeDEntity ent3 {IntVector3{1, 1, 1}};
    FourDEntity ent4 {"I AM DIFFERENT ENTITY",
            FloatVector4{0.5F, 1.0F, 1.5F, 2.0F}};

    REQUIRE(ent1.getName() == "");
    REQUIRE(ent1.getPosition() == IntVector3{});
    REQUIRE(ent2.getName() == "I AM ENTITY");
    REQUIRE((ent3.getPosition() == IntVector3{1, 1, 1}));
    REQUIRE(ent4.getName() == "I AM DIFFERENT ENTITY");
    REQUIRE((ent4.getPosition() == FloatVector4{0.5F, 1.0F, 1.5F, 2.0F}));
 }

 TEST_CASE("GAME:IEntity | Can Access / Modify Entity Name", "[game]") {
    ThreeDEntity ent {};
    ent.setName("HIYA");

    REQUIRE(ent.getName() == "HIYA");
 }

 TEST_CASE("GAME:IEntity | Can Access / Modify Entity Position", "[game]") {
    ThreeDEntity ent {};
    ent.setPosition(IntVector3{1, 2, 3});

    REQUIRE((ent.getPosition() == IntVector3{1, 2, 3}));
 }

 TEST_CASE("GAME:IEntity | Entity (In)Equality", "[game]") {
    ThreeDEntity ent {"SAME NAME"};
    ThreeDEntity otherEnt {"SAME NAME"}; // implicitly same position
    ThreeDEntity anotherEnt = otherEnt; // COPIES AREN'T THE SAME ENTITY

    REQUIRE(ent != otherEnt);
    REQUIRE(otherEnt != anotherEnt);
 }
