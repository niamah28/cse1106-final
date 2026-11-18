
CSE 1106 – Final Project
Project Option: 1 – Smart Classroom Comfort Monitor

Programming Language: C

Hardware: Raspberry Pi and LED

1. Project Description
The Smart Classroom Comfort Monitor is a Raspberry Pi-based application designed to monitor classroom temperatures and determine whether the environment is within an acceptable range.

The system allows users to enter temperature readings in Fahrenheit, displays a NORMAL or WARNING status, and indicates when a warning LED should be activated.

The default acceptable temperature range is 68°F to 76°F, inclusive.

2. Project Objectives
Accept classroom temperature readings in Fahrenheit.
Determine whether temperatures are within the acceptable range.
Display NORMAL or WARNING based on the reading.
Calculate the average of recorded temperatures.
Save temperature readings and their statuses to a file.
Allow users to modify the acceptable temperature range.
Activate a warning LED when temperatures are outside the acceptable range.
3. System Functionality
The program evaluates each temperature reading using the following conditions:

NORMAL: Temperature is between 68°F and 76°F, inclusive.
WARNING: Temperature is below 68°F or above 76°F.
LED OFF: Temperature is normal.
LED ON: Temperature is outside the acceptable range.
The acceptable temperature limits can be changed to meet different classroom requirements.

3. How to Run the Program
Download or clone the GitHub repository.
Open the terminal on the Raspberry Pi.
Navigate to the project folder.
Compile the C program:
gcc -o monitor monitor.c

Run the program:
./monitor

Enter classroom temperature readings when prompted.
Enter -999 to finish recording temperatures.
View the average temperature and saved readings.
Note: These commands run the temperature-monitoring prototype. Physical LED control requires the GPIO integration and its corresponding compilation setup.

4. Project Deliverables
C source code
Raspberry Pi hardware setup
Temperature reading log
Five documented test cases
GitHub repository
Final working demonstration


