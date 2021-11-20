#include "timer.h"

MyTimer::MyTimer()
{
    // create a timer
    timer = new QTimer(this);
    // setup signal and slot
    // msec
    timer->start(1000);
}
