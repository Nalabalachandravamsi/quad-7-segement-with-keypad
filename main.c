#include "ECEN.h"
void setup() {    
  volatile char *outb, *inl, x, first_number, second_number;
  port_initialization();
  outb = 0x25;
  inl = 0x109;
  volatile char row, coloum, count = 0, result = 0, answer, temp1, temp2, temp3;
  volatile long i;    
  volatile char numbers[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67};
  volatile char digit[] = {0x06, 0x66, 0x07, 0x5b, 0x6d, 0x7f, 0x3f, 0x4f, 0x7d, 0x67, 0x70, 0x40, 0x76, 0xc0};
  while (1) {
    for (row = 0; row < 4; row++) {
      *outb = 1 << row; 
      x = *inl; 
      if (x ) { 
        delay1(500); // Additional delay for debouncing
        x = *inl; 
        if (x != 0) { 
          for (coloum = 0; coloum < 4; coloum++) {
            if (x == (1 << coloum)) {                           
              if (count == 0) {    // Display first number
                if (coloum == 0) {
                  temp1 = digit[row];
                  digit2(digit[row]);
                }
                if (coloum == 1) {
                  temp1 = digit[3 + row];
                  digit2(digit[3 + row]);
                }
                if (coloum == 2) {
                  temp1 = digit[7 + row];
                  digit2(digit[7 + row]);
                }
                for (int index = 0; index < 10; index++) {
                  if (numbers[index] == temp1) {
                    first_number = index;
                  }
                }
              } else if (count == 1) {   // Display arithmetic symbol
                  if (coloum == 3) {
                    temp2 = digit[10 + row];
                    digit3(digit[10 + row]);
                  }
              } else if (count == 2) {      // Display second number
                  if (coloum == 0) {
                    temp3 = digit[row];
                    digit4(digit[row]);
                  }
                  if (coloum == 1) {
                    temp3 = digit[3 + row];
                    digit4(digit[3 + row]);
                  }
                  if (coloum == 2) {
                    temp3 = digit[7 + row];
                    digit4(digit[7 + row]);
                  }
                  for (int index = 0; index < 10; index++) {
                    if (numbers[index] == temp3) {
                      second_number = index;
                    }
                  }
              }
              count++;
              break;
              }
           }
        }
      }
    }

    if (count > 2) {
      delay1(100); // Debouncing time
      if (temp2 == 0x70) result = first_number + second_number;
      if (temp2 == 0x40) result = first_number - second_number;
      if (temp2 == 0x76) result = first_number * second_number;
      if (temp2 == (0xffffffc0)) result = first_number % second_number;

      if (result > 9) {
        for (int k = 0; k < 100; k++) {
          digit4(numbers[result % 10]);
          delay1(2);
          digit3(numbers[result / 10]);
          delay1(2);
        }
        } else {
          for (int k = 0; k < 100; k++) {
            digit4(numbers[result]);
          }
        }                        
    }
    if(count==0 | count>2){
      digit4(numbers[result % 10]);
      delay1(2);
      digit3(numbers[result / 10]);
      delay1(2);
    }
  }
}

void loop() {
    
}
