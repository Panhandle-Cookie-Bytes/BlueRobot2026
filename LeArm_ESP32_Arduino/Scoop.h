#ifndef SCOOP_H
#define SCOOP_H

#include <Arduino.h>
#include "Robot_Arm.hpp"

extern LeArm_t arm;

class Scoop {
private:
    // Move enum inside the class
    enum SequenceState { IDLE, STEP_1, STEP_2, STEP_3, STEP_4, STEP_5, STEP_6, STEP_7, STEP_8, STEP_9, STEP_10, STEP_11, STEP_12, STEP_13, STEP_14, STEP_15, STEP_16, STEP_17, STEP_18, STEP_19, STEP_20, STEP_21, STEP_22, STEP_23, STEP_24, STEP_25, STEP_26, STEP_27, STEP_28, STEP_29, STEP_30, STEP_31, STEP_32, STEP_33, STEP_34, STEP_35, FINISHED };
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
            moveArm(0.00, 125.60, 81.50, 43.00, 93.60, 120.00);
            Serial.println("Scoop Sequence Started...");
        }
    }

    void update() {
        if (currentState == IDLE) return;

        if (millis() - lastStepTime > stepDelay) {
            lastStepTime = millis();

            switch (currentState) {
                case STEP_1: currentState = STEP_2; moveArm(0.00, 125.60, 81.50, 43.00, 93.60, 120.00); break;
                case STEP_2: currentState = STEP_3; moveArm(0.00, 128.90, 94.70, 56.20, 150.80, 133.20); break;
                case STEP_3: currentState = STEP_4; moveArm(0.00, 128.90, 121.10, 56.20, 177.20, 133.20); break;
                case STEP_4: currentState = STEP_5; moveArm(130, 128.90, 121.10, 56.20, 177.20, 133.20); break;
                case STEP_5: currentState = STEP_6; moveArm(130.00, 115.60, 159.60, 168.40, 151.90, 179.40); break;
                case STEP_6: currentState = STEP_7; moveArm(130.00, 115.60, 186.00, 168.40, 84.80, 184.90); break;
                case STEP_7: currentState = STEP_8; moveArm(0.00, 115.60, 186.00, 168.40, 84.80, 184.90); break;
                case STEP_8: currentState = STEP_9; moveArm(0.00, 125.60, 81.50, 43.00, 93.60, 120.00); break;
                case STEP_9: currentState = STEP_10; moveArm(0.00, 120.00, 61.70, 81.50, 146.40, 111.30); break;
                case STEP_10: currentState = STEP_11; moveArm(0.00, 120.00, 55.10, 95.50, 178.30, 111.30); break;
                case STEP_11: currentState = STEP_12; moveArm(240.00, 120.00, 55.10, 95.80, 178.30, 111.30); break;
                case STEP_12: currentState = STEP_13; moveArm(240.00, 120.00, 197.10, 179.40, 135.40, 224.60); break;
                case STEP_13: currentState = STEP_14; moveArm(240.00, 120.00, 197.10, 179.40, 95.80, 224.60); break;
                case STEP_14: currentState = STEP_15; moveArm(89.50, 120.00, 197.10, 179.40, 110.10, 224.60); break;
                case STEP_15: currentState = STEP_16; moveArm(0.00, 120.00, 97.00, 67.20, 129.90, 86.00); break;
                case STEP_16: currentState = STEP_17; moveArm(0.00, 120.00, 97.00, 67.20, 177.20, 86.00); break;
                case STEP_17: currentState = STEP_18; moveArm(130, 120.00, 97.00, 67.20, 177.20, 86.00); break;
                case STEP_18: currentState = STEP_19; moveArm(130.00, 120.00, 209.10, 160.70, 115.60, 217.90); break;
                case STEP_19: currentState = STEP_20; moveArm(130.50, 120.00, 230.00, 170.60, 90.30, 240.00); break;
                case STEP_20: currentState = STEP_21; moveArm(0.00, 120.00, 230.00, 170.60, 103.50, 240.00); break;
                case STEP_21: currentState = STEP_22; moveArm(0.00, 125.60, 81.50, 43.00, 93.60, 120.00); break;
                case STEP_22: currentState = STEP_23; moveArm(0.00, 120.00, 17.70, 34.20, 65.00, 233.30); break;
                case STEP_23: currentState = STEP_24; moveArm(31.50, 120.00, 6.60, 14.30, 70.50, 240.00); break;
                case STEP_24: currentState = STEP_25; moveArm(165.00, 120.00, 6.60, 14.30, 70.50, 240.00); break;
                case STEP_25: currentState = STEP_26; moveArm(165.00, 120.00, 45.10, 71.50, 71.60, 240.00); break;
                case STEP_26: currentState = STEP_27; moveArm(165.00, 120.00, 45.10, 71.50, 133.20, 128.90); break;
                case STEP_27: currentState = STEP_28; moveArm(165.00, 84.80, 91.40, 69.40, 133.20, 77.20); break;
                case STEP_28: currentState = STEP_29; moveArm(165.00, 160.70, 91.40, 69.40, 133.20, 135.50); break;
                case STEP_29: currentState = STEP_30; moveArm(165.00, 84.80, 91.40, 69.40, 133.20, 77.20); break;
                case STEP_30: currentState = STEP_31; moveArm(165.00, 160.70, 91.40, 69.40, 133.20, 135.50); break;
                case STEP_31: currentState = STEP_32; moveArm(165.00, 84.80, 91.40, 69.40, 133.20, 77.20); break;
                case STEP_32: currentState = STEP_33; moveArm(165.00, 120.00, 91.40, 69.40, 133.20, 77.20); break;
                case STEP_33: currentState = STEP_34; moveArm(165.00, 120.00, 59.50, 16.50, 80.40, 0.00); break;
                case STEP_34: currentState = STEP_35; moveArm(165.00, 15.50, 59.50, 16.50, 80.40, 0.00); break;
                case STEP_35: currentState = FINISHED; break;
                case FINISHED:
                    Serial.println("Scoop Complete.");
                    currentState = IDLE;
                    break;
            }
        }
    }
};

#endif