/***  
 *   Complete project details at https://randomnerdtutorials.com  
*********/

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 6
#define S1 7
#define S2 9
#define S3 8
#define sensorOut 11
#define del 5
#define samples 50

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
//int samples = 50;
int redMean = 0;
int greenMean = 0;
int blueMean = 0;

int redRGB = 0;
int blueRGB = 0;
int greenRGB = 0;


void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
  Serial.begin(9600);
}
void loop() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  //redFrequency = pulseIn(sensorOut, LOW);
  for (int i=0; i<samples; i++){
    redFrequency = pulseIn(sensorOut, LOW);
    redMean=redMean+redFrequency;
    delay(del);
  }

  redMean=redMean/samples;

  
   // Printing the RED (R) value
 // Serial.print("R = ");
  //Serial.print(redMean);
  //delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  
  for (int i=0; i<samples; i++){
    greenFrequency = pulseIn(sensorOut, LOW);
    greenMean=greenMean+greenFrequency;
    delay(del);
  }

  greenMean=greenMean/samples;
  
  // Printing the GREEN (G) value  
  //Serial.print(" G = ");
  //Serial.print(greenMean);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  
  for (int i=0; i<samples; i++){
    blueFrequency = pulseIn(sensorOut, LOW);
    blueMean=blueMean+blueFrequency;
    delay(del);
  }

  blueMean=blueMean/samples;
  
  // Printing the BLUE (B) value 
  //Serial.print(" B = ");
  //Serial.println(blueMean);


  redRGB=map(redMean,180,14,0,255);
  blueRGB=map(blueMean,180,14,0,255);
  greenRGB=map(greenMean,180,14,0,255);


  if (blueMean<redMean && blueMean < greenMean){
    Serial.println("El color es azul");  
  }

  
  if (greenMean<redMean && greenMean < blueMean){
    Serial.println("El color es verde");  
  }

  
  if (redMean<blueMean && redMean < greenMean){
    Serial.println("El color es rojo");  
  }


  Serial.print("RGB = [");
  Serial.print(redRGB);
  Serial.print(", ");
  Serial.print(greenRGB);
  Serial.print(", ");
  Serial.print(blueRGB);
  Serial.println("]");
}
