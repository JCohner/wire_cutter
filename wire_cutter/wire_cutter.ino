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
volatile char machine_state = '0';
volatile char length_spec_char;
bool state_state_0 = 1;
bool state_state_A = 1;
bool state_state_D = 1;
bool state_state_E = 1;
bool state_state_B = 1;
bool state_state_pound = 1;
bool state_state_C = 1;

char zero_prompt_0[21] = "Load Spool";
char zero_prompt_1[21] = "Press A when done";

char A_prompt_0[21] = "Enter Desired Length";
char A_prompt_1[21] = "Press D when done";
char A_prompt_buffer[21];
volatile int A_prompt_buffer_indexer = 0; //^buffer indexer
volatile double wire_length;

char D_prompt_0[21] = "Desired Length (ft):";
char D_prompt_1[7];
char D_prompt_2[21]= "Press B to begin";

char E_prompt_0[7] = "Error!";
char E_prompt_1_flag1[21] = "input > 32757";
char E_prompt_1_flag2[21] = "input len > 6 chars";
char E_prompt_3[21] = "Press A to reinput";
volatile int E_flag = 0;

char B_prompt_0[21] = "Spooling!";
char B_prompt_1[21] = "Pres # to abort";
char B_prompt_2[21];
double measured;
double desired;
double effort;
double error;
double kp;  

char pound_prompt_0[21] = "Spooling Aborted!";
char pound_prompt_1[21] = "Pres A to reinput";

char C_prompt_0[21] = "Encoder Count Check";
char C_prompt_1[21] = "Counts: ";
char C_prompt_2[21];

char default_prompt[20] = "No Mans Land Fam";

void loop() {
  //Serial.println(machine_state);
  switch (machine_state){
    case '0':
      if(state_state_0){
        lcd.clear();
        lcd.print(zero_prompt_0);
        lcd.setCursor(0,1);
        lcd.print(zero_prompt_1);
        state_state_0 = 0;
      }
      reenable_states(machine_state);
      break;
    case 'A':
      if(state_state_A){
        lcd.clear();
        lcd.print(A_prompt_0);
        lcd.setCursor(0,1);
        lcd.print(A_prompt_1);
        lcd.setCursor(0,2);
        A_prompt_buffer_indexer=0;
        memset(A_prompt_buffer,'\0',sizeof(A_prompt_buffer));
        state_state_A = 0;
      }
      reenable_states(machine_state);
      break;
    case 'D':
      if(state_state_D){
        lcd.clear();
        lcd.print(D_prompt_0);
        lcd.setCursor(0,1);
        lcd.print(wire_length, 5);
        lcd.setCursor(0,2);
        lcd.print(D_prompt_2);
        state_state_D = 0;
      }
      reenable_states(machine_state);
      break;
    case 'E':
      if(state_state_E){
        lcd.clear();
        lcd.print(E_prompt_0);
        lcd.setCursor(0,1);
        if(E_flag == 1){ 
          lcd.print(E_prompt_1_flag1);
        } else if (E_flag == 2){
          lcd.print(E_prompt_1_flag2);
        }

        lcd.setCursor(0,3);
        lcd.print(E_prompt_3);
        
        state_state_E = 0;
      }
      reenable_states(machine_state);
      break;
    case 'B':
      if(state_state_B){
        lcd.clear();
        lcd.print(B_prompt_0);
        lcd.setCursor(0,1);
        lcd.print(B_prompt_1);
        motor_speed(100); 
        state_state_B = 0;
      } 
      measured = get_spool_dist();
      desired = wire_length;
      kp = 1.0;
      while ((measured <= desired) && (machine_state == 'B')){
        measured = get_spool_dist();
        error = (desired - measured)/desired; //some val hoepfully between 1 and 0
        effort = kp * error;
        motor_speed(effort);
        lcd.setCursor(0,2);
        lcd.print(get_spool_dist(),4);
        lcd.print(" (ft)  ");
      }
      lcd.setCursor(0,2);
      lcd.print("Done!      ");
      
      reenable_states(machine_state);
      break;
    case '#':
      if(state_state_pound){
        lcd.clear();
        lcd.print(pound_prompt_0);
        lcd.setCursor(0,1);
        lcd.print(pound_prompt_1);
        motor_speed(0);
        
        state_state_pound = 0;
      }
      reenable_states(machine_state);
      break;
    case 'C':
      if(state_state_C){
        lcd.clear();
        lcd.print(C_prompt_0);
        lcd.setCursor(0,1);
        lcd.print(C_prompt_1);
        motor_speed(0);
        zero_spool_counts();
        state_state_C = 0;
      }
      lcd.setCursor(0,2);
      lcd.print(get_spool_dist(),4);
      lcd.print(" (ft)  ");
      reenable_states(machine_state);
      break;  
    default:
      state_state_0 = 1;
      state_state_A = 1;
      state_state_D = 1;
      state_state_E = 1; 
      state_state_B = 1;
      state_state_C = 1; 
      state_state_pound = 1;  
  }
}

void reenable_states(char state){
  if (state == '0'){
     state_state_A = 1;
     state_state_D = 1;
     state_state_E = 1; 
     state_state_B = 1;
     state_state_C = 1; 
     state_state_pound = 1; 
  } else if (state == 'A'){
    state_state_0 = 1;
    state_state_D = 1;
    state_state_E = 1; 
    state_state_B = 1;
    state_state_C = 1; 
    state_state_pound = 1; 
  } else if (state == 'B'){
    state_state_0 = 1;
    state_state_A = 1;
    state_state_D = 1;
    state_state_E = 1; 
    state_state_C = 1; 
    state_state_pound = 1;  
  } else if (state == 'C'){
    state_state_0 = 1;
    state_state_A = 1;
    state_state_D = 1;
    state_state_E = 1; 
    state_state_B = 1; 
    state_state_pound = 1; 
  } else if (state == 'D'){
    state_state_0 = 1;
    state_state_A = 1;
    state_state_B = 1;
    state_state_E = 1; 
    state_state_C = 1; 
    state_state_pound = 1; 
  } else if (state == 'E'){
    state_state_0 = 1;
    state_state_A = 1;
    state_state_D = 1;
    state_state_B = 1; 
    state_state_C = 1; 
    state_state_pound = 1; 
  } else if (state == '#'){
    state_state_0 = 1;
    state_state_A = 1;
    state_state_D = 1;
    state_state_E = 1; 
    state_state_C = 1; 
    state_state_B = 1; 
  }
}

