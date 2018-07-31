#include <Keypad.h>
#include <PinChangeInt.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd = LiquidCrystal(0,0,0,0,0,0,0,0,0,0); //placeholder gives global scope

void setup() {
  motor_setup();
  lcd = lcd_setup();
  encoder_setup();
  keypad_serial_setup();
}

char incomingByte = 0;
volatile int machine_state = 0;
bool state_state = 1;
char my_string[300] = "Enter wire length (ft): ";
void loop() {
  switch (machine_state){
    case 0:
      if(state_state){
        lcd.home();
        lcd.cursor();
        lcd_scroll_string(my_string,0);
        state_state = 0;
      }
      break;
    case 1:
      break;
    case 2:
      break;
  }
  
  /*
  while(1){



    
    motor_speed(0);
    
    print_incoming_byte();
    
    lcd.setCursor(10,0);
    lcd.print(get_CW());
    lcd.setCursor(11,1);
    lcd.print(get_CCW());
    delay(100);
  }*/
}


