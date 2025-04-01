#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with I2C address 0x27 and dimensions 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  // Initialize LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  HAND GESTURE");

  // Configure pins
  pinMode(13, OUTPUT); // Indicator LED
  pinMode(8, OUTPUT);  // Buzzer
}

void loop() {
  // Read sensor inputs
  int s1 = analogRead(A0);
  int s2 = analogRead(A1);
  int s3 = analogRead(A2);
  int s4 = analogRead(A3);
  int s5 = analogRead(A6);

  // Debugging: Print sensor values
  Serial.print("S1: "); Serial.println(s1);
  Serial.print("S2: "); Serial.println(s2);
  Serial.print("S3: "); Serial.println(s3);
  Serial.print("S4: "); Serial.println(s4);
  Serial.print("S5: "); Serial.println(s5);

  // Check conditions for sensor inputs
  if (s1 > 725) {
    digitalWrite(13, LOW);
    Serial.println("Washroom");
    lcd.setCursor(0, 1);
    lcd.print("   WASHROOM    ");
    activateBuzzer();
    
  } else if (s2 > 710) {
    digitalWrite(13, HIGH);
    Serial.println("Drink Water");
    lcd.setCursor(0, 1);
    lcd.print(" DRINK WATER  ");
    activateBuzzer();
    
  } else if (s3 > 760) {
    digitalWrite(13, LOW);
    Serial.println("Food");
    lcd.setCursor(0, 1);
    lcd.print("     FOOD     ");
    activateBuzzer();
    
  } else if (s4 > 750) {
    digitalWrite(13, HIGH);
    Serial.println("Fruit");
    lcd.setCursor(0, 1);
    lcd.print("    MEDICINE    ");
    activateBuzzer();
    
  } else if (s5 > 740) {
    digitalWrite(13, HIGH);
    Serial.println("Help");
    lcd.setCursor(0, 1);
    lcd.print("      HELP    ");
    activateBuzzer();
  } else {
    // Default state when no condition is met
    Serial.println("Nothing");
    lcd.setCursor(0, 1);
    lcd.print("    NOTHING   ");
    digitalWrite(13, LOW);
  }

  delay(1000); // Add delay to avoid rapid looping
}

void activateBuzzer() {
  digitalWrite(8, HIGH); // Turn on the buzzer
  delay(1000);           // Wait for 2 seconds
  digitalWrite(8, LOW);  // Turn off the buzzer
}
