#ifndef __mini12864_H
#define __mini12864_H
#include "stm32f1xx_hal.h"

#define CS_ENABLE()                      HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)
#define CS_DISABLE()                     HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)
#define RST_ENABLE()                      HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET)
#define RST_DISABLE()                     HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET)
#define A0_ENABLE()                      HAL_GPIO_WritePin(A0_GPIO_Port, A0_Pin, GPIO_PIN_RESET)
#define A0_DISABLE()                     HAL_GPIO_WritePin(A0_GPIO_Port, A0_Pin, GPIO_PIN_SET)

//д����
void write_cmd(uint8_t Cbyte);
//д����
void write_data(uint8_t Dbyte);
//����
void LcmClear(void);
//��ʼ����
void LcmInit(void);
//��ʾ����
void  dianxian(void);
//��ʾ�ַ�
void  PUTchar8x8(uint8_t row,uint8_t col,uint8_t count,uint8_t *put);
void  PUTchar8x16(uint8_t row,uint8_t col,uint8_t count,uint8_t *put);
void  PUTchar16x16(uint8_t row,uint8_t col,uint8_t count,uint8_t  *put);
void  PUTchar24x24(uint8_t row,uint8_t col,uint8_t count,uint8_t  *put);
#endif
