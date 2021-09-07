#include <Wire.h> //Thư viện giao tiếp I2C
const int MPU_addr = 0x68; //Địa chỉ I2C của MPU6050
int16_t GyX, GyY, GyZ;

int sensor0 = 6;
int sensor1 = 7;
int sensor2 = 8;
int sensor3 = 9;
int sensor4 = 10;
int sensor5 = 11;
int sensor6 = 12;
int sensor7 = 13;
int sensor[8] = {1, 1, 1, 1, 1, 1, 1, 1} ;

int ENA = 5 ;
int ENB = 3;


int in1 = A0 ;
int in2 = A1;
int in3 = A2;
int in4 = A3;

unsigned int Kp = 10 , Ki = 0, Kd = 2;
int P, I, D, PID;
int e, e0 = 0;
byte PWM = 50;
int  a = 1 ;
int   b    = 0 ;
int c = 0 , val , f;
int d = 0 ;

void setup ()
{ Serial.begin ( 9600) ;
  Wire.begin();
  Wire.beginTransmission(MPU_addr); //Gửi tín hiệu đến địa chỉ MPU
  Wire.write(0x6B);
  Wire.write(0);     //Đưa về 0 để bật MPU
  Wire.endTransmission(true);
  Serial.begin(9600);
  pinMode ( sensor0 , INPUT );
  pinMode ( sensor1 , INPUT );
  pinMode ( sensor2 , INPUT );
  pinMode ( sensor3 , INPUT );
  pinMode ( sensor4 , INPUT );
  pinMode ( sensor5 , INPUT );
  pinMode ( sensor6 , INPUT );
  pinMode ( sensor7 , INPUT );
  pinMode ( in1 , OUTPUT );
  pinMode ( in2 , OUTPUT );
  pinMode ( in3 , OUTPUT );
  pinMode ( in4 , OUTPUT );

  pinMode ( ENA , OUTPUT );
  pinMode ( ENB , OUTPUT );
  //pinMode (  , OUTPUT  );
 // pinMode ( 25 , OUTPUT  );



 // digitalWrite ( 23 , 1 ) ;
 // digitalWrite ( 25 , 1 ) ;
  Serial.println ( "started" );




}

void loop ()
{
  prosess();
}
//  Wire.beginTransmission(MPU_addr); //Gửi tín hiệu đến địa chỉ MPU
//  Wire.write(0x3B);                 //Gửi giá trị lên MPU
//  Wire.endTransmission(false);
//  Wire.requestFrom(MPU_addr, 14, true); //Đề nghị thanh ghi của MPU
//
//  GyX = Wire.read() << 8 | Wire.read(); //Góc nghiên trục x
//  GyY = Wire.read() << 8 | Wire.read(); //Góc nghiên trục y
//  GyZ = Wire.read() << 8 | Wire.read(); //Góc nghiên trục z
  //Serial.println ( GyX ) ;

  //Serial.println (GyY ) ;



//  Serial.println ( GyY ) ;


//  if ( GyY < -2000 )
//  {
//    PWM = 100 ;
//    prosess () ;
//  }
//  else if ( GyY > 2000 )
//  {
//    PWM = 20 ;
//    prosess () ;
//  }
//  else {PWM = 45 ;
//  prosess () ;
//  }
//}
void prosess () {
  Error();
  if (e != 8 ) {
    Cal_PID();
    Move();
  }
  if ( e == 8   )
  {
    if ( c == 7  )
    {
      e = 4 ;
      Cal_PID () ;
      Move() ;
    }
    else if ( c == -7 )
    {
      e = -4 ;
      Cal_PID();
      Move();
    }
    c = 0;
  }


}

void Error()
{

  sensor[0] = digitalRead(sensor0);
  sensor[1] = digitalRead(sensor1);
  sensor[2] = digitalRead(sensor2);
  sensor[3] = digitalRead(sensor3);
  sensor[4] = digitalRead(sensor4);
  sensor[5] = digitalRead(sensor5);
  sensor[6] = digitalRead(sensor6);
  sensor[7] = digitalRead(sensor7);



  if      ((sensor[0] == b) && (sensor[1] == a) && (sensor[2] == a) && (sensor[3] == a) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) {
    e = -7  ;
    c = -7;
  }
  else if ((sensor[0] == b) && (sensor[1] == b) && (sensor[2] == a) && (sensor[3] == a) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -6  ;
  else if ((sensor[0] == a) && (sensor[1] == b) && (sensor[2] == a) && (sensor[3] == a) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -5  ;
  else if ((sensor[0] == a) && (sensor[1] == b) && (sensor[2] == b) && (sensor[3] == a) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -4  ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == b) && (sensor[3] == a) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -3  ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == b) && (sensor[3] == b) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -2  ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a) && (sensor[3] == b) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -1;

  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a) && (sensor[3] == b) && (sensor[4] == b) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = 0   ;

  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a) && (sensor[3] == a) && (sensor[4] == b) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = 1   ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a) && (sensor[3] == a) && (sensor[4] == b) && (sensor[5] == b) && (sensor[6] == a) && (sensor[7] == a)) e = 2   ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a) && (sensor[3] == a) && (sensor[4] == a) && (sensor[5] == b) && (sensor[6] == a) && (sensor[7] == a)) e = 3   ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a) && (sensor[3] == a) && (sensor[4] == a) && (sensor[5] == b) && (sensor[6] == b) && (sensor[7] == a)) e = 4   ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a) && (sensor[3] == a) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == b) && (sensor[7] == a)) e = 5   ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a) && (sensor[3] == a) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == b) && (sensor[7] == b)) e = 6   ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a) && (sensor[3] == a) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == b)) {
    e = 7   ;
    c = 7;
  }

  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a) && (sensor[3] == a) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = 8 ;
  else if ((sensor[0] == b) && (sensor[1] == b) && (sensor[2] == b) && (sensor[3] == b) && (sensor[4] == b) && (sensor[5] == b) && (sensor[6] == b) && (sensor[7] == b)) e = 8 ;



}
void Cal_PID()
{

  P = e;
  I += e;
  D = e - e0;
  PID = Kp * P + Ki * I + Kd * D;
  //  Serial.println ( PID ) ;
  e0 = e;
}
void Move()
{

  digitalWrite ( in1 , HIGH ) ;
  digitalWrite ( in2 , LOW );
  digitalWrite ( in3 , HIGH );
  digitalWrite ( in4 , LOW );

  analogWrite ( ENA , PWM - PID +60 ) ;
  analogWrite ( ENB , PWM + PID ) ;


  //  Serial.println (  PWM - PID )  ;
  //  Serial.println ( PWM + PID ) ;
}
void stop_ok ()
{
  digitalWrite ( in1 , 0 ) ;
  digitalWrite ( in2 , 0 );
  digitalWrite ( in3 , 0);
  digitalWrite ( in4 , 0 );
  analogWrite ( ENA , 0 ) ;
  analogWrite ( ENB , 0 ) ;
}
