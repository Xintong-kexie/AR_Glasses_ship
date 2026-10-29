#include "MLX90640_I2C_Driver.h"
#include "i2c.h"
#include "stm32l4xx_hal.h"

uint8_t ins = 0x06;
int MLX90640_I2CGeneralReset(void)
{
//	if(HAL_I2C_Mem_Write(&hi2c1, 0x00, 0x06, I2C_MEMADD_SIZE_8BIT, &ins, 1, 0x100) == HAL_OK)
//		return 0;
//	else
//		return -1;
//	hi2c1.Instance->CR1 |= I2C_CR1_SWRST;
//	hi2c1.Instance->CR1 &= ~I2C_CR1_SWRST;
//	MX_I2C1_Init();
	return 0;
}

int MLX90640_I2CRead(uint8_t slaveAddr,uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *data)
{
	uint8_t* ptr = (uint8_t*) data;
	int ack = 0;
	
	ack = HAL_I2C_Mem_Read(&hi2c2, slaveAddr, startAddress, I2C_MEMADD_SIZE_16BIT, ptr, nMemAddressRead*2, 0x100);
	if (ack != HAL_OK)
			return -1;

	for(int cnt = 0; cnt < nMemAddressRead*2; cnt += 2)
	{
		uint8_t tempBuffer = ptr[cnt+1];
		ptr[cnt+1] = ptr[cnt];
		ptr[cnt] = tempBuffer;
	}
	return 0;   
}

int MLX90640_I2CWrite(uint8_t slaveAddr,uint16_t writeAddress, uint16_t data)
{
	int ack = 0;
	uint8_t cmd[2];
	cmd[0] = data >> 8;
	cmd[1] = data & 0x00FF;
	static uint16_t dataCheck;
	
	ack = HAL_I2C_Mem_Write(&hi2c2, slaveAddr, writeAddress, I2C_MEMADD_SIZE_16BIT, cmd, sizeof(cmd), 500);
	if (ack != HAL_OK)
			return -1;
	
	MLX90640_I2CRead(slaveAddr,writeAddress,1, &dataCheck);
	if (dataCheck != data)
			return -2;
	
	return 0;
}

