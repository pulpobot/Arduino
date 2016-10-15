const int sensorPin = A0;
float baselineTemp = 20.0;

void setup() 
{
  //Open a serial port (connects Arduino to PC)
  Serial.begin(9600);
  //Setup all the LEDS to Output and turned off
  for(int pinNumber = 2; pinNumber < 5; pinNumber++)
  {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
  
  // Calibrate during the first five seconds, to obtain the ambient temperature
  int sensorValue = 0;
  float voltage = 0;
  float temperature = 0;
  while (millis() < 2000) 
  {
    Serial.println("Calibrating Value: " + (String)baselineTemp);
    sensorValue = analogRead(sensorPin);
    voltage = (sensorValue/1024.0) * 5;
    temperature = (voltage - 0.55) / 0.01; //* 100;
    // record the maximum temperature value
    if (temperature > baselineTemp) 
    {
      baselineTemp = temperature;
    }
    delay(1);
  } 
  
}

void loop() 
{
  //Read the sensor value (0 to 1023)
  int sensorVal = analogRead(sensorPin);
  //Debug the value
  Serial.print("Sensor Value: " + (String)sensorVal);
  
  //The voltage of the pin is between 0 and 5 volts
  //Convert the ADC reading to voltage
  float voltage = (sensorVal/1024.0) * 5;
  Serial.print(", Volts: ");
  Serial.print(voltage);
  /*For the TMP36GZ (BC547), every 10milivolts is 1 Celsius degree change
    He can read from −55 to +150 Celsius.
    That means that every 0.01 in the voltage variable is a 
    Celsius degree, and if we remove 0.55 on the voltage
    we are only "reading" values above 0 degrees    
  */
  //Set an offset to not read < 0 degrees (-0.55 in voltage)
  float temperature = (voltage - 0.55) / 0.01; //* 100;
  Serial.print(", degrees C: " + (String)temperature);
  Serial.println("");  
  
  //For every two degrees up to the baseline, turn on a LED
  if(temperature < baselineTemp)
  {
     digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(4, LOW);     
  }
  else if(temperature >= baselineTemp + 2 && temperature < baselineTemp + 4)
  {
     digitalWrite(2, HIGH);
     digitalWrite(3, LOW);
     digitalWrite(4, LOW);
  }  
  else if(temperature >= baselineTemp + 4 && temperature < baselineTemp + 6)
  {
     digitalWrite(2, HIGH);
     digitalWrite(3, HIGH);
     digitalWrite(4, LOW);
  }  
  else if(temperature >= baselineTemp + 6)
  {
     digitalWrite(2, HIGH);
     digitalWrite(3, HIGH);
     digitalWrite(4, HIGH);
  }
  
  //Add a delay, due to the ADC not able to read that fast, avoiding erratic values
  delay(100);
}
