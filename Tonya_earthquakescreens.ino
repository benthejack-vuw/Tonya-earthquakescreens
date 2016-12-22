//DONT CHANGE THESE, RATHER USE THE NAMES IN SETUP TO SET IT TO THE CORRECT ZONE
//THE RASPBERRY PI USES THESE ADDRESSES SO IT'S IMPORTANT THAT THEY ARE LEFT AS IS
#define ALASKA          1
#define CENTRAL_AMERICA 2
#define SOUTH_AMERICA   3
#define NEW_ZEALAND     4
#define JAPAN           5

//PINS USED FOR OLED SCREEN
#define dc   9
#define rst  8
#define cs   7


// Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>


//Option 2: use the hardware SPI pins (pins 11 & 13)
Adafruit_SSD1351 tft = Adafruit_SSD1351(cs, dc, rst);

bool motor = false;
int earthquakeVibrationTime = 10; //time in seconds

void setup() {

  //THE FOLLOWING LINE YOU NEED TO PUT IN THE CORRECT ZONE BEFORE UPLOADING TO THE ARDUINO
  Wire.begin(5`);
  Wire.onReceive(receiveEvent); // register event
  //--------------------------------------------------------------------------------------

  tft.begin();//begins the OLED screen
  tft.fillScreen(BLACK);
  pinMode(2, OUTPUT);           //for debugging LED - put an led between pin 9 and gnd with a 220ohm resistor for data testing
  digitalWrite(2, LOW);

}

void loop() {
  
  if(motor){
    digitalWrite(2, HIGH);
    delay(earthquakeVibrationTime*1000);
    digitalWrite(2, LOW);
    motor = false;
  }
  
  delay(100);
}


void drawData(int data){
  //YOUR EARTHQUAKE ELLIPSE DRAWING GOES HERE the data variable contains the magnitude of the quake
  //THIS FUNCTION WILL ONLY BE CALLED WHEN THERE IS A QUAKE IN THE CORRECT VICINITY
  
  //-------replace this drawing code, it currently only shows the data variable as text-------------
  tft.fillScreen(BLACK);
  tft.setCursor(0, 5);
  tft.setTextColor(BLUE);
  tft.setTextSize(3);
  tft.print(data);
}

// this function is registered as an event, it is triggered on an I2C commnication to this board.
void receiveEvent(int howMany) {
  int x = Wire.read();    // receive byte as an integer
  drawData(x);
  motor = x > 0;  
}

