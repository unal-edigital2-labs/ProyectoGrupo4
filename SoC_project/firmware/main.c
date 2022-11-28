#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include <irq.h>
#include <uart.h>
#include <console.h>
#include <generated/csr.h>

#include "delay.h"

unsigned int mean(unsigned int in[], int size){
	unsigned int x=0;
	for(int i=0;i<size;i++){

		x=x+in[i];
	}
	unsigned int mean_x=x/size;
	return mean_x;
}

unsigned int freq_count(){
	unsigned int valor ;
	timer0_en_write(0);
	timer0_reload_write(0);
//	printf ("1 \n");
	while(!(RGB_sensor_Out_in_read()));
	timer0_load_write(0xffffffff);
	timer0_en_write(1);
	timer0_update_value_write(1);
	
//	printf ("2 \n");
	while(RGB_sensor_Out_in_read()){
		timer0_update_value_write(1);
		valor = timer0_value_read();
	}
	//printf ("%lu \n", 0xffffffff-valor);

	
	return 0xffffffff-valor;

}

static char *readstr(void)
{
	char c[2];
	static char s[64];
	static int ptr = 0;

	if(readchar_nonblock()) {
		c[0] = readchar();
		c[1] = 0;
		switch(c[0]) {
			case 0x7f:
			case 0x08:
				if(ptr > 0) {
					ptr--;
					putsnonl("\x08 \x08");
				}
				break;
			case 0x07:
				break;
			case '\r':
			case '\n':
				s[ptr] = 0x00;
				putsnonl("\n");
				ptr = 0;
				return s;
			default:
				if(ptr >= (sizeof(s) - 1))
					break;
				putsnonl(c);
				s[ptr] = c[0];
				ptr++;
				break;
		}
	}
	return NULL;
}

static char *get_token(char **str)
{
	char *c, *d;

	c = (char *)strchr(*str, ' ');
	if(c == NULL) {
		d = *str;
		*str = *str+strlen(*str);
		return d;
	}
	*c = 0;
	d = *str;
	*str = c+1;
	return d;
}

static void prompt(void)
{
	printf("RUNTIME>");
}

static void help(void)
{
	puts("Available commands:");
	puts("help                            - this command");
	puts("reboot                          - reboot CPU");
	puts("led                             - led test");
	puts("switch                          - switch test");
	puts("display                         - display test");
	puts("rgbled                          - rgb led test");
	puts("vga                             - vga test");
	puts("infrarrojos                     - infrarrojo_test");
	puts("motor1                          - motor_test");
	puts("RGB_sensor		      - RGB_sensor");
}

static void reboot(void)
{
	ctrl_reset_write(0);
}

/*
static void display_test(void)
{
	int i;
	printf("display_test...\n");
	for(i=0; i<6; i++) {
		display_sel_write(i);
		display_value_write(7);
		display_write_write(1);
	}
}
*/

static void led_test(void)
{
	unsigned int i;
//./l		printf("Test del los leds... se interrumpe con el botton 1\n");
	while(!(buttons_in_read()&1)) {

	for(i=1; i<65536; i=i*2) {
		leds_out_write(i);
		delay_ms(50);
	}
	for(i=32768;i>1; i=i/2) {
		leds_out_write(i);
		delay_ms(50);
	}
	}
	
}


static void switch_test(void)
{
	unsigned short temp2 =0;
	printf("Test del los interruptores... se interrumpe con el botton 1\n");
	while(!(buttons_in_read()&1)) {
		unsigned short temp = switchs_in_read();
		if (temp2 != temp){
			printf("switch bus : %i\n", temp);
			leds_out_write(temp);
			temp2 = temp;
		}
	}
}

static void rgbled_test(void)
{	

	unsigned int T = 128;
	
	while (!(buttons_in_read()&1)) {
	ledRGB_1_r_period_write(T);
	ledRGB_1_g_period_write(T);
	ledRGB_1_b_period_write(T);

	ledRGB_1_r_enable_write(1);
	ledRGB_1_g_enable_write(1);
	ledRGB_1_b_enable_write(1);

	/*
	ledRGB_2_r_period_write(T);
	ledRGB_2_g_period_write(T);
	ledRGB_2_b_period_write(T);
	
	
	ledRGB_2_r_enable_write(1);
	ledRGB_2_g_enable_write(1);
	ledRGB_2_b_enable_write(1);
	*/
	for (unsigned int j=0; j<100; j++){
		ledRGB_1_g_width_write(j);
		for (unsigned int i=0; i<100; i++){
			ledRGB_1_r_width_write(100-i);
			ledRGB_1_b_width_write(i);
			delay_ms(20);
		}	
	}
	}
	
}


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

static void RGB_motor(int rgb_mean[] ){

	//printf("1");
	//RGB_sensor_S_out_write(0b1101);

		int samples=20;
		unsigned int green[20];
		unsigned int blue[20];
		unsigned int red[20];
		unsigned int clear[20];		

		RGB_sensor_S_out_write(0b1101);//green 20%frequency
		for(int i=0; i<samples;i++){
			green[i]=freq_count();
		}

		RGB_sensor_S_out_write(0b1001);//blue 20% frequency

		for(int i=0; i<samples;i++){
			blue[i]=freq_count();
		}
							   //SSSS
		//RGB_sensor_S_out_write(0b S3 S2 S1 S0);
		RGB_sensor_S_out_write(0b0001);//red 20% frequency

		for(int i=0; i<samples;i++){
			red[i]=freq_count();   //toma la
		}


		RGB_sensor_S_out_write(0b0101);

		for(int i=0; i<samples;i++){
			clear[i]=freq_count();   //toma la
		}


	int red_m=mean(red,samples);
	int green_m=mean(green,samples);
	int blue_m=mean(blue,samples);
	int clear_m=mean(clear,samples);


	rgb_mean[0] = red_m;
	rgb_mean[1] = green_m;
	rgb_mean[2] = blue_m;
	rgb_mean[3] = clear_m;
	
	/*printf("color_red: %i\n", red_m);
	printf("color_green: %i\n", green_m);
	printf("color_blue: %i\n", blue_m);
	printf("color_clear: %i\n", clear_m);

	detect_color(red_m,blue_m,green_m,clear_m);*/
}

void detect_color(int red,int blue, int green, int clear){

	if (red<blue && red<green ){
		printf("El color es rojo");
	}else if (green<blue && green<red){	
		printf("El color es verde");
	}else if (blue<red && blue<green){
		printf("El color es azul");
	}

}


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
/*
	unsigned int valor ;
	timer0_en_write(0);
	timer0_reload_write(0);
//	printf ("1 \n");
	while(!(RGB_sensor_Out_in_read()));
	timer0_load_write(0xffffffff);
	timer0_en_write(1);
	timer0_update_value_write(1);
	
//	printf ("2 \n");
	while(RGB_sensor_Out_in_read()){
		timer0_update_value_write(1);
		valor = timer0_value_read();
	}
	//printf ("%lu \n", 0xffffffff-valor);

	
	return 0xffffffff-valor;
*/
}




/*	unsigned int samples=900;
	
	unsigned int out;
	RGB_sensor_S_out_write(13);
	

	int print[samples];
	
	for(int i=0; i<samples; i=i+1){
		print[i]=-1;
	}
	
	
	int i=0;
	while(!(buttons_in_read()) & 1){
	
		out=RGB_sensor_Out_in_read();
	
		print[i]=out;
		i=i+1;
	}
	for(int i =0;i<samples;i=i+1){
		printf("sample_%i",i);
		printf(": %i\n",print[i]);
	}
	
*/	
	

/*
static void clock_micro(void){

	unsigned long time=0;
	
	while(!(buttons_in_read())&1){
		time=time+1;
		
	}
	
	unsigned int micro=clockCyclesToMicroseconds(time);
	printf("micro: %i\n", micro);
	
	
}

static void color_test(void){
	
	int test=1;
	clock_t time_i, time_f;
	
	time_i=clock();
	
	while(test=1){
		test = color_out_in_read();
		
	}
	time_f=clock();
	printf("color_test: %i \n", test);
	
	printf("time: %i \n", time_f);
	int total_time;
	total_time=time_f-time_i;
	
}
*/
/*
static void vga_test(void)
{
	int x,y;
	
	for(y=0; y<480; y++) {
		for(x=0; x<640; x++) {
			vga_cntrl_mem_we_write(0);
			vga_cntrl_mem_adr_write(y*640+x);
			if(x<640/3)	
				vga_cntrl_mem_data_w_write(((int)(x/10)%2^(int)(y/10)%2)*15);
			else if(x<2*640/3) 
				vga_cntrl_mem_data_w_write((((int)(x/10)%2^(int)(y/10)%2)*15)<<4);
			else 
				vga_cntrl_mem_data_w_write((((int)(x/10)%2^(int)(y/10)%2)*15)<<8);
			vga_cntrl_mem_we_write(1);
		}
	}
}
*/
static void loop(){
	unsigned int ON = 0, OFF = 0;
	int rgb_mean [4];
	bool done_001001=0;

	while(1){
		RGB_motor(rgb_mean);
		switch (ESP8266_in_read())
		{
		case 0b000000:
			
			
		
		case 0b100000:
			motor_test(0,1,1,0);
			motor_disp(360);
		/*			//printf("rojo: %i\n",rgb_mean[0]);

			while(rgb_mean[0] >9000 || rgb_mean[0] > rgb_mean[1] || rgb_mean[0] > rgb_mean[2]) {
				RGB_motor(rgb_mean);
				printf("rojo: %i\n",rgb_mean[0]);
				//printf("verde: %i\n",rgb_mean[1]);
				//printf("azul: %i\n",rgb_mean[2]);
				printf("clear: %i\n", rgb_mean[3]);
				infrarrojo_test();

			}
			//printf("RED FOUND\n");

			if (!done_001001){
				printf("rojo: %i\n",rgb_mean[0]);
				printf("azul: %i\n",rgb_mean[2]);
				printf("verde %i\n",rgb_mean[1]);

				motor_disp(90);
				delay_ms(3000);
				motor_disp(-90);
				//printf("holix2");
				done_001001=1;
			}

			//printf("DONE\n");
		*/
		default:
			motor_test(1,0,1,0);
			//printf("estoy es acá");
			//printf("aqui estoy aca");
			break;
		}
		//if ()

	}
}




static void console_service(void)
{
	char *str;
	char *token;

	str = readstr();
	if(str == NULL) return;
	token = get_token(&str);
	if(strcmp(token, "help") == 0)
		help();
	else if(strcmp(token, "reboot") == 0)
		reboot();
	else if(strcmp(token, "led") == 0)
		led_test();
	else if(strcmp(token, "switch") == 0)
		switch_test();
	//else if(strcmp(token, "display") == 0)
	//	display_test();
	else if(strcmp(token, "rgbled") == 0)
		rgbled_test();
//	else if(strcmp(token, "vga") == 0)
//		vga_test();
	else if(strcmp(token, "infrarrojos") == 0)
		infrarrojo_test();
	//else if(strcmp(token, "motor1") == 0)
	//	motor_test();
		
	else if(strcmp(token,"SRGB")==0)
		RGB_sensor_test();
	//else if(strcmp(token,"RGBt")==0)
	//	RGB_motor();
	else if(strcmp(token, "stepper")==0)
		motor_disp(360);
	else if(strcmp(token, "loop")==0)
		loop();
	//else if(strcmp(token,"time")==0)
	//	clock_micro();
	//else if(strcmp(token, "color")==0)
	//	color_test(); 
	/*else if(strcmp)*/
	prompt();
}











int main(void)
{
	#ifdef CONFIG_CPU_HAS_INTERRUPT
	irq_setmask(0);
	irq_setie(1);
	#endif
	uart_init();

	puts("\nSoC - RiscV project UNAL 2022-2"__DATE__" "__TIME__"\n");
	help();
	prompt();

	while(1) {
		console_service();
		
	/*	leds_out_write(15);
		delay_ms(100);
		leds_out_write(240);
		delay_ms(100);
		printf("El programa \n");*/
	}

	return 0;
}
