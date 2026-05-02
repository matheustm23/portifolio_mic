/*
 * spi.h
 *
 * Created: 24/04/2026 15:52:36
 *  Author: Matheus T Machado
 */ 


#ifndef SPI_H_
#define SPI_H_

//Prototipos de função
void SPI_config();
uint8_t SPI_transceiveByte(uint8_t pTransmittedByte);
void SPI_transceiveBuffer(uint8_t *pTransmitBuffer, uint8_t *pReceiveBuffer, uint16_t pSize);


#endif /* SPI_H_ */