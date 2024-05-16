#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);


 
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 4 // Green LED pin
#define LED_R 5 // Red LED pin
#define lock 3
#define buzzer 2
MFRC522 mfrc522(SS_PIN, RST_PIN);
int Btn = 6;
 volatile int x = 0; 
 void manual_button();
 void invalid();
 void valid();
void setup() 
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(Btn, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(4), Btn ,FALLING);
  pinMode(lock,OUTPUT);
  Serial.println("Place your card on reader...");
  Serial.println();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Scan Your Card "); 
  lcd.setCursor(0,1);
  lcd.print("  Door Locked   ");
   digitalWrite(lock,HIGH);
 }
void loop() 
{

manual_button();
looking_for_new_cards();

selecting_one_card();


//Show UID on serial monitor
                                 Serial.print("UID tag :");
                                 String content= "";
                                 byte letter;
                                 for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
                                 Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                                 Serial.print(mfrc522.uid.uidByte[i], HEX);
                                 content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
                                 content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
                                 Serial.println();
                                 Serial.print("Message : ");
                                 content.toUpperCase();
 
 if (content.substring(1) == "A1 E8 4E 09" || content.substring(1) == "EF 11 10 DD" ) 
  {
    valid();
  }
  else
    {
      invalid();
    }
  


 
 }


// function that look for new cards...
 void looking_for_new_cards(){
   if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
 }





// function that read card deatils....
 void selecting_one_card(){
    if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
 }
 








 
   
// Checking if the scanned tag or rfid card is intialized to the aurduino....

   void valid(){
    Serial.println("Access Granted");
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
     
    lcd.setCursor(0,1);
    lcd.print(" Door Un-Locked ");
    digitalWrite(lock,LOW);
    delay(3000);
    digitalWrite(lock,HIGH);
    delay(100);
    digitalWrite(LED_G, LOW);
    lcd.setCursor(0,1);
    lcd.print("   Door Locked   ");
   }

void invalid(){
    lcd.setCursor(0,1);
    lcd.print("Invalid RFID Tag");
    Serial.println(" Access denied");
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_R, LOW);
    tone(buzzer, 5000);
    delay(100);
    digitalWrite(LED_R, HIGH);
    delay(500);
    digitalWrite(LED_R, LOW);
    delay(100);
    digitalWrite(LED_R, HIGH);
    delay(500);
    digitalWrite(LED_R, LOW);
    noTone(buzzer);
    lcd.setCursor(0,1);
    lcd.print("   Door Locked   ");
 
 delay (100);
 }



 void manual_button(){
   if(digitalRead(Btn) == HIGH){
  
    Serial.println("Access Granted");
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
    
    lcd.setCursor(0,1);
    lcd.print(" Door Un-Locked ");
    digitalWrite(lock,LOW);
    delay(3000);
    digitalWrite(lock,HIGH);
    
    delay(100);
    digitalWrite(LED_G, LOW);
    lcd.setCursor(0,1);
    lcd.print("   Door Locked   ");
 }
 }
 



 // function for interrupt;
 void button() {

digitalWrite(LED_R, HIGH);
}

