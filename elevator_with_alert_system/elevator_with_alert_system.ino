//Sanket Ghodake

#include <LiquidCrystal.h>

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 =7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int analog_read_O2 = A1;
int analog_read_load_cell = A2;
int analog_read_LDR = A3;
int led_pin_red = 13;
int led_pin_green = 12;
int buzzer_pin = 3;

float O2,load_cell,ldr,O2_percentage,weight;

/*O2 Sensor Look up table:  
*  O2 0.0->0% and 0.45->21% and 0.98->30% then input->? 
*   f(x)= 60.2978x-30.2914x^2
*/

/*Weight Look up table:  
*  reading 0mV->0kg and 20mV->400kg then input->? 
*   f(x)= 20000x
*/

const float ldr_limit = 1.02; //turn on light below this value
const float load_cell_max = 15; // 20mV for 400kg then 320 kg(80%) is remainder
const float o2_sensor_max = 0.50; //ideal 0.45 at 21%
const float o2_sensor_min = 0.40;

void setup() {
  lcd.begin(20, 4);
  pinMode(analog_read_O2,INPUT);
  pinMode(analog_read_load_cell,INPUT);
  pinMode(analog_read_LDR,INPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(led_pin_red, OUTPUT);
  pinMode(led_pin_green, OUTPUT);
  analogReference(INTERNAL); // Using ADC range 0-1.1V -> https://www.arduino.cc/reference/en/language/functions/analog-io/analogreference/ 
  delay(100);
}
void loop() {
   // stopAlarm();
  
  
   O2= (float)analogRead(analog_read_O2)/1023.0*1.1;
   load_cell =  (float)analogRead(analog_read_load_cell)/1023.0*1.1;
   ldr =  (float)analogRead(analog_read_LDR)/1023.0*1.1;
   
   O2_percentage = (60.2978*O2)-(30.2914*O2*O2);
   weight = 20000*load_cell;
   
   lcd.setCursor(0,0);
   lcd.print("O2 Level:");
   lcd.print(O2_percentage);
    
   if(O2_percentage > 24 ){
    lcd.setCursor(0,1);
    lcd.print("Level is little high");
    }
   else if(O2_percentage < 10 ){
    lcd.setCursor(0,1);
    lcd.print("Level is too low");
    pressAlarm();
    }
   else if(O2_percentage < 18 ){
    lcd.setCursor(0,1);
    lcd.print("Level is little low");
    }
   else{
    lcd.setCursor(0,1);
    lcd.print("Level is good");
    }
   
   lcd.setCursor(0,2);
   lcd.print("Weight =");
   lcd.print(weight);
   lcd.print("Kg");
   if(weight > 360 ){
    lcd.setCursor(0,3);
    lcd.print("OVERLOADED");
    pressAlarm();
    }
   else if(weight > 320 ){
    lcd.setCursor(0,3);
    lcd.print("80% weight capacity");
    }
   else if(weight < 320 ){
    lcd.setCursor(0,3);
    lcd.print("Weigh should <320kg");
    }
   else if (weight == 0){
    lcd.setCursor(0,3);
    lcd.print("Lift Empty");
    turnOffLight();
    }

   if(ldr<1.02 && weight>0){
    turnOnLight();
    }
   else{
    turnOffLight();
   }
   
   delay(1000);
   lcd.clear();
   stopAlarm();
   
}

void pressAlarm(){
  digitalWrite(led_pin_red,HIGH);
  digitalWrite(buzzer_pin,HIGH);
}
void stopAlarm(){
  digitalWrite(led_pin_red,LOW);
  digitalWrite(buzzer_pin,LOW);
}
void turnOffLight(){
  digitalWrite(led_pin_green,LOW);
}
void turnOnLight(){
  digitalWrite(led_pin_green,HIGH);
}
