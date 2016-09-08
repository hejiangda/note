#include "stm32f1xx_hal.h"

#include "spi.h"
#include "mini12864.h"

//дָ��

void write_cmd(uint8_t Cbyte)
{
	CS_ENABLE();
	A0_ENABLE();
	HAL_SPI_Transmit(&hspi1,&Cbyte,1,0xFFFFFF);
}

//д����

void write_data(uint8_t Dbyte)
{
	CS_ENABLE();
	A0_DISABLE();
	HAL_SPI_Transmit(&hspi1,&Dbyte,1,0xFFFFFF);
}

/*
* ������ȡģ˳��������ʽ��
* ���ϵ��£���λ��ǰ�������ң�
* ��ѡ��ҳ��ַ0-7����ѡ����0-127
* ҳ����ֱ�Ӷ�ȡ8λ������Ϊ��ַ��
* �����ȶ�ȡ����λ�����ȡ����λ��
*/

void LcmClear()
{	 
  uint8_t x,y;
	for(y=0;y<8;y++)
	{
    write_cmd(0xb0+y);
    write_cmd(0x10);
    write_cmd(0x00);
    for(x=0;x<132;x++)  
      write_data(0); 
  }
}

//��ʼ��

void LcmInit()
{
	  CS_ENABLE();
    RST_ENABLE();
		HAL_Delay(200);
		RST_DISABLE();
		HAL_Delay(1000);
		write_cmd(0xe2);//system reset
		HAL_Delay(200);
		write_cmd(0x24);//SET VLCD RESISTOR RATIO
		write_cmd(0xa2);//BR=1/9
		write_cmd(0xa0);//set seg direction
		write_cmd(0xc8);//set com direction
		write_cmd(0x2f);//set power control
		write_cmd(0x40);//set scroll line
		write_cmd(0x81);//SET ELECTRONIC VOLUME
		write_cmd(0x20);//set pm: ͨ���ı��������ֵ���ı��ѹ
		write_cmd(0xaf);//set display enable
    LcmClear();
}

//��ʾ����

void  dianxian()
{
  uint8_t x,y;
  for(y=0;y<8;y++)
  {    
    write_cmd(0xb0+y);
    write_cmd(0x10);		
		write_cmd(0x00);
    for(x=0;x<128;x++) 
      write_data(0x55); 
  }	 
}

/*************************
8*8�ַ���ȡģ˳��������ʽ��
���ϵ��£���λ��ǰ�������ң�
��ѡ��ҳ��ַ0-7����ѡ����0-130
ҳ����ֱ�Ӷ�ȡ8λ������Ϊ��ַ��
�����ȶ�ȡ����λ�����ȡ����λ��
**********************/
void PUTchar8x8(uint8_t row,uint8_t col,uint8_t count,uint8_t *put)
{
	uint8_t i,j;
	uint8_t X=0;
	write_cmd(0xb0+row);
  	write_cmd(0x10+(8*col/16));
	write_cmd(0x00+(8*col%16));
	for(j=0;j<count;j++)
	{
		for(i=0;i<8;i++) write_data(put[X++]);
		write_cmd(0xb1+row);
		write_cmd(0x10+(8*col/16));
		write_cmd(0x00+(8*col%16));
		for(i=0;i<8;i++) write_data(put[X++]);
	    write_cmd(0xb0+row);
		col=col+1;
	}
}
/*****************
8*16�ַ���ȡģ˳��������ʽ��
���ϵ��£���λ��ǰ�������ң�
��ѡ��ҳ��ַ0-7����ѡ����0-127
ҳ����ֱ�Ӷ�ȡ8λ������Ϊ��ַ��
�����ȶ�ȡ����λ�����ȡ����λ��
**********************/

void  PUTchar8x16(uint8_t row,uint8_t col,uint8_t count,uint8_t *put)
{
	uint8_t i,j;
	uint8_t X=0;
		write_cmd(0xb0+row);
	  	write_cmd(0x10+(8*col/16));
		write_cmd(0x00+(8*col%16));
		for(j=0;j<count;j++)
		{ for(i=0;i<8;i++) write_data(put[X++]);
	  	  write_cmd(0xb1+row);
		  write_cmd(0x10+(8*col/16));
		  write_cmd(0x00+(8*col%16));
		  for(i=0;i<8;i++) write_data(put[X++]);
	      write_cmd(0xb0+row);
		  col=col+1; }

}
/*****************
16*16�ַ���ȡģ˳��������ʽ��
���ϵ��£���λ��ǰ�������ң�
��ѡ��ҳ��ַ0-7����ѡ����0-127
ҳ����ֱ�Ӷ�ȡ8λ������Ϊ��ַ��
�����ȶ�ȡ����λ�����ȡ����λ��
**********************/

void  PUTchar16x16(uint8_t row,uint8_t col,uint8_t count,uint8_t  *put)
{		uint8_t i,j;
		uint8_t X=0;
		write_cmd(0xb0+row);
	  	write_cmd(0x10+(8*col/16));
		write_cmd(0x00+(8*col%16));
		for(j=0;j<count;j++)
		{ for(i=0;i<16;i++) write_data(put[X++]);
	  	  write_cmd(0xb1+row);
		  write_cmd(0x10+(8*col/16));
		  write_cmd(0x00+(8*col%16));
		  for(i=0;i<16;i++) write_data(put[X++]);
	      write_cmd(0xb0+row);
		  col=col+2; }

}
/*****************
24*24�ַ���ȡģ˳��������ʽ��
���ϵ��£���λ��ǰ�������ң�
��ѡ��ҳ��ַ0-7����ѡ����0-127
ҳ����ֱ�Ӷ�ȡ8λ������Ϊ��ַ��
�����ȶ�ȡ����λ�����ȡ����λ��
**********************/

void  PUTchar24x24(uint8_t row,uint8_t col,uint8_t count,uint8_t  *put)
{		uint8_t i,j;
		uint8_t X=0;
		write_cmd(0xb0+row);
	  	write_cmd(0x10+(8*col/16));
		write_cmd(0x00+(8*col%16));
		for(j=0;j<count;j++)
		{ for(i=0;i<24;i++) write_data(put[X++]);
	  	  write_cmd(0xb1+row);
		  write_cmd(0x10+(8*col/16));
		  write_cmd(0x00+(8*col%16));
		  for(i=0;i<24;i++) write_data(put[X++]);
	      write_cmd(0xb2+row);
		  write_cmd(0x10+(8*col/16));
		  write_cmd(0x00+(8*col%16));
		  for(i=0;i<24;i++) write_data(put[X++]);
		  write_cmd(0xb0+row);
		  col=col+3; }
}
