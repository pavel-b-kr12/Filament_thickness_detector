//range 280,243 (even light from monitor in no-light room) ... 595 (complately dark)
//to use w https://pavel-b-kr12.github.io/serial_com_port_view_online/serial_com_port_view_online.htm
//mod from http://mauromombelli.com/2015/02/20/TCD1201D.html

#define SH	PORTB0	//digital pin 8
#define PHI1	PORTB1	//digital pin 9 (PWM)
#define PHI2	PORTB2	//digital pin 10 (PWM)
#define RS	PORTB3	//digital pin 11 (PWM)
#define BT	PORTB4	//digital pin 12
#define OS	A0	//A0

byte sadc[1024];  // signal output values read
int sdacCounter;

void setup() {
  //Serial.begin(115200);
  Serial.begin(1000000);

  pinMode(OS, INPUT);
  // set all OUTPUT
  DDRB = B00011111;
  // take all to LOW
  PORTB = B00000000;
  
  // set up the ADC
  ADCSRA &= ~(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // remove bits set by Arduino library, prescaler = 2
  
  unsigned long start = micros();
  for(int i=0; i < 10000; i++){
    PORTD = B00001000;
    PORTD = B00000000;
  }
  start = micros()-start;
  
  //clockNoClock();
}

void loop() {
	//runCCD();
  //maybe here you want a couple of read to decrease the integration time caused by the long serial write
  readCCD();
  //Serial.println();

  //here we write 1024 byte @ 115200baud: this mean 89mS
  //

// for (int i=0; i<1024;i+=1){
    // Serial.write(sadc[i]);
  // }
  // Serial.flush();
  //noInterrupts();

  // Serial.flush();
  //interrupts();
  
  delay(10);
}

inline void readCCD() {
  
  noInterrupts();
  
  sdacCounter = -1;

  PORTB = (0 << RS) | (1 << BT) | (1 << PHI2) | (0 << PHI1) | (0 << SH);
  PORTB = (0 << RS) | (1 << BT) | (0 << PHI2) | (1 << PHI1) | (0 << SH);
  
  for (byte b = 0; b < 1; b++){
    PORTB = (0 << RS) | (1 << BT) | (0 << PHI2) | (1 << PHI1) | (1 << SH);
    PORTB = (1 << RS) | (0 << BT) | (0 << PHI2) | (1 << PHI1) | (1 << SH);
    PORTB = (1 << RS) | (1 << BT) | (0 << PHI2) | (1 << PHI1) | (1 << SH);
    PORTB = (0 << RS) | (1 << BT) | (0 << PHI2) | (1 << PHI1) | (1 << SH);
  }
  
  for (byte b = 0; b < 1; b++){
    PORTB = (0 << RS) | (1 << BT) | (0 << PHI2) | (1 << PHI1) | (0 << SH);
    PORTB = (1 << RS) | (0 << BT) | (0 << PHI2) | (1 << PHI1) | (0 << SH);
    PORTB = (1 << RS) | (1 << BT) | (0 << PHI2) | (1 << PHI1) | (0 << SH);
    PORTB = (0 << RS) | (1 << BT) | (0 << PHI2) | (1 << PHI1) | (0 << SH);
  }
  
  //start reading
  for (int i=0; i<16;i++){
    read1Low();
    read1High();
  }


  sdacCounter++;
  for (int i=0; i<1024;i++){
    sdacCounter++;
    read1Low();
    read1High();
	
	 // if(i==140){
	// Serial.println(analogRead(OS));
	 // Serial.println(sadc[i]);
	 
	 // }
	// if(i<20){
	// Serial.print(sadc[i]); Serial.print("\t");
	// }
  }
  Serial.write(255+'0');
  //Serial.println();
  //Serial.flush();
  
  for (int i=0; i<7;i++){
    read1Low();
    read1High();
  }
  
  
   // for (int i=0; i<10;i+=1){
     // Serial.print(sadc[i]); Serial.print("\t");
   // }
   // Serial.println();
   
  interrupts();
}


inline void read1Low(){
  PORTB = (0 << RS) | (0 << BT) | (1 << PHI2) | (0 << PHI1) | (0 << SH);
  //if (sdacCounter>>1)
  //sadc[sdacCounter] = analogRead(OS);//>>2; //ADC is 10 bit, so keep 8 MSB

if(sdacCounter>=0 && sdacCounter<1024)
//if(sdacCounter>=0 && sdacCounter<3)
{
 int v=(280-analogRead(OS))/2;
 v+=254;
 if(v==255) v=0;
 Serial.write(v); 

		//Serial.print(v); Serial.print("\t");
		//Serial.print(analogRead(OS)); Serial.print("\t");
}

  PORTB = (1 << RS) | (0 << BT) | (1 << PHI2) | (0 << PHI1) | (0 << SH);
  PORTB = (1 << RS) | (1 << BT) | (1 << PHI2) | (0 << PHI1) | (0 << SH);
  //PORTB = (0 << RS) | (1 << BT) | (1 << PHI2) | (0 << PHI1) | (0 << SH);
  //PORTB = (0 << RS) | (1 << BT) | (0 << PHI2) | (1 << PHI1) | (0 << SH);
  PORTB = (0 << RS) | (1 << BT) | (0 << PHI2) | (1 << PHI1) | (0 << SH);
  /*
  	if(sdacCounter<30){
		Serial.print(analogRead(OS)); Serial.print("\t");
		//Serial.print((analogRead(OS)-280)/2); Serial.print("\t");
		//Serial.print(analogRead(OS)>>2); Serial.print("\t");
		//Serial.print(analogRead(OS)); Serial.print("\t");
	}
	*/
}

inline void read1High(){
  PORTB = (0 << RS) | (0 << BT) | (0 << PHI2) | (1 << PHI1) | (0 << SH);
  //sadc[sdacCounter] = analogRead(OS);//>>2; //ADC is 10 bit, so keep 8 MSB
//if(sdacCounter>0 && sdacCounter<11)
// {
// Serial.write((analogRead(OS)-241)/2); //Serial.print("\t");
// }
  PORTB = (1 << RS) | (0 << BT) | (0 << PHI2) | (1 << PHI1) | (0 << SH);
  PORTB = (1 << RS) | (1 << BT) | (0 << PHI2) | (1 << PHI1) | (0 << SH);
  //PORTB = (0 << RS) | (1 << BT) | (0 << PHI2) | (1 << PHI1) | (0 << SH);
  //PORTB = (0 << RS) | (1 << BT) | (1 << PHI2) | (0 << PHI1) | (0 << SH);
  PORTB = (0 << RS) | (1 << BT) | (1 << PHI2) | (0 << PHI1) | (0 << SH);
  
  	// if(sdacCounter==10){
		// Serial.print(analogRead(OS)); Serial.print("\t");
		// Serial.print(analogRead(OS)>>2); Serial.print("\t");
		// Serial.println(analogRead(OS));
	// }
}
