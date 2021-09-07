int RPWM = 3;
int LPWM = 4;
int R_EN = 22 ;
int L_EN = 23 ;
int speedr = 255 ;
int speedl = 200 ;

void setup() {
  pinMode (R_EN , OUTPUT ) ;
  pinMode (L_EN , OUTPUT );
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);

}
void loop() {
 
  digitalWrite (LPWM , HIGH );
  digitalWrite (RPWM ,
  //analogWrite ( R_EN , 250 ) ;
  //analogWrite ( L_EN , 0 ) ;
  delay (5000 );
  digitalWrite ( RPWM , HIGH ) ;
  //analogWrite (LPWM , 200) ;
  delay ( 5000);
  
  

}
