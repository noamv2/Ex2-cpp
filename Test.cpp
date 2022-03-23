#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"





TEST_CASE("Invalid arguments"){
    
    ariel::Notebook nb;

    SUBCASE("Negitive page values"){
    

    CHECK_THROWS(nb.write(-5, 2, 7, ariel::Direction::Horizontal, "12345"));
    CHECK_THROWS(nb.write(-1, 8, 5, ariel::Direction::Horizontal, "hello there"));
    CHECK_THROWS(nb.write(-12, 3, 2, ariel::Direction::Horizontal, "hello world"));


  }

  SUBCASE("Negetive ols and rows values"){
    CHECK_THROWS(nb.write(5, -2, 7, ariel::Direction::Horizontal, "12345"));
    CHECK_THROWS(nb.write(1, 8, -5, ariel::Direction::Horizontal, "hello there"));
    CHECK_THROWS(nb.write(12, -3, -2, ariel::Direction::Horizontal, "hello there"));
  }
}

TEST_CASE("Crossing notebook's edges"){
    ariel::Notebook nb;
    SUBCASE("String larger then a whole row"){
    
    CHECK_THROWS(nb.write(1, 0, 0, ariel::Direction::Horizontal,  "12345678901234567890"
                                                                  "12345678901234567890"
                                                                  "12345678901234567890"
                                                                  "12345678901234567890"
                                                                  "12345678901234567890"
                                                                  "12345678901234567890"));

    CHECK_THROWS(nb.write(12, 3, 2, ariel::Direction::Horizontal, "hello noam asfdadffdasfadfasdfad"
                                                                  "hello noam asfdadffdasfadfasdfad"
                                                                  "hello noam asfdadffdasfadfasdfad"
                                                                  "hello noam asfdadffdasfadfasdfad"
                                                                  "hello noam asfdadffdasfadfasdfad"));

  }

  SUBCASE("String smaller then 100 but cross the edges"){
    //write
    CHECK_THROWS(nb.write(5, 2, 99, ariel::Direction::Horizontal, "12345"));
    CHECK_THROWS(nb.write(1, 8, 92, ariel::Direction::Horizontal, "hello world"));
    CHECK_THROWS(nb.write(12, 1, 94, ariel::Direction::Horizontal, "hello world"));
    //read
    CHECK_THROWS(nb.read(5, 2, 99, ariel::Direction::Horizontal,3));
    CHECK_THROWS(nb.read(1, 8, 92, ariel::Direction::Horizontal, 22));
    CHECK_THROWS(nb.read(12, 1, 11, ariel::Direction::Horizontal, 10));
    //erase
    CHECK_THROWS(nb.erase(12, 1, 11, ariel::Direction::Horizontal, 110));
  }
}


TEST_CASE("legal cases"){
    ariel::Notebook nb;
    
    nb.write(5, 2, 0, ariel::Direction::Horizontal, "12345");
    nb.write(5, 2, 5, ariel::Direction::Horizontal, "abcde");
    CHECK("12345abcde" == nb.read(5,2,0, ariel::Direction::Horizontal, 10));


    nb.erase(5, 2, 0, ariel::Direction::Horizontal, 3);
    CHECK("~~~45abcde" == nb.read(5,2,0, ariel::Direction::Horizontal, 10));

    nb.erase(5, 2, 5, ariel::Direction::Horizontal, 3);
    CHECK("~~~45~~~de" == nb.read(5,2,0, ariel::Direction::Horizontal, 10));

    nb.write(0, 0, 0, ariel::Direction::Vertical, "1234567890");
    CHECK("1234567890" == nb.read(0,0,0, ariel::Direction::Vertical, 10));

    nb.erase(0, 0, 0, ariel::Direction::Vertical, 23);

    nb.write(1, 0, 0, ariel::Direction::Horizontal, "1234567890");
    nb.erase(1, 0, 0, ariel::Direction::Vertical, 23);
    CHECK("~234567890" == nb.read(1,0,0, ariel::Direction::Horizontal, 10));

}



  