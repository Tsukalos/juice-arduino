#include <LiquidCrystal.h>
#include <Ultrasonic.h>
#include <string.h> 
 
  LiquidCrystal lcd(0, 1, 5, 4, 3, 2); ///RS 0 .. EN  1.. D7 2.. D6 3.. D5 4.. D6 5

#define pino_trigger A5
#define pino_echo A4
 
Ultrasonic ultrasonic(pino_trigger, pino_echo);

int bba = A1;

int lin1 = 13, lin2 = 12, lin3 = 11,  lin4 = 10; 
int col1 = A0, col2 = 8, col3 = 7, col4 = 6; 
char stri[16];

void setup()
{
     
      pinMode(bba, OUTPUT);
      //PINOS DO TECLADO MATRICIAL 
      pinMode(lin1, OUTPUT); 
      pinMode(lin2, OUTPUT); 
      pinMode(lin3, OUTPUT); 
      pinMode(lin4, OUTPUT); 
      pinMode(col1, INPUT_PULLUP); //ligado resistor pullup interno para deixar a entrada do teclado matricial sempre em 1
      pinMode(col2, INPUT_PULLUP); 
      pinMode(col3, INPUT_PULLUP); 
      pinMode(col4, INPUT_PULLUP); 
      
      lcd.begin(16, 2);      
      lcd.clear(); 
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
void tem(int q)
{
    delay(q); 
}
void menu(){
            
      lcd.clear(); 
      lcd.setCursor(0, 0);                //Menu principal 
      lcd.print("Maquina de suco");
      lcd.setCursor(0, 1);
      lcd.print(" Suco de Uva! "); 
      delay(1500); 
      do{
      }while(ikey() == ' ');
      tem(1500);  
      lcd.clear();  
     
}

int distancia()
{
      int dis;   
     float cmMsec;
     long microsec = ultrasonic.timing();
     cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
//     long microsec = ultrasonic.timing();
     dis = (int)ultrasonic.convert(microsec, Ultrasonic::CM);
     return dis;   
}

void copo()
{
     int d;   
      
     lcd.clear(); 
     lcd.setCursor(0,0); 
     lcd.print("Coloque o copo:"); 
     lcd.setCursor(0,1); 
     lcd.print("Distancia:"); 
     do{
      d = distancia(); 
      lcd.setCursor(11,1); 
      lcd.print("   "); 
      lcd.setCursor(11,1); 
      lcd.print(d);   
      tem(300);     
     } while(d > 5); 
     
     lcd.clear();
     lcd.setCursor(0,0); 
     lcd.print("Copo detectado");   
     tem(3000); 
}

int cheio()
{  
    int aux = 0;
    
    tem(300); 
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Suco:");
    lcd.print(" 1-Pouco");  
    lcd.setCursor(0,1); 
    lcd.print("2-Medio 3-Cheio"); 

    do{
    if(ikey() == '1')
    {
        lcd.clear(); 
        lcd.setCursor(0,0); 
        lcd.print("Colocando"); 
        lcd.setCursor(0,1);  
        lcd.print("Suco..."); 
        tem(1500); 
        aux = 7;
     }else 
       if(ikey() == '2')
       {
          lcd.clear(); 
          lcd.setCursor(0,0); 
          lcd.print("Colocando");
          lcd.setCursor(0,1);  
          lcd.print("Suco..."); 
          tem(1500);
          aux = 13;
       } else 
             if(ikey() == '3')
             {
                lcd.clear(); 
                lcd.setCursor(0,0); 
                lcd.print("Colocando");
                lcd.setCursor(0,1);  
                lcd.print("Suco..."); 
                tem(1500);
                aux = 20;
             }
             
    }while(aux == 0); 
    
    return aux; 
}

void ret(){	
      int i; 
	for(i = 0; i < 3; i++){
      delay(1000); 
      lcd.print("."); 
      }
      delay(2000); 		
}

void bomba(int r){
   
      lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("Tempo : "); 
      lcd.print(r); 
      lcd.print(" s"); 
      lcd.setCursor(0,1); 
      lcd.print("Ligando motor"); 
      ret(); 
      
      if(distancia() > 5)
      {
            lcd.clear(); 
           do
          {
              lcd.setCursor(0,0); 
              lcd.print("Sem copo!"); 
              lcd.setCursor(0,1); 
              lcd.print("Coloque o copo!"); 
              delay(150); 
          } while(distancia() > 5); 
          
          lcd.clear(); 
          lcd.setCursor(0,0);
          lcd.print("Retomando"); 
          ret(); 
          delay(500); 
      }
      
      lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("Despejando suco!"); 
      
      digitalWrite(bba, HIGH); 
      while(r > 0)
      {
        delay(1000); 
        r--; 
      }
      digitalWrite(bba, LOW);  
      
      lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("Suco despejado!");    
      delay(4000);       
}

 void loop()
{                         
       int t = 0; 
       menu(); 
       t = cheio(); 
       copo(); 
       bomba(t);                                     
}
