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
int dctrai  , dcphai ;


int in1 = 46;
int in2 = 48;
int in3 = 50;
int in4 = 52;
int A = 120;
int B = 120;
int C = 110;
int D = 80;
int E = 170;
int e = 0 , c = 0 ;
int a = 0 ; // thi a= 0 , b= 1
int b = 1 ;

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

  Error ();
  if (e != 8 ) {
    process () ;

  }
  if ( e == 8   )
  {
    if ( c == 7 || c == 6  )
    {
      e = 7 ;
      process () ;

    }
    else if ( c == -7 || c == -6 )
    {
      e = -7 ;
      process () ;

    }
    if ( e== 0 ) 
    {
      e = -6 ;
      process () ;
    }



    c = 0;


  }
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
    else if ((sensor[0] == b) && (sensor[1] == b) && (sensor[2] == a) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a))
    {
      e = -6 ;
      c = -6 ;
    }
    else if ((sensor[0] == a) && (sensor[1] == b) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -5  ;
    else if ((sensor[0] == a) && (sensor[1] == b) && (sensor[2] == b) && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -4  ;
    else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == b)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -3  ;
    else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == b)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -2  ;
    // else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = -1;

    else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a) && (sensor[4] == b) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = 0   ;

    else if ((sensor[0] == b) && (sensor[1] == b) && (sensor[2] == b) && (sensor[4] == b) && (sensor[5] == b) && (sensor[6] == b) && (sensor[7] == b)) e = 0   ;
    else if ((sensor[0] == a) && (sensor[1] == b) && (sensor[2] == b) && (sensor[4] == b) && (sensor[5] == b) && (sensor[6] == b) && (sensor[7] == a)) e = 0   ;
    else if ((sensor[0] == a) && (sensor[1] == b) && (sensor[2] == b) && (sensor[4] == b) && (sensor[5] == b) && (sensor[6] == b) && (sensor[7] == b)) e = 0   ;
    else if ((sensor[0] == b) && (sensor[1] == b) && (sensor[2] == b) && (sensor[4] == b) && (sensor[5] == b) && (sensor[6] == b) && (sensor[7] == a)) e = 0   ;
    else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == b) && (sensor[4] == b) && (sensor[5] == b) && (sensor[6] == b) && (sensor[7] == a)) e = 0   ;
    else if ((sensor[0] == a) && (sensor[1] == b) && (sensor[2] == b) && (sensor[4] == b) && (sensor[5] == b) && (sensor[6] == a) && (sensor[7] == a)) e = 0   ;

    else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a) && (sensor[4] == b) && (sensor[5] == b) && (sensor[6] == a) && (sensor[7] == a)) e = 0   ;
    else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == b) && (sensor[4] == b) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = 0   ;

    else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == b) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = 1   ;
    else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == b) && (sensor[5] == b) && (sensor[6] == a) && (sensor[7] == a)) e = 2   ;
    else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == b) && (sensor[6] == a) && (sensor[7] == a)) e = 3   ;
    else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == b) && (sensor[6] == b) && (sensor[7] == a)) e = 4   ;
    else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == b) && (sensor[7] == a)) e = 5   ;
    else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == b) && (sensor[7] == b))
    {
      e = 6 ;
      c = 6 ;
    }
    else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == b)) {
      e = 7   ;
      c = 7;
    }

    else if ((sensor[0] == a) && (sensor[1] == a) && (sensor[2] == a)  && (sensor[4] == a) && (sensor[5] == a) && (sensor[6] == a) && (sensor[7] == a)) e = 8 ;
    // else if ((sensor[0] == b) && (sensor[1] == b) && (sensor[2] == b) && (sensor[4] == b) && (sensor[5] == b) && (sensor[6] == b) && (sensor[7] == b)) e = 8 ;



  }

  void Move()
  {

    digitalWrite ( in1 , HIGH ) ;
    digitalWrite ( in2 , LOW );
    digitalWrite ( in3 , HIGH );
    digitalWrite ( in4 , LOW );

    analogWrite ( ENA , dctrai) ;
    analogWrite ( ENB , dcphai ) ;
  }
  void trai ()
  {
    digitalWrite ( in1 , LOW ) ;
    digitalWrite ( in2 , HIGH );
    digitalWrite ( in3 , HIGH );
    digitalWrite ( in4 , LOW );

    analogWrite ( ENA , dctrai) ;
    analogWrite ( ENB , dcphai ) ;
  }
  void phai () {
    digitalWrite ( in1 , HIGH ) ;
    digitalWrite ( in2 , LOW );
    digitalWrite ( in3 , LOW );
    digitalWrite ( in4 , HIGH);

    analogWrite ( ENA , dctrai) ;
    analogWrite ( ENB , dcphai ) ;
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
  void process ()
  {
    if ( e == -7  || e == -6 || e == -5 || e == -4 )
    {
      dctrai = A ;
      dcphai = B ;
      phai () ;
    }
    else if ( e == 7 || e == 6 || e == 5 || e == 4 )
    {
      dctrai = B ;
      dcphai = A ;
      trai () ;
    }
    else if ( e == -3 || e == -2 ) {
      dctrai = C ;
      dcphai = D ;
      Move ()  ;
    }
    else if ( e == 3 || e == -2 ) {
      dctrai = D ;
      dcphai = C ;
      Move ()  ;

    }
    else if ( e == 1 || e == -1 || e == 0 )
    {
      dctrai = E ;
      dcphai = E ;
      Move () ;
    }
    else if ( e == 8 )
    {
      dctrai = A ;
      dcphai = B ;
      trai () ;
    }
    else if ( e == -8 )
    {
      dctrai = A ;
      dcphai = B ;
      phai () ;
    }


  }
