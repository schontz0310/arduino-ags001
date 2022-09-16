void somCerto()
{
  digitalWrite(SOM, HIGH);
  for (int j = 0; j < 2; j++)
  {
    tone(SOM, 900);
    digitalWrite(SOM, HIGH);
    digitalWrite(LED_VERDE, HIGH);
    delay(100);
    noTone(SOM);
    digitalWrite(LED_VERDE, LOW);
    delay(100);
  }
  digitalWrite(SOM, LOW);
}

void somErrado()
{
  digitalWrite(SOM, HIGH);
  for (int j = 0; j < 3; j++)
  {
    tone(SOM, 900);
    digitalWrite(SOM, HIGH);
    digitalWrite(LED_VERMELHO, HIGH);
    delay(300);
    noTone(SOM);
    digitalWrite(LED_VERMELHO, LOW);
    delay(50);
  }
  digitalWrite(SOM, LOW);
}
