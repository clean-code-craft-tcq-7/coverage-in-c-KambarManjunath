#include "typewise-alert.h"



StatusType (*AlertTargetFunc[])(BreachType breachType) = { sendToController,sendToEmail };

BreachLimit_t BreachLimit_Arr[3] = { {0,35,PASSIVE_COOLING},
				     {0,45,HI_ACTIVE_COOLING}, 
				     {0,40,MED_ACTIVE_COOLING} };

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if( value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
 	return inferBreach(temperatureInC, BreachLimit_Arr[coolingType].lowerLimit, BreachLimit_Arr[coolingType].upperLimit);
}

StatusType checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC)
 {
	BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
	StatusType checkAndAlertWrapper = (*AlertTargetFunc[alertTarget])(breachType);
	return checkAndAlertWrapper;
}

StatusType sendToController(BreachType breachType)
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  return SEND_TO_CONTROLLER;
}

