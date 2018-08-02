#include <PinChangeInt.h>
#define INA1 7 //D7
#define INA2 4 //D4
#define PWM 5//D5
#define motor_io 8 //D8

int motor_duty = 0;
volatile bool state = 0;
void motor_setup(){
  /*PWM pin init*/
  pinMode(INA1,OUTPUT);
  pinMode(INA2,OUTPUT);
  pinMode(PWM,OUTPUT);

  /*Motor button pin init*/
  pinMode(motor_io, INPUT);
  attachPinChangeInterrupt(motor_io, button_press,FALLING);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(INA1, HIGH);
  digitalWrite(INA2, LOW);
}

void button_press (){
  state = !state;
  
  if (state){
    motor_speed(100);
    digitalWrite(LED_BUILTIN,HIGH);
  } else {
    motor_speed(0);
    digitalWrite(LED_BUILTIN,LOW);
  }
  //analogWrite(PWM,motor_duty);
  
}

void motor_speed(float speed){
  speed /= 100;
  float analog_value = speed * 255;
  int motor_pwm = (int) analog_value;
  analogWrite(PWM, motor_pwm);
  
}
