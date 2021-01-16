//
// Created by famiglia on 16/01/21.
//

#ifndef SOURCE_TIMERREGISTER_H
#define SOURCE_TIMERREGISTER_H

#define TIMS ((unsigned volatile char *) 0xFED0)
#define TIMC ((unsigned volatile char *) 0xFED1)

#include <functional>

static std::function<void ()> registeredCallback;
static int timer;
//interrupt routine must be global
void TIM_irq() {

    *TIMC = timer;
    *TIMS |= (1<<6); /*writing clears the bit: 1<<6 */
    /*IF: Interrupt flag. Must be cleared before returning from the
    interrupt routine. */
    *TIMS  |= (1<<3); //start again
    //call the functon after timer start so that it will not skew
    registeredCallback();
    //passes a function to TimerRegister.callback..

}

class TimerRegister {
/*
 *  required to implement the following C++
    class whose constructor initializes the timer, and whose registerCallback member function is a
    nonblocking function that will call the function passed as argument from the interrupt routine
    periodically with the given period (you can assume periodMilliseconds must be between 1 and 250
    ms). Calling registerCallback again will replace the previous callback with the new one.

 */


public:

    TimerRegister() {
        *TIMS |= (1<<7) |  (1<<0); /*writing clears the bit: 6<<1 */

    }

    void registerCallback(std::function<void ()> function, int periodMilliseconds) {

        if (periodMilliseconds<1 && periodMilliseconds>255);
        //disable timer
        *TIMS  &= ~ ((1<<3) | (1<<6));  //and bitmask on 6 for safety, it's a rc_w1 bit
        timer = periodMilliseconds;
        //execute function
        registeredCallback = function;
        //reset counter
        *TIMC = periodMilliseconds -1;

        *TIMS  |= (1<<3);
    }
private:
};


#endif //SOURCE_TIMERREGISTER_H
