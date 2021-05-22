//Sanket Ghodake
// include the library code:
#include <LiquidCrystal.h>
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

/* initialize the library by associating any needed LCD interface pin with the arduino pin number it is connected to*/
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 =7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  String txtMsg = "Elevator with Alert System";
  lcd.begin(16, 2);// set up the LCD's number of columns and rows:
  lcd.print(txtMsg);// Print a message to the LCD.
  delay(300); // Delay to see what printed on display for some time
  for(int i=16 ;i<(txtMsg.length());i++){
    lcd.scrollDisplayLeft(); // scrolls txt to left one space
    delay(100); // to show scrolling action slowly
    }
//  lcd.setCursor(0, 1);
//  lcd.print("TE Mini Project");
}

void loop() {
  
}
