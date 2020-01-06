long getWaterLevel(int trigPin, int echoPin){
	unsigned long duration = 0;
	long distance = 0;

	for(int i = 0; i<10; i++){
		digitalWrite(trigPin, LOW);  // Added this line
		delayMicroseconds(2); // Added this line
		digitalWrite(trigPin, HIGH);
		delayMicroseconds(10); // Added this line
		digitalWrite(trigPin, LOW);
		duration += pulseIn(echoPin, HIGH);
	}


	duration = duration/10.0;

	//19.307 is the assumed air temperature,
	//since it has an impact on speed of sound, an ideal solution would be to use an additional temp sensor
	double speedOfSound = 0.03313 + 0.0000606 * 19.307;
	distance = duration / 2.0 * speedOfSound;

	if(distance == 0 || distance > 400){
		distance = -1;
	}

	return distance;
}
