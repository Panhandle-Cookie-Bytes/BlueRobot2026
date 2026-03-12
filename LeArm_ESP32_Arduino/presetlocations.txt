#include "Robot_Arm.hpp"
#include "PS2_CTL.hpp"
#include "Brush.h"
#include "Scoop.h"
#include "Strainer.h"
#include "Rake.h"

LeArm_t arm;
PS2_CTL ps2_ctrl;

Brush BrushSequence;
Scoop ScoopSequence;
Strainer StrainerSequence;
Rake RakeSequence;

struct ButtonState {
    bool cross = false, circle = false, square = false, triangle = false;
};
ButtonState lastState;

void setup() {
    Serial.begin(115200);
    arm.init();
    ps2_ctrl.init();
    Serial.println("System Ready.");
}

void loop() {
    ps2_ctrl.receive_msg();

    // check if any sequence is active
    bool armBusy = BrushSequence.isRunning() || ScoopSequence.isRunning() ||
                   StrainerSequence.isRunning() || RakeSequence.isRunning();

    if (!armBusy) {
        if (ps2_ctrl.keyvalue.bit_cross && !lastState.cross)         BrushSequence.start();
        else if (ps2_ctrl.keyvalue.bit_circle && !lastState.circle)  ScoopSequence.start();
        else if (ps2_ctrl.keyvalue.bit_triangle && !lastState.triangle) RakeSequence.start();
        else if (ps2_ctrl.keyvalue.bit_square && !lastState.square)   StrainerSequence.start();
    }

    // Always update
    BrushSequence.update();
    ScoopSequence.update();
    StrainerSequence.update();
    RakeSequence.update();

    // Edge detection update
    lastState.cross = ps2_ctrl.keyvalue.bit_cross;
    lastState.circle = ps2_ctrl.keyvalue.bit_circle;
    lastState.triangle = ps2_ctrl.keyvalue.bit_triangle;
    lastState.square = ps2_ctrl.keyvalue.bit_square;

    delay(10);
}