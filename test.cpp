#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#include "Xml.h"
#include <iostream>

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

//TEST_CASE( "Factorials are computed", "[factorial]" ) {
//    REQUIRE( Factorial(1) == 1 );
//    REQUIRE( Factorial(2) == 2 );
//    REQUIRE( Factorial(3) == 6 );
//    REQUIRE( Factorial(10) == 3628800 );
//}


using namespace eng;
TEST_CASE("XML TEST","[xml]")
{
    Xml file;
    REQUIRE(file.init("testfiles/test1.xml") == true);
    SECTION("checking rootElemt function")
    {
        //TinyXml version
        XMLElement* tinyElem = file.rootElement().getXMLElement();
        //My version
        XmlElement myElem = file.rootElement();
        REQUIRE(tinyElem->Name() == myElem.getElemName());

    }

    SECTION("checking firstChild function without an elem. name")
    {
        //TinyXml version
        XMLElement* tinyElem = file.rootElement().getXMLElement()->FirstChildElement();
        //My version
        XmlElement myElem = file.rootElement().firstChildElement();
        //resX == resX?
        REQUIRE(tinyElem->Name() == myElem.getElemName());

        SECTION("checking that the elem. values are the same")
        {
            int value;
            tinyElem->QueryIntText(&value);
            //1920 == 1920?
            REQUIRE(value == std::stoi(myElem.getValue()));
        }

    }

    SECTION("checking firstChild function with an elem. name")
    {
        //TinyXml version
        XMLElement* tinyElem = file.rootElement().getXMLElement()->FirstChildElement("fullscreen");
        //My version
        XmlElement myElem = file.rootElement().firstChildElement("fullscreen");
        //fullscreen == fullscreen?
        REQUIRE(tinyElem->Name() == myElem.getElemName());
    }

    SECTION("Test to brake Travis CI")
    {
        REQUIRE(1 == 2);
    }


}
