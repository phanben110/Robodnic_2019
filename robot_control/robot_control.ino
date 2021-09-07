// Phan Ben 18TDH 1 - 27/06/2019 //
// this is lines declare setup PS2X
#include <PS2X_lib.h>  //for v1.6
PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;
int a , b , c, d, e, f, g, h ;
int go = 50 ;

// this is lines declare variable
int EN_R[] = {32, 34, 36, 38};
int EN_L[] = {33, 35, 37, 39 };
int PWM_R[] = {3, 4, 5, 6};
int PWM_L[] = {7, 8, 9, 10} ;

const int action1 = 40;
const int action2 = 41;
const int action3 = 42;
const int action4 = 43;
int val ;

int speed_go = 100 ;
#define speed_stop 0
#define k 123
const int  chance  = 0 ;
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

  // setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(22, 23, 24, 25, true, true);

  if (error == 0)
  {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  }
  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  // Serial.print(ps2x.Analog(1), HEX);
  type = ps2x.readType();
  switch (type)
  {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }


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

}


// this is lines void loop


void loop ()
{

  if (error == 1)
    return;

  a = 123 - ps2x.Analog(PSS_LY ) ;
  b =  ps2x.Analog(PSS_LY ) - 123 ;
  c = 123 - ps2x.Analog(PSS_LX ) - go  ;
  d =  ps2x.Analog(PSS_LX ) - 123 - go ;
  e = 123 - ps2x.Analog(PSS_RY )  ;
  f =  ps2x.Analog(PSS_RY ) - 123 ;
  g = 123 - ps2x.Analog(PSS_RX )  - go ;
  h =  ps2x.Analog(PSS_RX ) - 123 - go ;
  

  if (a > 0 )
    val = 1 ;
  else if (b > 0 )
    val = 2 ;
  else if (c > 0)
    val = 3 ;
  else if (d > 0)
    val = 4 ;
  else if (e > 0 )
    val = 5 ;
  else if (f > 0 )
    val = 6 ;
  else if ( g > 0 )
    val = 7 ;
  else if (h > 0 )
    val = 8;

  switch ( val )
{
  case 1:
{
  speed_go = a + chance ;
  forward() ;
  Serial.println ( String ("forward: ") + speed_go ) ;
  break ;
}

case 2:
{
  speed_go = b + chance ;
  backward ( ) ;
  Serial.println (String ("backward: ") + speed_go ) ;
  break ;
}




case 3:
{
  speed_go = c  ;
  turn_left () ;
  Serial.println ( String ("turn_left: ") + speed_go ) ;
  break ;
}


case 4:
{
speed_go = d ;
turn_right () ;
Serial.println (String ("trurn_right: ") + speed_go ) ;
break ;
}



case 5:
{
speed_go = e + chance ;
forward_45_right ();
Serial.println ( String ("forward_45_right: ") + speed_go  ) ;
break ;
}

case 6:
{
speed_go = f + chance ;
backward_45_left ();
Serial.println ( String ("backward_45_left: ") + speed_go  ) ;
break ;
}

case 8:
{
speed_go = h ;
sideways_right () ;
Serial.println ( String ("sideways_right: ") + speed_go  ) ;
break ;
}

case 7:
{
speed_go = g ;
sideways_left () ;
Serial.println (String ("sideways_left: ") + speed_go ) ;
break ;
}
case 9:
{
  
}
default:
    {
        stop_ok () ;
    }
}


if (type == 2)
{
  // Guitar Hero Controller
  // read controller
  ps2x.read_gamepad();

  if (ps2x.ButtonPressed(GREEN_FRET))
    Serial.println("Green Fret Pressed");
  if (ps2x.ButtonPressed(RED_FRET))
    Serial.println("Red Fret Pressed");
  if (ps2x.ButtonPressed(YELLOW_FRET))
    Serial.println("Yellow Fret Pressed");
  if (ps2x.ButtonPressed(BLUE_FRET))
    Serial.println("Blue Fret Pressed");
  if (ps2x.ButtonPressed(ORANGE_FRET))
    Serial.println("Orange Fret Pressed");

  if (ps2x.ButtonPressed(STAR_POWER))
    Serial.println("Star Power Command");

  // will be TRUE as long as button is pressed
  if (ps2x.Button(UP_STRUM))
    Serial.println("Up Strum");
  if (ps2x.Button(DOWN_STRUM))
    Serial.println("DOWN Strum");

  // will be TRUE as long as button is pressed
  if (ps2x.Button(PSB_START))
    Serial.println("Start is being held");
  if (ps2x.Button(PSB_SELECT))
    Serial.println("Select is being held");

  // print stick value IF TRUE
  if (ps2x.Button(ORANGE_FRET))
  {
    Serial.print("Wammy Bar Position:");
    Serial.println(ps2x.Analog(WHAMMY_BAR), DEC);
  }
}
else
{
  // DualShock Controller
  // read controller and set large motor to spin at 'vibrate' speed
  ps2x.read_gamepad(false, vibrate);

  // will be TRUE as long as button is pressed
  if (ps2x.Button(PSB_START))
    Serial.println("Start is being held");
  if (ps2x.Button(PSB_SELECT))
    Serial.println("Select is being held");

  // will be TRUE as long as button is pressed
  if (ps2x.Button(PSB_PAD_UP))
  {
    speed_go = k + chance ;
    forward_45_left ();
    Serial.println ( String ("forward_45_left: ") + speed_go  ) ;

  }
  if (ps2x.Button(PSB_PAD_RIGHT))
  {
    Serial.print("Right held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
  }
  if (ps2x.Button(PSB_PAD_LEFT))
  {
    Serial.print("LEFT held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
  }
  if (ps2x.Button(PSB_PAD_DOWN))
  {
    speed_go = k + chance ;
    backward_45_right ();
    Serial.println ( String ("backward_45_left: ") + speed_go  ) ;

  }

  // this will set the large motor vibrate speed based on how hard you press the blue (X) button
  vibrate = ps2x.Analog(PSAB_BLUE);

  // will be TRUE if any button changes state (on to off, or off to on)
  if (ps2x.NewButtonState())
  {

    if (ps2x.Button(PSB_GREEN)) {
      digitalWrite ( action1 , !digitalRead (action1 ));
      if ( digitalRead ( action1) )
        Serial.println("nang: ");
      else
        Serial.println("ha: ");
    }

    // will be TRUE if button was JUST pressed
    if (ps2x.ButtonPressed(PSB_RED))
    {
      digitalWrite ( action3 , !digitalRead (action3 ));
      if ( digitalRead ( action3) )
        Serial.println("day ra ");
      else
        Serial.println("thu vo ");
    }
    // will be TRUE if button was JUST released
    if (ps2x.ButtonReleased(PSB_PINK))
    {
      digitalWrite ( action2 , !digitalRead (action2 ));
      if ( digitalRead ( action2) )
        Serial.println("gap: ");
      else
        Serial.println("nha: ");
    }

    // will be TRUE if button was JUST pressed OR released
    if (ps2x.NewButtonState(PSB_BLUE))
    {
      Serial.println("X just changed");
    }

    // print stick values if either is TRUE

  }
  delay(50);

  



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
void sideways_right ()
{
  mortor1_forward () ;
  mortor2_backward () ;
  mortor3_forward() ;
  mortor4_backward () ;
  Serial.println (" sideways right ok!! ");

}
void sideways_left ( )
{
  mortor1_backward () ;
  mortor2_forward() ;
  mortor3_backward () ;
  mortor4_forward () ;
  Serial.println  (" sideways left ok!! ") ;
}
void turn_left ()
{
  mortor1_backward () ;
  mortor3_forward () ;
  mortor4_forward () ;
  mortor2_backward () ;
  Serial.println ("turn left ok!! " );
}
void turn_right  ()
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
