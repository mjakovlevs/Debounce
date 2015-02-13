//
//  Debounce.cpp
//  
//
//  Created by Mihails Jakovlevs on 12/02/2015.
//  Rev 2.0
//

#include <Arduino.h>
#include "Debounce.h"

// constructors
Debounce::Debounce() {
    init(25, 1000, HOLD_MODE_ONCE);
}

Debounce::Debounce(long _t_debounce) {
    init(_t_debounce, 1000, HOLD_MODE_ONCE);
}

Debounce::Debounce(long _t_debounce, long _t_hold) {
    init(_t_debounce, _t_hold, HOLD_MODE_ONCE);
}

Debounce::Debounce(long _t_debounce, long _t_hold, bool _hold_mode) {
    init(_t_debounce, _t_hold, _hold_mode);
}

// constructor parameter init
void Debounce::init(long _t_debounce, long _t_hold, bool _hold_mode) {
    state_raw = false;
    state_raw_last = false;
    state_debounced = false;
    state_debounced_last = false;
    is_held = false;
    
    t_last = millis();
    t_hold_timer = 0;
    
    t_debounce = _t_debounce;
    t_hold = _t_hold;
    
    hold_mode = _hold_mode;
}

// call this when you read the button state, this will trigger debounce
void Debounce::writeState(bool _state_raw) {
    state_raw_last = state_raw;
    state_raw = _state_raw;
    
    debounce(t_debounce);
}

// THE debounce function
void Debounce::debounce(long _t_debounce) {
    if (state_raw != state_raw_last) {
        t_last = millis();
    }
    
    if (millis() - t_last > _t_debounce) {
        state_debounced_last = state_debounced;
        state_debounced = state_raw;
    }
}

// this returns true for one cycle when transition from false to true occurs (button is pressed down)
bool Debounce::pressed() {
    if (state_debounced != state_debounced_last && state_debounced) return true;
    else return false;
}

// this returns true for one cycle when transition from true to false occurs (button is released)
// also is only triggered if the button has not been held
bool Debounce::released() {
    if (state_debounced != state_debounced_last && !state_debounced && !is_held) return true;
    else return false;
}

// this is triggered when the button is being held down for the amount of time set in t_hold
bool Debounce::held() {
    if (pressed()) {
        t_hold_timer = millis();
        is_held = false;
    }
    // this is executed only if HOLD_MODE_RETRIG
    if (state_debounced && millis() - t_hold_timer > t_hold && hold_mode == HOLD_MODE_RETRIG) {
        t_hold_timer = millis();
        is_held = true;
        return true;
    }
    // this - if HOLD_MODE_ONCE and the button has not been held down
    else if (state_debounced && millis() - t_hold_timer > t_hold && !is_held) {
        t_hold_timer = millis();
        is_held = true;
        return true;
    }
    else return false;
}

// call this to return continuous button state
bool Debounce::down() {
    return state_debounced;
}

// user setters
void Debounce::setDebounceTime(long _t_debounce){
    t_debounce = _t_debounce;
}

void Debounce::setHoldMode(bool _hold_mode){
    hold_mode = _hold_mode;
}

void Debounce::setHoldTime(long _t_hold){
    t_hold = _t_hold;
}
