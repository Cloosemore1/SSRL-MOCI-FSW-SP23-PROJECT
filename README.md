# UGA SSRL MOCI Flight Software Spring 2023 Take Home Project
Congratulations on passing your first round of interviews for the UGA SSRL! Your Round 2 interview will be in the form of the Flight Software take-home project outlined in this document. If you have any questions in regards to the instructions or even if you need help or clarification with any part of the project, I highly encourage you to contact me at connor.loosemore2021@gmail.com. The projects will be scored based not only on whether project criteria are met, but also whether or not it is obvious that you put in effort into your submission. Don't fret if you can't get something working, just do your best work!

# Project Outline
Flight Software on MOCI (or any satellite) often involves communicating data between many separate components in an efficient and reliable way. Your take-home project will consist of a program written in C which handles packet communication between a COTS (Commercial Off-the-Shelf) component and the component which will be running your program. An API will be provided to you that you can use to communicate with the component, which will send you raw data with a specified packet format. Your task is to decode this data into useful, human readable format while also handling any necessary error correction on the data.

Your program will communicate with the component via SPI (Serial Peripheral Interface). If you are already familiar with SPI, great! If not, no need to worry, all the necessary information to communicate with the component will be provided. Essentially, your program will generate a clock pulse which switches back and forth between high and low. In addition to this clock line, there will be two data lines for communication. One from your program into the component (Master Out Slave In, or MOSI) and one from the component into your program (Master In Slave Out, MISO). On each rising edge of the clock line, the component will sample the level of the MOSI line, and if any data is to be sent back, the MISO line will also switch level on the rising clock edge. A timing diagram for this commnication is provided below, with the dotted line indicating when a bit is sampled or set:
![SPI_Diagram](https://user-images.githubusercontent.com/60021392/216702495-3152ef46-6e03-4b49-bb20-472a00e10fbf.png)
In order to actually implement this communication protocol in code, the component API provided in this repository has 3 functions you can use.
* void SET_CLK(boolean level) - Sets the clock line to the specified boolean logic level.
* void WRITE_MOSI(boolean level) - Sets the MOSI line to the specified boolean logic level.
* boolean READ_MISO(); - Returns the boolean logic level of the MISO line.

Now that we understand WHEN to send bits, we will look at WHAT bits to send. In this particular application, we are only concerned with reading data from the device, although in many other applications, SPI communication can be much more complex. Although our component is essentially a black box (we do not understand, nor do we need to be concerned with, the internal workings) we do know that its addressable memory is comprised of 256 8-bit words. Every communication between the devices will be initiated by the host (your program). In order to read data from the component, the program must send 2 bytes to the component to receive a single byte of data from a particular memory address of the component. 16 clock pulses MUST be completed for the component to begin relaying data, and an additional 8 clock pulses, for a total of 24, MUST be completed to complete the communication with the device. Shown below is a packet format diagram:
![PacketFormat](https://user-images.githubusercontent.com/60021392/216746401-09227e95-4c17-4afc-b1d1-edd6eccb787d.png)
As far as your program is concerned, the "read" command byte will always be the same - 0x55. The data byte will consist of 7 data bits, with the least significant bit acting as an even parity bit. You can read more on parity bits [here](https://www.tutorialspoint.com/what-is-a-parity-bit). The program will use this parity bit to check the data it receives for errors. For the purposes of this project, you can always assume that any error in the data resulted in an odd number of bits flipping. The 7 bits of data will be encoded in 7 bit ASCII. 


The program should be able to:
* Read data from every address on the component
* Detect and correct errors in the data by re-requesting the data
* Print the contents of the component memory to a human readable plain-text file


# Getting Started
Everything you should need (except for your own code, of course!) is included in this repository. You should clone it locally and work from that copy.

You can use the commands outlined above to interact with the **component.o** file. Be sure to create a makefile for compilation. The user should be able to run ">make clean" followed by ">make" in the terminal, and have your program compile into an executable file.

# Submission
You should submit a zip file of all the necessary files to compile and run your program to connor.loosemore2021@gmail.com by Tuesday, February 14th at 11:59 PM. Once again, if you have any questions at all, do not hesitate to reach out to me!

Good luck!
