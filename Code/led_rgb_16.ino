const int ShiftPWM_latchPin=10;
const bool ShiftPWM_invertOutputs = false;
const bool ShiftPWM_balanceLoad = false;
#include <ShiftPWM.h>

//variables de la libreria ShiftPWM para controlar los colores de los led RGB
unsigned char maxBrightness = 2;
unsigned int pwmFrequency = 4800;
unsigned int numRegisters = 6;   //numero de 74hc595
unsigned int numOutputs = numRegisters*8;
unsigned int numRGBLeds = numRegisters*8/3;


#include "charts120.h"

volatile bool beginning = true;
volatile unsigned long revolution = 200000; //en microsegundos
unsigned int timeOn;
unsigned int lap = 0;
unsigned long timeBefore = 0;
unsigned long timeNow;

void setup(){
  ShiftPWM.SetAmountOfRegisters(numRegisters);  
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  delay(2500);
  attachInterrupt(0,sync,RISING);
  delay(2500);
}

void loop(){
  while (!beginning){
    timeOn = revolution/120;//128
    //timeOff = revolution/3000;//1920
    show(cOne, sizeof(cOne), 255, 0, 0); //muestra el numero uno
    space(4);
    show(cTwo, sizeof(cTwo), 0, 0, 255);
    space(5);
    show(cThree, sizeof(cThree), 0, 0, 255);
    space(5);
    show(cFour, sizeof(cFour), 0, 0, 255);
    space(7);
    show(cFive, sizeof(cFive), 0, 0, 255);
    space(7);
    show(cSix, sizeof(cSix), 0, 0, 255);
    space(7);
    show(cSeven, sizeof(cSeven), 0, 0, 255);
    space(7);
    show(cEight, sizeof(cEight), 0, 0, 255);
    space(5);
    show(cNine, sizeof(cNine), 0, 0, 255);
    space(5);
    show(cTen, sizeof(cTen), 0, 0, 255);
    space(4);
    show(cEleven, sizeof(cEleven), 0, 0, 255);
    space(4);
    show(cTwelve, sizeof(cTwelve), 0, 0, 255);
    beginning  = true;
  }
}

//lee el array con las coordenadas enciende los led RGB con el color dado
void show(bool array[], int size_t, unsigned char r,unsigned char g,unsigned char b){
  for (int i = 0; i < size_t/16; i++){
    for (int e = 0; e < 16; e++){
      if (array[i*16 + e]){ // si la coordenada indica 1 (true) enciende el led
        ShiftPWM.SetRGB(e, r, g, b);
      }
    }
    delayMicro(timeOn); //tiempo con los led encendidos
    ShiftPWM.SetAll(0);
    //delayMicro(timeOff);//tiempo con los led apagados
  }
}


void delayMicro(unsigned long mc)
{
  unsigned long start = micros();
  while (micros() - start < mc);
}


void delayMicro2(unsigned long time){
  for (unsigned int u = time/300; u > 0; u--){
    delayMicroseconds(300);
  }
  delayMicroseconds(time%300);
}

void space(unsigned int number){
  delayMicro(number*timeOn);
}

void sync(){
  beginning = true;
  timeNow = micros();
  revolution = (timeNow - timeBefore);
  timeBefore = timeNow;
  beginning = false;
}















