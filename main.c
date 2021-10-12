#include "global.h"

//ACLK Dene timer interrup içinde

void main(void) {

    Perip_Init();
    MB_Init();
//    LED2_ON;

    while(1){

        if(IsTimeEllapsed(&MBCHECK_TimeRX, 20)){
            MB_Request_Task();

        }

        __bis_SR_register(LPM3_bits);     // Enter LPM3 mode w/ interrupts enabled


    }
}




uint8_t IsTimeEllapsed(uint32_t *LastCall,uint32_t Time){
    if(*LastCall>timeTick){
        if(((0xFFFFFFFF+timeTick)-(*LastCall))>= Time){
            (*LastCall) =timeTick;
            return 1;
        }

    }else{
        if((timeTick)-(*LastCall)>=Time){
            (*LastCall) =timeTick;
            return 1;
        }

    }
    return 0;

}



