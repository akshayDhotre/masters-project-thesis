//Program for parameterisation when tantheta0 not equal to tanthetaf//
//Created by Swagatu Kale & Prafulla Wange on 16/11/2014//

#include <wiringPi.h>

#include<stdio.h>
#include<math.h>

#include <stdlib.h>
#include <stdint.h>

int PWMpin= 1;
int range = 960; // value passed to pwmSetRange.
int clock = 200;   // value passed to pwmSetClock.
int x_new,i_new;

void main()
{
 	//Initializing RPI
	if (wiringPiSetup () == -1)
	exit (1) ;

	//set Pin 12 as pwm output
	pinMode (1, PWM_OUTPUT) ;
	
	pwmSetMode(PWM_MODE_MS);

	pwmSetRange(range);

	pwmSetClock(clock);


	
	//Initialising variables to calculate coefficients and tan of theta//
	float l1,l2,l3,a0,a1,a2,a3,b0,b1,b2,b3,n,theta0,thetaf,tt0,ttf,sec0;
	
	float x0,y0,xf,yf,tf,t[10000],p[100000],p1,p2,p3,x[10000],y[10000];
 	
	float xdot[5000],ydot[5000],xddot[5000],yddot[5000],xtdot[5000],ytdot[5000],pdot[10000]; 
 	
	float f0,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,phi[50000];
 
	double u1[5000],u2[5000],ud[5000];
 
	int i;
 
	double dutycycle[5000],rpm;
	int dutycycle_per[5000],phi_per[50000];

 	float rton[8]= {1450,1400,1350,1300,1250,1200,1150,1100};
 
	float ra[8]= {5,10,15,20,23,24,25,25};

 	float lton[6]= {1650,1700,1750,1800,1850,1900};

 	float la[6]={4,7,13,19,25,29};
 
	printf("\n **************************************************************************\n");
	printf("\n Input value for Simulation Time (tf):- ");
 	scanf("%f",&tf);
 	
 
	printf("\n Input initial position in X,Y format:- ");
 	scanf("%f,%f",&x0,&y0);
 
	printf("\n Input final position in X,Y format:- ");
 	scanf("%f,%f",&xf,&yf);
 
	printf("\n Input initial and final angle in theta0,thetaf format:- ");
 	scanf("%f,%f",&theta0,&thetaf);
  	
	//Calculating number of points at which u1 & u2 are to be found taking interval of 0.01//
	n=tf/0.5;
  
	t[0]=0;
  	tt0=tan(theta0);
  	ttf=tan(thetaf);
  	sec0=1/cos(theta0); 
 
	//Calculation of coefficients// 
  	l1=tt0;
  	l2=tt0*pow(sec0,3)/2;
 	l3=ttf; 
  	a0=x0;
  	a1=3*(yf-y0+ttf*x0-ttf*xf)/(tt0-ttf);
  	a2=(l2/(l3-l1)*pow(a1,2))-2*a1+3*((xf-x0)*l3-yf-y0)/(l3-l1);
  	a3=xf-x0-a1-a2;
  	b0=y0;
  	b1=l1*a1;
  	b2=l2*pow(a1,2)+l1*a2;
  	b3=yf-y0-l1*a1-b2;
  
  	for(i=1;i<=n;i++)	
  	{
   		t[i]=t[i-1]+0.5;
  		// printf("\t %f",t[i]);  
   
		//calculation of path parameter,p// 
		p1=10/pow(tf,3)*pow(t[i],3);
   		p2=15/pow(tf,4)*pow(t[i],4);
   		p3=6/pow(tf,5)*pow(t[i],5);
   		p[i]=p1-p2+p3;
   		pdot[i]=30/pow(tf,3)*pow(t[i],2)-60/pow(tf,4)*pow(t[i],3)+30/pow(tf,5)*pow(t[i],4);
  
		//calculation of derivatives of x(p) & y(p)//  
  		xdot[i]=a1+(2*a2*p[i])+(3*a3*(pow(p[i],2)));
  		ydot[i]=b1+(2*b2*p[i])+(3*b3*(pow(p[i],2)));
  		xddot[i]=(2*a2)+(6*a3*p[i]);
  		yddot[i]=(2*b2)+(6*b3*p[i]);
  		xtdot[i]=(6*a3);
  		ytdot[i]=(6*b3);
  
		//calculation of driving velocity,u1// 
  		f0=(pow(xdot[i],2)+pow(ydot[i],2));
  		u1[i]=sqrt(f0)*pdot[i];
  		//printf("%Lf",u1[i]);
  
		//calculation of steering angle,phi & steering velocity,u2//
   		f3=xdot[i]*ytdot[i]-xtdot[i]*ydot[i];
   		f4=f0*f3;
   		f5=3*(xdot[i]*yddot[i]-xddot[i]*ydot[i]);
   		f6=(xdot[i]*xddot[i]+ydot[i]*yddot[i]);
   		f7=f5*f6;
   		f8=f4-f7;
   		f10=pow(f0,3);
   		f11=xdot[i]*yddot[i]-xddot[i]*ydot[i];
   		f12=pow(f11,2);
   		f13=f10+f12;
   		f14=atan(f11/(pow(f0,1.5)));
   		phi[i]=(f14*180)/3.142857;
   
      		u2[i]=u1[i]*f8/f13*pdot[i];
   
   		//printf(" \t %Lf",u2[i]);
   		//printf("\t %f",phi[i]);
   		//printf("\n");
  	}
  

	printf("\n **************************************************************************\n");
	
	printf("\n Simulation Time is %f seconds.",tf);
	printf("\n Initial Position is (%f,%f).",x0,y0);	
	printf("\n Final Position is (%f,%f).",xf,yf);
	printf("\n Intital Angle is %f degree.",theta0);
	printf("\n Final Angle is %f degree.",thetaf);
		
  	printf("\n \n **************************************************************************\n");
	printf("\n Velocity Values \n");
	for (i=1;i<=n;i++) 
  	{  
		rpm=u1[i]*60/(3.142857*0.0627);

	   	dutycycle[i]= (0.7896*rpm+206.5);
    		
		dutycycle_per[i]=(dutycycle[i]);		
		
		pwmWrite(1,dutycycle_per[i]);
		
		delay(1000);
		
		printf("\n %d",dutycycle_per[i]);
		
  	}
	pwmWrite(1,0);
	printf("\n **************************************************************************\n");
	
	printf("\n Angle Values \n"); 
	for (i=1;i<=n;i++) 
  	{  
		if(phi[i]<0)
     			phi[i]=-0.7424*pow(phi[i],2)+8.153*phi[i]+1413;
     		else
     			phi[i]=-0.02321*pow(phi[i],2)+10.15*phi[i]+1619;

		phi_per[i]=(phi[i]/100);
	
		printf("\n %d",phi_per[i]);
  	}
	printf("\n **************************************************************************\n");
 
 
 
}
 