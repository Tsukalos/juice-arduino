#include <LiquidCrystal.h>
#include <string.h> 
 
  LiquidCrystal lcd(0, 1, 5, 4, 3, 2); ///RS 0 .. EN  1.. D7 2.. D6 3.. D5 4.. D6 5

int bot = 9;
int menu = 0; 
int bomba1 = 12;
int bomba2 = 11;
int led_dis = A4; 
//int led1 = 10; 
//int led2 = 9;
//int led3 = 8; 
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
      
      //OUTROS PINOS 
      pinMode(bot, INPUT);
      pinMode(bomba1, OUTPUT);
      pinMode(bomba2, OUTPUT);
      pinMode(led_dis, OUTPUT); 
      //pinMode(led1, OUTPUT);
      //pinMode(led2, OUTPUT);
      //pinMode(led3, OUTPUT);
      lcd.begin(16, 2);      

      lcd.clear(); 
}
char check_char(int i, int j){
	switch(i){
		case 0:
			if(j == 4)
				return 'a';
			else{
				if(j == 3)
					return 'b';
				else{
					if(j == 2)
						return 'c';
					else
						return 'd';
				}
			}
			break;
		case 1:
			if(j == 4)
				return '3';
			else{
				if(j == 3)
					return '6';
				else{
					if(j == 2)
						return '9';
					else
						return '#';
				}
			}
			break;
		case 2:
			if(j == 4)
				return '2';
			else{
				if(j == 3)
					return '5';
				else{
					if(j == 2)
						return '8';
					else
						return '0';
				}
			}
			break;
		case 3:
			if(j == 4)
				return '1';
			else{
				if(j == 3)
					return '4';
				else{
					if(j == 2)
						return '7';
					else
						return '*';
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
 
void loop()
{             

              digitalWrite(led_dis, HIGH);
              lcd.setCursor(0, 0);                //Menu principal 
              lcd.print("Maquina de suco");
              lcd.setCursor(0, 1);
              lcd.print("Escolha o suco ");  
              delay(3000); 
              digitalWrite(led_dis, LOW);
              delay(2000);                      
              if(ikey() != ' ') {
                lcd.clear();
                digitalWrite(led_dis, HIGH);
                do{                            
                  lcd.setCursor(0, 0);
                  lcd.print("1 - Laranja");
                  lcd.setCursor(0, 1);
                  lcd.print("2 - Acerola"); 
                  delay(2000);  
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("3 - Maracuja");
                  lcd.setCursor(0, 1);
                  lcd.print("4 - Abacaxi");
                  delay(2000);
                  lcd.clear();
              }while (ikey() != ' '); 
              }
             // if(ikey() == '1')
                        

    
}
