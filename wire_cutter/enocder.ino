#define Interrupt_A 2 //D2
#define Interrupt_B 3 //D3

volatile unsigned long int CW_count = 0;
volatile unsigned long int CCW_count = 0;
volatile char curr_state_a = 0;
volatile char curr_state_b = 0;
volatile char prev_state_a;
volatile char prev_state_b;

void encoder_setup(){
  /*Encoder Interrupt pins*/
  pinMode(Interrupt_A, INPUT);
  pinMode(Interrupt_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(Interrupt_A), quadrature_count_A, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(Interrupt_B), quadrature_count_B, CHANGE);
}

void quadrature_count_A(){
  prev_state_a = curr_state_a;
  prev_state_b = curr_state_b;
  curr_state_a = digitalRead(Interrupt_A);
  curr_state_b = digitalRead(Interrupt_B);

  if(curr_state_a == curr_state_b){
   if (curr_state_a == prev_state_a){
     //clockwise rotation
     CW_count++;
   } else {
    //counter-clockwise rotation
    CCW_count++;
   }
  } else {
    if (curr_state_a != prev_state_a){
     //clockwise rotation
     CW_count++;
    } else {
    //counter-clockwise rotation
    CCW_count++;
   }
  }
}

unsigned long int get_CW(void){
  return CW_count;
}

unsigned long int get_CCW(void){
  return CCW_count;
}

unsigned long int get_spool_counts(void){
  return (CW_count - CCW_count);
}

