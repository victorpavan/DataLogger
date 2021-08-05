#include<math.h>

void setup(){
	Serial.begin(9600);
	//pinMode(A0, INPUT);
	//analogReference(INTERNAL);
}

unsigned int soma = 0;
unsigned int count = 0;
unsigned long inicial = 0;

int sampleSound(){

	int maior = 0;
	int menor = 1024;


	for(unsigned int i=0; i<5000; i++){

		int valor = analogRead(A0);

		if(valor>maior){
			maior = valor;
		}

		if(valor<menor){
			menor = valor;
		}
	}
		

	return (maior - menor)/2;
}


void loop(){
	
//	Serial.println(sampleSound());
	Serial.println(analogRead(A0));

}
