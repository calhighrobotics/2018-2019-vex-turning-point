#include "auto.hpp"
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

/** Selects the auton program. */
static void autonSelect();

void lcdEventLoop()
{
    enum LCDState
    {
        MAIN, BATTERY, AUTON_SELECT, NUM_STATES
    };
    static LCDState state = AUTON_SELECT;

    buttons.poll();
    lcdClear(port);

    switch (state)
    {
        case MAIN:
            // display greeting message
            lcdSetText(port, 1, "B for better!");
            break;
        case BATTERY:
            // battery readout
            lcdPrint(port, 1, "Primary: %.1fV", powerLevelMain() / 1000.f);
            lcdPrint(port, 2, "Backup:  %.1fV", powerLevelBackup() / 1000.f);
            break;
        case AUTON_SELECT:
            // autonomous program selection
            autonSelect();
            break;
        default:
            lcdPrint(port, 1, "Unknown state %d", static_cast<int>(state));
    }

    if (buttons.justPressed(LCD_BTN_CENTER))
    {
        state = static_cast<LCDState>((state + 1) % NUM_STATES);
    }
}

void autonSelect()
{
    using namespace auton;

    // display each line of the auton names
    lcdPrint(port, 1, autonNames[getAuton()][0]);
    lcdPrint(port, 2, autonNames[getAuton()][1]);

    // use left/right buttons to cycle between auton programs
    if (buttons.justPressed(LCD_BTN_LEFT))
    {
        setAuton(static_cast<Auton>((getAuton() - 1) % NUM_AUTONS));
    }
    if (buttons.justPressed(LCD_BTN_RIGHT))
    {
        setAuton(static_cast<Auton>((getAuton() + 1) % NUM_AUTONS));
    }
}
