#include<SPI.h>
#include<SdFat.h>:

SdFat sdCard;
SdFile arquivo;

#define CS 10

void salvar(char *casa){

	int numerocasa = casa[0]-'0';

	Serial.println(numerocasa+5);

	if(!sdCard.begin(CS,SPI_HALF_SPEED)){
		digitalWrite(8, 1);
		sdCard.initErrorHalt();
	}

	if (!arquivo.open(casa, O_RDWR | O_CREAT | O_AT_END)){
		delay(300);
		digitalWrite(8, LOW);
		delay(500);
		digitalWrite(8, HIGH);
	}else{
		arquivo.println("Comunicacao com SD funcional");
	}

	arquivo.close();
	delay(1000);

}
void setup(){
	Serial.begin(9600);
	pinMode(8, OUTPUT);
	salvar("5");
}

void loop(){
}
