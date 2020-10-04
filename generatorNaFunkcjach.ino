#include <eRCaGuy_Timer2_Counter.h>
#include <FreqMeasure.h>

unsigned long SzerokoscImpulsu;
unsigned long SzerokoscImpulsuWe;
unsigned long SzerokoscPauzy;
unsigned long SzerokoscPauzyWe;
byte newData = 1;
byte prevData = 1;
int Status;
int StatusWe;
unsigned long ms;
unsigned long msWe;
int ImpulsPin;
int ImpulsPinWe;
double czestotliwosc = 50;
unsigned long timeract = 0;
unsigned long timerold = 0;
unsigned long period = 4000;
double sum=0;
int count=0;











void setup() {
  timer2.setup();
  FreqMeasure.begin();
  Serial.begin(115200);
  

}

void loop() {

SzerokoscPauzyWe = map(counter(),10,10000,40000,1);
generator(13,4000,SzerokoscPauzyWe);
//Serial.println(czestotliwosc);
}





unsigned long counter(void)
    {
     
     if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 30) {
      float frequency = FreqMeasure.countToFrequency(sum / count);
      czestotliwosc = frequency;
      //Serial.println(frequency);
      sum = 0;
      count = 0;
    }
  }
        return czestotliwosc;
      
    }

void generator(int nrPin,unsigned long puls, unsigned long pauza)
    {
        ImpulsPin = nrPin;
   
   unsigned long Obecnems = timer2.get_count()/2;
          
          
          SzerokoscPauzy = pauza;

          if (pauza<=4000) puls=pauza;
          SzerokoscImpulsu = puls;
  
  
  //if (pauza<150) pauza=150; else puls.Odswiez(impuls,pauza);
  
          if((Status == HIGH) && (Obecnems - ms >= SzerokoscImpulsu))
            {
              Status = LOW;
              ms = Obecnems;
              digitalWrite(ImpulsPin,Status);
              }
              else if ((Status == LOW) && (Obecnems - ms >= SzerokoscPauzy))
                {
                  Status = HIGH;
                  ms = Obecnems;
                  digitalWrite(ImpulsPin,Status);
                  }
  
      
      }
