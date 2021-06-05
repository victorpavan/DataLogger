#include<SPI.h>
#include<SdFat.h>:

#define CS 10

SdFat sdCard;
SdFile arquivo;

void setupSdcard(){

	if(!sdCard.begin(CS,SPI_HALF_SPEED)){
		sdCard.initErrorHalt();
	}	
}

void salvar(int casa) {

  digitalWrite(action, HIGH);

  char nome = casa+48;

	if (!arquivo.open(nome, O_RDWR | O_CREAT | O_AT_END)){
		delay(300);
		digitalWrite(action, LOW);
		delay(500);
		digitalWrite(action, HIGH);

	}else{
	arquivo.print(relogio[3]);
	arquivo.print('/');
	arquivo.print(relogio[4]);
	arquivo.print('/');
	arquivo.print(relogio[5]);
	arquivo.print(' ');
	arquivo.print(relogio[0]);
	arquivo.print(':');
	arquivo.print(relogio[1]);
	arquivo.print(';');
    arquivo.print(hdc[casa].readTemperature());
	arquivo.print(';');
	arquivo.print(hdc[casa].readHumidity());
	arquivo.print(';');
	arquivo.println(mlx[casa].readObjectTempC());
	}
	arquivo.close();

	delay(1000);
	digitalWrite(action, LOW);
}
