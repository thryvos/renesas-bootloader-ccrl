# renesas-bootloader-ccrl
Renesas bootloader (Flash programming) support CS+, CC-RL compiler.

This example project is to demostrate firmware upgrade feature to support on Renesas CS+, CC-RL compiler. 
Till today (15th September 2015), Renesas yet to have a bootloader full example code to support CC-RL compiler.
So, I create this working example code based on Renesas document guideline. 
You may find two projects from the repository:
1. sensor_tag_bl: Is a bootlodaer project allowed to perform firmware upgrade through PC COM.
2. sensor_tag_app: Is an application project.

Hardware setup:
MCU Part Number: R5F100BEANA
Flash: 64KB
RAM: 4KB
Pin count: 32pins
Internal clock 8MHz
PC COM: UART1 -> P01/RxD1, P00/TxD1
	      Setting-> 115200bps, 8 data bit, 1 stop bit, flow control none.
Button: P50/INTP1
Step to access Bootloader: Press the button and power up the target board.
		           If target board power up and not detect button trigger at the first place, 
                           then will direct goto flash area (application code)
