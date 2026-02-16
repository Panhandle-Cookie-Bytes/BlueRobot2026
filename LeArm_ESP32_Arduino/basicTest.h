#ifndef BASICTEST_H
#define BASICTEST_H

#include <Arduino.h>
#include "Robot_Arm.hpp"

// Tell this file that 'arm' is defined in the main .ino
extern LeArm_t arm;

enum SequenceState { IDLE, STEP_1, STEP_2, STEP_3, STEP_4, FINISHED };

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
                    moveArm(0, 125.60, 81.50, 20.90, 137.60, 40.70);
                    currentState = STEP_2;
                    break;
                case STEP_2:
                    moveArm(120, 120, 120, 120, 120, 120);
                    currentState = STEP_3;
                    break;
                case STEP_3:
                    moveArm(175, 175, 175, 175, 175, 175);
                    currentState = STEP_4;
                    break;
                case STEP_4:
                    moveArm(210, 210, 210, 210, 210, 210);
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