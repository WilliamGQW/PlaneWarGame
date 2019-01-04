#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ofMain.h"
#include "../src/ofApp.h"
#include "../src/ofApp.cpp"
#include <string>
#include <sstream>
using namespace std;

/**
 * Since most of my game project is related to the set up of openframework,
 * it is difficult to test with CATCH.
 * Therefore, I implemented tests for what I can test in the game.
 *
 * Below, I tested the templated toString function I created
 *
 */

SCENARIO("FIRST Test for template toString() function"){
    GIVEN("int"){
        const int score = 123456789;
        REQUIRE( toString(score) == "123456789");
    }
}


SCENARIO("SECOND Test for template toString() function"){
    GIVEN("int"){
        const int score = 1;
        REQUIRE( toString(score) == "1");
    }
}


SCENARIO("THIRD Test for template toString() function"){
    GIVEN("int"){
        const int score = 2;
        REQUIRE( toString(score) == "2");
    }
}

SCENARIO("FOURTH Test for template toString() function"){
    GIVEN("char"){
        REQUIRE( toString('8') == "8");
    }
}

}
