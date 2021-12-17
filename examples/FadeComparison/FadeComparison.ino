/*
 Open the arduino serial plotter to compare faders
 with / without logarithmic compensation
*/

#include <BaseFader.h>

BaseFader l1(true);
BaseFader l2(false);

void setup()
{
    Serial.begin(115200);
    l1.pattern(2, 3);
    l2.pattern(2, 3);
}

void loop()
{
    Serial.print(l1.update());
    Serial.print(" ");
    Serial.print(l2.update());
    Serial.println();
    delay(10);
}
