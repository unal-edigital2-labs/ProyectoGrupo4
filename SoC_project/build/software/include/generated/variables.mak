PACKAGES=libc libcompiler_rt libbase libfatfs liblitespi liblitedram libliteeth liblitesdcard liblitesata bios
PACKAGE_DIRS=/home/felefaus/Litex/litex/litex/soc/software/libc /home/felefaus/Litex/litex/litex/soc/software/libcompiler_rt /home/felefaus/Litex/litex/litex/soc/software/libbase /home/felefaus/Litex/litex/litex/soc/software/libfatfs /home/felefaus/Litex/litex/litex/soc/software/liblitespi /home/felefaus/Litex/litex/litex/soc/software/liblitedram /home/felefaus/Litex/litex/litex/soc/software/libliteeth /home/felefaus/Litex/litex/litex/soc/software/liblitesdcard /home/felefaus/Litex/litex/litex/soc/software/liblitesata /home/felefaus/Litex/litex/litex/soc/software/bios
LIBS=libc libcompiler_rt libbase libfatfs liblitespi liblitedram libliteeth liblitesdcard liblitesata
TRIPLE=riscv64-unknown-elf
CPU=vexriscv
CPUFAMILY=riscv
CPUFLAGS=-march=rv32i2p0_m     -mabi=ilp32 -D__vexriscv__
CPUENDIANNESS=little
CLANG=0
CPU_DIRECTORY=/home/felefaus/Litex/litex/litex/soc/cores/cpu/vexriscv
SOC_DIRECTORY=/home/felefaus/Litex/litex/litex/soc
PICOLIBC_DIRECTORY=/home/felefaus/Litex/pythondata-software-picolibc/pythondata_software_picolibc/data
COMPILER_RT_DIRECTORY=/home/felefaus/Litex/pythondata-software-compiler_rt/pythondata_software_compiler_rt/data
export BUILDINC_DIRECTORY
BUILDINC_DIRECTORY=/home/felefaus/Desktop/practicas_digital/lab03-2022-2-grupo04-22-2/SoC_project/build/software/include
LIBC_DIRECTORY=/home/felefaus/Litex/litex/litex/soc/software/libc
LIBCOMPILER_RT_DIRECTORY=/home/felefaus/Litex/litex/litex/soc/software/libcompiler_rt
LIBBASE_DIRECTORY=/home/felefaus/Litex/litex/litex/soc/software/libbase
LIBFATFS_DIRECTORY=/home/felefaus/Litex/litex/litex/soc/software/libfatfs
LIBLITESPI_DIRECTORY=/home/felefaus/Litex/litex/litex/soc/software/liblitespi
LIBLITEDRAM_DIRECTORY=/home/felefaus/Litex/litex/litex/soc/software/liblitedram
LIBLITEETH_DIRECTORY=/home/felefaus/Litex/litex/litex/soc/software/libliteeth
LIBLITESDCARD_DIRECTORY=/home/felefaus/Litex/litex/litex/soc/software/liblitesdcard
LIBLITESATA_DIRECTORY=/home/felefaus/Litex/litex/litex/soc/software/liblitesata
BIOS_DIRECTORY=/home/felefaus/Litex/litex/litex/soc/software/bios
LTO=0
BIOS_CONSOLE_FULL=1