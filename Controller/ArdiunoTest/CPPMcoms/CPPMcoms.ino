#include <Arduino.h>

#define minSyncLength 3000

typedef unsigned int unit16_t;
typedef unsigned char unit8_t;

unit16_t timeR;//time at rising edge
unit16_t timeF;//time at falling edge
unit16_t pulseLenght;//length of the pulse

unit8_t iChannel;//current channel

int valChannels[8];//data of all channels
 

void setup(){//set up the timer
  sei();
  TCCR1A = 0x00;
  TCCR1B = 0x02;
  TCCR1C = 0x00;
  TIMSK1 = 0x20;
  

  Serial.begin(9600);
}


ISR(TIMER1_CAPT_vect){
  cli();//disable interrupts
  //check if we're doing rising or falling check
  if(TCCR1B & (1<<ICES1)){//rising
    
    TCCR1B = (1<<ICNC1) | (0<<ICES1) | (1<<CS11);//set next interrupt as falling edge
    //setup the calculations
    timeR = ICR1;//grab rise time
  }
  else{
    TCCR1B = (1<<ICNC1) | (1<<ICES1) | (1<<CS11);//set next interrupt as rising edge
    
    //do calculations
    timeF = ICR1;//grab fall time
    pulseLenght = (timeF - timeR)/4;//calc pulse length with scaling
    //Serial.println(pulseLenght);
    //delay(20);
    if(pulseLenght > minSyncLength){//what pulse are we looking at
      iChannel = 0;//next channel we see will be channel 0
      
   }
    else{
      
      valChannels[iChannel] = (signed) pulseLenght - 551; //pass channel data to store and centre it
      iChannel++;//increase channel
      
    }
    
  }
  
  sei();//re-enable interrupts
}

void loop(){
  Serial.println(valChannels[0]);
  delay(100);
}


