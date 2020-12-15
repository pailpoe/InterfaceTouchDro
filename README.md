# Touchdro Interface
A electronic interface for TouchDro and 4 quadrature sensor.
Use a STM32F103C8T6 borard ( bluepill) with a bluetooth module (HC-06 or HC-05).
> Serial speed : 38400 bauds
  
The frame format is :  
> Xaaa;Ybbb;Zccc;Wddd;Teee;  

aaa : Step for X sensor ( example : -2563 or 4569)  
bbb : Step for Y sensor ( example : -2563 or 4569)  
ccc : Step for Z sensor ( example : -2563 or 4569)  
ddd : Step for W sensor ( example : -2563 or 4569)  
eee : spindle speed in RPM ( example : -800 or 2569)  

# Connexion
- Sensor X : PA8 ( A ) and PA9 ( B ), use the hardware timer 1
- Sensor Y : PA6 ( A ) and PA7 ( B ), use the hardware timer 3 
- Sensor Z : PA0 ( A ) and PA1 ( B ), use the hardware timer 2 
- Sensor W : PB6 ( A ) and PB7 ( B ), use the hardware timer 4 
- Serial : PA3 ( RX_board ) and PA2 ( TX_board ), use the hardware serial 2  

# Installation
1. Install ARDUINO IDE V1.8.8 +
2. Download a zip file containing the Arduino STM32 files : https://github.com/rogerclarkmelbourne/Arduino_STM32/archive/master.zip
3. Unzip the content of the zip file, and place the Arduino_STM32 folder to [Arduino sketches folder]/[hardware]/[Arduino_STM32]. 
Create the 'hardware' folder if it does not exist yet.
Example how the path should look like: C:\Users\<user>\Documents\Arduino\hardware\Arduino_STM32  
4. Restart ARDUINO IDE
5. Choose : Tools > Board:"Generic ST32F103C series"
6. Choose : Tools > Variant:"STMF32C103C8"
7. Choose : Tools > Upload Method:"STLink"
8. Choose : Tools > CPU Speed Mhz:"72Mhz (Normal)"
9. Add additionnal board manager URL : File > Preferences > Additional Boards Manager URLs : "http://dan.drown.org/stm32duino/package_STM32duino_index.json"
10. Install Arduino SAM Boards : Tools > Boards Manager > Install Arduino SAM boards ( 32bits cortex M3)
11. Compile ...
