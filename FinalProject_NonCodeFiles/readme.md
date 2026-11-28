1. Keep your single connector exactly as it is, with MISO, MOSI and SCK shared between both chips. Move only the RESET wire by hand — pull it off U1 pin 1 and put it on the other AVR's pin 1 when you want to flash the other chip.

One wire, moved with your fingers. That's the whole thing.

This works because only the chip with RESET pulled low enters programming mode. The other chip is just running normally, and PB3/PB4/PB5 are unused in both your programs, so they sit as high-impedance inputs and never fight the bus. No contention.
