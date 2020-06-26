#include<TimerOne.h>
double T,xung,vong;
double vitri,vitridat;
double E,E1,E2;
double alpha,beta,gama,Kp,Ki,Kd;
double Output, LastOutput;
void setup() {
  // put your setup code here, to run once:
 pinMode(2,INPUT_PULLUP);//chan ngat encoder
 pinMode(4,INPUT_PULLUP);//chan doc encoder
 pinMode(5,OUTPUT);//chan pwm
 pinMode(7,OUTPUT);//chan DIR1
 pinMode(8,OUTPUT);//chan DIR2
vitridat=180,vitri=0;
 E=0; E1=0; E2=0;
 Output=0;LastOutput=0;
 T=0.01;
 Kp=2854.4,Kd=65;Ki=8.5;
 Serial.begin(9600);
 attachInterrupt(0,Demxung,FALLING);
 Timer1.initialize(10000);
 Timer1.attachInterrupt(PID);
}
void loop() {
  // put your main code here, to run repeatedly:
  int i;
  for(i=0;i<10;i++)
    delay(1);
  Serial.println(vitri);  
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
  vitri=((xung*360)/1300);
  E=vitridat-vitri;
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
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    }
    else if(Output<0)
    {
      analogWrite(5,abs(Output));
      digitalWrite(7,LOW);
      digitalWrite(8,HIGH);
     }
     else
     {
      analogWrite(5,0);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      }
  }
