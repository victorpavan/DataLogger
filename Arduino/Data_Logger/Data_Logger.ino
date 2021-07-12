/*DATALOGGER ARDUINO
 * 
 * 
 */

#include<ClosedCube_HDC1080.h>
#include<Adafruit_MLX90614.h>
#include<TimeLib.h>
#include<Wire.h>
#include<DS1307RTC.h>
#include<SPI.h>
#include<SdFat.h>


//Configurações gerais (alterar de acordo com a necessidade)

#define SERIALBAUD 9600
#define action 8

//Definicoes de variáveis globais
unsigned int relogio[6]; //{hora, minuto, segundo, dia, mes, ano}
#define CS 10
bool pronto = false;

//Definição dos barramentos I2C
//SoftwareWire(sda, slc);
SoftwareWire barramento[] = {SoftwareWire(2,3), SoftwareWire(4,5), SoftwareWire(6,7)};

//Definição dos objetos dos sensores de temperatura(hdc) e infravermelho(mlx)
ClosedCube_HDC1080 hdc[3];
Adafruit_MLX90614 mlx[3];

void setup(){

	//Inicialização da comunicação serial
	Serial.begin(SERIALBAUD);
	//log(String("Inicializando comunicação serial a " + SERIALBAUD))
	
	//Inicializacao dos sensores nos barramentos I2C
	for(int i=0; i < 3; i++){
		hdc[i].begin(0x40, barramento[i]);
		mlx[i].begin(barramento[i]);
	}

	setupSdcard();
	pinMode(action, OUTPUT);
	
}

void blink(byte code){
	while(1){
		digitalWrite(action, bitRead(code, 0));
		delay(200);
		digitalWrite(action, LOW);
		delay(200);

		digitalWrite(action, bitRead(code, 1));
		delay(200);
		digitalWrite(action, LOW);
		delay(200);

		digitalWrite(action, bitRead(code, 2));
		delay(200);
		digitalWrite(action, LOW);
		delay(200);

		digitalWrite(action, bitRead(code, 3));
		delay(200);
		digitalWrite(action, LOW);
		delay(200);

		delay(1000);
	}
}


void timestep() {

	tmElements_t tm;

	if(RTC.read(tm)){

		relogio[0] = tm.Hour;
	   	relogio[1] = tm.Minute;
		relogio[2] = tm.Second;
		relogio[3] = tm.Day;
		relogio[4] = tm.Month;
		relogio[5] = tm.Year;

	}else{

		if (RTC.chipPresent()) {
			//Acertar Relogio
			blink(0b11);
		}else{
			//Problema com o modulo
			blink(0b1111);
		}
	}
}

void loop(){
/*
	for(int i=0; i < 1; i++){
		Serial.print("Casa ");
		Serial.print(i+1);
		Serial.println(": ");
		Serial.println();
		Serial.print("\t");
		Serial.print("T=");
		Serial.print(hdc[i].readTemperature());
		Serial.print("C, UR=");
		Serial.print(hdc[i].readHumidity());
		Serial.print("%");
		Serial.print("\t");
		Serial.print("IR=");
		Serial.println(mlx[i].readObjectTempC());


	}
	Serial.print("\033[0H\033[0J");
*/
	timestep();
	if(relogio[1]%10 == 0){
		if(!pronto){
			salvar('1');
			delay(100);
			salvar('2');
			delay(100);
			salvar('3');
			pronto = true;
		}
	}else{
		pronto = false;
	}
	delay(1000);
}
