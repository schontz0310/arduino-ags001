

void CANAL_A() {
  // CANAL_A é ativado se o pino digital 2 sai de nivel baixo(LOW) para nivel alto(HIGH).
  // Faz a chcagem do nivel logico do pino digital 3 para determinar a direção
  if (digitalRead(3) == LOW) {
    counter++;
  } else {
    counter--;
  }
}

void CANAL_B() {
  // CANAL_B é ativado se o pino digital 3 sai de nivel baixo(LOW) para nivel alto(HIGH).
  // Faz a chcagem do nivel logico do pino digital 2 para determinar a direção
  if (digitalRead(2) == LOW) {
    counter--;
  } else {
    counter++;
  }
}

void CANAL_C() {
  // CANAL_C é ativado se o pino digital 19 sai de nivel baixo(LOW) para nivel alto(HIGH).
  // Faz a chcagem do nivel logico do pino digital 18 para determinar a direção
  if (digitalRead(18) == LOW) {
    counter++;
  } else {
    counter--;
  }
}

void CANAL_D() {
  // CANAL_D é ativado se o pino digital 18 sai de nivel baixo(LOW) para nivel alto(HIGH).
  // Faz a chcagem do nivel logico do pino digital 19 para determinar a direção
  if (digitalRead(19) == LOW) {
    counter--;
  } else {
    counter++;
  }
}


float fuelLoad(VehicleFuel fuel){
  Serial.println(F("==============================================================="));
  Serial.println(F("INICIO DO ABASTECIMENTO"));
  Serial.println(F("==============================================================="));
  //permissáo checada
  uint8_t _buttonStatus = 0;
  fuelQuantity = 0;
  counter = 0;
  visorDrawScreen(SCREEN_PUMP_CHARGE_FUEL, String(fuelQuantity));
  switch (fuel)
  {
  case DIESEL_S500:
    Serial.println(F("==============================================================="));
    Serial.println(F("DIESEL S500"));
    Serial.println(F("==============================================================="));
    _pump = RELE_02;
    digitalWrite(_pump, HIGH);
    do {
      attachInterrupt(0, CANAL_A, RISING); //A rampa de subida do da interrupção 4 ativa a função CANAL_D(). AttachInterrupt 4 esta ligado no pino 19 do Arduino Mega.
      attachInterrupt(1, CANAL_B, RISING); //A rampa de subida do da interrupção 5 ativa a função CANAL_D(). AttachInterrupt 4 esta ligado no pino 19 do Arduino Mega.
      _buttonStatus = digitalRead(_pump);
      delay(10);
      if (_buttonStatus == 1) {
        fuelQuantity = (float)counter * 0.0025;
        if ((counter < 20) || (counter > 4000000)) {
          fuelQuantity = 0;
        } else {
          // tela de abastecimento
          visorDrawScreen(SCREEN_PUMP_CHARGE_FUEL, String(fuelQuantity));
        }
        delay(100);
      }
      if (digitalRead(BOTAO) == HIGH) { // Condicao que interrompe o abastecimento
        digitalWrite(_pump, LOW);
      }
    }
    while (_buttonStatus == 1);
    return fuelQuantity;
    break;
  
  case DIESEL_S10:
  Serial.println(F("==============================================================="));
  Serial.println(F("DIESEL S10"));
  Serial.println(F("==============================================================="));
  //permissáo checada
    _pump = RELE_01;
    digitalWrite(_pump, HIGH);
    do {
      attachInterrupt(4, CANAL_C, RISING); //A rampa de subida do da interrupção 4 ativa a função CANAL_D(). AttachInterrupt 4 esta ligado no pino 19 do Arduino Mega.
      attachInterrupt(5, CANAL_D, RISING); //A rampa de subida do da interrupção 5 ativa a função CANAL_D(). AttachInterrupt 4 esta ligado no pino 19 do Arduino Mega.
      _buttonStatus = digitalRead(_pump);
      delay(10);
      if (_buttonStatus == 1) {
        fuelQuantity = (float)counter * 0.0025;
        if ((counter < 20) || (counter > 4000000)) {
          fuelQuantity = 0;
        } else {
          // tela de abastecimento
          visorDrawScreen(SCREEN_PUMP_CHARGE_FUEL, String(fuelQuantity));
        }
        delay(100);
      }
      if (digitalRead(BOTAO) == HIGH) { // Condicao que interrompe o abastecimento
        digitalWrite(_pump, LOW);
      }
    }
    while (_buttonStatus == 1);
    return fuelQuantity;
    break;
  
  default:
    Serial.println(F("==============================================================="));
    Serial.println(F("CASE DEFAULT"));
    Serial.println(F("==============================================================="));
    //permissáo checada
    break;
  }
}



void registerFueLCharger() {
  visorDrawMenu(SCREEN_PROGRESS);
  jsonPayload = "";
  dataloggerWriteFuelCharge();
  visorDrawMenu(SCREEN_PROGRESS);
  jsonPayload = jsonFuelChargeMount();
  Serial.println(jsonPayload);
  // enviar novo abastecimento por mqtt para broker
  visorDrawMenu(SCREEN_PROGRESS);
  if(mqttSend(TOPIC_REGISTER, jsonPayload)){
    Serial.println("Eviou MQTT");
    visorDrawMenu(SCREEN_SUCCESS);
    somCerto();
    delay(1500);
    loop();
  }else{
    dataloggerWriteFailMqttLog(jsonPayload);
    Serial.println("Erro MQTT final");
    visorDrawMenu(SCREEN_SUCCESS);
    somCerto();
    delay(1500);
    loop();
  }

}
