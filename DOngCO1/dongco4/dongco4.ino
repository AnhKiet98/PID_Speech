#include<TimerOne.h>
double T,xung4;
double tocdo4,tocdodat4, pre_tocdo4, LPF_heso=0.08;
double E4,E4_1,E4_2;
double alpha4,beta4,gama4,Kp4,Ki4,Kd4;
double Output4, LastOutput4;
void setup() {
  // put your setup code here, to run once:
  pinMode(3,INPUT_PULLUP);//chan ngat encoder
  pinMode(41,INPUT_PULLUP);//chan doc encoder
  pinMode(7,OUTPUT);//chan pwm
  pinMode(35,OUTPUT);//chan DIR1
  pinMode(37,OUTPUT);//chan DIR2
tocdodat4=30.0,tocdo4=0.00, pre_tocdo4 = 0.0;
 E4=0; E4_1=0; E4_2=0;
 Output4=0;LastOutput4=0;
 T=0.1;
// Kp=3550.0,Kd=17.0;Ki=57.0;
//  Kp2=99;Kd2=13;Ki2=12;
Kp4=52.0;Kd4=10;Ki4=16;
 Serial.begin(9600);
 attachInterrupt(1,Demxung4,FALLING);
 Timer1.initialize(100000);
 Timer1.attachInterrupt(PID);
}
void loop() {
  // put your main code here, to run repeatedly:
  int i;
  Serial.println(tocdo4);  
}
void Demxung4()
{
  if(digitalRead(41)==HIGH)
     xung4++;
   else
     xung4--;
 }
 void PID()
 {
 // vitri=((xung*360)/1300);
 tocdo4 = (xung4/628)*(1/T)*60;
 tocdo4 = tocdo4 * LPF_heso + pre_tocdo4*(1-LPF_heso);
 pre_tocdo4 = tocdo4;
  //E=vitridat-vitri;
  xung4=0;
  E4=tocdodat4-tocdo4;
  alpha4= 2*T*Kp4 + Ki4*T*T+ 2*Kd4;
  beta4=T*T*Ki4-4*Kd4-2*T*Kp4;
  gama4=2*Kd4;
  Output4=(alpha4*E4 + beta4*E4_1 + gama4*E4_2 +2*T*LastOutput4/(2*T));
  LastOutput4=Output4;
  E4_2=E4_1;
  E4_1=E4;
  if(Output4 > 255)
     Output4=255;
  if(Output4 < -255)
     Output4=-255;
   if(Output4>0)
   {
    analogWrite(7,Output4);
    digitalWrite(35,LOW);
    digitalWrite(37,HIGH);;
    }
    else
     {
      analogWrite(7,abs(Output4));
      digitalWrite(35,HIGH);
      digitalWrite(37,LOW);
      }
  }
