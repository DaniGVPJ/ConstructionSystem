// Constants for servo positions
const int WHITE_ANGLE = 2000; // White color position
const int GREY_ANGLE = 1000;  // Grey color position
const int BLACK_ANGLE = 0;    // Black color position

// Pin assignments
#define LIGHT_SENSOR_PIN_1 0 // Analog pin for light sensor
#define LIGHT_SENSOR_PIN_2 2 // Analog pin for light sensor
#define LIGHT_SENSOR_PIN_3 3 // Analog pin for light sensor

// Variables for calibration
int whiteThreshold = 380;
int greyThreshold = 700;

void setup()
{
    // Initialize serial communication
    Serial.begin(9600);

    // Calibrate the thresholds
    calibrateThresholds();
}

void loop()
{
    // Read the value from the light sensor
    int sensorValue = analogRead(LIGHT_SENSOR_PIN_1);

    // Print the sensor value for debugging
    Serial.println(sensorValue);

    // Determine the color based on the sensor value
    if (sensorValue < whiteThreshold)
    {
        // Set servo to white color position
        pwm.writeMicroseconds(15, WHITE_ANGLE);
    }
    else if (sensorValue > greyThreshold)
    {
        // Set servo to black color position
        pwm.writeMicroseconds(15, BLACK_ANGLE);
    }
    else
    {
        // Set servo to grey color position
        pwm.writeMicroseconds(15, GREY_ANGLE);
    }
}

void calibrateThresholds()
{
    // Function to calibrate the thresholds based on user input

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
    int greyValue = analogRead(LIGHT_SENSOR_PIN_1);

    // Print the grey value
    Serial.print("Grey value: ");
    Serial.println(greyValue);

    // Calculate the new thresholds
    whiteThreshold = (greyValue + whiteThreshold) / 2;
    greyThreshold = (greyValue + greyThreshold) / 2;

    // Print the new thresholds
    Serial.print("White threshold: ");
    Serial.println(whiteThreshold);
    Serial.print("Grey threshold: ");
    Serial.println(greyThreshold);

    // Print calibration complete message
    Serial.println("Calibration complete");
}