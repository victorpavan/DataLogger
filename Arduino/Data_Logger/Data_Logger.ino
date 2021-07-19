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
#define action_r 8
#define action_g 9

//Definicoes de variáveis globais
unsigned int relogio[6]; //{hora, minuto, segundo, dia, mes, ano}
#define CS 10
bool pronto = false;
bool cartao_ok = true;
bool cartao_ok_led = false;

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

	//Inicializacao dos leds
	pinMode(action_r, OUTPUT);
	pinMode(action_g, OUTPUT);

	//Inicializacao dos sensores nos barramentos I2C
	for(int i=0; i < 3; i++){
		hdc[i].begin(0x40, barramento[i]);
		mlx[i].begin(barramento[i]);
	}

	//Teste do cartao
	setupSdcard();
	//Tudo certo para comecar
	digitalWrite(action_g, HIGH);

	
	//Cria cabecalho para marcar inicializacao
	if(cartao_ok){
		salvar("1", true);
		delay(100);
		salvar("2", true);
		delay(100);
		salvar("3", true);
	}
	

	
}

void blink(byte code){
	while(1){
		digitalWrite(action_g, LOW);
		digitalWrite(action_r, bitRead(code, 0));
		delay(200);
		digitalWrite(action_r, LOW);
		delay(200);

		digitalWrite(action_r, bitRead(code, 1));
		delay(200);
		digitalWrite(action_r, LOW);
		delay(200);

		digitalWrite(action_r, bitRead(code, 2));
		delay(200);
		digitalWrite(action_r, LOW);
		delay(200);

		digitalWrite(action_r, bitRead(code, 3));
		delay(200);
		digitalWrite(action_r, LOW);
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
		relogio[5] = tmYearToCalendar(tm.Year);

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

	for(int i=0; i < 3; i++){
		if(hdc[i].readTemperature() < 124.00){
			Serial.print(i+1);
			Serial.print(';');
			Serial.print(hdc[i].readTemperature());
			Serial.print(';');
			Serial.print(hdc[i].readHumidity());
			Serial.print(';');
			Serial.println(mlx[i].readObjectTempC());
		}else{
			Serial.print(i+1);
			Serial.print(';');
			Serial.print("N/A");
			Serial.print(';');
			Serial.print("N/A");
			Serial.print(';');
			Serial.println("N/A");
		}
	}
	
		

	timestep();
	if(!cartao_ok){
	   	digitalWrite(action_g, cartao_ok_led);
		cartao_ok_led = !cartao_ok_led;
	}else{
		if(relogio[2]%10 == 0){
			if(!pronto){
				salvar("1", false);
				delay(100);
				salvar("2", false);
				delay(100);
				salvar("3", false);
				pronto = true;
			}
		}else{
			pronto = false;
		}
	}
	delay(500);
}
