#include "lcd.hpp"
#include <API.h>

/** LCD port. */
#define port uart1
/** Event loop delay in milliseconds. */
constexpr static unsigned long lcdDelay = 100;

/** Tracks the state of the buttons. */
class ButtonState
{
public:
    /** Creates a ButtonState object. */
    ButtonState()
        : current{ 0 }, previous{ 0 } {}

    /** Polls all the LCD buttons. */
    void poll()
    {
        previous = current;
        current = lcdReadButtons(port);
    }

    /** Checks if a button was pressed. */
    bool pressed(unsigned int button) const
    {
        return current & button;
    }

    /** Checks if a button was just pressed. */
    bool justPressed(unsigned int button) const
    {
        return pressed(button) && !(previous & button);
    }

    /** Checks if a button was just released. */
    bool justReleased(unsigned int button) const
    {
        return !pressed(button) && (previous & button);
    }

private:
    /** Current button state. */
    unsigned int current;
    /** Previous button state. */
    unsigned int previous;
};

/** Tracks the state of the buttons. */
static ButtonState buttons;

/** Event loop which responds to LCD input. */
static void lcdEventLoop();

void lcd::init()
{
    lcdInit(port);
    lcdClear(port);
    lcdSetBacklight(port, false);

    taskRunLoop(lcdEventLoop, lcdDelay);
}

/** LCD loop state. */
enum LCDState
{
    MAIN, BATTERY, NUM_STATES
};

/** State loop var. */
static LCDState state = MAIN;

void lcdEventLoop()
{
    buttons.poll();
    lcdClear(port);

    switch (state)
    {
        case MAIN:
            lcdSetText(port, 1, "B for better!");
            break;
        case BATTERY:
            lcdPrint(port, 1, "Primary: %.1fV", powerLevelMain() / 1000.f);
            lcdPrint(port, 2, "Backup:  %.1fV", powerLevelBackup() / 1000.f);
            break;
        default:
            lcdPrint(port, 1, "Unknown state %d", static_cast<int>(state));
    }

    if (buttons.justPressed(LCD_BTN_CENTER))
    {
        state = static_cast<LCDState>((state + 1) % NUM_STATES);
    }
}
