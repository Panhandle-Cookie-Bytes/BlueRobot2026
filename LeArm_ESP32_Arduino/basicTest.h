#ifndef BASICTEST_H
#define BASICTEST_H

#include <Arduino.h>
#include "Robot_Arm.hpp"

// Tell this file that 'arm' is defined in the main .ino
extern LeArm_t arm;

enum SequenceState { IDLE, STEP_1, STEP_2, STEP_3, STEP_4, STEP_5, STEP_6, STEP_7, STEP_8, FINISHED };

class BasicTest {
private:
    SequenceState currentState = IDLE;
    unsigned long lastStepTime = 0;
    const int stepDelay = 2000;

    void moveArm(float m1, float m2, float m3, float m4, float m5, float m6) {
        arm.knot_run(1, m1 * 4.16, 800);
        arm.knot_run(2, m2 * 4.16, 800);
        arm.knot_run(3, m3 * 4.16, 800);
        arm.knot_run(4, m4 * 4.16, 800);
        arm.knot_run(5, m5 * 4.16, 800);
        arm.knot_run(6, m6 * 4.16, 800);
    }

public:
    void start() {
        if (currentState == IDLE) {
            currentState = STEP_1;
            lastStepTime = millis();
            Serial.println("Sequence Started...");
        }
    }

    void stop() {
        currentState = IDLE;
    }

    void update() {
        if (currentState == IDLE) return;

        if (millis() - lastStepTime > stepDelay) {
            lastStepTime = millis();

            switch (currentState) {
                case STEP_1:
                    moveArm(28, 132.10, 30.30, 39.90, 135.40, 40.90);
                    currentState = STEP_2;
                    break;
                case STEP_2:
                    moveArm(0, 132.10, 45.30, 66.00, 157.40, 40.90);
                    currentState = STEP_3;
                    break;
                case STEP_3:
                    moveArm(203.00, 132.10, 45.30, 66.00, 157.40, 40.90);
                    currentState = STEP_4;
                    break;
                case STEP_4:
                    moveArm(203.00, 132.10, 67.30, 0, 100.90, 213.60);
                    currentState = STEP_5;
                    break;
                case STEP_5:
                    moveArm(240.00, 132.10, 67.30, 0, 140.90, 213.60);
                    currentState = STEP_6;
                    break;
                case STEP_6:
                    moveArm(0, 132.10, 67.30, 0, 140.90, 213.60);
                    currentState = STEP_7;
                    break;
                case STEP_7:
                    moveArm(0, 132.10, 97.00, 0, 90.90, 127.80);
                    currentState = STEP_8;
                    break;
                case STEP_8:
                    moveArm(0, 132.10, 97.00, 0, 140.90, 127.80);
                    currentState = FINISHED;
                    break;
                case FINISHED:
                    Serial.println("Sequence Complete.");
                    currentState = IDLE;
                    break;
            }
        }
    }
};

#endif