#include<stdlib.h>
#include <Wire.h>                  // Include Wire library (required for I2C devices)
#include <LiquidCrystal_I2C.h>     // Include LiquidCrystal_I2C library 
#include <SPI.h>
#include <AD7705.h>
AD7705 ad(8,7);// DRDY,RESET
// SS    10 // CS
// MOSI  11 // DIN
// MISO  12 // DOUT
// SCK   13 // SCLK
 

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows

double readAnalogVoltage(char chn){
  long datVal;
  double retVal;
  ad.setSetup(chn,1,25,0);
  datVal = ad.read_unipolar();
  retVal = 0.007629394*datVal;
  return retVal/100;
}


void setup() {
  ad.conf();
  Serial.begin(9600);
  lcd.init();                        // Initialize I2C LCD module
  lcd.backlight();                   // Turn backlight ON
  lcd.setCursor(0, 0);             
  lcd.print("All init OK!");
  delay(1000);
  lcd.clear();
}


double Chn1 = 0.00;
double Chn2 = 0.00;

char s_buf[16];
char s_buf1[16];

void loop() {
  Chn1 = readAnalogVoltage(1);
  //Chn1 = 5;
  // Chn1 is the HV side voltage
  Chn1 = Chn1 * 2.6 * 12;
  Chn2 = readAnalogVoltage(2);
  //Chn2 = 2.75;
  dtostrf(Chn1,1,4,s_buf);
  sprintf(s_buf1, "HV: %s kV", s_buf);
  Serial.println(s_buf1);
  lcd.setCursor(0, 0);             
  lcd.print(s_buf1);
  lcd.setCursor(0, 1);  
  dtostrf(Chn2,1,3,s_buf);
  sprintf(s_buf1, "Fila: %s V", s_buf);
  lcd.print(s_buf1);
  
  //delay(100);
  //lcd.clear();
}
