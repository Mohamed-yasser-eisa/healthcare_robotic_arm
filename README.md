# healthcare_robotic_arm
 
Build date: (19 July, 2021)

This is my graduation project, it was a team based project.

1- Project description:

    A fully controlled robotic arm that can help doctors to measure vital signs of 
    the patients like the temperature and heart rate, from a far distance or any 
    place in the hospital, the arm has 4 joints to move in 4 degrees 
    of freedoms to get to the given position in real world.

2- Tools:

    (STM32F103C8T6, 4 large servomotors with magnetic encoder, MATLAB, 
    magnetic encoder, temperature sensor, power supply, I2C motor driver, Arduino 
    IDE).

3- Files description:

    3.1- (fial_edition.ino): is the code used for STM32 microcontroller to control and move servomotors to the given position. 
    3.2- (ik4dof.m): is the MATLAB code, which is used to simulate the arm movements and calculates the angle of movement of each servomotor.
    3.3- (Paper.pdf): paper of our graduation project.
    3.4- (Report.pdf): detailed description for our project.

4- Video: (https://youtu.be/o14xiIMUBvY)