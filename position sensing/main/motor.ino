#include <Servo.h>

//Pin to read the position sensor
#define MOTORANALOGPIN A0

// Variable to map the position in degrees with the analog values given by the position sensor
#define MINPOSLIMIT 0.0f //degrees
#define MAXPOSLIMIT 90.0f //degrees
int adc_out_min_limit = 290; // Value of the analog value of the potentiometer in zero degrees
int adc_out_max_limit = 490; // Value of the analog value of the potentiometer in 90 degrees

/*
 * Function: CalibratePositionSensor
 *  The user is asked/required to move the EduExo to the position limits and then the values
 *  read by the analog channel are stored in the variables adc_out_min_limit (int) and
 *  adc_out_max_limit (int).
 *  
 * Inputs: void
 *  
 * Outputs: void
 */
void CalibratePositionSensor(void){
  Serial.println("Move the exo to zero degrees and press C to continue");
  int adc_out_min_limit = readMotorOnPressC();
  if (!adc_out_min_limit) {
    return; // If no user C input (other), return to avoid printing the next message
  }
  Serial.println("Move the exo to ninety degrees and press C to continue");
  int adc_out_max_limit = readMotorOnPressC();
}

// Wait for user input C, if provided, return current angle and print it.
// Otherwise, return.
int readMotorOnPressC(void) {
  char incomingChar = 0;

  // Wait until the user presses 'C'
  while (true) {
    if (Serial.available() > 0) {
      incomingChar = Serial.read();
      if (incomingChar == 'C' || incomingChar == 'c') {
        int motor_position = analogRead(MOTORANALOGPIN); // Conversion from bits to degrees.
        Serial.print("Your motor position is at: ");
        Serial.println(motor_position);
        return motor_position;
      } 
      else {
        Serial.println("Exit calibration now!");
        return;
      }
    }
  }
}

/*
 * Function: ReadMotorPosition
 *  Read data received from the position sensor
 *  
 * Inputs: void
 *  
 * Outputs:
 *  -(float): Actual motor position in degrees
 */
float ReadMotorPosition(void) {
  float sensorValue = analogRead(A0);
  float angle = map(sensorValue, adc_out_min_limit, adc_out_max_limit, MINPOSLIMIT, MAXPOSLIMIT);

  return angle;
}
