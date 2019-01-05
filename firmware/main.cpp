#include "Particle.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

void startupTasks() {
        RGB.control(true);
        RGB.brightness(2);
        RGB.control(false);
}

STARTUP(startupTasks());

const uint32_t tickDebounce = 50 * 1000 * SYSTEM_US_TICKS; // 50ms debounce period

volatile bool ledState;

void blink() {
        static uint32_t lastTick = 0;
        if (SYSTEM_TICK_COUNTER - lastTick < tickDebounce) return;
        lastTick = SYSTEM_TICK_COUNTER;
        ledState = !ledState;

        digitalWrite(D7, ledState);
}


void setup() {
        pinMode(A0, INPUT_PULLUP);
        pinMode(D7, OUTPUT);
        attachInterrupt(A0, blink, FALLING);

        Serial.begin(115200);
}



void loop() {
        Serial.printlnf("DERP! %ld", millis());
        delay(5000);
}
