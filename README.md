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