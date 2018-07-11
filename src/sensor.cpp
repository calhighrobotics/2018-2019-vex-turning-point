#include "sensor.hpp"
#include <API.h>

void sensor::init()
{
    pinMode(PUNCHER_LIMIT, INPUT);
}