#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Panel.h"
#include "../GeneralInterface.h"
#include <typeinfo>

Panel p({1,1}, 10, 5, green, red);
Controller c1({0,0},4,5), c2({6,7}, 3, 2);

TEST_CASE("panel can contain variant number of controllers") {

    WHEN("components are being added") {
        p.add(c1);
        p.add(c2);

        THEN("they get the panel as their parent and the size increases accordingly") {
            REQUIRE(c1.getParent() == &p);
            REQUIRE( p.size() == 2);
        }
    }
}

TEST_CASE("panel can retreive his children") {

    REQUIRE(p.getChild(1) == &c2);
}

TEST_CASE("each of panel's children can get focus manually") {
    
    WHEN("setting focus to one of his children") {
        p.setCurrent(&c1);
    
        THEN("the subject child is currently in focus") {
            REQUIRE(p.getCurrent() == 0); // since c1 is the first child it index is 0
        }
    }
}

TEST_CASE("focus is changing iterrately") {

    WHEN("moving the focus to the next child") {
        p.nextInstance();

        THEN("next child gets the focus") {
            REQUIRE(p.getCurrent() == 1); // since the next child is c2 and it index is 1
        }
    }

    WHEN("the current child is the last and focus being moved to the next child") {
        
        if(p.getCurrent() == p.size() - 1) {
            AND_WHEN("focus being moved to the next child") {
                p.nextInstance(); 

                THEN("the focus moves to \"brother\"" ) {
                    for(int i=0; i<p.size(); i++) {
                        REQUIRE_FALSE(p.getCurrent() == i);
                    }
                }  
            }
        }
    }
}
