// PHAN BEN 18TDH1 15/6/2019 //

// khai báo cảm biến

int sensor1 = 22;
int sensor2 = 24;
int sensor3 = 26;
int sensor4 = 28;
int sensor5 = 30;
int sensor[5] = {1, 1, 1, 1, 1} ;

//khai báo động cơ
int ENA = 2 ;
int ENB = 3;
int ENC = 4 ;
int END = 5 ;
int in1 = 34;
int in2 = 36;
int in3 = 38;
int in4 = 40;
- m,


//khai bao cảm bien siêu âm

int trig = 33;
int echo = 32;


//khởi tạo tốc độ

int khoi_tao_toc_do = 200 ;

// hằng số PID

float Kp = 30 ;
float Ki = 0;
float Kd = 0;;

float lech = 0 , P = 0, I = 0, D = 0 , PID_value = 0;
float truoc_lech = 0, truoc_I = 0;

int trai_motor , phai_motor ;


void setup ()
{
  pinMode ( sensor1 , INPUT );
  pinMode ( sensor2 , INPUT );
  pinMode ( sensor3 , INPUT );
  pinMode ( sensor4 , INPUT );
  pinMode ( sensor5 , INPUT );

  pinMode ( in1 , OUTPUT );
  pinMode ( in2 , OUTPUT );
  pinMode ( in3 , OUTPUT );
  pinMode ( in4 , OUTPUT );

  pinMode ( ENA , OUTPUT );
  pinMode ( ENB , OUTPUT );

  pinMode ( trig , OUTPUT );
  pinMode ( echo , INPUT );
  Serial.begin ( 9600) ;
  Serial.println ( "started" );
  

}


void loop ()
{
  doc_gia_tri_cam_bien ();

  Serial.println ( lech ) ;
  unsigned long thoi_gian ;
  int khoang_cach ;
  digitalWrite ( trig, 0) ;
  delayMicroseconds ( 2) ;
  digitalWrite ( trig , 1);
  delayMicroseconds ( 5) ;
  digitalWrite ( trig , 0 ) ;
  thoi_gian = pulseIn ( echo, HIGH ) ;
  khoang_cach = int ( thoi_gian / 2 / 29.412 );
  Serial.println ( khoang_cach );
  Serial.println ( " cm " );

  if ( khoang_cach < 15)
  {
    if ( khoang_cach > 5 )
    { dung () ;
      Serial.println ( "stop" );
    }
  }
  else {
    tinh_toan_pid () ;
    motor_control () ;
  }



 

}


void doc_gia_tri_cam_bien () //giá trị của cảm biến chú ý line while : 0 and line draw : 1
{
  sensor[0] = !digitalRead(sensor1);
  sensor[1] = !digitalRead(sensor2);
  sensor[2] = !digitalRead(sensor3);
  sensor[3] = !digitalRead(sensor4);
  sensor[5] = !digitalRead(sensor5);

  if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[4] == 1) && (sensor[4] == 0))
    lech = 4;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[4] == 0) && (sensor[4] == 0))
    lech = 3;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[4] == 0) && (sensor[4] == 1))
    lech = 2;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[4] == 0) && (sensor[4] == 1))
    lech = 1;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[4] == 1) && (sensor[4] == 1))
    lech = 0;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[4] == 1) && (sensor[4] == 1))
    lech = -1;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[4] == 1) && (sensor[4] == 1))
    lech = -2;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[4] == 1) && (sensor[4] == 1))
    lech = -3;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[4] == 1) && (sensor[4] == 1))
    lech = -4;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[4] == 1) && (sensor[4] == 1))
    if (lech == -4) lech = -5;
    else lech = 5;

}

void tinh_toan_pid ()
{
  P = lech ;
  I = I + lech ;
  D = lech - truoc_lech ;

  PID_value = (Kp * P) + ( Ki * I ) + ( Kd * D );

  truoc_lech = lech ;
}


void motor_control ()
{
  int trai_motor = khoi_tao_toc_do - PID_value ;
  int phai_motor = khoi_tao_toc_do + PID_value ;
  trai_motor = constrain ( trai_motor , 0, 255);
  phai_motor = constrain ( phai_motor , 0, 255);
  analogWrite ( ENA , trai_motor  );
  analogWrite ( ENB , trai_motor );
  analogWrite ( ENC , phai_motor );
  analogWrite ( END , phai_motor );
  tien ();
  
  Serial.println( "PID trai , phai " ) ;
  Serial.println( trai_motor );
  Serial.println( phai_motor ) ;


}
void tien ()
{
  digitalWrite ( in1 , HIGH ) ;
  digitalWrite ( in2 , LOW );
  digitalWrite ( in3 , HIGH );
  digitalWrite ( in4 , LOW );

}
void lui ()
{
  digitalWrite ( in1 , LOW );
  digitalWrite ( in2 , HIGH );
  digitalWrite ( in3 , LOW );
  digitalWrite ( in4 , HIGH );

}
void quay_phai ()
{
  digitalWrite ( in1 , HIGH );
  digitalWrite ( in2 , LOW );
  digitalWrite ( in3 , LOW );
  digitalWrite ( in4 , LOW );

}
void quay_trai ()
{
  digitalWrite ( in1 , LOW );
  digitalWrite ( in2 , LOW );
  digitalWrite ( in3 , HIGH );
  digitalWrite ( in4 , LOW );


}
void re_phai ()
{
  digitalWrite ( in1 , HIGH );
  digitalWrite ( in2 , LOW );
  digitalWrite ( in3 , LOW );
  digitalWrite ( in4 , HIGH );


}
void re_trai ()
{
  digitalWrite ( in1 , LOW );
  digitalWrite ( in2 , HIGH );
  digitalWrite ( in3 , HIGH );
  digitalWrite ( in4 , LOW );

}
void dung ()
{
  digitalWrite ( in1 , LOW );
  digitalWrite ( in2 , LOW );
  digitalWrite ( in3 , LOW ) ;
  digitalWrite ( in4 , LOW );

}
