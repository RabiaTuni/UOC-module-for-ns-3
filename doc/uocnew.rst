
..highlight:: bash

Underwater Optical Communication module Integration (uocnew)
**************************************************
Underwater Optical Communication is the means of using light intensity for the purpose of communication underwater. Wavelengths especially in the blue/green region of the visible light spectrum has the least attenuation underwater; thus, making the communication possible in the underwater environment.This technology allows the use of unlimited bandwidth, lower power consumption and immunity to interference when compared to the conventional radio frequency and acoustics technology.

Model Description
************************
The source code for the new module lives in the directory ``src/uocnew``.

Design
======
This module can be used to study the performance of the physical layer and discuss the impact on the network layer of underwater optical networks as an extension to the ns-3 core libraries. The module has a UOC channel model, propagation loss model, SNR model, error model, and transmitter and receiver NetDevice models to implement distinct characteristics of an underwater optical system. It is designed to help researchers evaluate the performance of a p2p UOC system through signal-to-noise ratio (SNR), bit error rate (BER), and packet error rate (PER) models for On-Off Keying (OOK) modulation. The module can simulate UOC in different water types such as pure sea, coastal ocean, clean ocean, and turbid harbor. The purpose is to demonstrate the impact of water conditions such as turbidity, attenuation, and temperatures on the received optical signal.

Scope and Limitations
=====================
The module in its current form can design and evaluate a standalone underwater optical communication system and is expected to help understand and optimize the future hybrid underwater wireless sensor networks. The module lacks combinations of UOC physical channel and modulation schemes. At this stage it cannot evaluate the performance of large optical networks.


References
==========


Usage
*****

This section is principally concerned with the usage of your model, using
the public API.  Focus first on most common usage patterns, then go
into more advanced topics.



Helpers
=======
 the easiest way to UOC node to node communication is by using the following helpers: 

UOCChannelHelper : to create a UOC channel 
UOCDeviceHelper : to set transmitter and the receiver parameters of the UOC net device
transmitter parameters: 
Our signal is a positive square form  signal that is pushed into the transmitter power taking the time as parameter.  The signal consists of the following parameters: 
1- size 
2- Duty ratio 
3- bias 
4- Max 
5- Min 

Other parameters of the transmitter are 
1- Semiangle
2- Transmit power

Others Parameters: 
Transmitter Data rate 

Receiver Parameters: 
1-refractive index 
2-field of view 
3-Incidence Angle
4-PhotoDetectorArea
5-position 
6-Receiver sensitivity 
Also from the receiver we can choose the applied Modulation scheme where :
0 value  represent OOK
1 value  represent 4-PAM 


Attributes
==========

What classes hold attributes, and what are the key ones worth mentioning? // will be gevin in details soon

Output
======

What kind of data does the model generate?  What are the key trace
sources?   What kind of logging output can be enabled? // will be gevin in details soon

Examples
========

The module has one example scenerio of a p2p optical communication system which explains the use of the UOC module.


Validation
**********

Describe how the model has been tested/validated.  What tests run in the
test suite?  How much API and code is covered by the tests?  Again, 
references to outside published work may help here.
