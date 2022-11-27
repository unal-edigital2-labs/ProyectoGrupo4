# ProyectoGrupo4 - Vehículo Dispensador de Medicamentos Hospitalarios 💊
#### Integrantes 👤
+ Federik Leonardo Fajardo Useche
+ Jose Fernando Murcia Rincón
+ Andres David Rodriguez Soler

#### Proyecto 🦾

En este repositorio se presenta el proyecto correspondiente a Electrónica Digital II 2022-2. El proyecto consiste en un dispensador de medicamentos basados en la FPGA Zybo 7. Con esta tarjeta de desarrollo se busca configurar el procesador y crear los periféricos necesarios para el funcionamiento del dispositivo. 

El carro dispensador cuenta con un sensor RGB (TCS3200) para encontrar la estación o lugar donde debe parar y dispensar; con dos sensores infrarojo (HW511) para poder seguir una linea y navegar de estación a estación, un modulo L298N para controlar la activación de dos motores de 5V DC que efectuan el movimiento del carro, con un motor paso a paso para realizar la dispensación y con un ESP8266 para enlazar mediante WiFi nuestro carro a una app diseñada especificamente para el control del carro con la cual se efectuan las ordenes de estación a dirigirse y medicamento a dispensar.

A continuación se presenta de manera esquemática el diagrama de bloques del SoC junto a los perifericos que le integran 

## SOC Procesador - Perifericos ⚙️
![DigiMapa](https://user-images.githubusercontent.com/80412854/203686772-221cc740-57fd-4b64-ab0e-1aa64c5b5457.png)

## Periféricos

  ### Driver modulo L298N 

El proyecto inicio realizando el driver para el modulo L298N el cual envia las señales de activación/desactivación de los motores 5V DC. En esta primera etapa fue importante consultar el datasheet del L298N, donde se identificó entre las capacidades más sobresalientes de este módulo la división de la etapa de potencia de la etapa de control; dado lo anterior, se pudo realizar la conexión directa de las señales de control entre la FPGA y este modulo desde un terminal Pmod hacia las terminales de IN1, IN2, IN3 y IN4. La alimentación de potencia del L298N se realizó mediante una fuente externa de 12V y se verifico su correcta operación para no afectar el regulador interno ni comprometer su correcta operación.

Se identifico que la mejor manera de poder tener a disposición las señales de control de la FPGA al L298N en el SoC fue a traves de la definición proveida para terminales GPIO. Como las entradas IN1, IN2, IN3 y IN4  en el L298N requieren estados HIGH/LOW el SoC debe manejar y enviar este mismo tipo de señales, con lo cual al manejarles como GPIO fue bastante apropiado.  

  ### Sensores infrarrojo 

  ### Sensor RGB 🌈

  ### Motor Paso a Paso 🔩

  ### Infrarrojo ⭕️
