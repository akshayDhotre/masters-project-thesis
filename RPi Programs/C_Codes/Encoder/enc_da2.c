#include <stdio.h>
#include "rotaryencoder.h"
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <math.h>

#define pi 3.1418

int i=1;
float a,b,c,d,t,v;
float D1,D2;

int main()
{
printf("Hello!\n");
wiringPiSetup () ;
struct encoder *encoder = setupencoder(0,2);
long value;
D1=0;
for(;;)
 {
 updateEncoders();
 long l = encoder->value*2*pi*4/2000;
   if(l!=value)
   {
	D2 = (encoder->value*2*pi*4/2000)+1;
	a=0;
	b=0;
	c = (D2-D1)*cos(0.349)+ a;
        d = (D2-D1)*sin(0.349)+ b;  
	t = 1; // run time in sec
        v = (D2-D1)/i;
	printf("\n ********************************************************************* \n");
	printf("\n The speed of the car is V = %f m.m./s \n",v);
	printf("\n The co-ordinates of the destination is X2 = %f \t Y2 = %f \n",c,d);
	printf("\n Distance Travelled = %d m.m.\n", (void*)l);
	delay(1000);
	D1=D2;
	i++;
     value = l;
   }

 }

return(0);
}












