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

La tarjeta ESP8266 fue utilizada de tal forma que se pudiera mandar la información de las acciones a realizar por el carrito. La tarjeta de desarrollo cuenta con un módulo wifi y la capacidad de acceder y personalizar una pagina web basada en un servidor local. A través de HTML se crean los botones, se decidió que iban a ser 3 estaciones y 3 posibles medicamentos, es decir, se configuraron 6 botones. La comunicación de la ESP con la FPGA se hizo por medio de GPIO, por lo que cada boton envia una señal que puede tener un valor de 0 ó 1 (3.3V). Con las diferentes combinaciones posibles se programa un comportamiento definido para el carrito.
