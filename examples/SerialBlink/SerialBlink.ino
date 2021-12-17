/**
 * This example does not blink a light, but outputs its state directly to the Serial
 * port.
 */

#include <BaseBlinker.h>

class SerialBlinker : public BaseBlinker
{
public:
    void write(int state) override
    {
        Serial.println(state);
    }
};

SerialBlinker myBlinker;

void setup()
{
    Serial.begin(9600);
    myBlinker.pattern(2, 4);
}

void loop()
{
    myBlinker.update();
}
