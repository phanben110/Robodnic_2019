int sensor0 = 22;
int sensor1 = 24;
int sensor2 = 26;
//int sensor3 = 28;
int sensor4 = 30;
int sensor5 = 32;
int sensor6 = 34;
int sensor7 = 36;
int sensor[8] = {1, 1, 1, 1, 1, 1, 1, 1} ;

int ENA = 8 ;
int ENB = 9;


int in1 = 46;
int in2 = 48;
int in3 = 50;
int in4 = 52;

unsigned int Kp = 5 , Ki =  0 , Kd = 1; //(6,0,2) 50
int P, I, D, PID;
int e, e0 = 0;
byte PWM = 50;
int  a = 1 ;
int   b    = 0 ;
int c = 0 ;

void setup ()
{
  pinMode ( sensor0 , INPUT );
  pinMode ( sensor1 , INPUT );
  pinMode ( sensor2 , INPUT );
 // pinMode ( sensor3 , INPUT );
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

  pinMode ( 23 , OUTPUT  );
  pinMode ( 25 , OUTPUT  );

  digitalWrite ( 23 , 1 ) ;
  digitalWrite ( 25 , 1 ) ;

  Serial.begin ( 9600) ;
  Serial.println ( "started" );


}

void loop ()
{
  Serial.println ("===" ) ;
  Serial.println ( digitalRead (22)  ) ;
  Serial.println ( digitalRead (24)  ) ;
  Serial.println ( digitalRead (26) ) ;
 // Serial.println ( digitalRead (28)  ) ;
  Serial.println ( digitalRead (30) ) ;
  Serial.println ( digitalRead (32) ) ;
  Serial.println ( digitalRead (34)  ) ;
  Serial.println ( digitalRead (36) ) ;
  Serial.println ("+++" ) ;
  Error();
  if (e != 8 ) {
    Cal_PID();
    Move();
  }
  if ( e == 8   )
  {
    if ( c == 7  )
    {
      e = 8 ;
      Cal_PID () ;
      Move() ;
    }
    else if ( c == -7 )
    {
      e = -8 ;
      Cal_PID();
      Move();
    }

  }
  c = 0;




}
void Error()
{

  sensor[0] = digitalRead(sensor0);
  sensor[1] = digitalRead(sensor1);
  sensor[2] = digitalRead(sensor2);
 // sensor[3] = digitalRead(sensor3);
  sensor[4] = digitalRead(sensor4);
  sensor[5] = digitalRead(sensor5);
  sensor[6] = digitalRead(sensor6);
  sensor[7] = digitalRead(sensor7);



  if      ((sensor[0] == b) && (sensor[1] == a) && (sensor[2] == a) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) {
    e = -7  ;
    c = -7;
  }
  else if ((sensor[0] == b) && (sensor[1] == b) && (sensor[2] == a) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -6  ;
  else if ((sensor[0] == a) && (sensor[1] == b) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -5  ;
  else if ((sensor[0] == a) && (sensor[1] == b) && (sensor[2] == b) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -4  ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == b)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -3  ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == b)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -2  ;
 // else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -1;

  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a) && (sensor[4] == b) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = 0   ;

  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == b) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = 1   ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == b) && (sensor[5] == b) && (sensor[6] == a) && (sensor[7] == a)) e = 2   ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == b) && (sensor[6] == a) && (sensor[7] == a)) e = 3   ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == b) && (sensor[6] == b) && (sensor[7] == a)) e = 4   ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == b) && (sensor[7] == a)) e = 5   ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == b) && (sensor[7] == b)) e = 6   ;
  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == b)) {
    e = 7   ;
    c = 7;
  }

  else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = 8 ;
  else if ((sensor[0] == b) && (sensor[1] == b) && (sensor[2] == b) && (sensor[4] == b) && (sensor[5] == b) && (sensor[6] == b) && (sensor[7] == b)) e = 8 ;



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

  analogWrite ( ENA , PWM - PID ) ;
  analogWrite ( ENB , PWM + PID ) ;


  Serial.println (  PWM - PID )  ;
  Serial.println ( PWM + PID ) ;
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
