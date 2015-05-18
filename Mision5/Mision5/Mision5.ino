int sensorValue;

int valoresLuz [100];
int contador = 0;
int valorDefecto = 0;
bool yaContado = false;
void setup()
{
  Serial.begin(9600);  // sets the serial port to 9600
  for(int i = 0; i < 100; i++)
  {
   valoresLuz[i] = 0; 
  }
  //Cogemos la luz ambiente.
  valorDefecto =  analogRead(0);
  Serial.println("EMPEZAMOS EN 3 SEGUNDOS...");
  delay(3000);
}

void loop()
{
  for(int i = 0; i < 100; i++) 
  {
    sensorValue = analogRead(0);       // read analog input pin 0
    if(sensorValue > (valorDefecto + 15) && !yaContado)
    {
        contador++;
        yaContado = true;
    }
    else if(sensorValue <(valorDefecto+15))
      yaContado = false;
    valoresLuz[i] = sensorValue;
    Serial.println(sensorValue, DEC);  // prints the value read
    delay(100);                        // wait 100ms for next reading
  }
  Serial.print("Se ha encendido: ");
  Serial.print(contador);
  Serial.println(" veces.");
  delay(5000);
  Serial.println();
  Serial.println();
  Serial.println("Valores del vector generado en estos 10 segundos:");
  Serial.println("{");
  for(int i = 0; i < 100; i++)
  {
     Serial.print(valoresLuz[i]);
    Serial.print(" ,"); 
  }
  Serial.println();
  Serial.println("}");
  delay(1000000);
}
