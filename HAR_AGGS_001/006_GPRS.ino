void gprsBegin() {
  Serial.println(F("Setup GSM..."));
  //Inicializamos a serial onde está o modem
  Serial2.begin(57600);
  delay(100);
  Serial.println(F("MODEM INFO"));
  Serial.println(modemGSM.getModemInfo());
  if (!modemGSM.restart()) {
    Serial.println(F("FALHOU REINICIALIZACAO DO MODEM GSM"));
    statusCheck = 1;
    stateCheck[3] = 1;
    somErrado();
    return;
  } else {
    Serial.println(modemGSM.getModemInfo());
  }
  retryCount = 0;
  AGAIN:
  if (!modemGSM.waitForNetwork())
  {
    Serial.println(F("FALHA DE CONEXÃO COM A REDE"));
    if (retryCount >= retryNumber ){
      statusCheck = 1;
      stateCheck[3] = 1;
      somErrado();
      return;
    }else{
      retryCount ++;
      Serial.print("TENTATIVA = ");
      Serial.println(retryCount);
      goto AGAIN;
    }
  }
  if (modemGSM. isNetworkConnected ()) {
    Serial.println(F("CONECTADO A REDE COM SUCESSO"));
  } 
  retryCount = 0;

  AGAIN_GPRS_CON:
  if (!modemGSM.gprsConnect("m2mprepago.br", "Arqia", "Arqia")) {  
    delay(500);
    Serial.print(F("TENTATIVA = "));
    Serial.println(retryCount);
    Serial.println(F("CONEXÃO DE DADOS FALHOU"));
    retryCount++;
    if (retryCount <= retryNumber) {
      goto AGAIN_GPRS_CON;
    }
    statusCheck = 1;
    stateCheck[3] = 1;
    somErrado();
    return;
  } else {
    Serial.println(F("SETUP GSM BEM SUCEDIDO"));
    statusCheck = 0;
    stateCheck[3] = 0;
    somCerto();
    return;
  } 
}
