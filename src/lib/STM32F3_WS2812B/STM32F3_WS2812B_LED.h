#include <Arduino.h>
#include <stdint.h>

#define pin PA_7

void inline LEDsend_1(){
        digitalWriteFast(pin, HIGH);
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); 
        digitalWriteFast(pin, LOW);
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); 
}

void inline LEDsend_0(){
        digitalWriteFast(pin, HIGH);
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); 
        digitalWriteFast(pin, LOW);
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); 
}

uint8_t bitReverse(uint8_t input)
{
    uint8_t r = input;     // r will be reversed bits of v; first get LSB of v
    uint8_t s = 8 - 1; // extra shift needed at end

    for (input >>= 1; input;input >>= 1)
    {
        r <<= 1;
        r |= input & 1;
        s--;
    }
    r <<= s; // shift when v's highest bits are zero
    return r;
}

//uint8_t WS281BLedColour[3] = {0,0,0};
uint8_t WS281BLedColourFlipped[3] = {0};
uint32_t LedColourData = 0;

//uint8_t state;

void WS281BsetLED(uint8_t *Data) // takes RGB data
{
    pinMode(PA7, OUTPUT);

    // while (1) // uncomment for colour demo
    // {
    //     WS281BLedColour[state % 3]++; // uncomment this block for colour demo

    //     if (WS281BLedColour[0] == 255 || WS281BLedColour[1] == 255 || WS281BLedColour[2] == 255)
    //     {
    //         state++;
    //         WS281BLedColour[0] = 0;
    //         WS281BLedColour[1] = 0;
    //         WS281BLedColour[2] = 0;
    //     }

    WS281BLedColourFlipped[0] = bitReverse(Data[0]);
    WS281BLedColourFlipped[1] = bitReverse(Data[1]);
    WS281BLedColourFlipped[2] = bitReverse(Data[2]);

    uint32_t g = (WS281BLedColourFlipped[1]);
    uint32_t r = (WS281BLedColourFlipped[0]) << 8;
    uint32_t b = (WS281BLedColourFlipped[2]) << 16;

    LedColourData = r + g + b;

    for (uint8_t i = 0; i < 24; i++)
    {
        bool val = (LedColourData >> i) & 1;

        if (val)
        {
            LEDsend_1();
        }
        else
        {
            LEDsend_0();
        }
    }
    digitalWriteFast(pin, LOW);
    delayMicroseconds(5000);
    LedColourData = 0;
    // }
}