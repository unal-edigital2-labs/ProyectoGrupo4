################################################################################
# IO constraints
################################################################################
# serial:0.tx
set_property LOC T17 [get_ports {serial_tx}]
set_property IOSTANDARD LVCMOS33 [get_ports {serial_tx}]

# serial:0.rx
set_property LOC Y17 [get_ports {serial_rx}]
set_property IOSTANDARD LVCMOS33 [get_ports {serial_rx}]

# clk:0
set_property LOC K17 [get_ports {clk}]
set_property IOSTANDARD LVCMOS33 [get_ports {clk}]

# cpu_reset:1
set_property LOC Y16 [get_ports {cpu_reset}]
set_property IOSTANDARD LVCMOS33 [get_ports {cpu_reset}]

# led:0
set_property LOC M14 [get_ports {led0}]
set_property IOSTANDARD LVCMOS33 [get_ports {led0}]

# led:1
set_property LOC M15 [get_ports {led1}]
set_property IOSTANDARD LVCMOS33 [get_ports {led1}]

# led:2
set_property LOC G14 [get_ports {led2}]
set_property IOSTANDARD LVCMOS33 [get_ports {led2}]

# led:3
set_property LOC D18 [get_ports {led3}]
set_property IOSTANDARD LVCMOS33 [get_ports {led3}]

# sw:0
set_property LOC G15 [get_ports {sw0}]
set_property IOSTANDARD LVCMOS33 [get_ports {sw0}]

# sw:1
set_property LOC P15 [get_ports {sw1}]
set_property IOSTANDARD LVCMOS33 [get_ports {sw1}]

# sw:2
set_property LOC W13 [get_ports {sw2}]
set_property IOSTANDARD LVCMOS33 [get_ports {sw2}]

# sw:3
set_property LOC T16 [get_ports {sw3}]
set_property IOSTANDARD LVCMOS33 [get_ports {sw3}]

# btnc:0
set_property LOC K18 [get_ports {btnc}]
set_property IOSTANDARD LVCMOS33 [get_ports {btnc}]

# btnd:1
set_property LOC P16 [get_ports {btnd}]
set_property IOSTANDARD LVCMOS33 [get_ports {btnd}]

# btnu:2
set_property LOC K19 [get_ports {btnu}]
set_property IOSTANDARD LVCMOS33 [get_ports {btnu}]

# ledRGB:1.r
set_property LOC V16 [get_ports {ledRGB1_r}]
set_property IOSTANDARD LVCMOS33 [get_ports {ledRGB1_r}]

# ledRGB:1.g
set_property LOC F17 [get_ports {ledRGB1_g}]
set_property IOSTANDARD LVCMOS33 [get_ports {ledRGB1_g}]

# ledRGB:1.b
set_property LOC M17 [get_ports {ledRGB1_b}]
set_property IOSTANDARD LVCMOS33 [get_ports {ledRGB1_b}]

# LIR:0
set_property LOC T10 [get_ports {LIR0}]
set_property IOSTANDARD LVCMOS33 [get_ports {LIR0}]

# RIR:0
set_property LOC U12 [get_ports {RIR0}]
set_property IOSTANDARD LVCMOS33 [get_ports {RIR0}]

# RGB_sensor_S:0
set_property LOC V12 [get_ports {RGB_sensor_S0}]
set_property IOSTANDARD LVCMOS33 [get_ports {RGB_sensor_S0}]

# RGB_sensor_S:1
set_property LOC W16 [get_ports {RGB_sensor_S1}]
set_property IOSTANDARD LVCMOS33 [get_ports {RGB_sensor_S1}]

# RGB_sensor_S:2
set_property LOC J15 [get_ports {RGB_sensor_S2}]
set_property IOSTANDARD LVCMOS33 [get_ports {RGB_sensor_S2}]

# RGB_sensor_S:3
set_property LOC H15 [get_ports {RGB_sensor_S3}]
set_property IOSTANDARD LVCMOS33 [get_ports {RGB_sensor_S3}]

# RGB_sensor_EN:0
set_property LOC V13 [get_ports {RGB_sensor_EN0}]
set_property IOSTANDARD LVCMOS33 [get_ports {RGB_sensor_EN0}]

# RGB_sensor_Out:0
set_property LOC U17 [get_ports {RGB_sensor_Out0}]
set_property IOSTANDARD LVCMOS33 [get_ports {RGB_sensor_Out0}]

# motorEN1:0
set_property LOC U14 [get_ports {motorEN10}]
set_property IOSTANDARD LVCMOS33 [get_ports {motorEN10}]

# motorEN2:0
set_property LOC U15 [get_ports {motorEN20}]
set_property IOSTANDARD LVCMOS33 [get_ports {motorEN20}]

# motorEN3:0
set_property LOC V17 [get_ports {motorEN30}]
set_property IOSTANDARD LVCMOS33 [get_ports {motorEN30}]

# motorEN4:0
set_property LOC V18 [get_ports {motorEN40}]
set_property IOSTANDARD LVCMOS33 [get_ports {motorEN40}]

# stepper:0
set_property LOC T14 [get_ports {stepper0}]
set_property IOSTANDARD LVCMOS33 [get_ports {stepper0}]

# stepper:1
set_property LOC T15 [get_ports {stepper1}]
set_property IOSTANDARD LVCMOS33 [get_ports {stepper1}]

# stepper:2
set_property LOC P14 [get_ports {stepper2}]
set_property IOSTANDARD LVCMOS33 [get_ports {stepper2}]

# stepper:3
set_property LOC R14 [get_ports {stepper3}]
set_property IOSTANDARD LVCMOS33 [get_ports {stepper3}]

# ESP8266:0
set_property LOC V15 [get_ports {ESP82660}]
set_property IOSTANDARD LVCMOS33 [get_ports {ESP82660}]

# ESP8266:1
set_property LOC W15 [get_ports {ESP82661}]
set_property IOSTANDARD LVCMOS33 [get_ports {ESP82661}]

# ESP8266:2
set_property LOC T11 [get_ports {ESP82662}]
set_property IOSTANDARD LVCMOS33 [get_ports {ESP82662}]

# ESP8266:3
set_property LOC W14 [get_ports {ESP82663}]
set_property IOSTANDARD LVCMOS33 [get_ports {ESP82663}]

# ESP8266:4
set_property LOC Y14 [get_ports {ESP82664}]
set_property IOSTANDARD LVCMOS33 [get_ports {ESP82664}]

# ESP8266:5
set_property LOC T12 [get_ports {ESP82665}]
set_property IOSTANDARD LVCMOS33 [get_ports {ESP82665}]

################################################################################
# Design constraints
################################################################################

################################################################################
# Clock constraints
################################################################################


create_clock -name clk -period 8.0 [get_ports clk]

################################################################################
# False path constraints
################################################################################


set_false_path -quiet -through [get_nets -hierarchical -filter {mr_ff == TRUE}]

set_false_path -quiet -to [get_pins -filter {REF_PIN_NAME == PRE} -of_objects [get_cells -hierarchical -filter {ars_ff1 == TRUE || ars_ff2 == TRUE}]]

set_max_delay 2 -quiet -from [get_pins -filter {REF_PIN_NAME == C} -of_objects [get_cells -hierarchical -filter {ars_ff1 == TRUE}]] -to [get_pins -filter {REF_PIN_NAME == D} -of_objects [get_cells -hierarchical -filter {ars_ff2 == TRUE}]]