/**
 * This example does not blink a light, but outputs its state directly to the Serial
 * port.
 */

#include <BaseIndicator.h>

class SerialBlinker : public BaseIndicator
{
public:
    void write(int state) override
    {
        Serial.print("LED: ");
        Serial.println(state);
    }
};

SerialBlinker myBlinker;

void setup()
{
    myBlinker.pattern(2, 4);
}

void loop()
{
    myBlinker.update();
}
