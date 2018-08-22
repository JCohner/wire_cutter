#include <PinChangeInt.h>
#define INA1 7 //D7
#define INA2 4 //D4
#define PWM 5//D5
#define MOTOR_IO A7 //REMOVED THIS FUNCTIONALITY TO FREE UP I2C Pins

int motor_duty = 0;
volatile bool state = 0;
void motor_setup(){
  /*PWM pin init*/
  pinMode(INA1,OUTPUT);
  pinMode(INA2,OUTPUT);
  pinMode(PWM,OUTPUT);

  /*Motor button pin init*/
  pinMode(MOTOR_IO, INPUT);
  attachPinChangeInterrupt(MOTOR_IO, button_press,FALLING);
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

void motor_speed(float m_speed){
  //speed /= 100;
  if (m_speed >= 1.0){
    m_speed = 1.0;
  } else if (m_speed <= 0.0){
    m_speed = 0.0;
  }
  float analog_value = m_speed * 255;
  int motor_pwm = (int) analog_value;
  analogWrite(PWM, motor_pwm);
  
}

