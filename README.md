# maxbit
Test-codes-for-maixbit-K210

 Maixduino provided two configurations for this board: 1.5 Mbps and 1 Mbps. However, both are too fast for our Maix Bit board. In practice, I find 500 kbps to be a reliable speed to write to the board. In order to change that, we have to modify the configuration file supplied by Maixduino.
 
 bitm.menu.burn_baudrate.500000=500 kbps
bitm.menu.burn_baudrate.500000.build.burn_baudrate=500000

Save the fie. Now launch Arduino again. You should see 500 kbps listed under Tools>Burn Baud Rate. Select it.

Finally, choose k-flash under Tools>Programmer:

