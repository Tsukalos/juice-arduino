#include <LiquidCrystal.h>
 
  LiquidCrystal lcd(0, 1, 5, 4, 3, 2); ///RS 0 .. EN  1.. D7 2.. D6 3.. D5 4.. D6 5

int bot = 9;
int menu = 0; 
int bomba1 = 12;
int bomba2 = 11;
int led1 = 10; 
int led2 = 9;
int led3 = 8; 

void setup()
{
      pinMode(bot, INPUT);
      pinMode(bomba1, OUTPUT);
      pinMode(bomba2, OUTPUT);
      pinMode(led1, OUTPUT);
      pinMode(led2, OUTPUT);
      pinMode(led3, OUTPUT);AASSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
      lcd.begin(16, 2);      
}
 
void loop()
{
    switch (menu){
  
            case 0:     lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print("Maquina de suco");
                        lcd.setCursor(4, 1);
                        lcd.print("Aperte 1");
                        digitalWrite(bomba1, LOW);
                        digitalWrite(bomba2, LOW);
                        break;
                        
            case 1:     lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("1 - Laranja");
                        lcd.setCursor(0,1);
                        lcd.print("2 - Acerola"); 
                        digitalWrite(bomba1, HIGH);
                        digitalWrite(bomba2, LOW);
                        break;

            case 2:     lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("3 - Uva");
                        lcd.setCursor(0,1);
                        lcd.print("4 - Morango");
                        digitalWrite(bomba1, LOW);
                        digitalWrite(bomba2, HIGH);
                        break;  
                                
            case 3:     lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("Suco 1 %:");
                        lcd.setCursor(0,1);
                        lcd.print("Digite:   ");
                        digitalWrite(bomba1, HIGH);
                        digitalWrite(bomba2, HIGH);
                        break;  

            case 4:     lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("Suco 2 %:  ");
                        lcd.setCursor(0,1);
                        lcd.print("DIgite:   ");
                        digitalWrite(bomba1, LOW);
                        digitalWrite(bomba2, LOW);
                        break;  

            case 5:     lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("Recipiente 1");
                        lcd.setCursor(0,1);
                        lcd.print("Acabando suco");
                        digitalWrite(led1, HIGH);
                        digitalWrite(led2, HIGH);
                        digitalWrite(led3, HIGH);
                        break;  

            case 6:     lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("Recipiente 2");
                        lcd.setCursor(0,1);
                        lcd.print("Sem suco");
                        digitalWrite(led1, LOW);
                        digitalWrite(led2, LOW);
                        digitalWrite(led3, LOW);
                        break;  
                       
    }

    delay(2000);
    menu++; 
    if(menu == 7) menu = 0;
    
}
   
   

