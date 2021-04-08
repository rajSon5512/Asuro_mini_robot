#include "asuro.h"

/********* Start - Motor library for autonomous robot *********/
#define FULL_SPEED 0xFF
#define HALF_SPEED 128
#define ZERO_SPEED 0

// Motor FWD
void MotorDriveFwd(void)
{
	MotorDir(FWD,FWD);
	MotorSpeed(FULL_SPEED,FULL_SPEED);
}

// Motor RWD
void MotorDriveRwd(void)
{
	MotorDir(RWD,RWD);
	MotorSpeed(FULL_SPEED,FULL_SPEED);
}

// Turn Left
void MotorTurnLeft(void)
{
	MotorDir(RWD,FWD);
	MotorSpeed(FULL_SPEED,HALF_SPEED);
}

// Turn Right
void MotorTurnRight(void)
{
	MotorDir(FWD,RWD);
	MotorSpeed(HALF_SPEED, FULL_SPEED);
}

// Motor Stop
void MotorStop(void)
{
	MotorSpeed(0,0);
}

/********* End - Motor library for autonomous robot *********/

/********* Start - Main loop *********/
int main (void)
{
	Init();
	unsigned int i;
	unsigned char switch_x, switch_y;

	// Indicate by blinking STATUS LED -> GREEN twice
	StatusLED(GREEN);
	for(i = 0; i < 80; i++) { Sleep(0xFF); }
	StatusLED(OFF);
	for(i = 0; i < 80; i++) { Sleep(0xFF); }
	StatusLED(GREEN);
	for(i = 0; i < 80; i++) { Sleep(0xFF); }
	StatusLED(OFF);
	for(i = 0; i < 80; i++) { Sleep(0xFF); }

	// Auto Drive
	while(1)
	{
		// Poll all switches for collision, done twice for ensuring capacitor discharges
		switch_x = PollSwitch();
		switch_y = PollSwitch();
		if (switch_x == 0 && switch_y == 0)	// No Collision, go fwd
		{
			MotorDriveFwd(); // Both engines running forward, full speed
			StatusLED(GREEN);
			// BackLED(OFF,OFF);
		}
		else if (switch_x && switch_y && switch_x == switch_y)
		{
			MotorStop();	// Stop drive
			StatusLED(RED);
			if (switch_x & 0x07)	// Left switches collision
			{
				MotorTurnLeft();	// Turn Left
				// BackLED(ON,OFF);
			}
			if (switch_x & 0x38)	// Right switches collision
			{
				MotorTurnRight();	// Turn right
				// BackLED(OFF,ON);
			}
			for(i = 0; i < 280; i++) { Sleep(0xFF); } // 2 sec sleep
		}
	}
	return 0;
}
/********* End - Main loop *********/