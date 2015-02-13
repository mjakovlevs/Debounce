//
//  Debounce.h
//
//  Mihails Jakovlevs mjakovlevs@gmail.com
//  Rev 2.0 12.02.2015
//

#ifndef ____Debounce__
#define ____Debounce__

// hold mode parameters
#define HOLD_MODE_ONCE false
#define HOLD_MODE_RETRIG true

// same thing, shorthand
#define ONCE false
#define RETRIG true

class Debounce {
private:
    bool state_raw;             //undebounced state
    bool state_raw_last;        //last undebounced state
    bool state_debounced;       //debounced state
    bool state_debounced_last;  //last debounced state
    
    bool hold_mode;             //type of hold behavior
    bool is_held;               //hold flag, used for hold function
    
    long t_debounce;            //debounce time in milliseconds
    long t_hold;                //hold time in milliseconds
    long t_last;                //last time in milliseconds
    long t_hold_timer;          //timer used for timed hold function
    
public:
    Debounce();
    Debounce(long _t_debounce);
    Debounce(long _t_debounce, long _t_hold);
    Debounce(long _t_debounce, long _t_hold, bool _hold_mode);
    
    void init(long _t_debounce, long _t_hold, bool _hold_mode);
    
    void debounce(long _t_debounce);
    
    bool pressed();
    bool released();
    bool held();
    bool held(long _t_hold);
    bool down();
    
    // read button input, triggers debouncer
    void writeState(bool _state_raw);
    
    // user parameter setters
    void setHoldMode(bool _hold_mode);
    void setDebounceTime(long _t_debounce);
    void setHoldTime(long _t_hold);
};

#endif
