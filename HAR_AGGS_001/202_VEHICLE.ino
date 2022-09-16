
String vehicleRead(){
  Serial.println(F("==== FUNCAO VEICULO =========================================="));
  String _vehicle = "";
  do {
    visorReadCard(SCREEN_VEHICLE_READ, "", "");
    rfid.PCD_Init(SS_SDA_PIN, RST_PIN);
    Serial.println(F("PASSE A TAG DO VEICULO"));
    do {
      successRead = rfidReaderGetID();
      tecla_presionada = keyboard.getKey();
    } while (!successRead);
    Serial.println(rfidReaderIDValue);
    visorReadCard(SCREEN_VEHICLE_SEARCH, "", rfidReaderIDValue);
    _vehicle = dataloggerGetVehicle(rfidReaderIDValue);
    Serial.println(_vehicle);
    if(_vehicle != "NO_VEHICLE"){
    visorReadCard(SCREEN_VEHICLE_FOUND,
    _vehicle.substring(_vehicle.indexOf("#") + 1, _vehicle.lastIndexOf("#")), 
    rfidReaderIDValue);
    somCerto();
    return _vehicle;
    }else{
      visorReadCard(SCREEN_VEHICLE_NOT_FOUND, "", rfidReaderIDValue);
      visorDrawMenu(SCREEN_ERROR);
      somErrado();
      delay(1500);
      loop();
    }
    return "error";
    delay(100);
  } while (status != 1);
  return "error";
}
