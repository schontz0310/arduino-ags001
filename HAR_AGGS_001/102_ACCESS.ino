
bool accessValidate(MetodeAccesses metode){
  memset(_buffer, 0, sizeof(_buffer));
  _position = 0;
   String _secret;
  switch (metode)
  {
    case PASSWORD:
      do {
        _keyPressed = keyboardGetKeyNumeric();
        switch (_keyPressed)
        {
          case 'C':
            memset(_buffer, 0, sizeof(_buffer));
            if (_position > 0){
            _position = 0;
            }
          break;
          case 'B':
            if (_position > 0 && _position != 14) {
                _position--;
              }
              if (_position == 14 && _buffer[_position] == ' ') {
                _position--;
              }
              if (_position == 0 && _buffer[_position] == ' ') {
                _position = 0;
              }
              _buffer[_position] = ' ';    
          break;
          case 'A':
            _secret = "";
            for (byte i = 0; i < sizeof(_buffer); i++) {
              _secret.concat(String(_buffer[i]));
            }
            Serial.print("Senha digitada = ");
            Serial.println(_secret);
            if (_secret == SENHA_AGS) {
              Serial.println(F("Senha correta"));
              return true;
            } else {
              Serial.println(F("Senha incorreta"));
              return false;
            }
          break;
          case '*':
            memset(_buffer, 0, sizeof(_buffer));
            if (_position > 0){
            _position = 0;
            }
            loop();
          break;
          case '0':
          if (_position < 15){
            Serial.println("entrou no case 0");
            _buffer[_position] = '0';
            _position++;  
          }
          break;
          
          case '1':
          if (_position < 15){
            Serial.println("entrou no case 1");
            _buffer[_position] = '1';
            _position++;  
          }
          break;
          
          case '2':
          if (_position < 15){
            Serial.println("entrou no case 2");
            _buffer[_position] = '2';
            _position++;  
          }
          break;
          
          case '3':
          if (_position < 15){
            Serial.println("entrou no case 3");
            _buffer[_position] = '3';
            _position++;  
          }
          break;
          
          case '4':
          if (_position < 15){
            Serial.println("entrou no case 4");
            _buffer[_position] = '4';
            _position++;  
          }
          break;
          
          case '5':
          if (_position < 15){
            Serial.println("entrou no case 5");
            _buffer[_position] = '5';
            _position++;  
          }
          break;
          
          case '6':
          if (_position < 15){
            Serial.println("entrou no case 6");
            _buffer[_position] = '6';
            _position++;  
          }
          break;
          
          case '7':
          if (_position < 15){
            Serial.println("entrou no case 7");
            _buffer[_position] = '7';
            _position++;  
          }
          break;
          
          case '8':
          if (_position < 15){
            Serial.println("entrou no case 8");
            _buffer[_position] = '8';
            _position++;  
          }
          break;
          
          case '9':
          if (_position < 15){
            Serial.println("entrou no case 9");
            _buffer[_position] = '9';
            _position++;  
          }
          break;
        }
        Serial.println(_keyPressed);
        visorDrawMenu(SCREEN_ACCCESSES_PASSWORD);
      } while (_keyPressed != '.');
    break;
    case CARD:
    rfid.PCD_Init(SS_SDA_PIN, RST_PIN);
    Serial.println(F("PASSE A TAG DO VEICULO"));
    bool cardIsRead;
    do {
      cardIsRead =  rfidReaderGetID();
      tecla_presionada = keyboard.getKey();
    } while (!cardIsRead);    delay(500);
    Serial.println(rfidReaderIDValue);
    visorReadCard(SCREEN_OPERATOR_SEARCH, "", rfidReaderIDValue);
    delay(500);
    _operatorLevel = dataloggerGetOperator(rfidReaderIDValue);
    Serial.println(_operatorLevel);
    if(_operatorLevel != "NO_OPERATOR"){
      if(dataloggerCheckOperatorIsAdmin(rfidReaderIDValue)){
        return true;
      }else{
        return false;
      }
    }else{
      visorReadCard(SCREEN_OPERATOR_NOT_FOUND, "", rfidReaderIDValue);
      visorDrawMenu(SCREEN_ERROR);
      somErrado();
      delay(1500);
      loop();
    }
    break;  
    default:
    break;
  }
}
