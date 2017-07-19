#include <LiquidCrystal.h>
#include <Ultrasonic.h>
#include <string.h> 
 
  LiquidCrystal lcd(0, 1, 5, 4, 3, 2); ///RS 0 .. EN  1.. D7 2.. D6 3.. D5 4.. D6 5

#define pino_trigger A5
#define pino_echo A4
 
Ultrasonic ultrasonic(pino_trigger, pino_echo);
/*
int bot = 9;
int menu = 0; 
int bomba1 = 12;
int bomba2 = 11;
int led_dis = A4; 
//int led1 = 10; 
//int led2 = 9;
//int led3 = 8; */
int lin1 = 13, lin2 = 12, lin3 = 11,  lin4 = 10; 
int col1 = 9, col2 = 8, col3 = 7, col4 = 6; 
char stri[16];

void setup()
{
      //PINOS DO TECLADO MATRICIAL 
      pinMode(lin1, OUTPUT); 
      pinMode(lin2, OUTPUT); 
      pinMode(lin3, OUTPUT); 
      pinMode(lin4, OUTPUT); 
      pinMode(col1, INPUT_PULLUP); //ligado resistor pullup interno para deixar a entrada do teclado matricial sempre em 1
      pinMode(col2, INPUT_PULLUP); 
      pinMode(col3, INPUT_PULLUP); 
      pinMode(col4, INPUT_PULLUP); 
      
/*      //OUTROS PINOS 
      pinMode(bot, INPUT);
      pinMode(bomba1, OUTPUT);
      pinMode(bomba2, OUTPUT);
      pinMode(led_dis, OUTPUT); 
      //pinMode(led1, OUTPUT);
      //pinMode(led2, OUTPUT);
      //pinMode(led3, OUTPUT);*/

      lcd.begin(16, 2);      
      lcd.clear(); 
      
      lcd.clear(); 
      lcd.setCursor(0, 0);                //Menu principal 
      lcd.print("Maquina de suco");
      lcd.setCursor(0, 1);
      lcd.print("Escolha o suco "); 
      delay(1500); 
      lcd.clear(); 
      
      //Serial.begin(9600); 
}
char check_char(int i, int j){
	switch(i){
		case 0:
			if(j == 3)
				return 'A';
			else{
				if(j == 2)
					return 'B';
				else{
					if(j == 1)
						return 'C';
					else
						return 'D';
				}
			}
			break;
		case 1:
			if(j == 3)
				return '3';
			else{
				if(j == 2)
					return '6';
				else{
					if(j == 1)
						return '9';
					else
						return '#';
				}
			}
			break;
		case 2:
			if(j == 3)
				return '2';
			else{
				if(j == 2)
					return '5';
				else{
					if(j == 1)
						return '8';
					else
						return '0';
				}
			}
			break;
		case 3:
			if(j == 3)
				return '1';
			else{
				if(j == 2)
					return '4';
				else{
					if(j == 1)
						return '7';
					else{ if(j == 0)
						return '*';}
				}
			}
			break;
	}
	return ' ';
}//end check_char
char ikey(){      //Função para retornar o caracter da tecla pressionada 
	//Criados vetores com os pinos de forma a faciltiar os loops
	int lv[4] = {lin1, lin2, lin3, lin4}; 
	int cv[4] = {col1, col2, col3, col4};
	
	int i,j;
	
	//Todos os pinos da fileira lin são setados como high.
	for(i = 0; i<4; i++)
		digitalWrite(lv[i],HIGH);
	
	for(i = 0; i<4; i++){
		digitalWrite(lv[i],LOW);
		for(j = 0; j < 4; j++){
			if (digitalRead(cv[j]) == 0)
				return check_char(i,j);
		}
		digitalWrite(lv[i], HIGH);
	}	
	return ' ';
}
void copo()
{
     int dis;   
     float cmMsec;
     long microsec = ultrasonic.timing();
     cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
      
     lcd.clear(); 
     lcd.setCursor(0,0); 
     lcd.print("Coloque o copo:"); 
     lcd.setCursor(0,1); 
     lcd.print("Distancia:"); 
     do{
      long microsec = ultrasonic.timing();
      dis = (int)ultrasonic.convert(microsec, Ultrasonic::CM);
      lcd.setCursor(11,1); 
      lcd.print("   "); 
      lcd.setCursor(11,1); 
      lcd.print(dis);   
      delay(300);     
     } while(dis > 3); 
     
     lcd.clear();
     lcd.setCursor(0,0); 
     lcd.print("Copo detectado");   
}

void tempo(int *n)
{
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Digite o tempo:"); 
    lcd.print(ikey());  
    while(ikey() != ' ') {}  
}

void ret(){
      delay(1000); 
      lcd.print("."); 
      delay(1000); 
      lcd.print("."); 
      delay(1000); 
      lcd.print("."); 
      delay(2000); 
}

void bomba(int t){
   
      lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("Tempo : "); 
      lcd.print(t); 
      lcd.setCursor(0,1); 
      lcd.print("Ligando motor"); 
      ret(); 
      
      lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("Despejando suco!"); 
      
      delay(t*1000); 
      
      lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("Bon apettiti! :) ");    
      delay(5000); 
        //digitalWrite(bomba, HIGH); 
      //delay(t*1000); 
      //digitalWrite(bomba, LOW); 
}

void ler(){
      
      lcd.clear();
//      lcd.setCursor(0,0); 
      while (true) {
        lcd.setCursor(0,0);  
        lcd.print(ikey()); 
      }
    
}
 void loop()
{                         
             int tempo;  
             ler(); 
             copo(); 
             bomba(3); 
                          
             while(true){
              lcd.clear(); 
              lcd.setCursor(0,0); 
              lcd.print("Dig din");
              delay(500);               
             }
}
