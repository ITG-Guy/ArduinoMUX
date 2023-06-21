#include <Adafruit_SSD1306.h>
#include <splash.h>

#define PIN_NUM_01 1
#define PIN_NUM_02 2
#define PIN_NUM_03 3
#define PIN_NUM_04 4
#define PIN_NUM_05 5
#define PIN_NUM_06 6
#define PIN_NUM_07 7
#define PIN_NUM_08 8
#define PIN_NUM_09 9
#define PIN_NUM_10 10
#define PIN_NUM_11 11
#define PIN_NUM_12 12
#define PIN_NUM_13 13

/* Example 00 For Display */
#include <Wire.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     4
#define SERIAL_LOGGING true
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//////////////////////////////

/* Example 04 serial read*/
char cmd;

/* Example 02 Voltage sensor enabled. */
float vout = 0.0; 
float vin = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;

/* Example 03 Multimeter enabled*/
//Mux control pins
int s0_m = 13;
int s1_m = 12;
int s2_m = 11;
int s3_m = 10;

int s0_p = 7;
int s1_p = 6;
int s2_p = 5;
int s3_p = 4;

int current_mux_channel = 15;

/* Example 03 Multimeter enabled*/
void selectChannel(int channel){
  int controlPin_m[] = {s0_m, s1_m, s2_m, s3_m}; 
  int muxChannel_m[16][4]={ {0,0,0,0},  
                            {1,0,0,0}, //channel 1 
                            {0,1,0,0}, //channel 2 
                            {1,1,0,0}, //channel 3 
                            {0,0,1,0}, //channel 4 
                            {1,0,1,0}, //channel 5 
                            {0,1,1,0}, //channel 6 
                            {1,1,1,0}, //channel 7 
                            {0,0,0,1}, //channel 8 
                            {1,0,0,1}, //channel 9 
                            {0,1,0,1}, //channel 10 
                            {1,1,0,1}, //channel 11 
                            {0,0,1,1}, //channel 12 
                            {1,0,1,1}, //channel 13 
                            {0,1,1,1}, //channel 14 
                            {1,1,1,1} //channel 15 
                            };
  int controlPin_p[] = {s0_p, s1_p, s2_p, s3_p}; 
  int muxChannel_p[16][4]={ {0,0,0,0},  
                            {1,0,0,0}, //channel 1 
                            {0,1,0,0}, //channel 2 
                            {1,1,0,0}, //channel 3 
                            {0,0,1,0}, //channel 4 
                            {1,0,1,0}, //channel 5 
                            {0,1,1,0}, //channel 6 
                            {1,1,1,0}, //channel 7 
                            {0,0,0,1}, //channel 8 
                            {1,0,0,1}, //channel 9 
                            {0,1,0,1}, //channel 10 
                            {1,1,0,1}, //channel 11 
                            {0,0,1,1}, //channel 12 
                            {1,0,1,1}, //channel 13 
                            {0,1,1,1}, //channel 14 
                            {1,1,1,1} //channel 15 
                            };
                             //loop through the 4 sig 
  for(int i = 0; i < 4; i ++){ 
    digitalWrite(controlPin_m[i], muxChannel_m[channel][i]);
    digitalWrite(controlPin_p[i], muxChannel_p[channel][i]); 
  } 
}

// int readMux(int channel)  { 
//   //read the value at the SIG pin 
//   int val = analogRead(SIG_pin); //return the value 
//   return val; 
// } 

void setup() {
  // put your setup code here, to run once:
  /* Example 00 Display */
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  /* Example 01 LED light up and down.*/
  // pinMode(PIN_NUM_13,OUTPUT);
  // pinMode(PIN_NUM_12,OUTPUT);

  /* Example 02 Voltage sensor enabled. */
  // Serial.begin(9600);  // To serial communication with host pc.
  pinMode(A0, INPUT);

  /* Example 03 Multimeter enabled*/
  pinMode(s0_m, OUTPUT);
  pinMode(s1_m, OUTPUT);
  pinMode(s2_m, OUTPUT);
  pinMode(s3_m, OUTPUT);

  pinMode(s0_p, OUTPUT);
  pinMode(s1_p, OUTPUT);
  pinMode(s2_p, OUTPUT);
  pinMode(s3_p, OUTPUT);

  digitalWrite(s0_m, LOW);
  digitalWrite(s1_m, LOW);
  digitalWrite(s2_m, LOW);
  digitalWrite(s3_m, LOW);

  digitalWrite(s0_p, LOW);
  digitalWrite(s1_p, LOW);
  digitalWrite(s2_p, LOW);
  digitalWrite(s3_p, LOW);

  selectChannel(current_mux_channel);
#if SERIAL_LOGGING 
  Serial.begin(9600);  // To serial communication with host pc.
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
  /* Example 01 LED light up and down.*/
  // digitalWrite(PIN_NUM_13,HIGH);
  // delay(1000);
  // digitalWrite(PIN_NUM_13,LOW);
  // delay(1000);
  // digitalWrite(PIN_NUM_12,HIGH);
  // delay(1000);
  // digitalWrite(PIN_NUM_12,LOW);
  // delay(1000);

  /* Example 02 Voltage sensor enabled. */
    value = analogRead(A0);
    vout = (value * 5.0) / 1024.0;  //The fomula for calculating the voltage value.
    vin = vout / ( R2 / ( R1 + R2) );
#if SERIAL_LOGGING
    Serial.print("V: ");
    Serial.println(vin); //print out the voltage.
#endif

  /* Example 00 Display*/
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,28);
    display.print("MUX_CH: ");
    display.println(current_mux_channel);
    display.print("V: ");
    display.println(vin);
    //display.println("Hello world!");
    

  /* Example 04 Serial read */
   if(Serial.available()>0){

    String serial_data = Serial.readString();  // 데이터를 문자열로 읽기
    Serial.println(serial_data);  // 읽은 데이터를 시리얼 모니터에 출력하기
    display.print(serial_data);
    if (serial_data.toInt()>=0 && serial_data.toInt()<16)
    {
      current_mux_channel = serial_data.toInt();
      selectChannel(current_mux_channel);
    }
   } else {
     display.print("No signal");
   }
    

    display.display();



    delay(1000);

}
