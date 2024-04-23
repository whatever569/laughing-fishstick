#ifndef CONTROLS_H
#define CONTROLS_H

#define A_BUTTON_SHIFT
#define A_BUTTON_PORT

#define B_BUTTON_SHIFT
#define B_BUTTON_PORT

#define C_BUTTON_SHIFT
#define C_BUTTON_PORT

#define D_BUTTON_SHIFT
#define D_BUTTON_PORT

#define MASK(x) (1UL<<x)

bool isAPressed()
{
    return false;
}
bool isBPressed()
{
    return false;
}
bool isCPressed()
{
    return false;
}
bool isDPressed()
{
    return false;
}
#endif