/**
 * @file slushboard.cpp
 *
 */
/*
 * Based on https://github.com/Roboteurs/slushengine/tree/master/Slush
 */
/* Copyright (C) 2017 by Arjan van Vught mailto:info@raspberrypi-dmx.nl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

extern "C" {
    #include <stdint.h>
    #include <stdio.h>
    #include <assert.h>
    #include <unistd.h>
    #include "SPI.h"
}

#include "slushboard.h"

extern GPIO_Pin motor_SPI_CS[7];
extern GPIO_Pin MTR_RESET;

SlushBoard::SlushBoard(void)
{
    // #if defined (__linux__)  || defined(__circle__)
    // 	if (bcm2835_init() == 0) {
    // 		printf("Not able to init the bmc2835 library\n");
    // 	}
    // #endif

    // bcm2835_gpio_fsel(SLUSH_L6470_RESET, BCM2835_GPIO_FSEL_OUTP);
    // bcm2835_gpio_set(SLUSH_L6470_RESET);

    MTR_RESET.init(SLUSH_L6470_RESET);

    // bcm2835_gpio_fsel(SLUSH_MTR0_CHIPSELECT, BCM2835_GPIO_FSEL_OUTP);
    // bcm2835_gpio_fsel(SLUSH_MTR1_CHIPSELECT, BCM2835_GPIO_FSEL_OUTP);
    // bcm2835_gpio_fsel(SLUSH_MTR2_CHIPSELECT, BCM2835_GPIO_FSEL_OUTP);
    // bcm2835_gpio_fsel(SLUSH_MTR3_CHIPSELECT, BCM2835_GPIO_FSEL_OUTP);

    motor_SPI_CS[0].init(SLUSH_MTR0_CHIPSELECT);
    motor_SPI_CS[1].init(SLUSH_MTR1_CHIPSELECT);
    motor_SPI_CS[2].init(SLUSH_MTR2_CHIPSELECT);
    motor_SPI_CS[3].init(SLUSH_MTR3_CHIPSELECT);
    motor_SPI_CS[4].init(SLUSH_MTR4_CHIPSELECT);
    motor_SPI_CS[5].init(SLUSH_MTR5_CHIPSELECT);
    motor_SPI_CS[6].init(SLUSH_MTR6_CHIPSELECT);

    // bcm2835_gpio_set(SLUSH_MTR0_CHIPSELECT);
    // bcm2835_gpio_set(SLUSH_MTR1_CHIPSELECT);
    // bcm2835_gpio_set(SLUSH_MTR2_CHIPSELECT);
    // bcm2835_gpio_set(SLUSH_MTR3_CHIPSELECT);

    for (int i = 0; i <= 6; i++)
        motor_SPI_CS[i].set();

    // bcm2835_gpio_fsel(SLUSH_MTR0_BUSY, BCM2835_GPIO_FSEL_INPT);
    // bcm2835_gpio_fsel(SLUSH_MTR1_BUSY, BCM2835_GPIO_FSEL_INPT);
    // bcm2835_gpio_fsel(SLUSH_MTR2_BUSY, BCM2835_GPIO_FSEL_INPT);
    // bcm2835_gpio_fsel(SLUSH_MTR3_BUSY, BCM2835_GPIO_FSEL_INPT);

    // bcm2835_gpio_clr(SLUSH_L6470_RESET);
    // udelay(10000);
    // bcm2835_gpio_set(SLUSH_L6470_RESET);
    // udelay(10000);
    
    MTR_RESET.clear();
    usleep(100000);
    MTR_RESET.set();
    usleep(100000);

    // bcm2835_gpio_fsel(SLUSH_MCP23017_RESET, BCM2835_GPIO_FSEL_OUTP);
    // bcm2835_gpio_set(SLUSH_MCP23017_RESET);

    InitSpi();
    // InitI2c();
}

SlushBoard::~SlushBoard(void)
{
    for (int i = 0; i <= 6; i++)
        motor_SPI_CS[i].clear();
}

void SlushBoard::InitSpi(void)
{
    // bcm2835_spi_begin();

    // bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE);
    // bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);
    // bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);

    if (SPI_DEV1_init(SPIDEV_BYTES_NUM, SPIDEV1_BUS_SPEED_HZ, SPI_SS_LOW,
                      SPIDEV_DELAY_US, SPIDEV_DATA_BITS_NUM,
                      SPI_MODE3) == -1)
        DEBUG_PRINT("(Main)spidev1.0 initialization failed");
    else
        DEBUG_PRINT("(Main)spidev1.0 initialized - READY");
}

void SlushBoard::InitI2c(void)
{
    // char data;

    // bcm2835_i2c_begin();

    /*
     *  MCP23017
     *  Initializes as input, with pull-up
     */

    // I2cSetup(MCP23017_I2C_ADDRESS);

    // Mcp23017WriteReg(MCP23017_IODIRA, 0xFF);
    // Mcp23017WriteReg(MCP23017_IODIRB, 0xFF);

    // Mcp23017WriteReg(MCP23017_GPPUA, 0xFF);
    // Mcp23017WriteReg(MCP23017_GPPUB, 0xFF);

    /*
     * MAX1164
     * Initializes the first channel in single ended mode with Vdd as Vref
     */

    // I2cSetup(MAX1164_I2C_ADDRESS);

    // data = 0x8a;
    // (void) bcm2835_i2c_write((char *)&data, 1);
    // data = 0x01;
    // (void) bcm2835_i2c_write((char *)&data, 1);
}

void SlushBoard::I2cSetup(uint8_t address)
{
    // bcm2835_i2c_setSlaveAddress(address);
    // bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_626);
}

uint8_t SlushBoard::Mcp23017ReadReg(uint8_t reg)
{
    // char data = reg;

    // I2cSetup(MCP23017_I2C_ADDRESS);

    // (void) bcm2835_i2c_write((char *)&data, 1);
    // (void) bcm2835_i2c_read((char *)&data, 1);

    // return data;
}

void SlushBoard::Mcp23017WriteReg(uint8_t reg, uint8_t data)
{
    // uint8_t buffer[2];

    // buffer[0] = reg;
    // buffer[1] = data;

    // I2cSetup(MCP23017_I2C_ADDRESS);

    // bcm2835_i2c_write((char *)buffer, 2);
}

void SlushBoard::setIOState(TSlushIOPorts nPort, TSlushIOPins nPinNumber, uint8_t state)
{
    // assert(nPort <= SLUSH_IO_PORTB);
    // assert(nPinNumber <= SLUSH_IO_PIN7);

    // IOFSel(nPort, nPinNumber, SLUSH_IO_FSEL_OUTP);

    // if (state == 0) {
    //     IOClr(nPort, nPinNumber);
    // } else {
    //     IOSet(nPort, nPinNumber);
    // }
}

void SlushBoard::setIOState(uint8_t nPort, uint8_t nPinNumber, uint8_t state)
{
    // setIOState((TSlushIOPorts) nPort, (TSlushIOPins) nPinNumber, state);
}


uint8_t SlushBoard::getIOState(TSlushIOPorts nPort, TSlushIOPins nPinNumber)
{
    // assert(nPort <= SLUSH_IO_PORTB);
    // assert(nPinNumber <= SLUSH_IO_PIN7);

    // IOFSel(nPort, nPinNumber, SLUSH_IO_FSEL_INPT);

    // return IOLev(nPort, nPinNumber);
}

uint8_t SlushBoard::getIOState(uint8_t nPort, uint8_t nPinNumber)
{
    // return getIOState((TSlushIOPorts) nPort, (TSlushIOPins) nPinNumber);
}

void SlushBoard::IOFSel(TSlushIOPorts nPort, TSlushIOPins nPinNumber, TSlushIOFSel fsel)
{
    // assert(nPort <= SLUSH_IO_PORTB);
    // assert(nPinNumber <= SLUSH_IO_PIN7);
    // assert(fsel <= SLUSH_IO_FSEL_INPT);

    // uint8_t data = Mcp23017ReadReg(MCP23017_IODIRA + nPort);
    // uint8_t pin = 1 << (nPinNumber % 8);

    // if (fsel == SLUSH_IO_FSEL_OUTP) {
    //     data &= (~(pin));
    // } else {
    //     data |= pin;
    // }

    // Mcp23017WriteReg(MCP23017_IODIRA + nPort, data);
}

void SlushBoard::IOClr(TSlushIOPorts nPort, TSlushIOPins nPinNumber)
{
    // assert(nPort <= SLUSH_IO_PORTB);
    // assert(nPinNumber <= SLUSH_IO_PIN7);

    // uint8_t data = IORead(nPort);

    // data &= (~(1 << (nPinNumber % 8)));

    // IOWrite(nPort, data);
}

void SlushBoard::IOSet(TSlushIOPorts nPort, TSlushIOPins nPinNumber)
{
    // assert(nPort <= SLUSH_IO_PORTB);
    // assert(nPinNumber <= SLUSH_IO_PIN7);

    // uint8_t data = IORead(nPort);

    // data |= 1 << (nPinNumber % 8);

    // IOWrite(nPort, data);
}

uint8_t SlushBoard::IOLev(TSlushIOPorts nPort, TSlushIOPins nPinNumber)
{
    // assert(nPort <= SLUSH_IO_PORTB);
    // assert(nPinNumber <= SLUSH_IO_PIN7);

    // uint8_t data = IORead(nPort);
    // uint8_t pin = 1 << (nPinNumber % 8);

    // if ((data & pin) == pin) {
    //     return 1;
    // } else {
    //     return 0;
    // }
}

uint8_t SlushBoard::IORead(TSlushIOPorts nPort)
{
    // assert(nPort <= SLUSH_IO_PORTB);

    // return Mcp23017ReadReg(MCP23017_GPIOA + nPort);
}

void SlushBoard::IOWrite(TSlushIOPorts nPort, uint8_t data)
{
    // assert(nPort <= SLUSH_IO_PORTB);

    // Mcp23017WriteReg(MCP23017_OLATA + nPort, data);
}
