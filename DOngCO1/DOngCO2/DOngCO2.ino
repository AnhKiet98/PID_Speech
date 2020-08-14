#include<TimerOne.h>
double T,xung2;
double tocdo2,tocdodat2, pre_tocdo2, LPF_heso=0.08;
double E2,E2_1,E2_2;
double alpha2,beta2,gama2,Kp2,Ki2,Kd2;
double Output2, LastOutput2;
void setup() {
  // put your setup code here, to run once:
  pinMode(20,INPUT_PULLUP);//chan ngat encoder
  pinMode(43,INPUT_PULLUP);//chan doc encoder
  pinMode(5,OUTPUT);//chan pwm
  pinMode(27,OUTPUT);//chan DIR1
  pinMode(29,OUTPUT);//chan DIR2
tocdodat2=-8.0,tocdo2=0.00, pre_tocdo2 = 0.0;
 E2=0; E2_1=0; E2_2=0;
 Output2=0;LastOutput2=0;
 T=0.1;
// Kp=3550.0,Kd=17.0;Ki=57.0;
//  Kp2=99;Kd2=13;Ki2=12;
  Kp2=35;Kd2=5.0;Ki2=7;
 Serial.begin(9600);
 attachInterrupt(3,Demxung2,FALLING);
 Timer1.initialize(100000);
 Timer1.attachInterrupt(PID);
}
void loop() {
  // put your main code here, to run repeatedly:
  int i;
  Serial.println(tocdo2);  
}
void Demxung2()
{
  if(digitalRead(43)==LOW)
     xung2++;
   else
     xung2--;
 }
 void PID()
 {
 // vitri=((xung*360)/1300);
 tocdo2 = (xung2/388)*(1/T)*60;
 tocdo2 = tocdo2 * LPF_heso + pre_tocdo2*(1-LPF_heso);
 pre_tocdo2 = tocdo2;
  //E=vitridat-vitri;
  xung2=0;
  E2=tocdodat2-tocdo2;
  alpha2= 2*T*Kp2 + Ki2*T*T+ 2*Kd2;
  beta2=T*T*Ki2-4*Kd2-2*T*Kp2;
  gama2=2*Kd2;
  Output2=(alpha2*E2 + beta2*E2_1 + gama2*E2_2 +2*T*LastOutput2/(2*T));
  LastOutput2=Output2;
  E2_2=E2_1;
  E2_1=E2;
  if(Output2 > 255)
     Output2=255;
  if(Output2 < -255)
     Output2=-255;
   if(Output2>0)
   {
    analogWrite(5,Output2);
    digitalWrite(27,HIGH);
    digitalWrite(29,LOW);;
    }
    else
     {
      analogWrite(5,abs(Output2));
      digitalWrite(27,LOW);
      digitalWrite(29,HIGH);
      }
  }
