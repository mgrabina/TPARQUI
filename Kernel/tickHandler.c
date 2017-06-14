#include <videoDriver.h>
#include <rtc.h>
static uint8_t * const video = (uint8_t*)0xB8000;
void getTime();
void getRtcDate();

void tickHandler(){
	
	getTime();
	getRtcDate();
}
