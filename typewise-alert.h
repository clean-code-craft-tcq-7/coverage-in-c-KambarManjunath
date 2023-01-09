#pragma once

#include <stdio.h>

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;


typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef enum {
	SEND_TO_CONTROLLER,
	SEND_TO_EMAIL_NORMAL,
	SEND_TO_EMAIL_TOO_LOW,
	SEND_TO_EMAIL_TOO_HIGH	
}StatusType;


typedef struct{
double lowerLimit;
double upperLimit;
CoolingType coolingType;	
}BreachLimit_t;


BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

StatusType checkAndAlert( AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

StatusType sendToController(BreachType breachType);
StatusType sendToEmail(BreachType breachType);
StatusType sendTooLowMessage(const char* recepient);
StatusType sendTooHighMessage(const char* recepient);
StatusType sendNormalMessage(const char* recepient);

