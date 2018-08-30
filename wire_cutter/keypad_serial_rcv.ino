#include <Wire.h>
#include <string.h>

void keypad_serial_setup(void){
  Serial.begin(9600);
  //pinMode(13,OUTPUT);
  Wire.begin(8); //join i2c bus as slave
  Wire.onReceive(get_keypad_state);
}
void print_incoming_byte(void){
  /* CODE FOR NUM PAD INTERFACE FROM SECOND NANO*/
    if(Serial.available() > 0){
      lcd.clear();
      Serial.readBytes(&incomingByte,1);
      //digitalWrite(LED_BUILTIN,HIGH);
      //Serial.println(i);
      lcd.print(incomingByte);
    }
}

char c;
void get_keypad_state(int howMany){
  if (machine_state == 'A'){
    /*
     * Special case in which we want user input of how many feet to cut
    */
    while (Wire.available()) {
      c = Wire.read();
    }
    if(c == 'D'){
      machine_state = 'D';
      if (strlen(A_prompt_buffer) > 8){
        machine_state = 'E';
        E_flag = 2;
      }
      wire_length = atof(A_prompt_buffer);
      if ((wire_length > 32757) || (wire_length < 0)){
        machine_state = 'E';
        E_flag = 1;
      }
    }
    A_prompt_buffer[A_prompt_buffer_indexer++] = c;
    lcd.print(c);
  } else {
    /*
     * Normal operation, switches between states of the state machine
     * i.e. "load spool" - > "how many feet" -> "operating" -> etc
    */
    while (Wire.available()) {
      c = Wire.read();
    }
    machine_state = c;
  }
  
}

char get_keypad_input(){
  return c;
}

