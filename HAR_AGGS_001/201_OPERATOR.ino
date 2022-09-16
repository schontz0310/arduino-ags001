
String operatorRead(){
  Serial.println(F("==== FUNCAO OPERADOR =========================================="));
  String _operator = "";
  do {
    visorReadCard(SCREEN_OPERATOR_READ, "", "");
    rfid.PCD_Init(SS_SDA_PIN, RST_PIN);
    Serial.println(F("PASSE O CARTÃO DO OPERADOR"));
    do {
      successRead =  rfidReaderGetID();
      tecla_presionada = keyboard.getKey();
      if ( tecla_presionada == 'A') {
        Serial.println(F("ACESSANDO MENU"));
        visorMenuPrincipal();
      }
    } while (!successRead);
    Serial.println(rfidReaderIDValue);
    visorReadCard(SCREEN_OPERATOR_SEARCH, "", rfidReaderIDValue);
    _operator = dataloggerGetOperator(rfidReaderIDValue);
    Serial.println(_operator);
    if(_operator != "NO_OPERATOR"){
    visorReadCard(SCREEN_OPERATOR_FOUND,
    _operator.substring(_operator.indexOf("#") + 1, _operator.lastIndexOf("#")), 
    rfidReaderIDValue);
    somCerto();
    return _operator;
    }else{
      visorReadCard(SCREEN_OPERATOR_NOT_FOUND, "", rfidReaderIDValue);
      visorDrawMenu(SCREEN_ERROR);
      somErrado();
      delay(1500);
      loop();
    }
    delay(100);
  } while (status != 1);
}
