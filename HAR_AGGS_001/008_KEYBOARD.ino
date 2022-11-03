char _lastPressedKey;
int _offset;
int _timesPressed;
int _counter = 0;
int _cursorPossition = 0;
unsigned long _elapsedTime;
unsigned long _lastTime = 0;
char _pressedKey;
String NameValue;

String keyboardGetKeyAlfanumeric (ScreenName targetScreen){
  _offset = 250;
  memset(_buffer, 0, sizeof(_buffer) -1);
  _cursorPossition = 0;
  _screen = targetScreen;
  visorDrawMenu(targetScreen);
  _timesPressed = 0;
  _counter = 0;
  _elapsedTime = millis();
  do{
    _pressedKey = keyboard.getKey();
    if (millis() > _lastTime + _offset)
    {
      _lastTime = millis();
      if (_timesPressed > 0)
      {
        _counter++;
        if (_counter == 3)
        {
          if (_cursorPossition < 14) {
            _cursorPossition++;
          }
          _timesPressed = 0;
        }
      }
    }
    switch (_pressedKey)
    {

      case 'D':
      case '#':
      case '*':
        loop();
      break;

      case 'A':
        if (_lastPressedKey != 'A' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = 'A';
        if (_timesPressed > 1)
        {
          _timesPressed = 1;
          break;
        }
        
        if (_timesPressed == 1)
        { 
          NameValue = ' ';
          for (byte i = 0; i < sizeof(_buffer); i++)
            {
              NameValue.concat(String(_buffer[i]));
              Serial.println(NameValue);
            }
            NameValue.toUpperCase();
            return NameValue;
        }
      break;

      case 'B':
        if (_lastPressedKey != 'B' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = 'B';

        if (_timesPressed > 1)
        {
          _timesPressed = 1;
          break;
        }

        if (_timesPressed == 1)
        {
          if (_cursorPossition > 0 && _cursorPossition != 14){
            _cursorPossition--;
          }
          if (_cursorPossition == 14 && _buffer[_cursorPossition] == ' '){
            _cursorPossition--;
          }
          _buffer[_cursorPossition] = ' ';
          visorDrawMenu(targetScreen); 
        }
        if (_cursorPossition > 0 && _cursorPossition != 14) {
          _cursorPossition--;
        }
        if (_cursorPossition == 14 && _buffer[_cursorPossition] == ' ') {
          _cursorPossition--;
        }
        break;
      break;

      case 'C':
        if (_lastPressedKey != 'C' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = 'C';
        if (_timesPressed > 1)
        {
          _timesPressed = 1;
          break;
        }
        
        if (_timesPressed == 1)
        {
          memset(_buffer, 0, sizeof(_buffer));
          _cursorPossition = 0;
          visorDrawMenu(targetScreen); 
        }
        break;

      case '0':
        if (_lastPressedKey != '0' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '0';
        if (_timesPressed > 5)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = '+';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 2)
        {
          _buffer[_cursorPossition] = '-';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 3)
        {
          _buffer[_cursorPossition] = '*';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 4)
        {
          _buffer[_cursorPossition] = '/';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 5)
        {
          _buffer[_cursorPossition] = '0';
          visorDrawMenu(targetScreen);
        }
      break;

      case '1':
        if (_lastPressedKey != '1' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '1';
        if (_timesPressed > 5)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = '(';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 2)
        {
          _buffer[_cursorPossition] = ')';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 3)
        {
          _buffer[_cursorPossition] = '.';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 4)
        {
          _buffer[_cursorPossition] = ',';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 5)
        {
          _buffer[_cursorPossition] = '1';
          visorDrawMenu(targetScreen);
        }
      break;

      case '2':
        if (_lastPressedKey != '2' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '2';
        if (_timesPressed > 4)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = 'A';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 2)
        {
          _buffer[_cursorPossition] = 'B';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 3)
        {
          _buffer[_cursorPossition] = 'C';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 4)
        {
          _buffer[_cursorPossition] = '2';
          visorDrawMenu(targetScreen);
        }
      break;

      case '3':
        if (_lastPressedKey != '3' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '3';
        if (_timesPressed > 4)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = 'D';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 2)
        {
          _buffer[_cursorPossition] = 'E';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 3)
        {
          _buffer[_cursorPossition] = 'F';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 4)
        {
          _buffer[_cursorPossition] = '3';
          visorDrawMenu(targetScreen);
        }
      break;  

      case '4':
        if (_lastPressedKey != '4' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '4';
        if (_timesPressed > 4)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = 'G';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 2)
        {
          _buffer[_cursorPossition] = 'H';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 3)
        {
          _buffer[_cursorPossition] = 'I';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 4)
        {
          _buffer[_cursorPossition] = '4';
          visorDrawMenu(targetScreen);
        }
      break;

      case '5':
        if (_lastPressedKey != '5' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '5';
        if (_timesPressed > 4)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = 'J';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 2)
        {
          _buffer[_cursorPossition] = 'K';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 3)
        {
          _buffer[_cursorPossition] = 'L';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 4)
        {
          _buffer[_cursorPossition] = '5';
          visorDrawMenu(targetScreen);
        }
      break;

      case '6':
        if (_lastPressedKey != '6' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '6';
        if (_timesPressed > 4)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = 'M';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 2)
        {
          _buffer[_cursorPossition] = 'N';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 3)
        {
          _buffer[_cursorPossition] = 'O';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 4)
        {
          _buffer[_cursorPossition] = '6';
          visorDrawMenu(targetScreen);
        }
      break;

      case '7':
        if (_lastPressedKey != '7' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '7';
        if (_timesPressed > 5)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = 'P';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 2)
        {
          _buffer[_cursorPossition] = 'Q';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 3)
        {
          _buffer[_cursorPossition] = 'R';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 4)
        {
          _buffer[_cursorPossition] = 'S';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 5)
        {
          _buffer[_cursorPossition] = '7';
          visorDrawMenu(targetScreen);
        }
      break;

      case '8':
        if (_lastPressedKey != '8' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '8';
        if (_timesPressed > 4)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = 'T';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 2)
        {
          _buffer[_cursorPossition] = 'U';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 3)
        {
          _buffer[_cursorPossition] = 'V';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 4)
        {
          _buffer[_cursorPossition] = '8';
          visorDrawMenu(targetScreen);
        }
      break;

      case '9':
        if (_lastPressedKey != '9' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '9';
        if (_timesPressed > 5)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = 'W';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 2)
        {
          _buffer[_cursorPossition] = 'X';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 3)
        {
          _buffer[_cursorPossition] = 'Y';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 4)
        {
          _buffer[_cursorPossition] = 'Z';
          visorDrawMenu(targetScreen);
        }
        if (_timesPressed == 5)
        {
          _buffer[_cursorPossition] = '9';
          visorDrawMenu(targetScreen);
        }
      break;

      default:
      break;
    }
  } while (_pressedKey != '?');
  Serial.println("Saiu da funcao do teclado alfa");
}


String keyboardGetKeyNumerics (ScreenName targetScreen){
  _offset = 250;
  memset(_buffer, 0, sizeof(_buffer) -1);
  _cursorPossition = 0;
  _screen = targetScreen;
  visorDrawMenu(targetScreen);
  _timesPressed = 0;
  _counter = 0;
  _elapsedTime = millis();
  do{
    _pressedKey = keyboard.getKey();
    if (millis() > _lastTime + _offset)
    {
      _lastTime = millis();
      if (_timesPressed > 0)
      {
        _counter++;
        if (_counter == 3)
        {
          if (_cursorPossition < 14) {
            _cursorPossition++;
          }
          _timesPressed = 0;
        }
      }
    }
    switch (_pressedKey)
    {

      case 'D':
      case '#':
      case '*':
        loop();
      break;

      case 'A':
        if (_lastPressedKey != 'A' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = 'A';
        if (_timesPressed > 1)
        {
          _timesPressed = 1;
          break;
        }
        
        if (_timesPressed == 1)
        { 
          NameValue = ' ';
          for (byte i = 0; i < sizeof(_buffer); i++)
            {
              NameValue.concat(String(_buffer[i]));
              Serial.println(NameValue);
            }
            NameValue.toUpperCase();
            return NameValue;
        }
      break;

      case 'B':
        if (_lastPressedKey != 'B' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = 'B';

        if (_timesPressed > 1)
        {
          _timesPressed = 1;
          break;
        }

        if (_timesPressed == 1)
        {
          if (_cursorPossition > 0 && _cursorPossition != 14){
            _cursorPossition--;
          }
          if (_cursorPossition == 14 && _buffer[_cursorPossition] == ' '){
            _cursorPossition--;
          }
          _buffer[_cursorPossition] = ' ';
          visorDrawMenu(targetScreen); 
        }
        if (_cursorPossition > 0 && _cursorPossition != 14) {
          _cursorPossition--;
        }
        if (_cursorPossition == 14 && _buffer[_cursorPossition] == ' ') {
          _cursorPossition--;
        }
        break;
      break;

      case 'C':
        if (_lastPressedKey != 'C' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = 'C';
        if (_timesPressed > 1)
        {
          _timesPressed = 1;
          break;
        }
        
        if (_timesPressed == 1)
        {
          memset(_buffer, 0, sizeof(_buffer));
          _cursorPossition = 0;
          visorDrawMenu(targetScreen); 
        }
        break;

      case '0':
        if (_lastPressedKey != '0' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '0';
        if (_timesPressed > 1)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = '0';
          visorDrawMenu(targetScreen);
        }
      break;

      case '1':
        if (_lastPressedKey != '1' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '1';
        if (_timesPressed > 1)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = '1';
          visorDrawMenu(targetScreen);
        }
      break;

      case '2':
        if (_lastPressedKey != '2' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '2';
        if (_timesPressed > 1)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = '2';
          visorDrawMenu(targetScreen);
        }
      break;

      case '3':
        if (_lastPressedKey != '3' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '3';
        if (_timesPressed > 1)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = '3';
          visorDrawMenu(targetScreen);
        }
      break;  

      case '4':
        if (_lastPressedKey != '4' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '4';
        if (_timesPressed > 1)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = '4';
          visorDrawMenu(targetScreen);
        }
      break;

      case '5':
        if (_lastPressedKey != '5' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '5';
        if (_timesPressed > 1)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = '5';
          visorDrawMenu(targetScreen);
        }
      break;

      case '6':
        if (_lastPressedKey != '6' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '6';
        if (_timesPressed > 1)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = '6';
          visorDrawMenu(targetScreen);
        }
      break;

      case '7':
        if (_lastPressedKey != '7' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '7';
        if (_timesPressed > 1)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = '7';
          visorDrawMenu(targetScreen);
        }
      break;

      case '8':
        if (_lastPressedKey != '8' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '8';
        if (_timesPressed > 1)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = '8';
          visorDrawMenu(targetScreen);
        }
      break;

      case '9':
        if (_lastPressedKey != '9' && _timesPressed > 0)
        {
          _timesPressed = 0;
        }
        _elapsedTime = millis();
        _timesPressed++;
        _counter = 0;
        _lastPressedKey = '9';
        if (_timesPressed > 1)
        {
          _timesPressed = 1;
        }
        if (_timesPressed == 1)
        {
          _buffer[_cursorPossition] = '9';
          visorDrawMenu(targetScreen);
        }
      break;

      default:
      break;
    }
  } while (_pressedKey != '?');
  Serial.println("Saiu da funcao do teclado alfa");
}


char keyboardGetKeyNumeric(){
  do{
  _pressedKey = keyboard.getKey();
  } while (!_pressedKey);
  return _pressedKey;
}

  
