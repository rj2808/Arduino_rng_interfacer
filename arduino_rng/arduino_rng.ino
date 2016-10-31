
#define BINS_SIZE 256
#define CALIBRATION_SIZE 50000

#define NO_BIAS_REMOVAL 0
#define EXCLUSIVE_OR 1
#define VON_NEUMANN 2

#define ASCII_BYTE 0
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
  byte threshold;
  int adc_value = analogRead(adc_pin);
  byte adc_byte = adc_value >> 2;
  if(calibration_counter >= CALIBRATION_SIZE){
    threshold = findThreshold();
    initializing = false;
  }
  if(initializing){
    calibrate(adc_byte);
    calibration_counter++;
  } 
  else{
    
   
      processInput(adc_byte, threshold);
    
  }
}

void processInput(byte adc_byte, byte threshold){
  boolean input_bool;
  input_bool = (adc_byte < threshold) ? 1 : 0;
  switch(bias_removal){
    case VON_NEUMANN:
      //vonNeumann(input_bool); 
      break;
    case EXCLUSIVE_OR:
      //exclusiveOr(input_bool);
      break;
    case NO_BIAS_REMOVAL:
      buildByte(input_bool);
      break;
  }
}


void buildByte(boolean input){
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


void calibrate(byte adc_byte){
  bins[adc_byte]++;  
}

unsigned int findThreshold(){
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

void blinkLed(){
  digitalWrite(led_pin, HIGH);
  delay(3);
  digitalWrite(led_pin, LOW);
}


