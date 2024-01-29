#include <HX711_ADC.h> // need to install 
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // need to install

HX711_ADC LoadCell(2, 0); // parameters: dt pin 6, sck pin 7;
LiquidCrystal_I2C lcd(0x27, 16,2); // 0x27 is the i2c address might different;you can check with Scanner
unsigned long t = 0;
int percent;
float canWeight;
int greenled = 12;
int redled = 13; 
void setup() 
{

    pinMode(redled , OUTPUT);
  pinMode(greenled , OUTPUT);
  Serial.begin(9600);
  LoadCell.begin(); // start connection to HX711
  LoadCell.start(2000); // load cells gets 2000ms of time to stabilize
  LoadCell.setCalFactor(523.0); // calibration factor for load cell => dependent on your individual setup
  lcd.init(); 
  lcd.backlight();
}

void loop() {
  /*
  LoadCell.update(); // retrieves data from the load cell
  float i = LoadCell.getData(); // get output value
  Serial.println(i);
  delay(1000);
  lcd.setCursor(0, 0); // set cursor to first row
  lcd.print("Weight[g]:"); // print out to LCD
  lcd.setCursor(0, 1); // set cursor to second row
  lcd.print(i); // print out the retrieved value to the second row

*/
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; //increase value to slow down serial print activity
  
  //check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      canWeight = LoadCell.getData();
      Serial.print("Load_cell output val: ");
      Serial.println(canWeight); 
      delay(800);
      newDataReady = 0;
      t = millis();
      delay(500);
      percent = (canWeight/ 250) * 100;
      Serial.print("9in percent ");
      Serial.println(percent);
      
    }
   
  }
  //*/
  
  if (canWeight < 10){
      Serial.println("Can is empty ");
      digitalWrite(redled, HIGH);
      digitalWrite(greenled , LOW);
    }
    else {
      //Serial.println("Can is full");
      digitalWrite(greenled, HIGH);
      Serial.println("fully fully");
      digitalWrite(redled, LOW);
    }
    }
    
  