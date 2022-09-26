void rfidReaderBegin() {
  rfid.PCD_Init();
  rfid.PCD_SetRegisterBitMask(rfid.RFCfgReg, (0x07<<4));
  if (rfid.PCD_PerformSelfTest() > 0) {
    Serial.println(F("RFID OK"));
    statusCheck = 0;
    stateCheck[2] = 0;
    somCerto();
  }  else {
    Serial.println(F("RFID ERROR"));
    statusCheck = 1;
    stateCheck[2] = 1;
    somErrado();
  }
}

bool rfidReaderGetID(){
  rfidReaderIDValue = "";
  String _value = "";
  if ( ! rfid.PICC_IsNewCardPresent()) {
    return 0;
  }
  if ( ! rfid.PICC_ReadCardSerial()) {
    return 0;
  }

  for (byte i = 0; i < rfid.uid.size; i++)
  {
    _value.concat(String(rfid.uid.uidByte[i] < 0x10 ? "0" : ""));
    _value.concat(String(rfid.uid.uidByte[i], HEX));
  }
  _value.toUpperCase();
  rfidReaderIDValue = _value;
  rfid.PICC_HaltA();
  return 1;
}
