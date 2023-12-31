#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  0 
#define SERVOMAX  600
#define USMIN  0 
#define USMAX  2000 
#define SERVO_FREQ 50


uint8_t servonum = 13;
const int WHITE_ANGLE = 2000; // White color position
const int GREY_ANGLE = 1000;  // Grey color position
const int BLACK_ANGLE = 501;    // Black color position

 int whiteThreshold;
 int greyThreshold;
// Pin assignments
#define LIGHT_SENSOR_PIN_1 1 // Analog pin for light sensor
#define LIGHT_SENSOR_PIN_2 2 // Analog pin for light sensor
#define LIGHT_SENSOR_PIN_3 3 // Analog pin for light sensor

// Variables for calibration


void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  pwm.writeMicroseconds(13, GREY_ANGLE);
  pwm.writeMicroseconds(14, GREY_ANGLE);
  pwm.writeMicroseconds(15, GREY_ANGLE);
  calibrateThresholds();

}
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void loop() {
  // Drive each servo one at a time using setPWM()

  int sensorValue1 = analogRead(LIGHT_SENSOR_PIN_1);
  int sensorValue2 = analogRead(LIGHT_SENSOR_PIN_2);
  int sensorValue3 = analogRead(LIGHT_SENSOR_PIN_3);
  
  Serial.print("2: ");
  Serial.print(sensorValue2);
  Serial.print("   1: ");
  Serial.print(sensorValue1);
  Serial.print("   3: ");
  Serial.println(sensorValue3);


//--Servo-1---------------------------------------------------------------------------------------
  if (sensorValue1 <= whiteThreshold){                //Si ve blanco gira hacia adelante
    pwm.writeMicroseconds(13, WHITE_ANGLE);
  }
  else if (sensorValue1 <= greyThreshold){             //Si ve gris para 
    pwm.writeMicroseconds(13, GREY_ANGLE);
  }
  else{             //Si ve negro gira hacia atras
    pwm.writeMicroseconds(13, BLACK_ANGLE);
  }

//--Servo-2----------------------------------------------------------------------------------------

  if (sensorValue2 <= whiteThreshold){                //Si ve blanco gira hacia adelante
    pwm.writeMicroseconds(14, WHITE_ANGLE);
  }
  else if (sensorValue2 <= greyThreshold){             //Si ve gris para 
    pwm.writeMicroseconds(14, GREY_ANGLE);
  }
  else{             //Si ve negro gira hacia atras
    pwm.writeMicroseconds(14, BLACK_ANGLE);
  }

  //--Servo-3----------------------------------------------------------------------------------------

    if (sensorValue3 <= whiteThreshold){                //Si ve blanco gira hacia adelante
    pwm.writeMicroseconds(15, WHITE_ANGLE);
  }
  else if (sensorValue3 <= greyThreshold){             //Si ve gris para 
    pwm.writeMicroseconds(15, GREY_ANGLE);
  }
  else{             //Si ve negro gira hacia atras
    pwm.writeMicroseconds(15, BLACK_ANGLE);
  }
}
  void calibrateThresholds()
{
    // Function to calibrate the thresholds based on user input
    int whiteArray[10];
    int blackArray[10];
    // Print calibration instructions
    Serial.println("Calibration Mode");
    Serial.println("Place the light sensor in front of a grey screen.");
    Serial.println("Press '1' when ready.");

    // Wait for user input
    while (!Serial.available())
    {
        // Wait for serial input
    }

    // Clear the input buffer
    Serial.read();

    // Get the sensor value for grey

    int whiteReadings = 0;
    for (int i = 0; i < 10; i++){
      whiteArray[i] = analogRead(LIGHT_SENSOR_PIN_1);
      whiteReadings += whiteArray[i];
    }
    whiteReadings = whiteReadings /10;
Serial.println("Press '1' when ready.");
Serial.println(whiteReadings);
    int blackReadings = 0;
    for (int i = 0; i < 10; i++){
      blackArray[i] = analogRead(LIGHT_SENSOR_PIN_2);
      blackReadings += blackArray[i];
    }
    blackReadings = blackReadings /10;
Serial.println("Press '1' when ready.");
Serial.println(blackReadings);


    // Calculate the new thresholds
    int greyValue = (blackReadings + whiteReadings)/2;
    greyThreshold = (blackReadings + greyValue)/2;
    whiteThreshold =(greyValue + whiteReadings)/2;

    // Print the grey value
    Serial.print("Grey value: ");
    Serial.println(greyThreshold);
    
    // Print the new thresholds
    Serial.print("White threshold: ");
    Serial.println(whiteThreshold);
    Serial.print("Grey threshold: ");
    Serial.println(greyThreshold);

    // Print calibration complete message
    Serial.println("Calibration complete");
}


