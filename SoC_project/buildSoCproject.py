#!/usr/bin/env python3

from migen import *
from migen.genlib.io import CRG
from migen.genlib.cdc import MultiReg

## debe dejar solo una tarjeta
# import tarjetas.digilent_nexys4 as tarjeta # si usa tarjeta nexy 4 
# import tarjetas.nexys4ddr as tarjeta # si usa tarjeta nexy 4 4DRR
import tarjetas.digilent_zybo_z7 as tarjeta # si usa tarjeta zybo z7
# import tarjetas.c4e6e10 as tarjeta

from litex.soc.integration.soc_core import *
from litex.soc.integration.builder import *
from litex.soc.interconnect.csr import *

from litex.soc.cores import gpio
from litex.soc.cores import pwm
from module import rgbled
from module import vgacontroller
from module.display import SevenSegmentDisplay

# BaseSoC ------------------------------------------------------------------------------------------

class BaseSoC(SoCCore):
	def __init__(self):
		sys_clk_freq = int(125e6)
		platform = tarjeta.Platform()
		# SoC with CPU
		SoCCore.__init__(self, platform,
# 			cpu_type="picorv32",
			cpu_type="vexriscv",
			clk_freq=125e6,
			integrated_rom_size=0x8000,
			integrated_sram_size=0x1000,
			integrated_main_ram_size=20*1024)

		# Clock Reset Generation
		self.submodules.crg = CRG(platform.request("clk"), platform.request("cpu_reset"))

		# Leds
		SoCCore.add_csr(self,"leds")
		user_leds = Cat(*[platform.request("led", i) for i in range(4)])
		self.submodules.leds = gpio.GPIOOut(user_leds)
		
		# Switchs
		SoCCore.add_csr(self,"switchs")
		user_switchs = Cat(*[platform.request("sw", i) for i in range(4)])
		self.submodules.switchs = gpio.GPIOIn(user_switchs)
		
		# Buttons  ("btnl", 0, Pins("P17"), IOStandard("LVCMOS33")),

		SoCCore.add_csr(self,"buttons")
		user_buttons = Cat(*[platform.request("btn%c" %c) for c in ['c','d','u' ]])
		self.submodules.buttons = gpio.GPIOIn(user_buttons)
		

		# RGB leds
		SoCCore.add_csr(self,"ledRGB_1")
		self.submodules.ledRGB_1 = rgbled.RGBLed(platform.request("ledRGB",1))
		
		##SENSORES INFRARROJO
		#Sensor Infrarrojo Izquierdo 
		SoCCore.add_csr(self,"LIR")
		pads_LIR = Cat(*[platform.request("LIR",i) for i in range(1)])
		self.submodules.LIR = gpio.GPIOIn(pads_LIR)
		#Sensor Infrarrojo Izquierdo 
		SoCCore.add_csr(self,"RIR")
		pads_RIR = Cat(*[platform.request("RIR",i) for i in range(1)])
		self.submodules.RIR = gpio.GPIOIn(pads_RIR)
		
		#RGB sensor Color S0 S1 S2 S3 Out RGB_Sensor_EN
		SoCCore.add_csr(self,"RGB_sensor_S")
		pads_RGB_sensor_S = Cat(*[platform.request("RGB_sensor_S", i) for i in range(4)])
		self.submodules.RGB_sensor_S = gpio.GPIOOut(pads_RGB_sensor_S)
		#RGB_Sensor_EN
		SoCCore.add_csr(self,"RGB_sensor_EN")
		pads_RGB_sensor_EN = Cat(*[platform.request("RGB_sensor_EN", i) for i in range(1)])
		self.submodules.RGB_sensor_EN = gpio.GPIOOut(pads_RGB_sensor_EN)
		#RGB_Sensor_Out
		SoCCore.add_csr(self,"RGB_sensor_Out")
		pads_RGB_sensor_Out = Cat(*[platform.request("RGB_sensor_Out", i) for i in range(1)])
		self.submodules.RGB_sensor_Out = gpio.GPIOIn(pads_RGB_sensor_Out)
		
		
		##ENABLES MOTORES
		
		#MotorEN1
		SoCCore.add_csr(self,"motorEN1")
		pads_motorEN1 = Cat(*[platform.request("motorEN1", i) for i in range(1)])
		self.submodules.motorEN1 = gpio.GPIOOut(pads_motorEN1)
		#MotorEN2
		SoCCore.add_csr(self,"motorEN2")
		pads_motorEN2 = Cat(*[platform.request("motorEN2", i) for i in range(1)])
		self.submodules.motorEN2 = gpio.GPIOOut(pads_motorEN2)
		#MotorEN2
		SoCCore.add_csr(self,"motorEN3")
		pads_motorEN3 = Cat(*[platform.request("motorEN3", i) for i in range(1)])
		self.submodules.motorEN3 = gpio.GPIOOut(pads_motorEN3)
		#MotorEN2
		SoCCore.add_csr(self,"motorEN4")
		pads_motorEN4 = Cat(*[platform.request("motorEN4", i) for i in range(1)])
		self.submodules.motorEN4 = gpio.GPIOOut(pads_motorEN4)
		
		
		#
		#SoCCore.add_csr(self,)
		

		#stepper
		SoCCore.add_csr(self,"stepper")
		pads_stepper = Cat(*[platform.request("stepper", i) for i in range(4)])
		self.submodules.stepper = gpio.GPIOOut(pads_stepper)
	

		#ESP8266
		SoCCore.add_csr(self,"ESP8266")
		pads_ESP8266 = Cat(*[platform.request("ESP8266", i) for i in range(6)])
		self.submodules.ESP8266 = gpio.GPIOIn(pads_ESP8266)


#		SoCCore.add_csr(self,"ESP8266_0")
#		pads_ESP8266_0 = Cat(*[platform.request("ESP8266_0", i) for i in range(1)])
#		self.submodules.ESP8266_0 = gpio.GPIOIn(pads_ESP8266_0)
#		SoCCore.add_csr(self,"ESP8266_1")
#		pads_ESP8266_1 = Cat(*[platform.request("ESP8266_1", i) for i in range(1)])
#		self.submodules.ESP8266_1 = gpio.GPIOIn(pads_ESP8266_1)
#		SoCCore.add_csr(self,"ESP8266_2")
#		pads_ESP8266_2 = Cat(*[platform.request("ESP8266_2", i) for i in range(1)])
#		self.submodules.ESP8266_2 = gpio.GPIOIn(pads_ESP8266_2)
#		SoCCore.add_csr(self,"ESP8266_3")
#		pads_ESP8266_3 = Cat(*[platform.request("ESP8266_3", i) for i in range(1)])
#		self.submodules.ESP8266_3 = gpio.GPIOIn(pads_ESP8266_3)
#		SoCCore.add_csr(self,"ESP8266_4")
#		pads_ESP8266_4 = Cat(*[platform.request("ESP8266_4", i) for i in range(1)])
#		self.submodules.ESP8266_4 = gpio.GPIOIn(pads_ESP8266_4)
#		SoCCore.add_csr(self,"ESP8266_5")
#		pads_ESP8266_5 = Cat(*[platform.request("ESP8266_5", i) for i in range(1)])
#		self.submodules.ESP8266_5 = gpio.GPIOIn(pads_ESP8266_5)
		
#		SoCCore.add_csr(self,"ledRGB_2")
#		self.submodules.ledRGB_2 = rgbled.RGBLed(platform.request("ledRGB",2))
		
		# 7segments Display para zybo z7 comentar 
  
#		self.submodules.display = SevenSegmentDisplay(sys_clk_freq)
#		self.add_csr("display")
#		self.comb += [
#          platform.request("display_cs_n").eq(~self.display.cs),
#           platform.request("display_abcdefg").eq(~self.display.abcdefg)
#   	]				
		# VGA para zybo z7 comentar 
#		SoCCore.add_csr(self,"vga_cntrl")
#		vga_red = Cat(*[platform.request("vga_red", i) for i in range(4)])
#		vga_green = Cat(*[platform.request("vga_green", i) for i in range(4)])
#		vga_blue = Cat(*[platform.request("vga_blue", i) for i in range(4)])
#		self.submodules.vga_cntrl = vgacontroller.VGAcontroller(platform.request("hsync"),platform.request("vsync"), vga_red, vga_green, vga_blue)

# Build --------------------------------------------------------------------------------------------
if __name__ == "__main__":
	builder = Builder(BaseSoC(),output_dir="build", csr_csv="csr.csv")
	builder.build(build_name="top")

