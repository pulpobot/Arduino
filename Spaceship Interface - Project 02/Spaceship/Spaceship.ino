int switchState = 0;
void setup() 
{  
 //LED pins as Outputs
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  //Switch pin as Input
  pinMode(2, INPUT);
}

void loop() 
{
  //Read the voltage of switch (pin 2)
  switchState = digitalRead(2);
  //if the switch is not pressed
  if(switchState == LOW)
  {
    //Tell the green LED to turn on
    digitalWrite(3, HIGH);
    //And the red ones to turn off
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  //else, the button is pressed
  else
  {
    //Tell the green LED to turn off
    digitalWrite(3, LOW);
    //And the red ones to turn on back and forth
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    
    delay(250);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(250);    
  }
}
