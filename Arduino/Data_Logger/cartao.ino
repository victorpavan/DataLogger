#include<SPI.h>
#include<SdFat.h>

#define CS 10

SdFat sdCard;
SdFile arquivo;

void setupSdcard(){
	if(!sdCard.begin(CS,SPI_HALF_SPEED)){
		cartao_ok = false;
	}	
}

void salvar(char *casa, bool cabecalho) {

	int numerocasa = casa[0]-'0'-4;

	digitalWrite(action_r, HIGH);

	if (!arquivo.open(casa, O_RDWR | O_CREAT | O_AT_END)){
		delay(300);
		digitalWrite(action_r, LOW);
		digitalWrite(action_g, LOW);
		delay(500);
		digitalWrite(action_r, HIGH);
		digitalWrite(action_g, HIGH);

	}else{

		if(cabecalho){
			arquivo.println("DATA; HORA; TEMP; UMIDADE; TEMP_IR; SOM_PICO");
		}else{
			arquivo.print(relogio[3]);
			arquivo.print("/");
			arquivo.print(relogio[4]);
			arquivo.print("/");
			arquivo.print(relogio[5]);
			arquivo.print(";");
			arquivo.print(relogio[0]);
			arquivo.print(":");
			arquivo.print(relogio[1]);
			arquivo.print(";");

			if(hdc[numerocasa].readTemperature() < 124.00){

				arquivo.print(hdc[numerocasa].readTemperature());
				arquivo.print(";");
				arquivo.print(hdc[numerocasa].readHumidity());
				arquivo.print(";");
				arquivo.print(mlx[numerocasa].readObjectTempC());
				arquivo.print(";");
				arquivo.println(intensidade_som[numerocasa]);
			}else{

				arquivo.print("N/A");
				arquivo.print(";");
				arquivo.print("N/A");
				arquivo.print(";");
				arquivo.print("N/A");
				arquivo.print(";");
				arquivo.println("N/A");
			}
		}

	}
	arquivo.close();

	delay(500);
	digitalWrite(action_r, LOW);
}
