
void keypad_serial_setup(void){
  Serial.begin(9600);
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

