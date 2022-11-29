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

### Motor Paso a Paso 🔩

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

### Infrarrojo ⭕️

### Tarjeta ESP8266 💻
