#include<TimerOne.h>
double T,xung1;
double tocdo1,tocdodat1, pre_tocdo1, LPF_heso=0.08;
double E1,E1_1,E2_1;
double alpha1,beta1,gama1,Kp1,Ki1,Kd1;
double Output1, LastOutput1;
void setup() {
  // put your setup code here, to run once:
 pinMode(20,INPUT_PULLUP);//chan ngat encoder
 pinMode(43,INPUT_PULLUP);//chan doc encoder
 pinMode(6,OUTPUT);//chan pwm
 pinMode(31,OUTPUT);//chan DIR1
 pinMode(33,OUTPUT);//chan DIR2
tocdodat1=30.0,tocdo1=0.0, pre_tocdo1 = 0.0;
 E1=0; E1_1=0; E2_1=0;
 Output1=0;LastOutput1=0;
 T=0.1;
// Kp=3550.0,Kd=17.0;Ki=57.0;
  Kp1=30,5;Kd1=0.0;Ki1=0.001;
 Serial.begin(9600);
 attachInterrupt(1,Demxung1,FALLING);
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
  if(digitalRead(43)==LOW)
     xung1++;
   else
     xung1--;
 }
 void PID()
 {
 // vitri=((xung*360)/1300);
 tocdo1 = (xung1/427)*(1/T)*60;
 tocdo1 = tocdo1 * LPF_heso + pre_tocdo1*(1-LPF_heso);
 pre_tocdo1 = tocdo1;
  //E=vitridat-vitri;
  xung1=0;
  E1=tocdodat1-tocdo1;
  alpha1= 2*T*Kp1 + Ki1*T*T+ 2*Kd1;
  beta1=T*T*Ki1-4*Kd1-2*T*Kp1;
  gama1=2*Kd1;
  Output1=(alpha1*E1 + beta1*E1_1 + gama1*E2_1 +2*T*LastOutput1/(2*T));
  LastOutput1=Output1;
  E2_1=E1_1;
  E1_1=E1;
  if(Output1 > 255)
     Output1=255;
  if(Output1 < -255)
     Output1=-255;
   if(Output1>0)
   {
    analogWrite(6,Output1);
    digitalWrite(31,LOW);
    digitalWrite(33,HIGH);
    }
    else
     {
      analogWrite(6,abs(Output1));
      digitalWrite(31,HIGH);
      digitalWrite(33,LOW);
      }
  }
