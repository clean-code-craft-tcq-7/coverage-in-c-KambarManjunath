#include "typewise-alert.h"


/***************************************************EmailMsgHandler.c *************************************************/
StatusType (*EmailMesssage[])(const char* recepient) = { sendNormalMessage, sendTooLowMessage , sendTooHighMessage };


StatusType sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  StatusType EmailMesssageNotify = (*EmailMesssage[breachType])(recepient);
	  return EmailMesssageNotify;

}

StatusType sendNormalMessage(const char* recepient)
{
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is Normal\n");
	  return SEND_TO_EMAIL_NORMAL;
}

StatusType sendTooLowMessage(const char* recepient)
{
	  printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
	  return SEND_TO_EMAIL_TOO_LOW;

}

StatusType sendTooHighMessage(const char* recepient)
{
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
	  return SEND_TO_EMAIL_TOO_HIGH;
}


