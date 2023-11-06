#include <SoftwareSerial.h>

SoftwareSerial softSerial(10, 11); // RX, TX 

const int MOTOR_PIN_1 = 3;
const int MOTOR_PIN_2 = 5;

const int MOTOR_1_SETTING = 4;
const int MOTOR_2_SETTING = 6;

const int PING_PIN_IN = 22;
const int PING_PIN_OUT = 24;
int speed = 0;
void setup() 
{ 
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_1_SETTING, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(MOTOR_2_SETTING, OUTPUT);
  
  pinMode(PING_PIN_IN, INPUT);
  pinMode(PING_PIN_OUT, OUTPUT);

  pinMode(13, OUTPUT);
  
  Serial.begin(9600);
  softSerial.begin(9600); 
  
  Serial.println("Speed 1 to 255, 0 will stop the motor");
  
  digitalWrite(MOTOR_1_SETTING, LOW);
  analogWrite(MOTOR_PIN_1, LOW); 
  digitalWrite(MOTOR_2_SETTING, LOW);
  analogWrite(MOTOR_PIN_2, LOW);

  digitalWrite(13, LOW);
   
} 
 
 
void loop() 
{  

  bool obstacleFound = false; 
  while(1)
  {
  /*
    if (readPing() < 20)
    {     
      stopCar();
      
      while(readPing()< 20); //idle until obstacle is further away
      
      driveCar(); 
    }
    */
    if (softSerial.available())
    {
      
      char input = softSerial.read();
      Serial.println(input);     
      switch(input)
      {
        case 'f':
          driveCar();
        break;

        case 's':
          stopCar();
        break;

        case 'r': 
          turnRight();
        break;

        case 'l':
          turnLeft();
        break;  
      }

    }
      
  }

}

void driveCar()
{
    digitalWrite(13, HIGH);
    Serial.println("driveCar");
    //motor 1
    digitalWrite(MOTOR_1_SETTING, HIGH); //om HIGH, hög pwm = låg fart
    analogWrite(MOTOR_PIN_1, 200);

    //motor 2
    digitalWrite(MOTOR_2_SETTING, HIGH); //om HIGH, hög pwm = låg fart
    analogWrite(MOTOR_PIN_2, 200);
  
}


void stopCar()
{
    digitalWrite(13, LOW);
    Serial.println("stopCar");
    //motor 1
    digitalWrite(MOTOR_1_SETTING, LOW);
    analogWrite(MOTOR_PIN_1, LOW);

    //motor 2
    digitalWrite(MOTOR_2_SETTING, LOW);
    analogWrite(MOTOR_PIN_2, LOW);
  
}

void turnRight()
{
  digitalWrite(13, LOW);
  Serial.println("turnRight");
  //stop right motor
  digitalWrite(MOTOR_2_SETTING, LOW);
  analogWrite(MOTOR_PIN_2, LOW);

  delay(500);

  driveCar();
}



void turnLeft()
{
  digitalWrite(13, LOW);
  Serial.println("turnLeft");
  //stop left motor
  digitalWrite(MOTOR_1_SETTING, LOW);
  analogWrite(MOTOR_PIN_1, LOW);

  delay(500);

  driveCar();

  
}

int readPing()
{
  digitalWrite(22, LOW);
  digitalWrite(22, HIGH);
  delayMicroseconds(20); 
  digitalWrite(22, LOW);

  unsigned long int duration = pulseIn(24, HIGH, 20000);
  
  unsigned long int distance = (duration/2)/29;
  
  //no obstacles found, return a big value
  if (duration == 0)
  {
    return 300;
  }
  else
  {
    return distance;  
  }
  
}


/*
        speed = Serial.parseInt();
         
        if (speed > 0 && speed <= 255)
        {
          Serial.print("Speed: ");
          Serial.println(speed);
          digitalWrite(MOTOR_1_SETTING, HIGH); //om HIGH, hög pwm = låg fart
          analogWrite(MOTOR_PIN_1, speed);
          
        }
        else if (speed > 255)
        {
          Serial.print("Speed out of range ");
          Serial.println(speed);
        }
    
        else
        {
          Serial.print("Stop");
          digitalWrite(MOTOR_1_SETTING, LOW);
          analogWrite(MOTOR_PIN_1, LOW);
        }
      }
    
      delay(100);


    }
} 
*/
