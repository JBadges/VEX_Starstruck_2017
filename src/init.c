/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "DriveTrain.h"
#include "ElectricalConstants.h"
#include "Claw.h"
#include "PID.h"

/*
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {
}

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize() {
  printf("%s\n", "INIT");

  printf("%s\n", "INITIALIZING PID STRUCTS");
  pid(&PID_leftDrive, 1.0, 0.0, 0.0 , -500, 500);
  pid(&PID_rightDrive, 1.0, 0.0, 0.0 , -500, 500);
  pid(&PID_leftClaw, 1.0, 0.0, 0.0 , -500, 500);
  pid(&PID_rightClaw, 1.0, 0.0, 0.0 , -500, 500);
  pid(&PID_gyro, 1.0, 0.0, 0.0, -500, 500);

  leftEncoder = encoderInit(ENCODER_LEFT_TOP, ENCODER_LEFT_BOT, false);
  rightEncoder = encoderInit(ENCODER_RIGHT_TOP, ENCODER_RIGHT_BOT, false);
  gyro = gyroInit(GYRO, 1);

  calibrateGyro();
  calibratePots();

  printf("%s\n", "DONE INIT");
}
