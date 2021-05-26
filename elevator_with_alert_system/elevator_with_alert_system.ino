/*! Project: Elevator with Smart Alert System 
 *
 * @author     Sanket Sunil Ghodake
 * @date       2021/05/22
 *
 * \subsection Aim
 * To interface load cell, LDR and air-oxygen-sensor with microcontroller 
 * to make appropriate alerts(like overload, low oxygen level) while we are in elevator
 *
 *\subsection Proteus Simulation
 * Used Proteus 8.0 Professional
 * AVR ATmega 328p:
 *    Microcontroller 
 * LCD LM044L:
 *    Display readings.
 * Oxygen sensor: (All readings considered w.r.t to LuminOX LOX‐2 25% Oxygen Sensor)
 *    To measure the air-oxygen present in elevator. Normal air contains 21% oxygen. Sensor measures 0-25% oxygen.
 *    As sensor not available in proteus, we make certain replacement to this simulation part
 *    Sensor o/p range is 0-0.98V so in simulation output part of senor is dc v/g source of 1V with
 *    potentiometer to give output between range 0-1V.
 * Load Cell: (Refer Report part to get info about how load cells are used)
 *    To measure present weight in elevator, and displaying it on screen. It also checks for 'no load' and 'overload' condition.
 *    HX711 24bit ADC is not worked in proteus, it amplifies load cell o/p and performed 24 bit ADC to it and o/p it.
 *    Load cell o/p range : 0-20mV so in simulation output part of senor is dc v/g source of 20mV with
 *    potentiometer to give output between range 0-20mV.(Not amplifying signal so accuracy reduces)
 * LDR : 
 *    To control lights depending on light intensity of surrounding environment.
 * Speaker :
 *    Alarms according to different conditions 
 * Green LED:
 *    To show turnig on/off lights
 * Red LED:
 *    Alarm pupose
 *
 * \subsection Connections in proteus simulation, with Arduino UNO board respectiv pins on AVR ATmega 328p 
 * Speaker 				:  IO3 				:   PD3
 * Green LED 			:  IO12 			:   PB4
 * Red LED 				:  IO13 			:	  PB5
 * RS      				:  IO8 				:   PB0
 * E    				  :  IO9 				:   PB1
 * D4-D7				  :  IO4-IO7 		:		PD4-PD7
 * LDR o/p				:  A3 				:   PC3
 * O2 o/p				  :  A1 				:   PC1
 * Load Cell o/p	:  A2 				:   PC2
*/

/*  LIQUID CRYSTAL LIBRARY:
 *   
 *  To use this library ->
 *      #include <LiquidCrystal.h>
 *      
 * The LiquidCrystal library works with all LCD displays that are compatible with the Hitachi HD44780 driver.
 * For detail explanation - https://www.arduino.cc/en/Reference/LiquidCrystal
 * 
 * 0 being the first column | 0 being the first row
 * 
 * Functions:
 * 1) LiquidCrystal(rs, enable, d4, d5, d6, d7) ->Creates a variable of type LiquidCrystal: LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
 * 2) lcd.begin(cols, rows) -> Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display. 
 *                  begin() needs to be called before any other LCD library commands.
 * 3) lcd.clear() -> Clears the LCD screen and positions the cursor in the upper-left corner.
 * 4) lcd.home() -> Positions the cursor in the upper-left of the LCD. That is, use that location in outputting subsequent text to the display.
 *                  To also clear the display, use the clear() function instead.
 * 5) lcd.setCursor(col, row) -> Position the LCD cursor; that is, set the location at which subsequent text written to the LCD will be displayed.
 * 6) lcd.write(data) -> Write a character to the LCD.
 * 7) lcd.print(data) -> Prints text to the LCD.
 * 8) lcd.print(data, BASE) -> BASE (optional): the base in which to print numbers: BIN for binary (base 2), DEC for decimal (base 10), 
 *                  OCT for octal (base 8), HEX for hexadecimal (base 16).
 * 9) lcd.cursor() -> Display the LCD cursor: an underscore (line) at the position to which the next character will be written.                
 * 10) lcd.noCursor()-> Hides the LCD cursor.
 * 11) lcd.blink() -> Display the blinking LCD cursor
 * 12) lcd.noBlink() -> Turns off the blinking LCD cursor.
 * 13) lcd.display() -> Turns on the LCD display, after it's been turned off with noDisplay(). 
 *                  This will restore the text (and cursor) that was on the display
 * 14) lcd.noDisplay() -> Turns off the LCD display, without losing the text currently shown on it.
 * 15) lcd.scrollDisplayLeft() -> Scrolls the contents of the display (text and cursor) one space to the left.
 * 16) lcd.scrollDisplayRight() -> Scrolls the contents of the display (text and cursor) one space to the right.
 * 17) lcd.autoscroll() -> Turns on automatic scrolling of the LCD. 
 * 18) lcd.noAutoscroll() -> Turns off automatic scrolling of the LCD.
 * 19) lcd.leftToRight() -> Set the direction for text written to the LCD to left-to-right, the default.
 * 20) lcd.rightToLeft() -> Set the direction for text written to the LCD to right-to-left
 * 21)*lcd.createChar(num, data) -> >>TODO LATER<< <-
 */

/*
 * Analog Input:
 * 1) Analog Input Pins -> https://www.arduino.cc/en/Tutorial/Foundations/AnalogInputPins
 * 2) analogRead(pin) -> Reads the value from the specified analog pin
 * 3) analogReference(type) -> Configures the reference voltage used for analog input 
 *               (i.e. the value used as the top of the input range).
 *               type: which type of reference to use (see list of options in the description).
 *               Don’t use anything less than 0V or more than 5V for external reference voltage 
 *               on the AREF pin! If you’re using an external reference on the AREF pin, you must set the
 *               analog reference to EXTERNAL before calling analogRead(). Otherwise, you will short together
 *               the active reference voltage (internally generated) and the AREF pin, possibly damaging the 
 *                microcontroller on your Arduino board.
 *  4) analogReadResolution(bits) -> Sets the size (in bits) of the value returned by analogRead().
 *  5) analogWrite(pin, value) -> Writes an analog value (PWM wave) to a pin.
 *                https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
*/

/*O2 Sensor Look up table:  
*  O2 0.0->0% and 0.45->21% and 0.98->30% then input->? 
*   f(x)= 60.2978x-30.2914x^2
*/

/*Weight Look up table:  
*  reading 0mV->0kg and 20mV->400kg then input->? 
*   f(x)= 20000x
*/
#include <LiquidCrystal.h>

/* initialize the library by associating any needed LCD interface pin with the arduino pin number it is connected to*/
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 =7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int analog_read_O2 = A1;
int analog_read_load_cell = A2;
int analog_read_LDR = A3;
int led_pin_red = 13;
int led_pin_green = 12;
int buzzer_pin = 3;

float O2,load_cell,ldr,O2_percentage,weight;//vairables required for calculations

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
  //Converting digital values to analog reading
   O2= (float)analogRead(analog_read_O2)/1023.0*1.1;
   load_cell =  (float)analogRead(analog_read_load_cell)/1023.0*1.1;
   ldr =  (float)analogRead(analog_read_LDR)/1023.0*1.1;
   
  //Based on the euations stated above
   O2_percentage = (60.2978*O2)-(30.2914*O2*O2);
   weight = 20000*load_cell;
   
  //logic part:
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

//Useful functions
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
