
#define BINS_SIZE 256
#define CALIBRATION_SIZE 50000

#define NO_BIAS_REMOVAL 0                            // bias removal scheme
#define EXCLUSIVE_OR 1
#define VON_NEUMANN 2

#define ASCII_BYTE 0                                 // formats for output
#define BINARY 1      
#define ASCII_BOOL 2

/***  Configure the RNG **************/
int bias_removal = NO_BIAS_REMOVAL;
int output_format = BINARY;
float baud_rate = 115200;
/*************************************/


unsigned int bins[BINS_SIZE];
int adc_pin = 0;
int led_pin = 13;
boolean initializing = true;
unsigned int calibration_counter = 0;


void setup(){
  pinMode(led_pin, OUTPUT);
  Serial.begin(baud_rate);
  for (int i=0; i < BINS_SIZE; i++){
    bins[i] = 0; 
  }
}

void loop(){
  byte threshold;                                     // byte stores an integer from 0 to 255
  int adc_value = analogRead(adc_pin);
  byte adc_byte = adc_value >> 2;                     // mapping the value to 0-255 range
  if(calibration_counter >= CALIBRATION_SIZE){
    threshold = findThreshold();                      // set the threshold once calibration is over
    initializing = false;
  }
  if(initializing){
    calibrate(adc_byte);
    calibration_counter++;
  } 
  else{
    
   
      processInput(adc_byte, threshold);              // process any input that is fed after the calibration is over
    
  }
}

void processInput(byte adc_byte, byte threshold){
  boolean input_bool;
  input_bool = (adc_byte < threshold) ? 1 : 0;        // compare the input to obtained threshold value and give appropriate output
  switch(bias_removal){
    case VON_NEUMANN:                                 // feeds the output of the previous step to the selected bias removal scheme 
      vonNeumann(input_bool); 
      break;
    case EXCLUSIVE_OR:
      //exclusiveOr(input_bool);
      break;
    case NO_BIAS_REMOVAL:
      buildByte(input_bool);
      break;
  }
}


void buildByte(boolean input){                        // responds to the calls of debiasing functions and gives output according to the chosen format
  static int byte_counter = 0; 
  static unsigned int out = 0;

  //if (input == 1){
       //Serial.print(input);       
    //   out = (out << 1) | 0x01;
       
  //}
  //else{
       //Serial.print(input);       
    //   out = (out << 1); 
  //}
  //byte_counter++;
  //byte_counter %= 1;
  //if(byte_counter == 0){

    
    if (output_format == ASCII_BYTE) Serial.println(input, DEC); //Serial.print(", ");
    if (output_format == BINARY) Serial.print(input, BIN);
    //Serial.println("");
    //out = 0;  
  //}
  if (output_format == ASCII_BOOL) Serial.print(input, DEC);
  
  
}


void calibrate(byte adc_byte){                       // while calibration is on, it updated the frequencies in the bins
  bins[adc_byte]++;  
}

unsigned int findThreshold(){                        // screens the received data while calibration and sets threshold as the median
  unsigned long half;
  unsigned long total = 0;
  int i;

  for(i=0; i < BINS_SIZE; i++){
    total += bins[i];
  }	

  half = total >> 1;
  total = 0;
  for(i=0; i < BINS_SIZE; i++){
    total += bins[i];
    if(total > half){
      break;
    }	
  }
  return i;
}



