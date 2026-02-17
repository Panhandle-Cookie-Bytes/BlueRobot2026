#include "Robot_Arm.hpp"
#include "PS2_CTL.hpp"
#include "basicTest.h"

// 1. Global Objects
LeArm_t arm;
PS2_CTL ps2_ctrl;
BasicTest basicTestSequence;

// Edge detection variables
bool lastCross = false;

void setup() {
    Serial.begin(115200);
    arm.init();
    ps2_ctrl.init();
}

void loop() {
    ps2_ctrl.receive_msg();

    if (ps2_ctrl.keyvalue.bit_cross) {
        Serial.println("Cross is Pressed!!");
    }

    // 2. Trigger the Sequence
    if (ps2_ctrl.keyvalue.bit_cross && !lastCross) {
        Serial.println("EDGE DETECTED: Starting Sequence...");
        basicTestSequence.start();
    }

    // 3. Let the state machine process its timing
    basicTestSequence.update();

    // 4. Update edge detection
    lastCross = ps2_ctrl.keyvalue.bit_cross;
}