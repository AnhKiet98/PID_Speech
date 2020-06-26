#include<TimerOne.h>
double T,xung;
double tocdo,tocdodat, pre_tocdo, LPF_heso=0.08;
double E,E1,E2;
double alpha,beta,gama,Kp,Ki,Kd;
double Output, LastOutput;
void setup() {
  // put your setup code here, to run once:
 pinMode(2,INPUT_PULLUP);//chan ngat encoder
 pinMode(4,INPUT_PULLUP);//chan doc encoder
 pinMode(5,OUTPUT);//chan pwm
 pinMode(6,OUTPUT);//chan DIR1
tocdodat=10.0,tocdo=0.0, pre_tocdo = 0.0;
 E=0; E1=0; E2=0;
 Output=0;LastOutput=0;
 T=0.3;
// Kp=3550.0,Kd=17.0;Ki=57.0;
  Kp=85.5,Kd=0.0;Ki=0.000;
 Serial.begin(9600);
 attachInterrupt(0,Demxung,FALLING);
 Timer1.initialize(300000);
 Timer1.attachInterrupt(PID);
}
void loop() {
  // put your main code here, to run repeatedly:
  int i;
  Serial.println(tocdo);  
}
void Demxung()
{
  if(digitalRead(4)==LOW)
     xung++;
   else
     xung--;
 }
 void PID()
 {
 // vitri=((xung*360)/1300);
 tocdo = (xung/512)*(1/T)*60;
 tocdo = tocdo * LPF_heso + pre_tocdo*(1-LPF_heso);
 pre_tocdo = tocdo;
  //E=vitridat-vitri;
  xung=0;
  E=tocdodat-tocdo;
  alpha= 2*T*Kp + Ki*T*T+ 2*Kd;
  beta=T*T*Ki-4*Kd-2*T*Kp;
  gama=2*Kd;
  Output=(alpha*E + beta*E1 + gama*E2 +2*T*LastOutput/(2*T));
  LastOutput=Output;
  E2=E1;
  E1=E;
  if(Output > 255)
     Output=255;
  if(Output < -255)
     Output=-255;
   if(Output>0)
   {
    analogWrite(5,Output);
    analogWrite(6,0);
    }
    else
     {
      analogWrite(5,0);
      analogWrite(6,abs(Output));
      }
  }
