# bam_ws

## Description
This repository is created to contains source for my project named "Automated chicken feeder system". This project uses camera to detect and count the number of chicken in a pen. The feeder system works by taking the number of chickens detected, then count the amount of equivalent total of the chicken's feed. There are a specific hours for the feeding system works. Currently, this system is set to feed the chickens at 7am and 5pm. Besides, this system is initially built for (Arduino)ATMega2560 environment.
 
## System's Diagram
  __________                _______                  ____________________________          ___________________
 |          |              |       |    Serial      |                            |        |                   |
 |  Camera  |------------->|  PC   |--------------->| Microcontroller Unit (MCU) |------->| Actuator & Pen    |
 |_________ |              |______ | Communication  |__________________________  |        |__________________ |

1.  Camera          : Capturing the object
2.  PC              : Runs the obejct detection program, also take the PC's current time. Then send over the data (number of chicken's & time) with Serial (Pyserial)
3.  MCU             : Microcontroller Unit receives the data on the serial. Control the actuator.
4.  Actuaotor & Pen : Servo is the actuator. Actuator's role is to open or close the feeding valve at the Pen. 

## Arduino Digital Pin Connections:
1. D3   ->  Trigger (HCSR-04)
2. D4   ->  Echo    (HCSR-04)
3. D5   ->  Signal  (Servo)
4. D6   ->  SCK     (Sensor Loadcell) 
5. D7   ->  DT      (Sensor Loadcell)

