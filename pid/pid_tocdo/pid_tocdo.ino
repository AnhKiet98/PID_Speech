#include<TimerOne.h>
double T,xung1,xung2;
double tocdo1,tocdodat1, pre_tocdo1,tocdo2,tocdodat2, pre_tocdo2, LPF_heso=0.08;
double E1,E1_1,E2_1,E2,E1_2,E2_2;
double alpha1,beta1,gama1,Kp1,Ki1,Kd1,alpha2,beta2,gama2,Kp2,Ki2,Kd2;
double Output1, LastOutput1,Output2, LastOutput2;
void setup() {
  // put your setup code here, to run once:
 pinMode(3,INPUT_PULLUP);//chan ngat encoder
 pinMode(8,INPUT_PULLUP);//chan doc encoder
 pinMode(6,OUTPUT);//chan pwm
 pinMode(12,OUTPUT);//chan DIR1
 pinMode(13,OUTPUT);//chan DIR2

 pinMode(2,INPUT_PULLUP);//chan ngat encoder
 pinMode(4,INPUT_PULLUP);//chan doc encoder
 pinMode(5,OUTPUT);//chan pwm
 pinMode(7,OUTPUT);//chan DIR1
 pinMode(11,OUTPUT);//chan DIR2
tocdodat1=30.0,tocdo1=0.0, pre_tocdo1 = 0.0;
tocdodat2=30.0,tocdo2=0.0, pre_tocdo2 = 0.0;
 E1=0; E1_1=0; E2_1=0;
 E2=0; E1_2=0; E2_2=0;
 Output1=0;LastOutput1=0;
 Output2=0;LastOutput2=0;
 T=0.1;
// Kp=3550.0,Kd=17.0;Ki=57.0;
  Kp1=30,5;Kd1=0.0;Ki1=0.001;
  Kp2=92,5;Kd2=0.0;Ki2=0.001;
 Serial.begin(9600);
 attachInterrupt(1,Demxung1,FALLING);
 attachInterrupt(0,Demxung2,FALLING);
 Timer1.initialize(100000);
 Timer1.attachInterrupt(PID);
}
void loop() {
  // put your main code here, to run repeatedly:
  int i;
  //Serial.println(tocdo);  
}
void Demxung1()
{
  if(digitalRead(8)==LOW)
     xung1++;
   else
     xung1--;
 }
 void Demxung2()
{
  if(digitalRead(4)==LOW)
     xung2++;
   else
     xung2--;
 }
 void PID()
 {
 // vitri=((xung*360)/1300);
 tocdo1 = (xung1/427)*(1/T)*60;
 tocdo2 = (xung2/512)*(1/T)*60;
 tocdo1 = tocdo1 * LPF_heso + pre_tocdo1*(1-LPF_heso);
 tocdo2 = tocdo2 * LPF_heso + pre_tocdo2*(1-LPF_heso);
 pre_tocdo1 = tocdo1;
 pre_tocdo2 = tocdo2;
 /**/
 xung1=0;
 E1=tocdodat1-tocdo1;
 alpha1= 2*T*Kp1 + Ki1*T*T+ 2*Kd1;
 beta1=T*T*Ki1-4*Kd1-2*T*Kp1;
 gama1=2*Kd1;
 Output1=(alpha1*E1 + beta1*E1_1 + gama1*E2_1 +2*T*LastOutput1/(2*T));
 LastOutput1=Output1;
 E2_1=E1_1;
 E1_1=E1;
/**/
 xung2=0;
 E2=tocdodat2-tocdo2;
 alpha2= 2*T*Kp2 + Ki2*T*T+ 2*Kd2;
 beta2=T*T*Ki2-4*Kd2-2*T*Kp2;
 gama2=2*Kd2;
 Output2=(alpha2*E2 + beta2*E1_2 + gama2*E2_2 +2*T*LastOutput2/(2*T));
 LastOutput2=Output2;
 E2_2=E1_2;
 E1_2=E2;
 
 if(Output1 > 255)
     Output1=255;
  if(Output1 < -255)
     Output1=-255;
     
  if(Output2 > 255)
     Output2=255;
  if(Output2 < -255)
     Output2=-255;
  if(Output1>0)
   {
    analogWrite(6,Output1);
    digitalWrite(12,LOW);
    digitalWrite(13,HIGH);;
    }
    else
     {
      analogWrite(6,abs(Output1));
      digitalWrite(12,HIGH);
      digitalWrite(13,LOW);
      }
   if(Output2>0)
   {
    analogWrite(5,Output2);
    digitalWrite(7,LOW);
    digitalWrite(11,HIGH);;
    }
    else
     {
      analogWrite(5,Output2);
      digitalWrite(7,LOW);
      digitalWrite(11,LOW);
      }
  }
