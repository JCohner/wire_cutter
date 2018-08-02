#include <LiquidCrystal.h>
#include <string.h>
#include <stdio.h>

#define LCD_RS 9 //D9
#define LCD_E 10 //D10
#define LCD_D0 11 //D11
#define LCD_D1 12 //D12
#define LCD_D2 8 
#define LCD_D3 6
#define LCD_D4 A3
#define LCD_D5 A2
#define LCD_D6 A1
#define LCD_D7 A0



LiquidCrystal lcd_setup(){
  /*LCD pin init*/
  pinMode(LCD_RS,OUTPUT);
  pinMode(LCD_E,OUTPUT);
  pinMode(LCD_D0,OUTPUT);
  pinMode(LCD_D1,OUTPUT);
  pinMode(LCD_D2,OUTPUT);
  pinMode(LCD_D3,OUTPUT);
  pinMode(LCD_D4,OUTPUT);
  pinMode(LCD_D5,OUTPUT);
  pinMode(LCD_D6,OUTPUT);
  pinMode(LCD_D7,OUTPUT);
  LiquidCrystal lcd(LCD_RS ,LCD_E, LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
  lcd.begin(20,4);

  return lcd;
}

void lcd_scroll_string(char * str, int row){
  int len = strlen(str);
  char string_copy[300];
  strcpy(string_copy, str);
  lcd.setCursor(0,row);
  for (int ii = 0; ii < (len + 1); ++ii){
    
    for (int jj = 0; jj < 20; ++jj){
      lcd.write(str[((jj+ii) % len)]);
    }

    delay(700);
    lcd.setCursor(0,row); //20 chars up start at row col 0
    
  }
  
  return; 
}

