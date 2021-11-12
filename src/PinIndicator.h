#include "Indicator.h"

class PinIndicator : public Indicator
{
public:
    PinIndicator(int pin, bool invert = false);
    void write(bool enable);

private:
    int pin_;
    bool invert_;
};
