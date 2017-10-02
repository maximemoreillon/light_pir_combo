void IO_setup(){

  pinMode(PIR_PIN, INPUT);
  pinMode(LIGHT_PIN, OUTPUT);

  // Initial state
  if(strcmp(light_status,"ON") == 0) {
    digitalWrite(LIGHT_PIN, HIGH);
  }
  else {
    digitalWrite(LIGHT_PIN, LOW);
  }
}


void read_PIR(){
  int PIR_reading = digitalRead(PIR_PIN);
  if(PIR_reading != last_PIR_reading) {
    // Motion sensor reading changed
    last_PIR_reading = PIR_reading;
    if(PIR_reading == HIGH){
      Serial.println("Motion detected");
      MQTT_client.publish(MQTT_MOTION_STATUS_TOPIC, MQTT_QOS, MQTT_RETAIN, "MOTION");
    }
    else {
      MQTT_client.publish(MQTT_MOTION_STATUS_TOPIC, MQTT_QOS, MQTT_RETAIN, "IDLE");
    }
  }
}

