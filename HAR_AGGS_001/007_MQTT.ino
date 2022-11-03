void mqttBegin(){
  retryCount = 0;
  Serial.println(F("Connecting to MQTT Server..."));
  client.setServer(MQTT_SERVER, MQTT_PORT);
  AGAIN_MQTT_CON:
  if (client.connect("pump", USER, PASS) == true)  {
    delay(1000);
    statusCheck = 0;
    stateCheck[4] = 0;
    somCerto();
    Serial.println(F("MQTT Client Connected..."));
    return;
  } else {
    Serial.print(F("error = not connected"));
    Serial.print(F("error = "));
    Serial.println(client.state());
    delay(1000);
    client.disconnect();
    retryCount++;
    if (retryCount <= retryNumber) {
      goto AGAIN_MQTT_CON;
    }
    statusCheck = 1;
    stateCheck[4] = 1;
    somErrado();
    return;
  }
}

bool mqttSend (String topic, String payload) {
  bool flag = true;
  if(!modemGSM.isNetworkConnected()){
    Serial.println(F("Step 2"));
    flag = false;
  };
  if(flag == false){
    Serial.println(F("step 3"));
    gprsBegin(); 
  }
  String _payload = payload;
  String _topic = topic;
  int steps = 0;
  AGAIN_MQTT:
  if(client.connect("pump", USER, PASS)) {
    Serial.println(F("Step 5"));
    if (client.publish(_topic.c_str(), _payload.c_str())){
      return true;
    }else{
      if(steps < 1){
        Serial.print(F("tentativa = "));
        Serial.println(steps);
        steps++;
        Serial.println(client.state());
        mqttBegin();
        client.disconnect();
        goto AGAIN_MQTT;
      }else{
        return false;
      }
    }
  }else {
    if(steps < 1){
        Serial.print(F("tentativa = "));
        Serial.println(steps);
        steps++;
        Serial.println(client.state());
        mqttBegin();
        client.disconnect();
        goto AGAIN_MQTT;
      }else{
        return false;
      }
   }  
 }
