#include<TimerOne.h>
#define WHEEL_RADIUS 0.1             // 휠 반경 [ m ]
#define WHEEL_SEPARATION_WIDTH 0.32   // 휠 베이스간 전폭 [ m ]
#define WHEEL_SEPARATION_LENGTH 0.30  // 휠 베이스간 전장 [ m ]
#define radtorpm 9.5

double Tar_wheel_front_left, Tar_wheel_front_right, Tar_wheel_rear_left, Tar_wheel_rear_right; //구동 모터별 변수 설정
//dongco1
double T,xung1;
double tocdo1,tocdodat1, pre_tocdo1, LPF_heso=0.08;
double E1,E1_1,E1_2;
double alpha1,beta1,gama1,Kp1,Ki1,Kd1;
double Output1, LastOutput1;

//dongco2
double xung2;
double tocdo2,tocdodat2, pre_tocdo2;
double E2,E2_1,E2_2;
double alpha2,beta2,gama2,Kp2,Ki2,Kd2;
double Output2, LastOutput2;

//dongco3
double xung3;
double tocdo3,tocdodat3, pre_tocdo3;
double E3,E3_1,E3_2;
double alpha3,beta3,gama3,Kp3,Ki3,Kd3;
double Output3, LastOutput3;


//dongco4
double xung4;
double tocdo4,tocdodat4, pre_tocdo4;
double E4,E4_1,E4_2;
double alpha4,beta4,gama4,Kp4,Ki4,Kd4;
double Output4, LastOutput4;

void setup() {
const float Tar_linear_x =0;
const float Tar_linear_y =0;
const float Tar_angular_z =0;
Tar_wheel_front_left=(1/WHEEL_RADIUS) * (Tar_linear_x - Tar_linear_y - (WHEEL_SEPARATION_WIDTH + WHEEL_SEPARATION_LENGTH)*Tar_angular_z)*radtorpm;  //Tar_wheel_front_left값 계산 수식
Tar_wheel_front_right = (1/WHEEL_RADIUS) * (Tar_linear_x + Tar_linear_y + (WHEEL_SEPARATION_WIDTH + WHEEL_SEPARATION_LENGTH)*Tar_angular_z)*radtorpm; //Tar_wheel_front_right값 계산 수식
Tar_wheel_rear_left = (1/WHEEL_RADIUS) * (Tar_linear_x + Tar_linear_y - (WHEEL_SEPARATION_WIDTH + WHEEL_SEPARATION_LENGTH)*Tar_angular_z)*radtorpm;   //Tar_wheel_rear_left값 계산 수식
Tar_wheel_rear_right = (1/WHEEL_RADIUS) * (Tar_linear_x - Tar_linear_y + (WHEEL_SEPARATION_WIDTH + WHEEL_SEPARATION_LENGTH)*Tar_angular_z)*radtorpm;  //Tar_wheel_rear_right값 계산 수식
  // put your setup code here, to run once:
  //dong co 1
  pinMode(21,INPUT_PULLUP);//chan ngat encoder
  pinMode(45,INPUT_PULLUP);//chan doc encoder
  pinMode(4,OUTPUT);//chan pwm
  pinMode(23,OUTPUT);//chan DIR1
  pinMode(25,OUTPUT);//chan DIR2
  tocdodat1=(Tar_wheel_front_left),tocdo1=0.00, pre_tocdo1 = 0.0;
  E1=0; E1_1=0; E1_2=0;
  Output1=0;LastOutput1=0;
  T=0.1;
  Kp1=99;Kd1=14;Ki1=16;

  //dongco 2
  pinMode(20,INPUT_PULLUP);//chan ngat encoder
  pinMode(43,INPUT_PULLUP);//chan doc encoder
  pinMode(5,OUTPUT);//chan pwm
  pinMode(27,OUTPUT);//chan DIR1
  pinMode(29,OUTPUT);//chan DIR2
  tocdodat2=(Tar_wheel_front_right),tocdo2=0.00, pre_tocdo2 = 0.0;
  E2=0; E2_1=0; E2_2=0;
  Output2=0;LastOutput2=0;
  Kp2=35;Kd2=5.0;Ki2=7;

  //dong co 3
  pinMode(2,INPUT_PULLUP);//chan ngat encoder
  pinMode(39,INPUT_PULLUP);//chan doc encoder
  pinMode(6,OUTPUT);//chan pwm
  pinMode(31,OUTPUT);//chan DIR1
  pinMode(33,OUTPUT);//chan DIR2
  tocdodat3=(Tar_wheel_rear_left),tocdo3=0.00, pre_tocdo3 = 0.0;
  E3=0; E3_1=0; E3_2=0;
  Output3=0;LastOutput3=0;
  Kp3=75;Kd3=7;Ki3=17;


  //dong co 4
  pinMode(3,INPUT_PULLUP);//chan ngat encoder
  pinMode(41,INPUT_PULLUP);//chan doc encoder
  pinMode(7,OUTPUT);//chan pwm
  pinMode(35,OUTPUT);//chan DIR1
  pinMode(37,OUTPUT);//chan DIR2
  tocdodat4=(Tar_wheel_rear_right),tocdo4=0.00, pre_tocdo4 = 0.0;
  E4=0; E4_1=0; E4_2=0;
  Output4=0;LastOutput4=0;
  Kp4=52.0;Kd4=10;Ki4=16;
  
 Serial.begin(9600);
 attachInterrupt(0,Demxung3,FALLING);
 attachInterrupt(1,Demxung4,FALLING);
 attachInterrupt(2,Demxung1,FALLING);
 attachInterrupt(3,Demxung2,FALLING);
 Timer1.initialize(100000);
 Timer1.attachInterrupt(PID);
}
void loop() {
  // put your main code here, to run repeatedly:
//  Serial.print(Tar_wheel_front_left);
//  Serial.print("  ");
//  Serial.print(Tar_wheel_front_right);
//  Serial.print("  ");
//  Serial.print(Tar_wheel_rear_left);
//  Serial.print("  ");
//  Serial.print(Tar_wheel_rear_right);
//  Serial.println("  ");

}

void Demxung1()
{
  if(digitalRead(45)==HIGH)
     xung1++;
   else
     xung1--;
}

void Demxung2()
{
  if(digitalRead(43)==LOW)
     xung2++;
   else
     xung2--;
 }

 void Demxung3()
{
  if(digitalRead(39)==LOW)
     xung3++;
   else
     xung3--;
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

  //dong co 1
  tocdo1 = (xung1/628)*(1/T)*60;
  tocdo1 = tocdo1 * LPF_heso + pre_tocdo1*(1-LPF_heso);
  pre_tocdo1 = tocdo1;
  xung1=0;
  E1=tocdodat1-tocdo1;
  alpha1= 2*T*Kp1 + Ki1*T*T+ 2*Kd1;
  beta1=T*T*Ki1-4*Kd1-2*T*Kp1;
  gama1=2*Kd1;
  Output1=(alpha1*E1 + beta1*E1_1 + gama1*E1_2 +2*T*LastOutput1/(2*T));
  LastOutput1=Output1;
  E1_2=E1_1;
  E1_1=E1;

  //dongco2
  tocdo2 = (xung2/388)*(1/T)*60;
  tocdo2 = tocdo2 * LPF_heso + pre_tocdo2*(1-LPF_heso);
  pre_tocdo2 = tocdo2;
  xung2=0;
  E2=tocdodat2-tocdo2;
  alpha2= 2*T*Kp2 + Ki2*T*T+ 2*Kd2;
  beta2=T*T*Ki2-4*Kd2-2*T*Kp2;
  gama2=2*Kd2;
  Output2=(alpha2*E2 + beta2*E2_1 + gama2*E2_2 +2*T*LastOutput2/(2*T));
  LastOutput2=Output2;
  E2_2=E2_1;
  E2_1=E2;

  //dong co 3

  tocdo3 = (xung3/628)*(1/T)*60;
  tocdo3 = tocdo3 * LPF_heso + pre_tocdo3*(1-LPF_heso);
  pre_tocdo3 = tocdo3;
  xung3=0;
  E3=tocdodat3-tocdo3;
  alpha3= 2*T*Kp3 + Ki3*T*T+ 2*Kd3;
  beta3=T*T*Ki3-4*Kd3-2*T*Kp3;
  gama3=2*Kd3;
  Output3=(alpha3*E3 + beta3*E3_1 + gama3*E3_2 +2*T*LastOutput3/(2*T));
  LastOutput3=Output3;
  E3_2=E3_1;
  E3_1=E3;
  //dong co 4
  tocdo4 = (xung4/628)*(1/T)*60;
  tocdo4 = tocdo4 * LPF_heso + pre_tocdo4*(1-LPF_heso);
  pre_tocdo4 = tocdo4;
  xung4=0;
  E4=tocdodat4-tocdo4;
  alpha4= 2*T*Kp4 + Ki4*T*T+ 2*Kd4;
  beta4=T*T*Ki4-4*Kd4-2*T*Kp4;
  gama4=2*Kd4;
  Output4=(alpha4*E4 + beta4*E4_1 + gama4*E4_2 +2*T*LastOutput4/(2*T));
  LastOutput4=Output4;
  E4_2=E4_1;
  E4_1=E4;

  //dong co 1
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

  //dong co 2
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

      //dong co 3
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
      //dong co 4
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
