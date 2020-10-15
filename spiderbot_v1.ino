#include <Servo.h>

#define srv_rodilla_izq_delantera PA0
#define srv_cadera_izq_delantera PA1

#define srv_rodilla_der_delantera PA2
#define srv_cadera_der_delantera PA3

#define srv_rodilla_izq_trasera PA6
#define srv_cadera_izq_trasera PA7

#define srv_rodilla_der_trasera PB0
#define srv_cadera_der_trasera PB1

#define joystick_x_pin PA4
#define led_pin PA9

#define park_pin PB7
#define test_function_pin PB6


Servo rodilla_izq_delantera;
Servo cadera_izq_delantera;

Servo rodilla_der_delantera;
Servo cadera_der_delantera;

Servo rodilla_izq_trasera;
Servo cadera_izq_trasera;

Servo rodilla_der_trasera;
Servo cadera_der_trasera;

bool park_flag;
bool avanzar_flag;
int valor_x;
bool test_function_flag;
long chrono;
long chrono_led;
long chrono_test;
int secuencia_paso=0;
int led_brillo=0;




void setup() {

  pinMode(PB7, INPUT_PULLUP);
  pinMode(PB6, INPUT_PULLUP);

  pinMode(joystick_x_pin,INPUT);
  pinMode(led_pin,OUTPUT);
  
  rodilla_izq_delantera.attach(srv_rodilla_izq_delantera);
  cadera_izq_delantera.attach(srv_cadera_izq_delantera);
  
  rodilla_der_delantera.attach(srv_rodilla_der_delantera);
  cadera_der_delantera.attach(srv_cadera_der_delantera);
  
  rodilla_izq_trasera.attach(srv_rodilla_izq_trasera);
  cadera_izq_trasera.attach(srv_cadera_izq_trasera);
  
  rodilla_der_trasera.attach(srv_rodilla_der_trasera);
  cadera_der_trasera.attach(srv_cadera_der_trasera);


  park_flag = digitalRead(PB7);
  test_function_flag=digitalRead(test_function_pin);
  chrono=millis();
  chrono_test=millis();
  chrono_led=millis();

}




void loop()
{

 park_flag = digitalRead(PB7);
 test_function_flag=digitalRead(test_function_pin);

if(test_function_flag)
  {
    test_servo();  
  }
  else
  {   
    if ( !park_flag)
      { 
        gracia();  }
       else
      {
        park();
      }
   }
ctrl_led();

}



void park()
{
  secuencia_paso=0;
     rodilla_izq_delantera.write(45);
     cadera_izq_delantera.write(135);
     
     rodilla_der_delantera.write(135);
     cadera_der_delantera.write(45);
        
     rodilla_izq_trasera.write(135);
     cadera_izq_trasera.write(45);

     rodilla_der_trasera.write(45);
     cadera_der_trasera.write(135);
     
  }

void ctrl_led()
{
if(chrono_led-millis()>66)
  {
    chrono_led=millis();
    int valor_joystick=analogRead(joystick_x_pin);
    led_brillo=map(valor_joystick,0,4095,0,65535);
    analogWrite(led_pin,led_brillo);
  }
}
  

void test_servo()
{

if(chrono_test-millis()>200)
  {
    chrono_test=millis();
    int valor_joystick=analogRead(joystick_x_pin);
    int angulo=map(valor_joystick,0,4095,0,180);
    cadera_izq_delantera.write(angulo);
    cadera_der_delantera.write(angulo);
    cadera_izq_trasera.write(angulo);
    cadera_der_trasera.write(angulo);
    rodilla_izq_delantera.write(angulo);
    rodilla_der_delantera.write(angulo);
    rodilla_izq_trasera.write(angulo);
    rodilla_der_trasera.write(angulo);
     
  }
}



void gracia()
{
  if ((millis() - chrono) > 150)
  { chrono = millis();
    
 switch (secuencia_paso)
{
      case 0:
      rodilla_izq_delantera.write(60);
      cadera_izq_delantera.write(100);
        secuencia_paso++;
        break;
      
      case 1:
      rodilla_izq_delantera.write(45);
      rodilla_izq_trasera.write(112);
    
      secuencia_paso++;
        break;

      case 2:
     cadera_izq_trasera.write(10);
      rodilla_izq_trasera.write(135);
    
      secuencia_paso++;
        break;
      
      case 3 :
      rodilla_der_delantera.write(112);
      cadera_der_delantera.write(80);
         secuencia_paso++;
      break;
  
  case 4:
      rodilla_der_delantera.write(135);
      rodilla_der_trasera.write(60);
    
      secuencia_paso++;
        break;

  case 5 :
      cadera_der_trasera.write(170);
      rodilla_der_trasera.write(45);

      
     secuencia_paso++;
      break;
  
  case 6:
      cadera_izq_delantera.write(135);
      cadera_izq_trasera.write(45);
      cadera_der_delantera.write(45);
      cadera_der_trasera.write(135);
      
        secuencia_paso=0;
        break;
case 7:
      secuencia_paso++;
        break;
case 8:
      secuencia_paso++;
        break;
  case 9:
      secuencia_paso++;
        break;
case 10:
      secuencia_paso++;
        break;
case 11:
      secuencia_paso++;
        break;

  case 12:
        break;

  }
  }
}
