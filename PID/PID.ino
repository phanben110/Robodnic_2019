

// PHAN BEN 18TDH1 15/6/2019 //

// khai báo cảm biến

int sensor0 = 22;
int sensor1 = 24;
int sensor2 = 26;
int sensor3 = 28;
int sensor4 = 30;
int sensor5 = 32;
int sensor6 = 34;
int sensor7 = 36;


int sensor[8] = {1, 1, 1, 1, 1, 1, 1, 1} ;

//khai báo động cơ
int ENA = 4  ;
int ENB = 3;
//int ENC =  ;
//int END =  ;
int in1 = 46;
int in2 = 48;
int in3 = 50;
int in4 = 52;


//khai bao cảm bien siêu âm

//int trig = 33;
//int echo = 32;


//khởi tạo tốc độ

int speed_tien = 200 ;
int speed_lui = 100 ;
int speed_quay = 180 ;
int speed_re = 180;
int lech ;

unsigned int Kp = 8, Ki = 0, Kd = 2;
int P, I, D, PID;
int e, e0 = 0;
byte PWM = 100;

void setup ()
{
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

  //  pinMode ( trig , OUTPUT );
  //  pinMode ( echo , INPUT );
  Serial.begin ( 9600) ;
  Serial.println ( "started" );


}


void loop ()
{
  // while(1)
  // {
  Error();
  Cal_PID();
  Move();

  //  }



  //  doc_gia_tri_cam_bien ();
  //
  //  Serial.println ( lech ) ;
  //  unsigned long thoi_gian ;
  //  int khoang_cach ;
  //  digitalWrite ( trig, 0) ;
  //  delayMicroseconds ( 2) ;
  //  digitalWrite ( trig , 1);
  //  delayMicroseconds ( 5) ;
  //  digitalWrite ( trig , 0 ) ;
  //  thoi_gian = pulseIn ( echo, HIGH ) ;
  //  khoang_cach = int ( thoi_gian / 2 / 29.412 );
  //  Serial.println ( khoang_cach );
  //  Serial.println ( " cm " );
  //
  //  if ( khoang_cach < 15)
  //  {
  //    if ( khoang_cach > 5 )
  //    { dung () ;
  //      Serial.println ( "stop" );
  //    }
  //  }
  //  else {
  //    motor_control () ;
  //  }

}
int Error()
{

  sensor[0] = digitalRead(sensor0);
  sensor[1] = digitalRead(sensor1);
  sensor[2] = digitalRead(sensor2);
  sensor[3] = digitalRead(sensor3);
  sensor[4] = digitalRead(sensor4);
  sensor[5] = digitalRead(sensor5);
  sensor[6] = digitalRead(sensor6);
  sensor[7] = digitalRead(sensor7);
  if      ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0) && (sensor[5] == 1) && (sensor[6] == 1) && (sensor[7] == 1)) e = 0;

  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 1) && (sensor[7] == 1)) e = -4;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 1) && (sensor[7] == 1)) e = -3;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 1) && (sensor[7] == 1)) e = -2;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 1) && (sensor[7] == 1)) e = -1;

  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 0) && (sensor[5] == 0) && (sensor[6] == 1) && (sensor[7] == 1)) e = 1;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1) && (sensor[5] == 0) && (sensor[6] == 0) && (sensor[7] == 1)) e = 2;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 0) && (sensor[7] == 0)) e = 3;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 1) && (sensor[7] == 0)) e = 4;

  else e = 5;
}
void Cal_PID()
{

  P = e;
  I += e;
  D = e - e0;
  PID = Kp * P + Ki * I + Kd * D;
  Serial.println ( PID ) ;
  e0 = e;
}
void Move()
{

  digitalWrite ( in1 , HIGH ) ;
  digitalWrite ( in2 , LOW );
  digitalWrite ( in3 , HIGH );
  digitalWrite ( in4 , LOW );

  analogWrite ( ENA , PWM - PID ) ;
  analogWrite ( ENB , PWM + PID ) ;
}
/*
  void doc_gia_tri_cam_bien () //giá trị của cảm biến chú ý line while : 0 and line draw : 1
  {
  sensor[0] = !digitalRead(sensor0);
  sensor[1] = !digitalRead(sensor1);
  sensor[2] = !digitalRead(sensor2);
  sensor[3] = !digitalRead(sensor3);
  sensor[4] = !digitalRead(sensor4);

  if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 0))
    lech = 4;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0))
    lech = 3;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 1))
    lech = 2;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 1))
    lech = 1;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 1))
    lech = 0;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 1))
    lech = -1;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
    lech = -2;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
    lech = -3;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
    lech = -4;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
    if (lech == -4) lech = -5;
    else lech = 5;

  }




  void motor_control ()
  {
  if ( lech == 5 )
    dung () ;
  if ( lech == 4 )
    quay_trai () ;
  if ( lech == 3 )
    re_trai () ;
  if ( lech == 2 )
    re_trai () ;
  if ( lech == 1 )
    re_trai () ;
  if ( lech == 0 )
    tien () ;
  if ( lech == -1)
    re_phai () ;
  if ( lech == -2 )
    re_phai () ;
  if ( lech == -3 )
    re_phai () ;
  if ( lech == -4 )
    quay_phai () ;
  if ( lech == -5 )
    dung  () ;
  }
  void tien ()
  {
  analogWrite ( ENA , speed_tien ) ;
  analogWrite ( ENB , speed_tien ) ;
  analogWrite ( ENC , speed_tien ) ;
  analogWrite ( END , speed_tien ) ;

  digitalWrite ( in1 , HIGH ) ;
  digitalWrite ( in2 , LOW );
  digitalWrite ( in3 , HIGH );
  digitalWrite ( in4 , LOW );

  }
  void lui ()
  {
  analogWrite ( ENA , speed_lui ) ;
  analogWrite ( ENB , speed_lui ) ;
  analogWrite ( ENC , speed_lui ) ;
  analogWrite ( END , speed_lui ) ;

  digitalWrite ( in1 , LOW );
  digitalWrite ( in2 , HIGH );
  digitalWrite ( in3 , LOW );
  digitalWrite ( in4 , HIGH );

  }
  void re_phai ()
  {
  analogWrite ( ENA , speed_quay ) ;
  analogWrite ( ENB , speed_quay ) ;
  analogWrite ( ENC , speed_quay ) ;
  analogWrite ( END , speed_quay ) ;

  digitalWrite ( in1 , HIGH );
  digitalWrite ( in2 , LOW );
  digitalWrite ( in3 , LOW );
  digitalWrite ( in4 , LOW );

  }

  void re_trai ()
  {
  analogWrite ( ENA , speed_quay  ) ;
  analogWrite ( ENB , speed_quay  ) ;
  analogWrite ( ENC , speed_quay ) ;
  analogWrite ( END , speed_quay ) ;

  digitalWrite ( in1 , LOW );
  digitalWrite ( in2 , LOW );
  digitalWrite ( in3 , HIGH );
  digitalWrite ( in4 , LOW );


  }
  void quay_phai ()
  {
  analogWrite ( ENA , speed_re ) ;
  analogWrite ( ENB , speed_re  ) ;
  analogWrite ( ENC , speed_re ) ;
  analogWrite ( END , speed_re ) ;

  digitalWrite ( in1 , HIGH );
  digitalWrite ( in2 , LOW );
  digitalWrite ( in3 , LOW );
  digitalWrite ( in4 , HIGH );


  }
  void quay_trai ()
  {
  analogWrite ( ENA , speed_re  ) ;
  analogWrite ( ENB , speed_re  ) ;
  analogWrite ( ENC , speed_re ) ;
  analogWrite ( END , speed_re ) ;

  digitalWrite ( in1 , LOW );
  digitalWrite ( in2 , HIGH );
  digitalWrite ( in3 , HIGH );
  digitalWrite ( in4 , LOW );

  }
  void dung ()
  {
  analogWrite ( ENA , 0 ) ;
  analogWrite ( ENB , 0 ) ;
  analogWrite ( ENC , 0 ) ;
  analogWrite ( END , 0 ) ;
  digitalWrite ( in1 , LOW );
  digitalWrite ( in2 , LOW );
  digitalWrite ( in3 , LOW ) ;
  digitalWrite ( in4 , LOW );

  }
*/
