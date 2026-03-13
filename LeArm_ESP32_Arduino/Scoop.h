#ifndef SCOOP_H
#define SCOOP_H

#include <Arduino.h>
#include "Robot_Arm.hpp"

extern LeArm_t arm;

class Scoop {
private:
    // Move enum inside the class
    enum SequenceState { IDLE, STEP_1, STEP_2, STEP_3, STEP_4, STEP_5, STEP_6, STEP_7, STEP_8, STEP_9, STEP_10, STEP_11, STEP_12, STEP_13, STEP_14, STEP_15, STEP_16, STEP_17, STEP_18, STEP_19, STEP_20, FINISHED };
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
                case STEP_1: currentState = STEP_3; moveArm(0, 110.10, 80.30, 84.80, 125.50, 91.40); break;
                case STEP_3: currentState = STEP_4; moveArm(203.00, 127.70, 79.30, 99.10, 189.30, 137.60); break;
                case STEP_4: currentState = STEP_5; moveArm(240., 127.70, 182.70, 170.60, 106.80, 183.70); break;
                case STEP_5: currentState = STEP_6; moveArm(240.00, 127.70, 182.70, 170.60, 80.40, 183.70); break;
                case STEP_6: currentState = STEP_7; moveArm(2.00, 127.70, 182.70, 170.60, 80.40, 183.70); break;
                case STEP_7: currentState = STEP_8; moveArm(2.00, 127.70, 182.70, 170.60, 109.00, 187.00); break;
                case STEP_8: currentState = STEP_9; moveArm(0.00, 120.00, 95.80, 65.00, 154.10, 116.70); break;
                case STEP_9: currentState = STEP_10; moveArm(0.00, 120.00, 95.80, 65.00, 172.80, 116.70); break;
                case STEP_10: currentState = STEP_11; moveArm(240.00, 120.00, 95.80, 65.00, 172.80, 116.7); break;
                case STEP_11: currentState = STEP_12; moveArm(240.00, 120.00, 95.80, 65.00, 146.40, 116.70); break;
                case STEP_12: currentState = STEP_13; moveArm(240.00, 120.00, 173.90, 195.90, 146.40, 194.80); break;
                case STEP_13: currentState = STEP_14; moveArm(240.00, 120.00, 173.90, 195.90, 93.60, 194.80); break;
                case STEP_14: currentState = STEP_15; moveArm(33.50, 120.00, 173.90, 195.90, 93.60, 194.80); break;
                case STEP_15: currentState = STEP_16; moveArm(33.50, 120.00, 173.90, 195.90, 146.40, 194.80); break;
                case STEP_16: currentState = STEP_17; moveArm(0, 110.10, 80.30, 84.80, 125.50, 91.40); break;
                case STEP_17: currentState = FINISHED; break;
                case FINISHED:
                    Serial.println("Scoop Complete.");
                    currentState = IDLE;
                    break;
            }
        }
    }
};

#endif