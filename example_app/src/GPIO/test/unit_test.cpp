#include "FauxGPIO.h"
#include "gtest/gtest.h"

TEST(GPIOTests, set_TEST) {
    FauxGPIO gpio;
    
    for (int i = 0; i < 8; i++) {
        gpio.set(i, true);
        EXPECT_TRUE(gpio.m_pinArray[i]);
        gpio.set(i, false);
        EXPECT_FALSE(gpio.m_pinArray[i]);
    }
}

TEST(GPIOTests, numPins_TEST) {
    FauxGPIO gpio;
    EXPECT_EQ(gpio.numPins(), gpio.m_pinArray.size());
}
