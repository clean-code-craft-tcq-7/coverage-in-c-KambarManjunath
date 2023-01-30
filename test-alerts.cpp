#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"


TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("infers the breach according to high limits") {
  REQUIRE(inferBreach(35, 7, 30) == TOO_HIGH);
}

TEST_CASE("infers the breach according to Normal ") {
  REQUIRE(inferBreach(20, 5, 40) == NORMAL);
}

TEST_CASE("Classify temperature Breach as a Passive cooling  ") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING ,-1 ) == TOO_LOW);
}

TEST_CASE("Classify temperature Breach as a HIgh active cooling  ") {
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING ,55 ) == TOO_HIGH);
}

TEST_CASE("Classify temperature Breach as a Mid active cooling  ") {
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING ,20 ) == NORMAL);
}

TEST_CASE("Check and Send Alert notification to controller ") {
	BatteryCharacter batteryChar = {PASSIVE_COOLING,"BMS"};
  REQUIRE(checkAndAlert(TO_CONTROLLER,batteryChar,30 ) == SEND_TO_CONTROLLER);
}

TEST_CASE("Check and Send Email Alert to receipt to notify Tempature Breach as a Passive cooling") {
	BatteryCharacter batteryChar = {PASSIVE_COOLING,"BMS"};
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,45) == SEND_TO_EMAIL_TOO_HIGH);
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,20 ) == SEND_TO_EMAIL_NORMAL);
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,-3) == SEND_TO_EMAIL_TOO_LOW);
}

TEST_CASE("Check and Send Email Alert to receipt to notify Tempearture breach as a Mid active cooling") {
	BatteryCharacter batteryChar = {MED_ACTIVE_COOLING,"BMS"};
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,22) == SEND_TO_EMAIL_NORMAL);
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,-2 ) == SEND_TO_EMAIL_TOO_LOW);
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,50) == SEND_TO_EMAIL_TOO_HIGH);
}

TEST_CASE("Check and Send Email Alert to receipt to notify Tempearture breach as a HIgh active cooling  ") {
	BatteryCharacter batteryChar = {HI_ACTIVE_COOLING,"BMS"};
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,25) == SEND_TO_EMAIL_NORMAL);
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar, -4 ) == SEND_TO_EMAIL_TOO_LOW);
  REQUIRE(checkAndAlert(TO_EMAIL,batteryChar,60) == SEND_TO_EMAIL_TOO_HIGH);
}

