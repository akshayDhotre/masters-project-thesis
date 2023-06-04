#include <stdio.h>
#include "rotaryencoder.h"
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>

#define pi 3.1418
int main()
{
printf("Hello!\n");
wiringPiSetup () ;
/*using pins 23/24*/
struct encoder *encoder = setupencoder(3,4);
long value;
while (1)
 {
 updateEncoders();
 long l = encoder->value*2*pi*4/2000;
   if(l!=value)
   {
  
	printf("Distance Travelled = %d m.m.\n", (void *)l);
     value = l;
   }

 }

return(0);
}