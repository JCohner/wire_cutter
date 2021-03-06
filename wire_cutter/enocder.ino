#define Interrupt_A 2 //D2
#define Interrupt_B 3 //D3
#define WHEEL_DIAM 6 //in inches 
#include <stdio.h>
float INCHES_PER_COUNT = 0.0117809725; //6.0 * 3.14159 / 1600.0; 

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
  attachInterrupt(digitalPinToInterrupt(Interrupt_B), quadrature_count_A, CHANGE);
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

long int get_spool_counts(void){
  long int spool_counts = ((long int) CW_count) - ((long int)CCW_count);
  return spool_counts; 
}

void zero_spool_counts(void){
  CW_count = 0;
  CCW_count = 0;
  return;
}

double get_spool_dist(void){
  return ((INCHES_PER_COUNT / 12.0) * ((double) get_spool_counts())); 
}

