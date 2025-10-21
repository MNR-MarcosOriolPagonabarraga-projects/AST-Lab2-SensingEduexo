#define ADC2N -8.956f // converts raw ADC counts → Newtons
#define N2Nm 0.14f //meters

//Pin to read the load cell
#define LOADCELL_ANALOGPIN A3
 // N samples to correct the offset of the load cell
#define NSAMPLES_OFFSET_CORRECTION 1000

// Global variable to store the offset corrected of the load cell
float offset_load_cell = 460.25;


/*
 * Function: ReadLoadCell
 *  Function to read the channel associated to the connection with the load cell
 *  
 * Inputs: void
 *  
 * Outputs:
 *  -adc_val(float): Value given by the load cell in ADC counts.
 */
float ReadLoadCell(){
  // Read the raw ADC value
  float ADC_val = analogRead(LOADCELL_ANALOGPIN);
  
  // Apply offset correction
  float corrected_adc = ADC_val - offset_load_cell;

  // Convert ADC value → Newtons → Newton-meters
  float torque_Nm = corrected_adc * ADC2N * N2Nm;

  return torque_Nm;
}

/*
 * Function: CorrectOffsetLoadCell
 *  Function to correct the offset of the load cell. The value is stored in offset_load_cell
 *  
 * Inputs: void
 *  
 * Outputs: void
 */
void CorrectOffsetLoadCell(void) {
  float cum_sum_read_load_cell = 0.0;

  Serial.println("Starting load cell offset calibration...");

  for (int i = 0; i < NSAMPLES_OFFSET_CORRECTION; i++) {
    cum_sum_read_load_cell += analogRead(LOADCELL_ANALOGPIN);
    delay(1); // wait 1 millisecond between samples
  }

  // Calculate average offset
  offset_load_cell = cum_sum_read_load_cell / NSAMPLES_OFFSET_CORRECTION;

  Serial.print("Calibration finished. Offset value: ");
  Serial.println(offset_load_cell);
}