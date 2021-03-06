#include<TimerOne.h>
double T,xung1;
double tocdo1,tocdodat1, pre_tocdo1, LPF_heso=0.08;
double E1,E1_1,E1_2;
double alpha1,beta1,gama1,Kp1,Ki1,Kd1;
double Output1, LastOutput1;
void setup() {
  // put your setup code here, to run once:
  pinMode(21,INPUT_PULLUP);//chan ngat encoder
  pinMode(45,INPUT_PULLUP);//chan doc encoder
  pinMode(4,OUTPUT);//chan pwm
  pinMode(23,OUTPUT);//chan DIR1
  pinMode(25,OUTPUT);//chan DIR2
tocdodat1=30.0,tocdo1=0.00, pre_tocdo1 = 0.0;
 E1=0; E1_1=0; E1_2=0;
 Output1=0;LastOutput1=0;
 T=0.1;
// Kp=3550.0,Kd=17.0;Ki=57.0;
  Kp1=99;Kd1=14;Ki1=16;
 Serial.begin(9600);
 attachInterrupt(2,Demxung1,FALLING);
 Timer1.initialize(100000);
 Timer1.attachInterrupt(PID);
}
void loop() {
  // put your main code here, to run repeatedly:
  int i;
  Serial.println(tocdo1);  
}
void Demxung1()
{
  if(digitalRead(45)==HIGH)
     xung1++;
   else
     xung1--;
 }
 void PID()
 {
 // vitri=((xung*360)/1300);
 tocdo1 = (xung1/628)*(1/T)*60;
 tocdo1 = tocdo1 * LPF_heso + pre_tocdo1*(1-LPF_heso);
 pre_tocdo1 = tocdo1;
  //E=vitridat-vitri;
  xung1=0;
  E1=tocdodat1-tocdo1;
  alpha1= 2*T*Kp1 + Ki1*T*T+ 2*Kd1;
  beta1=T*T*Ki1-4*Kd1-2*T*Kp1;
  gama1=2*Kd1;
  Output1=(alpha1*E1 + beta1*E1_1 + gama1*E1_2 +2*T*LastOutput1/(2*T));
  LastOutput1=Output1;
  E1_2=E1_1;
  E1_1=E1;
  if(Output1 > 255)
     Output1=255;
  if(Output1 < -255)
     Output1=-255;
   if(Output1>0)
   {
    analogWrite(4,Output1);
    digitalWrite(23,LOW);
    digitalWrite(25,HIGH);;
    }
    else
     {
      analogWrite(4,abs(Output1));
      digitalWrite(23,HIGH);
      digitalWrite(25,LOW);
      }
  }
