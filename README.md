# ProyectoGrupo4 - Vehículo Dispensador de Medicamentos Hospitalarios 💊
#### Integrantes 👤
+ Federik Leonardo Fajardo Useche
+ Jose Fernando Murcia Rincón
+ Andres David Rodriguez Soler

#### Proyecto 🦾

En este repositorio se presenta el proyecto correspondiente a Electrónica Digital II 2022-2. El proyecto consiste en un dispensador de medicamentos basados en la FPGA Zybo 7. Con esta tarjeta de desarrollo se busca configurar el procesador y crear los periféricos necesarios para el funcionamiento del dispositivo. 

El carrito dispensador cuenta con un sensor RGB (TCS3200) para encontrar la estación o lugar donde debe parar y dispensar; con un sensor infrarojo (HW511) para poder seguir una linea, la cual será el camino necesario para moverse; y por último cuenta con 3 motores DC de 5V, uno para dispensar mediante un contenedor rotatorio con capacidad de 3 medicamentos diferentes, y dos para hacer posible el movimiento del carrito mediante sus ruedas. Por último fue usada la ESP8266 para hacer posible la comunicación con la FPGA mediante Wi-Fi y la creación de un servidor local con botones capaces de indicar al carrito la estación y el medicamento que debe ser dispensado. 

La configuración del SoC y los perifericos del dispositivo son mostrados a continuación.

## SOC Procesador - Perifericos ⚙️
![DigiMapa](https://user-images.githubusercontent.com/80412854/203686772-221cc740-57fd-4b64-ab0e-1aa64c5b5457.png)

## Periféricos
### Sensor RGB 🌈
El sensor RGB
```
static void RGB_sensor_test(void){
	 
	RGB_sensor_S_out_write(0b1101);

	//delay_us(100);

	unsigned int datos[500];


	int j=0;

	for(int i =0;i<500;i++){

		datos[i]=-1;
	}

	while(j<2000){
		datos[j]=freq_count();
		j=j+1;
	}

	for(int i=0; i<500; i++){
		printf("out: %i\n",datos[i]);
	}
	//unsigned int time=0;

	//RGB_sensor_S_out_write();

	//RGB

	//printf("tiempo = %u", time);
}

```

### Motores 🔩
## Ruedas Carrito
```
static void motor_test(bool EN1,bool EN2,bool EN3 ,bool EN4){
	
	//while(!(buttons_in_read())&1){
		motorEN1_out_write(EN1);
		motorEN2_out_write(EN2);
		motorEN3_out_write(EN3);
		motorEN4_out_write(EN4);
		
		//printf("hola");
		//delay_ms(500);
	//}
}

```
## Dispensador
```
void motor_disp(int degrees){

	int paso1=0b1100;
	int paso2=0b0110;
	int paso3=0b0011;
	int paso4=0b1001;

	if (degrees>0){
		for(int i=0; i< degrees*512/360;i++){
			stepper_out_write(paso1);
			delay_ms(2);
			stepper_out_write(paso2);
			delay_ms(2);
			stepper_out_write(paso3);
			delay_ms(2);
			stepper_out_write(paso4);
			delay_ms(2);
		}
	}else if (degrees<0){

		for (int i=0; i>degrees*512/360;i--){
			stepper_out_write(paso4);
			delay_ms(2);
			stepper_out_write(paso3);
			delay_ms(2);
			stepper_out_write(paso2);
			delay_ms(2);
			stepper_out_write(paso1);
			delay_ms(2);
		}
	}
```

### Infrarrojo ⭕️

```
static void infrarrojo_test(void){
	unsigned int LIR;
	unsigned int RIR;


	if (LIR_in_read() ==0 && RIR_in_read() == 0) motor_test(0,1,1,0);	// DETENER MOTORRES
	if (LIR_in_read() ==1 && RIR_in_read() == 0) motor_test(0,0,1,0);	// MOTORES IZQUIERDA 
	if (LIR_in_read() ==0 && RIR_in_read() == 1) motor_test(0,1,0,0);	// MOTORES DERECHA	
	if (LIR_in_read() ==1 && RIR_in_read() == 1) motor_test(0,0,0,0);	// MOTORES ADELANTE 
	
	/*while(!(buttons_in_read())&1){
		LIR = LIR_in_read();
		RIR = RIR_in_read();
		printf("LIR = %i\n", LIR);
		printf("RIR = %i\n", RIR);
		delay_ms(1000);
	
	}
	*/
}
```

### Tarjeta ESP8266 💻

La tarjeta ESP8266 fue utilizada de tal forma que se pudiera mandar la información de las acciones a realizar por el carrito. La tarjeta de desarrollo cuenta con un módulo wifi y la capacidad de acceder y personalizar una pagina web basada en un servidor local. A través de HTML se crean los botones, se decidió que iban a ser 3 estaciones y 3 posibles medicamentos, es decir, se configuraron 6 botones. La comunicación de la ESP con la FPGA se hizo por medio de GPIO, por lo que cada boton envia una señal que puede tener un valor de 0 ó 1 (3.3V) a través de pines digitales 6, 7, 8, , 9, 10 y 11 de la tarjeta. Con las diferentes combinaciones posibles se programa un comportamiento definido para el carrito en la fpga.

![Pinout NodeMcu](https://user-images.githubusercontent.com/80412854/204703009-41ad69aa-537f-44de-8b36-17f91a4782cc.jpg)

```
// IP: 192.168.43.207/

#include <ESP8266WiFi.h>

// Replace with your network credentials
char* ssid = "Redmi";
char* password = "27c2586bd542";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
      //// botones RBG estaciones
String output10State = "off"; //boton
String output09State = "off"; //
String output08State = "off"; //
      //// botones medicamento a dispensar
String output11State = "off"; //
String output07State = "off"; //
String output06State = "off"; //

// Assign output variables to GPIO pins
      //// GPIO botones RGB 
const int output10 = D0;
const int output09 = D1;
const int output08 = D2;
      //// GPIO medicamento a dispensar
const int output11 = D3;
const int output07 = D4;
const int output06 = D5;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output10, OUTPUT);
  pinMode(output09, OUTPUT);
  pinMode(output08, OUTPUT);
  pinMode(output11, OUTPUT);
  pinMode(output07, OUTPUT);
  pinMode(output06, OUTPUT);
  
  // Set outputs to LOW
  digitalWrite(output10, HIGH);
  digitalWrite(output09, HIGH);
  digitalWrite(output08, HIGH);
  digitalWrite(output11, HIGH);
  digitalWrite(output07, HIGH);
  digitalWrite(output06, HIGH);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /10/on") >= 0) {
              Serial.println("GPIO 10 on");
              output10State = "on";
              digitalWrite(output10, LOW);
            } else if (header.indexOf("GET /10/off") >= 0) {
              Serial.println("GPIO 10 off");
              output10State = "off";
              digitalWrite(output10, HIGH);

              
            } else if (header.indexOf("GET /09/on") >= 0) {
              Serial.println("GPIO 09 on");
              output09State = "on";
              digitalWrite(output09, LOW);
            } else if (header.indexOf("GET /09/off") >= 0) {
              Serial.println("GPIO 09 off");
              output09State = "off";
              digitalWrite(output09, HIGH);

              
            }else if (header.indexOf("GET /08/on") >= 0) {
              Serial.println("GPIO 08 on");
              output08State = "on";
              digitalWrite(output08, LOW);
            } else if (header.indexOf("GET /08/off") >= 0) {
              Serial.println("GPIO 08 off");
              output08State = "off";
              digitalWrite(output08, HIGH);

              
            }else if (header.indexOf("GET /11/on") >= 0) {
              Serial.println("GPIO 11 on");
              output11State = "on";
              digitalWrite(output11, LOW);
            } else if (header.indexOf("GET /11/off") >= 0) {
              Serial.println("GPIO 11 off");
              output11State = "off";
              digitalWrite(output11, HIGH);

              
            }else if (header.indexOf("GET /07/on") >= 0) {
              Serial.println("GPIO 07 on");
              output07State = "on";
              digitalWrite(output07, LOW);
            } else if (header.indexOf("GET /07/off") >= 0) {
              Serial.println("GPIO 07 off");
              output07State = "off";
              digitalWrite(output07, HIGH);

              
            }else if (header.indexOf("GET /06/on") >= 0) {
              Serial.println("GPIO 06 on");
              output06State = "on";
              digitalWrite(output06, LOW);
            } else if (header.indexOf("GET /06/off") >= 0) {
              Serial.println("GPIO 06 off");
              output06State = "off";
              digitalWrite(output06, HIGH);
    
            }
            

    
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            /*
            client.println(".button3 {background-color: #555555;}</style></head>");
            client.println(".button4 {background-color: #555555;}</style></head>");
            client.println(".button5 {background-color: #555555;}</style></head>");
            client.println(".button6 {background-color: #555555;}</style></head>");
            */

                        
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 10  
            client.println("<p>GPIO 10 - State " + output10State + "</p>");
            // If the output10State is off, it displays the ON button       
            if (output10State=="off") {
              client.println("<p><a href=\"/10/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/10/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 13  
            client.println("<p>GPIO 09 - State " + output09State + "</p>");
            // If the output13State is off, it displays the ON button       
            if (output09State=="off") {
              client.println("<p><a href=\"/09/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/09/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //client.println("</body></html>");


            // Display current state, and ON/OFF buttons for GPIO 13  
            client.println("<p>GPIO 08 - State " + output08State + "</p>");
            // If the output13State is off, it displays the ON button       
            if (output08State=="off") {
              client.println("<p><a href=\"/08/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/08/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //client.println("</body></html>");

            // Display current state, and ON/OFF buttons for GPIO 13  
            client.println("<p>GPIO 11 - State " + output11State + "</p>");
            // If the output13State is off, it displays the ON button       
            if (output11State=="off") {
              client.println("<p><a href=\"/11/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/11/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //client.println("</body></html>");

            // Display current state, and ON/OFF buttons for GPIO 13  
            client.println("<p>GPIO 07 - State " + output07State + "</p>");
            // If the output13State is off, it displays the ON button       
            if (output07State=="off") {
              client.println("<p><a href=\"/07/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/07/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //client.println("</body></html>");

            // Display current state, and ON/OFF buttons for GPIO 13  
            client.println("<p>GPIO 06 - State " + output06State + "</p>");
            // If the output11State is off, it displays the ON button       
            if (output06State=="off") {
              client.println("<p><a href=\"/06/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/06/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

```
