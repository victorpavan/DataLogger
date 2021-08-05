int portas[7] = {2, 3, 4, 5, 6, 7, 17};

void setup(){

	for(int p; p<7; p++){
		pinMode(portas[p], OUTPUT);
	}
	for(int p; p<7; p++){
		digitalWrite(portas[p], 0);
	}

	digitalWrite(7, 1);
}

void loop(){
}
