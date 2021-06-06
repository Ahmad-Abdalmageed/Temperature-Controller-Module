/*
 * SPI.c
 *
 * Created: 5/6/2021 5:20:42 PM
 * Author: Ahmad Abdalmageed
 */ 

#include "SPI.h"

void SPI_MasterInit(void)
{	
	// Set SS / MOSI / SCK  as output pins for master*/
	DIO_vsetPINDir('B', 4, 1);
	DIO_vsetPINDir('B', 5, 1);
	DIO_vsetPINDir('B', 7, 1);
	
	// Set MISO as Input
	DIO_vsetPINDir('B', 6, 0);
	
	// Enable Master mode
	SPCR |= (1 << MSTR);
	
	// Select SPI Mode, Found Mode Compatible with Proteus 8.10
	SPCR &= ~(1 << CPOL);
	SPCR |= (1 << CPHA);

	// Set clock to SC/128
	SPCR |= (1 << SPR0);
	SPCR |= (1 << SPR1);
	
	// Enable SPI
    SPCR |= (1 << SPE);
}

char SPI_MasterTransmitchar(char Data)
{	
	// Write to SPDR 
	SPDR = Data;
	
	// Await SPI Communication to Finish
	while( ((SPSR & (1 << SPIF)) >> SPIF) == 0 );
	
	// FLush SPDR Register
	return SPDR ;
}