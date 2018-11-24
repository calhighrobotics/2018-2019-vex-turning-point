#include "lcd.hpp"
#include <API.h>

/** LCD port. */
#define port uart1
/** Event loop delay in milliseconds. */
constexpr static unsigned long lcdDelay = 100;

/** Event loop which responds to LCD input. */
static void lcdEventLoop();

void lcd::init()
{
    lcdInit(port);
    lcdClear(port);
    lcdSetBacklight(port, false);

    taskRunLoop(lcdEventLoop, lcdDelay);
}

void lcdEventLoop()
{
    lcdSetText(port, 1, "B for better!");
}
