void delay1 (char);
void digit1(char);
void digit2(char);
void digit3(char);
void digit4(char);
void port_initialization(void);

void port_initialization(void) {
    volatile char *dirf, *dirk, *dirb, *dirl, *outf, *outk, *inl;
    dirf = (volatile char *)0x30;
    dirb = (volatile char *)0x24;
    dirk = (volatile char *)0x107;
    dirl = (volatile char *)0x10a;
    *dirf = 0xff; 
    *dirb = 0xff;
    *dirk = 0x0f; 
    *dirl = 0x00;
    outf = (volatile char *)0x31; 
    inl = (volatile char *)0x109;
    outk = (volatile char *)0x108; 
}

void delay1(char num) {
    volatile long i;
    while (num) {
        for (i = 0; i < 200; i++);
        num--;
    }
}

void digit1(char num) {
    volatile char *outf, *outk;
    outf = (volatile char *)0x31; 
    outk = (volatile char *)0x108;     
    *outk = 0x0f; // Turn off all digits
    *outf = num;  // Set the segments        
    *outk = 0x0e; // Turn on the first digit
}

void digit2(char num) {
    volatile char *outf, *outk;
    outf = (volatile char *)0x31; 
    outk = (volatile char *)0x108;    
    *outk = 0x0f; // Turn off all digits
    *outf = num;  // Set the segments
    *outk = 0x0d; // Turn on the second digit
}

void digit3(char num) {
    volatile char *outf, *outk;
    outf = (volatile char *)0x31; 
    outk = (volatile char *)0x108;    
    *outk = 0x0f; // Turn off all digits
    *outf = num;  // Set the segments
    *outk = 0x0b; // Turn on the third digit
}

void digit4(char num) {
    volatile char *outf, *outk;
    outf = (volatile char *)0x31; 
    outk = (volatile char *)0x108;    
    *outk = 0x0f; // Turn off all digits
    *outf = num;  // Set the segments
    *outk = 0x07; // Turn on the fourth digit
}
