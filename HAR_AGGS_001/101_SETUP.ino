void validateSetup () {
  Serial.println("===========================");
  uint8_t errorValue  = 0;
  for (size_t i = 0; i <= 5; i++)
  {
    Serial.print("== error value = ");
    Serial.println(errorValue);
    Serial.print("== posição = ");
    Serial.println(i);
    Serial.print("== stateCheck = ");
    Serial.println(stateCheck[i]);
    Serial.print("== errorCode = ");
    Serial.println(errorCode[i]);
    if (stateCheck[i] == 1){
      errorValue = errorValue + errorCode[i];
    }
  }
  Serial.print(F("Final error Code = "));
  Serial.println(errorValue);
  Serial.println("===========================\n\n") ;
}
