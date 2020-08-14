#include<TimerOne.h>
double T,xung3;
double tocdo3,tocdodat3, pre_tocdo3, LPF_heso=0.08;
double E3,E3_1,E3_2;
double alpha3,beta3,gama3,Kp3,Ki3,Kd3;
double Output3, LastOutput3;
void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT_PULLUP);//chan ngat encoder
  pinMode(39,INPUT_PULLUP);//chan doc encoder
  pinMode(6,OUTPUT);//chan pwm
  pinMode(31,OUTPUT);//chan DIR1
  pinMode(33,OUTPUT);//chan DIR2
tocdodat3=30.0,tocdo3=0.00, pre_tocdo3 = 0.0;
 E3=0; E3_1=0; E3_2=0;
 Output3=0;LastOutput3=0;
 T=0.1;
// Kp=3550.0,Kd=17.0;Ki=57.0;
//  Kp2=99;Kd2=13;Ki2=12;
//Kp2=76;Kd2=9.4;Ki2=15;
Kp3=75;Kd3=7;Ki3=17;
 Serial.begin(9600);
 attachInterrupt(0,Demxung3,FALLING);
 Timer1.initialize(100000);
 Timer1.attachInterrupt(PID);
}
void loop() {
  // put your main code here, to run repeatedly:
  int i;
  Serial.println(tocdo3);  
}
void Demxung3()
{
  if(digitalRead(39)==LOW)
     xung3++;
   else
     xung3--;
 }
 void PID()
 {
 // vitri=((xung*360)/1300);
 tocdo3 = (xung3/628)*(1/T)*60;
 tocdo3 = tocdo3 * LPF_heso + pre_tocdo3*(1-LPF_heso);
 pre_tocdo3 = tocdo3;
  //E=vitridat-vitri;
  xung3=0;
  E3=tocdodat3-tocdo3;
  alpha3= 2*T*Kp3 + Ki3*T*T+ 2*Kd3;
  beta3=T*T*Ki3-4*Kd3-2*T*Kp3;
  gama3=2*Kd3;
  Output3=(alpha3*E3 + beta3*E3_1 + gama3*E3_2 +2*T*LastOutput3/(2*T));
  LastOutput3=Output3;
  E3_2=E3_1;
  E3_1=E3;
  if(Output3 > 255)
     Output3=255;
  if(Output3 < -255)
     Output3=-255;
   if(Output3>0)
   {
    analogWrite(6,Output3);
    digitalWrite(31,LOW);
    digitalWrite(33,HIGH);;
    }
    else
     {
      analogWrite(5,abs(Output3));
      digitalWrite(31,HIGH);
      digitalWrite(33,LOW);
      }
  }
