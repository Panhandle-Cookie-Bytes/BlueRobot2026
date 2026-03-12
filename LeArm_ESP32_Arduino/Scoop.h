#ifndef SCOOP_H
#define SCOOP_H

#include <Arduino.h>
#include "Robot_Arm.hpp"

extern LeArm_t arm;

class Scoop {
private:
    // Move enum inside the class
    enum SequenceState { IDLE, STEP_1, STEP_2, STEP_3, STEP_4, STEP_5, STEP_6, STEP_7, STEP_8, FINISHED };
    SequenceState currentState = IDLE;
    unsigned long lastStepTime = 0;
    const int stepDelay = 1000;

    void moveArm(float m1, float m2, float m3, float m4, float m5, float m6) {
        arm.knot_run(1, m1 * 4.16, 500);
        arm.knot_run(2, m2 * 4.16, 800);
        arm.knot_run(3, m3 * 4.16, 800);
        arm.knot_run(4, m4 * 4.16, 800);
        arm.knot_run(5, m5 * 4.16, 800);
        arm.knot_run(6, m6 * 4.16, 800);
    }

public:
    // Public getter so Main Code can check if arm is busy
    bool isRunning() {
        return currentState != IDLE;
    }

    void start() {
        if (currentState == IDLE) {
            currentState = STEP_1;
            lastStepTime = millis(); // Trigger immediately
            // Force first move immediately
            moveArm(28, 132.10, 30.30, 39.90, 135.40, 40.90);
            Serial.println("Scoop Sequence Started...");
        }
    }

    void update() {
        if (currentState == IDLE) return;

        if (millis() - lastStepTime > stepDelay) {
            lastStepTime = millis();

            switch (currentState) {
                case STEP_1: currentState = STEP_2; moveArm(40.50, 118.90, 120.00, 28.70, 138.70, 138.80); break;
                case STEP_2: currentState = STEP_3; moveArm(240.00, 118.90, 120.00, 28.70, 138.70, 138.80); break;
                case STEP_3: currentState = STEP_4; moveArm(142, 126.70, 176, 41.80, 175.00, 154.20); break;
                case STEP_4: currentState = STEP_5; moveArm(142, 126.70, 176, 41.80, 175.00, 154.20); break;
                case STEP_5: currentState = STEP_6; moveArm(142, 126.70, 176, 41.80, 175.00, 94.80); break;
                case STEP_6: currentState = STEP_7; moveArm(142, 126.70, 176, 41.80, 175.00, 154.20); break;
                case STEP_7: currentState = STEP_8; moveArm(142, 126.70, 176, 41.80, 175.00, 94.80); break;
                case STEP_8: currentState = STEP_9; moveArm(142, 126.70, 176, 41.80, 175.00, 94.80); break;
                case STEP_9: currentState = STEP_10; moveArm(142, 126.70, 176, 41.80, 175.00, 94.80); break;
                case STEP_10: currentState = FINISHED; break;
                case FINISHED:
                    Serial.println("Scoop Complete.");
                    currentState = IDLE;
                    break;
            }
        }
    }
};

#endif