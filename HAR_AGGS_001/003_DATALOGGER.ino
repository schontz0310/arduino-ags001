void dataloggerBegin(){
  if (SD.begin(PIN_SS_DATA_LOG)) {
    delay(100);
    Serial.println(F("SD PASSOU"));
    statusCheck = 0;
    stateCheck[0] = 0;
    somCerto();
  } else {
    delay(100);
    Serial.println(F("SD NAO PASSOU"));
    statusCheck = 1;
    stateCheck[0] = 1;
    somErrado();
  }  
}

void dataloggerSetTimestamp() {
  if (GET_SYSTEM_TIMESTAMP == true) {
    if (getDate(__DATE__) && getTime(__TIME__)) 
    {
      Serial.println("Guardando Timestamp do sistema");
      Serial.println(getDate(__DATE__));
      Serial.println(getTime(__TIME__));
      delay(200);
      RTC.write(tm);
      getTimestamp();
      statusCheck = 0;
      stateCheck[1] = 0;
      somCerto();
    }else{
       statusCheck = 1;
       stateCheck[1] = 1;
       somErrado();
    } 
  }else {
    getTimestamp();
    statusCheck = 0;
    stateCheck[1] = 0;
    somCerto();
  }
}

bool getDate(const char *str) {
  Serial.println(__DATE__);
  Serial.println(__TIME__);
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;
  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthNameDatalogger[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

bool getTime(const char *str) {
  int Hour, Min, Sec;
  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

String getTimestamp() {
  
  timestamp = "-erro-"; //Mensagem em caso de erro na leitura da data/hora
  if (RTC.read(tm)) { //Função para lder hora
    Serial.println("Entrou na Leitura de hora do rtc");
    timestamp = "";
    timestamp += get2digits(tm.Day); //Dia
    timestamp += "/";
    timestamp += get2digits(tm.Month); //Mes
    timestamp += "/";
    timestamp += get2digits(tmYearToCalendar(tm.Year)); //Ano
    timestamp += ";";
    timestamp += get2digits(tm.Hour); //Hora
    timestamp += ":";
    timestamp += get2digits(tm.Minute); //Minuto
    timestamp += ":";
    timestamp += get2digits(tm.Second); //Segundo
  }
  delay(500);
  Serial.println(timestamp);
  return timestamp;
}

String  get2digits(int number) {
  String val = "";
  if (number >= 0 && number < 10) {
    val += "0";
  }
  val += String(number);
  return val;
}

String dataloggerGetCompany(){
  Serial.println("entrou na funcao getCompany");
  if (!SD.exists("CAD-COM.txt")){
    Serial.println("tentou criar arquivo");
    SD.open("CAD-COM.txt", FILE_WRITE);
  } 
  if (!SD.exists("CAD-COM.txt")){
    Serial.println("criacaoo do arquivo deu errado");
    if(!SD.begin(PIN_SS_DATA_LOG)){
      Serial.println("Erro na abertura do cartao SD");
      delay(1500);
      return "NO_COMPANY";
    }
  }
  fileName.close();
  delay(50);
  fileName = SD.open("CAD-COM.txt");
  if (fileName) {
    while (fileName.available())
    {
      fileRegisterLine = fileName.readStringUntil(13);
      tagUuid = fileRegisterLine.substring(fileRegisterLine.lastIndexOf(";") + 1);
      if (fileRegisterLine.length() > 10){
        COMPANY = tagUuid;
        return tagUuid;
      }
    }
    return "NO_COMPANY";
  }
}


bool dataLoggerCheckCompanyExist(String uuid){
  String _uuidToCheck = uuid;
  fileName.close();
  Serial.println("entrou na funcao WriteCompanyRegister");
  if (!SD.exists("CAD-COM.txt")){
    Serial.println("tentou criar arquivo");
    SD.open("CAD-COM.txt", FILE_WRITE);
  } 
  if (!SD.exists("CAD-COM.txt")){
    Serial.println("criacao do arquivo deu errado");
    if(!SD.begin(PIN_SS_DATA_LOG)){
      visorDrawMenu(SCREEN_ERROR);
      Serial.println("Erro na abertura do cartao SD");
      delay(1500);
      loop();
    }
  }
  _uuidToCheck = uuid;
  fileName.close();
  delay(50);
  fileName = SD.open("CAD-COM.txt");
  if (fileName) {
    String _uuidRead;
    while (fileName.available())
    {
      visorDrawMenu(SCREEN_PROGRESS);
      _uuidRead = fileName.readStringUntil(13);
      Serial.println(_uuidRead);
      _uuidRead.trim();
      _uuidRead.remove(0,43);
      int length = _uuidRead.indexOf(";");
      _uuidRead.remove(length);
      Serial.print(F("Verificação de UUID = "));
      Serial.print(_uuidRead);
      Serial.print (F(" Sistema <---> Nova Tag "));
      Serial.println (_uuidToCheck);
      if (_uuidToCheck == _uuidRead){
        return true;
      }
    }
    return false;
  }
}

void dataLoggerWriteCompanyRegisterInDatalogger(){
  Serial.println("entrou na funcao WriteCompanyRegister");
  if (!SD.exists("CAD-COM.txt")){
    Serial.println("tentou criar arquivo");
    SD.open("CAD-COM.txt", FILE_WRITE);
  } 
  if (!SD.exists("CAD-COM.txt")){
    Serial.println("criacao do arquivo deu errado");
    if(!SD.begin(PIN_SS_DATA_LOG)){
      visorDrawMenu(SCREEN_ERROR);
      Serial.println("Erro na abertura do cartao SD");
      delay(1500);
      loop();
    }
  }
  Serial.println(fileName);
  fileName.close();
  Serial.println(fileName);
  fileName = SD.open("CAD-COM.txt", FILE_WRITE);
  Serial.println(fileName);
  if (fileName) {
    Serial.println(F("GRAVANDO DADOS NO CARTÃO SD"));
    fileName.print(getTimestamp());                     // DATA E HORA
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(getUID());                           // NUMERO UNICO DO EQUIPAMENTO
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print("080");                              // CODIGO DA FUNÇÃO
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.println(companyNumber);              // UID TAG RFID
    fileName.close();
    delay(500);
  } else {
    Serial.println(F("FALHA AO GRAVAR DADOS NO CARTÃO SD"));
    visorDrawMenu(SCREEN_ERROR);
    Serial.println("Erro na abertura do cartao SD, [Utils.cpp - 892]");
    delay(1500);
    loop();
  }
}



String dataloggerGetVehicle(String uuid){
  Serial.println("entrou na funcao getVehicle");
  if (!SD.exists("CAD-VEH.txt")){
    Serial.println("tentou criar arquivo");
    SD.open("CAD-VEH.txt", FILE_WRITE);
  } 
  if (!SD.exists("CAD-VEH.txt")){
    Serial.println("criacao do arquivo deu errado");
    if(!SD.begin(PIN_SS_DATA_LOG)){
      visorDrawMenu(SCREEN_ERROR);
      Serial.println("Erro na abertura do cartao SD, [Utils.cpp - getVehicle]");
      delay(1500);
      loop();
    }
  }
  _uuidToCheck = uuid;
  _vehicleUuid = "";
  fileName.close();
  delay(50);
  fileName = SD.open("CAD-VEH.txt");
  if (fileName) {
    while (fileName.available())
    {
      visorDrawMenu(SCREEN_PROGRESS);
      _vehicleUuid = fileName.readStringUntil(13);
      _vehicleFuel = _vehicleUuid.substring(_vehicleUuid.lastIndexOf(";") + 1);
      _vehicleUuid.remove(_vehicleUuid.lastIndexOf(";"));
      _vehicleName = _vehicleUuid.substring(_vehicleUuid.lastIndexOf(";") + 1);
      Serial.println(_vehicleUuid);
      _vehicleUuid.trim();
      _vehicleUuid.remove(0,43);
      int length = _vehicleUuid.indexOf(";");
      _vehicleUuid.remove(length);
      Serial.print(F("Verificação de UUID = "));
      Serial.print(_vehicleUuid);
      Serial.print (F(" Sistema <---> Nova Tag "));
      Serial.println (_uuidToCheck);
      if (_uuidToCheck == _vehicleUuid){
        return _vehicleUuid + "#" + _vehicleName + "#" + _vehicleFuel;
      }
    }
    return "NO_VEHICLE";
  }
}


bool dataloggerCheckVehicleExist(String uuid){
  Serial.println("entrou na funcao checkVehicleExist");
  if (!SD.exists("CAD-VEH.txt")){
    Serial.println("tentou criar arquivo");
    SD.open("CAD-VEH.txt", FILE_WRITE);
  } 
  if (!SD.exists("CAD-VEH.txt")){
    Serial.println("criacao do arquivo deu errado");
    if(!SD.begin(PIN_SS_DATA_LOG)){
      visorDrawMenu(SCREEN_ERROR);
      Serial.println("Erro na abertura do cartao SD, [Utils.cpp - checkVehicleExist]");
      delay(1500);
      loop();
    }
  }
  _uuidToCheck = uuid;
  fileName.close();
  delay(50);
  fileName = SD.open("CAD-VEH.txt");
  if (fileName) {
    while (fileName.available())
    { 
      visorDrawMenu(SCREEN_PROGRESS);
      _uuidRead = fileName.readStringUntil(13);
      Serial.println(_uuidRead);
      _uuidRead.trim();
      _uuidRead.remove(0,43);
      int length = _uuidRead.indexOf(";");
      _uuidRead.remove(length);
      Serial.print(F("Verificação de UUID = "));
      Serial.print(_uuidRead);
      Serial.print (F(" Sistema <---> Nova Tag "));
      Serial.println (_uuidToCheck);
      if (_uuidToCheck == _uuidRead){
        return true;
      }
    }
    return false;
  }
}

void dataloggerWriteVehicle(){
  Serial.println("entrou na funcao WirteVehicle");
  if (!SD.exists("CAD-VEH.txt")){
    Serial.println("tentou criar arquivo");
    SD.open("CAD-VEH.txt", FILE_WRITE);
  } 
  if (!SD.exists("CAD-VEH.txt")){
    Serial.println("cria;áo do arquivo deu errado");
    if(!SD.begin(PIN_SS_DATA_LOG)){
      visorDrawMenu(SCREEN_ERROR);
      Serial.println("Erro na abertura do cartao SD, [Utils.cpp - 770]");
      delay(1500);
      loop();
    }
  }
  Serial.println(fileName);
  fileName.close();
  Serial.println(fileName);
  fileName = SD.open("CAD-VEH.txt", FILE_WRITE);
  Serial.println(fileName);
  if (fileName) {
    Serial.println(F("GRAVANDO DADOS NO CARTÃO SD"));
    fileName.print(getTimestamp());                  // DATA E HORA
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(getUID());              // NUMERO UNICO DO EQUIPAMENTO
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print("002");                              // CODIGO DA FUNÇÃO
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(tagUuid);                     // UID TAG RFID
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(_vehicleName);                  // NOME DO VEICULO
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.println(_vehicleFuel);
    fileName.close();
    delay(500);
  } else {
    Serial.println(F("FALHA AO GRAVAR DADOS NO CARTÃO SD"));
    visorDrawMenu(SCREEN_ERROR);
    Serial.println("Erro na abertura do cartao SD, [Utils.cpp - 789]");
    delay(1500);
    loop();
  }
}


void dataloggerWriteOperator(){
  Serial.println("entrou na funcao WirteOperator");
  if (!SD.exists("CAD-OPE.txt")){
    Serial.println("tentou criar arquivo");
    SD.open("CAD-OPE.txt", FILE_WRITE);
  } 
  if (!SD.exists("CAD-OPE.txt")){
    Serial.println("cria;áo do arquivo deu errado");
    if(!SD.begin(PIN_SS_DATA_LOG)){
      visorDrawMenu(SCREEN_ERROR);
      Serial.println("Erro na abertura do cartao SD, [Utils.cpp - 736]");
      delay(1500);
      loop();
    }
  }
  Serial.println(fileName);
  fileName.close();
  Serial.println(fileName);
  fileName = SD.open("CAD-OPE.txt", FILE_WRITE);
  Serial.println(fileName);
  if (fileName) {
    Serial.println(F("GRAVANDO DADOS NO CARTÃO SD"));
    fileName.print(getTimestamp());                     // DATA E HORA
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(getUID());              // NUMERO UNICO DO EQUIPAMENTO
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print("001");                              // CODIGO DA FUNÇÃO
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(tagUuid);                     // UID TAG RFID
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(_operatorName);                 // NOME DO OPERADOR
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.println(_operatorLevel);              // NIVEL DE PERMISSAO DO OPERADOR
    fileName.close();
    delay(500);
  } else {
    Serial.println(F("FALHA AO GRAVAR DADOS NO CARTÃO SD"));
    visorDrawMenu(SCREEN_ERROR);
    Serial.println("Erro na abertura do cartao SD, [Utils.cpp - 669]");
    delay(1500);
    loop();
  }
}


void dataloggerWriteFailMqttLog(String payload){
  Serial.println("entrou na funcao WriteFailMqttLog");
  if (!SD.exists("CAD-ERR.txt")){
    Serial.println("tentou criar arquivo");
    SD.open("CAD-ERR.txt", FILE_WRITE);
  } 
  if (!SD.exists("CAD-ERR.txt")){
    Serial.println("criacao do arquivo deu errado");
    if(!SD.begin()){
      visorDrawMenu(SCREEN_ERROR);
      Serial.println("Erro na abertura do cartao SD");
      delay(1500);
      loop();
    }
  }
  Serial.println(fileName);
  fileName.close();
  Serial.println(fileName);
  fileName = SD.open("CAD-ERR.txt", FILE_WRITE);
  Serial.println(fileName);
  if (fileName) {
    Serial.println(F("GRAVANDO DADOS NO CARTÃO SD"));
    fileName.println(payload);         
    fileName.close();
    delay(500);
  } else {
    Serial.println(F("FALHA AO GRAVAR DADOS NO CARTÃO SD"));
    Serial.println("Erro na abertura do cartao SD, [Utils.cpp - 706]");
    delay(1500);
  }
}


String dataloggerGetOperator(String uuid){
  Serial.println("entrou na funcao getOperator");
  if (!SD.exists("CAD-OPE.txt")){
    Serial.println("tentou criar arquivo");
    SD.open("CAD-OPE.txt", FILE_WRITE);
  }
  if (!SD.exists("CAD-OPE.txt")){
    Serial.println("criacao do arquivo deu errado");
    if(!SD.begin(PIN_SS_DATA_LOG)){
      visorDrawMenu(SCREEN_ERROR);
      Serial.println("Erro na abertura do cartao SD, [Utils.cpp - getOperator]");
      delay(1500);
      loop();
    }
  }
  _uuidToCheck = uuid;
  _operatorUuid = "";
  fileName.close();
  delay(50);
  fileName = SD.open("CAD-OPE.txt");
  if (fileName) {
    while (fileName.available())
    {
      visorDrawMenu(SCREEN_PROGRESS);
      _operatorUuid = fileName.readStringUntil(13);
      _operatorLevel = _operatorUuid.substring(_operatorUuid.lastIndexOf(";") + 1);
      _operatorUuid.remove(_operatorUuid.lastIndexOf(";"));
      _operatorName = _operatorUuid.substring(_operatorUuid.lastIndexOf(";") + 1);
      Serial.println(_operatorUuid);
      _operatorUuid.trim();
      _operatorUuid.remove(0,43);
      int length = _operatorUuid.indexOf(";");
      _operatorUuid.remove(length);
      Serial.print(F("Verificação de UUID = "));
      Serial.print(_operatorUuid);
      Serial.print (F(" Sistema <---> Nova Tag "));
      Serial.println (_uuidToCheck);
      if (_uuidToCheck == _operatorUuid){
        return _operatorUuid + "#" + _operatorName + "#" + _operatorLevel;
      }
    }
    return "NO_OPERATOR";
  }
  return "NO_OPERATOR";
}


bool dataloggerCheckOperatorExist(String uuid){
  _uuidToCheck = uuid;
  fileName.close();
  delay(50);
  fileName = SD.open("CAD-OPE.txt");
  if (fileName) {
    while (fileName.available())
    {
      visorDrawMenu(SCREEN_PROGRESS);
      _uuidRead = fileName.readStringUntil(13);
      Serial.println(_uuidRead);
      _uuidRead.trim();
      _uuidRead.remove(0,43);
      int length = _uuidRead.indexOf(";");
      _uuidRead.remove(length);
      Serial.print(F("Verificação de UUID = "));
      Serial.print(_uuidRead);
      Serial.print (F(" Sistema <---> Nova Tag "));
      Serial.println (_uuidToCheck);
      if (_uuidToCheck == _uuidRead){
        return true;
      }
    }
    return false;
  }
}


bool dataloggerCheckOperatorIsAdmin(String uuid){
  _uuidToCheck = uuid;
  fileName.close();
  delay(50);
  fileName = SD.open("CAD-OPE.txt");
  if (fileName) {
    while (fileName.available())
    {
      visorDrawMenu(SCREEN_PROGRESS);
      _uuidRead = fileName.readStringUntil(13);
      _operatorLevel = _uuidRead.substring(_uuidRead.lastIndexOf(";") + 1);
      Serial.println(_uuidRead);
      _uuidRead.trim();
      _uuidRead.remove(0,43);
      int length = _uuidRead.indexOf(";");
      _uuidRead.remove(length);
      Serial.print(F("Verificação de UUID = "));
      Serial.print(_uuidRead);
      Serial.print (F(" Sistema <---> Nova Tag "));
      Serial.println (_uuidToCheck);
      if (_uuidToCheck == _uuidRead){
        if(_operatorLevel == "1"){
          return true;
        }else{
          return false;
        }
      }
    }
    return false;
  }
}


void dataloggerWritePermission(){
  Serial.println("entrou na funcao WritePermission");
  if (!SD.exists("CAD-PER.txt")){
    Serial.println("tentou criar arquivo");
    SD.open("CAD-PER.txt", FILE_WRITE);
  } 
  if (!SD.exists("CAD-PER.txt")){
    Serial.println("cria;áo do arquivo deu errado");
    if(!SD.begin(PIN_SS_DATA_LOG)){
      visorDrawMenu(SCREEN_ERROR);
      Serial.println("Erro na abertura do cartao SD, [Utils.cpp - 882]");
      delay(1500);
      loop();
    }
  }
  Serial.println(fileName);
  fileName.close();
  Serial.println(fileName);
  fileName = SD.open("CAD-PER.txt", FILE_WRITE);
  Serial.println(fileName);
  if (fileName) {
    Serial.println(F("GRAVANDO DADOS NO CARTÃO SD"));
    fileName.print(getTimestamp());
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(getUID());              // NUMERO UNICO DO EQUIPAMENTO
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print("003");                              // CODIGO DA FUNÇÃO
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.println(_UUIDPermission);                  // UID TAG RFID
    fileName.close();
    delay(500);
  } else {
    Serial.println(F("FALHA AO GRAVAR DADOS NO CARTÃO SD"));
    visorDrawMenu(SCREEN_ERROR);
    Serial.println("Erro na abertura do cartao SD, [Utils.cpp - 892]");
    delay(1500);
    loop();
  }
}

bool dataloggerCheckPermissionExist(String uuid){
  Serial.println("entrou na funcao WritePermission");
  if (!SD.exists("CAD-PER.txt")){
    Serial.println("tentou criar arquivo");
    SD.open("CAD-PER.txt", FILE_WRITE);
  } 
  if (!SD.exists("CAD-PER.txt")){
    Serial.println("cria;áo do arquivo deu errado");
    if(!SD.begin(PIN_SS_DATA_LOG)){
      visorDrawMenu(SCREEN_ERROR);
      Serial.println("Erro na abertura do cartao SD, [Utils.cpp - 882]");
      delay(1500);
      loop();
    }
  }
  _uuidToCheck = uuid;
  fileName.close();
  delay(50);
  fileName = SD.open("CAD-PER.txt");
  if (fileName) {
    while (fileName.available())
    {
      visorDrawMenu(SCREEN_PROGRESS);
      _uuidRead = fileName.readStringUntil(13);
      Serial.println(_uuidRead);
      _uuidRead.trim();
      _uuidRead.remove(0,43);
      int length = _uuidRead.indexOf(";");
      _uuidRead.remove(length);
      Serial.print(F("Verificação de UUID = "));
      Serial.print(_uuidRead);
      Serial.print (F(" Sistema <---> Nova Tag "));
      Serial.println (_uuidToCheck);
      if (_uuidToCheck == _uuidRead){
          return true;
      }else{
          return false;
      }
    }
    return false;
  }
}


void dataloggerWriteFuelCharge(){
  Serial.println("entrou na funcao WriteFuelCharger");
  if (!SD.exists("CAD-REG.txt")){
    Serial.println("tentou criar arquivo");
    SD.open("CAD-REG.txt", FILE_WRITE);
  } 
  if (!SD.exists("CAD-REG.txt")){
    Serial.println("cria;áo do arquivo deu errado");
    if(!SD.begin(PIN_SS_DATA_LOG)){
      visorDrawMenu(SCREEN_ERROR);
      Serial.println("Erro na abertura do cartao SD");
      delay(1500);
      loop();
    }
  }
  Serial.println(fileName);
  fileName.close();
  Serial.println(fileName);
  fileName = SD.open("CAD-REG.txt", FILE_WRITE);
  Serial.println(fileName);
  if (fileName) {
    Serial.println(F("GRAVANDO DADOS NO CARTÃO SD"));
    fileName.print(getTimestamp());                  // DATA E HORA
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(getUID());              // NUMERO UNICO DO EQUIPAMENTO
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print("099");                              // CODIGO DA FUNÇÃO
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(_operatorUuid);                   // UID TAG RFID
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(_operatorName);                   // NOME DO VEICULO
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(_operatorLevel);
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(_vehicleUuid);
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(_vehicleName);
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(_vehicleFuel);
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.print(fuelQuantity);
    fileName.print(";");                                // SEPARADOR CONDICIONAL
    fileName.println(COMPANY);
    fileName.close();
    delay(500);
  } else {
    Serial.println(F("FALHA AO GRAVAR DADOS NO CARTÃO SD"));
    visorDrawMenu(SCREEN_ERROR);
    Serial.println("Erro na abertura do cartao SD");
    delay(1500);
    loop();
  }
}
