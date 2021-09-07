

// Phan Ben 18TDH 1 - 27/06/2019 //
// this is lines declare variable
int EN_R[] = {32, 34, 36, 38};
int EN_L[] = {33, 35, 37, 39 };
int PWM_R[] = {3, 4, 5, 6};
int PWM_L[] = {7, 8, 9, 10} ;
int ENA  = 11 ;
int ENB = 12 ;
int in1 = 52;
int in2 = 53;


const int action1 = 42;
const int action2 = 44;
const int action3 = 44;
const int action4 = 46 ;

byte data = 0 ;

int speed_go = 0 ;
int speed_turn = 0 ;
int  speed_stop = 0;
void mortor1_forward();
void mortor2_forward() ;
void mortor3_forward() ;
void mortor4_forward () ;
void mortor1_backward () ;
void mortor2_backward () ;
void mortor3_backward () ;
void mortor4_backward () ;
void mortor1_stop() ;
void mortor2_stop() ;
void mortor3_stop () ;
void mortor4_stop () ;
// this is lines void setup
void setup ()
{    
  Serial.begin (9600);

 //digitalWrite ( 12 , 1 ) ;
  for (int i = 0 ; i < 4 ; i++ )
  {
    pinMode (EN_R[i] , OUTPUT ) ;
    pinMode (EN_L[i] , OUTPUT  ) ;
    pinMode (PWM_R[i] , OUTPUT  ) ;
    pinMode (PWM_L[i] , OUTPUT ) ;

  }

  pinMode (action1 , OUTPUT ) ;
  pinMode (action2 , OUTPUT ) ;
  pinMode (action3 , OUTPUT ) ;
  pinMode (action4 , OUTPUT ) ;
  pinMode ( ENA , OUTPUT );
  pinMode ( ENB , OUTPUT ); 
  pinMode ( in1 , OUTPUT );
  pinMode ( in2 , OUTPUT );

}

// this is lines void loop
   

void loop ()
{
  if ( Serial.available () > 0 )
  {
    data = Serial.read () ;
    Serial.println  (data )  ;


  }
  if ( data == 109 ) 
  {
    speed_go = 110 ;  
  }
  if (data == 121) 
  {
    speed_go = 50 ;    
  }
  if ( data == 49)
  {
    forward () ;
    data = 0 ;
  }

  if ( data == 50)
  {
    backward () ;
    data = 0 ;


  }


  if ( data == 51 )
  {
    speed_go ;
    turn_right ();

    data = 0 ;


  }

  if ( data == 52 )
  {
    speed_go;
    turn_left () ;
    data = 0 ;


  }


  if ( data  == 57 )
  {
    stop_ok () ;
    stop_stop () ;
    data = 0 ;


  }


  if (data == 53)
  {
    sideways_left () ;
    data = 0 ;


  }


  if ( data == 54 )
  {
    sideways_right () ;
    data = 0;


  }


  if (data == 55 )
  {
    backward_45_left () ;
    data = 0 ;


  }


  if (data == 56)
  {
    backward_45_right () ;
    data = 0;


  }


  if (data == 98  )
  {

    forward_45_left () ;
    data = 57 ;


  }


  if (data == 97 )
  {
    forward_45_right  () ;
    data = 0 ;


  }


  if (data == 99)
  {
    digitalWrite ( action1 , HIGH ) ;
    Serial.println ("status action1 : ON " );
    data = 0 ;


  }


  if (data == 100 )
  {
    digitalWrite ( action1 , LOW  ) ;
    Serial.println ("status action1 : OFF " );
    data = 0;


  }


  if (data == 101)
  {
    digitalWrite ( action2 , HIGH  ) ;
    Serial.println ("status action2 : ON " );
    data = 0;


  }

  if ( data == 102 )
  {
    digitalWrite ( action2 , LOW  );
    Serial.println ("status action2 : OFF " );
    data = 0 ;


  }


  if ( data == 103 )
  {
    up ( ) ;
    Serial.println ("status action3 : ON " );
    data = 0 ;


  }


  if  (data == 104)
  {
    down () ;
    Serial.println ("status action3 : OFF " );
    data = 0 ;


  }


  if (data == 105 )
  {
    digitalWrite (action4 , HIGH  ) ;
    Serial.println ("status action4 : ON " );
    data = 0 ;


  }


  if (data == 106 )
  {
    digitalWrite ( action4  , LOW  );
    Serial.println ("status action4 : OFF " );
    data = 0 ;


  }

 if (data == 106 )
  {
    stop_stop () ;
    Serial.println ("status action4 : OFF " );
    data = 0 ;
  }




}

// this is lines motor forward
void mortor1_forward ()
{
  digitalWrite ( EN_L[0] , HIGH ) ;
  digitalWrite ( EN_R[0] , HIGH ) ;
  analogWrite ( PWM_L[0] , speed_go  );
  analogWrite  ( PWM_R[0] , speed_stop );
}
void mortor2_forward ()
{
  digitalWrite ( EN_L[1] , HIGH ) ;
  digitalWrite ( EN_R[1] , HIGH ) ;
  
  analogWrite ( PWM_L[1] , speed_go ) ;
  analogWrite ( PWM_R[1] , speed_stop ) ;

}
void mortor3_forward ()
{
  digitalWrite ( EN_L[2] , HIGH  ) ;
  digitalWrite ( EN_R[2] , HIGH ) ;
  analogWrite (PWM_L[2] , speed_go ) ;
  analogWrite (PWM_R[2] , speed_stop ) ;
}
void mortor4_forward ()
{
  digitalWrite (EN_L[3] , HIGH ) ;
  digitalWrite (EN_R[3] , HIGH );
  analogWrite (PWM_L[3] , speed_go  ) ;
  analogWrite (PWM_R[3] , speed_stop ) ;
}


// this is lines mortor_backward
void mortor1_backward ( )
{
  digitalWrite ( EN_L[0] , HIGH ) ;
  digitalWrite ( EN_R[0] , HIGH  ) ;
  analogWrite ( PWM_L[0] , speed_stop  );
  analogWrite  ( PWM_R[0] , speed_go );
}

void mortor2_backward ()
{
  digitalWrite ( EN_L[1] , HIGH  ) ;
  digitalWrite ( EN_R[1] , HIGH) ;
  analogWrite ( PWM_L[1] , speed_stop ) ;
  analogWrite ( PWM_R[1] , speed_go ) ;


}
void mortor3_backward ()
{
  digitalWrite ( EN_L[2] , HIGH  ) ;
  digitalWrite ( EN_R[2] , HIGH ) ;
  analogWrite (PWM_L[2] , speed_stop ) ;
  analogWrite (PWM_R[2] , speed_go ) ;
}
void mortor4_backward ()
{
  digitalWrite (EN_L[3] , HIGH ) ;
  digitalWrite (EN_R[3] , HIGH  );
  analogWrite (PWM_L[3] , speed_stop  ) ;
  analogWrite (PWM_R[3] , speed_go ) ;
}
void mortor1_stop ()
{
  digitalWrite (EN_L[0] , LOW ) ;
  digitalWrite (EN_R[0] , LOW  );
  analogWrite (PWM_L[0] , speed_stop  ) ;
  analogWrite (PWM_R[0] , speed_stop ) ;
}
void mortor2_stop ()
{
  digitalWrite ( EN_L[1] , LOW  ) ;
  digitalWrite ( EN_R[1] , LOW ) ;
  analogWrite ( PWM_L[1] , speed_stop ) ;
  analogWrite ( PWM_R[1] , speed_stop ) ;


}
void mortor3_stop ()
{
  digitalWrite ( EN_L[2] , LOW  ) ;
  digitalWrite ( EN_R[2] , LOW  ) ;
  analogWrite (PWM_L[2] , speed_stop ) ;
  analogWrite (PWM_R[2] , speed_stop ) ;
}
void mortor4_stop ()
{
  digitalWrite (EN_L[3] , LOW ) ;
  digitalWrite (EN_R[3] , LOW  );
  analogWrite (PWM_L[3] , speed_stop  ) ;
  analogWrite (PWM_R[3] , speed_stop ) ;
}

void forward ()
{
  mortor1_forward () ;
  mortor2_forward () ;
  mortor3_forward () ;
  mortor4_forward () ;
  Serial.println (" forward ok!! " );

}
void backward ()
{
  mortor1_backward() ;
  mortor2_backward() ;
  mortor3_backward() ;
  mortor4_backward() ;
  Serial.println (" backward ok!! " );

}
void   turn_right  ()
{
  mortor1_forward () ;
  mortor2_backward () ;
  mortor3_forward() ;
  mortor4_backward () ;
  Serial.println (" sideways right ok!! ");

}
void turn_left ()
{
  mortor1_backward () ;
  mortor2_forward() ;
  mortor3_backward () ;
  mortor4_forward () ;
  Serial.println  (" sideways left ok!! ") ;
}
void sideways_left ( )
{
  mortor1_backward () ;
  mortor3_forward () ;
  mortor4_forward () ;
  mortor2_backward () ;
  Serial.println ("turn left ok!! " );
}
void sideways_right ()
{
  mortor1_forward () ;
  mortor3_backward () ;
  mortor4_backward  () ;
  mortor2_forward () ;
  Serial.println ("turn right ok!! " );
}
void forward_45_left ()
{
  mortor1_stop () ;
  mortor2_forward () ;
  mortor3_stop () ;
  mortor4_forward () ;
  Serial.println ("forward 45 left ok!! ") ;
}
void backward_45_right ()
{
  mortor1_stop () ;
  mortor2_backward () ;
  mortor3_stop () ;
  mortor4_backward () ;
  Serial.println ("back ward 45 right ok!! " );
}
void forward_45_right ()
{
  mortor1_forward () ;
  mortor2_stop () ;
  mortor3_forward () ;
  mortor4_stop () ;
  Serial.println ( "forward 45 right ok!! " );
}
void backward_45_left ()
{
  mortor1_backward () ;
  mortor2_stop () ;
  mortor3_backward () ;
  mortor4_stop () ;
  Serial.println ( " backward 45 left ok!! ") ;

}
void stop_ok()
{
  mortor1_stop () ;
  mortor2_stop () ;
  mortor3_stop () ;
  mortor4_stop () ;
  Serial.println("stop ok!!" );

}
void down ( )
{
  digitalWrite ( in1 , HIGH ) ;
  digitalWrite ( in2 , HIGH) ;
  //digitalWrite ( in3 , HIGH );
  //digitalWrite ( in4 , LOW );
  analogWrite ( ENA , 0  );
  analogWrite  ( ENB , 255 );
  
}
void up ( )
{
  digitalWrite ( in1  , HIGH ) ;
  digitalWrite ( in2  , HIGH ) ;
 // digitalWrite ( in3 , LOW );
  //digitalWrite ( in4 , HIGH );
  analogWrite ( ENA , 255  );
  analogWrite  ( ENB , 0);
}
void stop_stop () 
{
  digitalWrite ( in1  , LOW  ) ;
  digitalWrite ( in2  , LOW  ) ;
//  digitalWrite ( in3 , LOW  );
 // digitalWrite ( in4 , LOW );
  analogWrite ( ENA , 0   );
  analogWrite  ( ENB , 0  );
}
