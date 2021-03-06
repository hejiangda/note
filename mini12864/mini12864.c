#include "stm32f1xx_hal.h"

#include "spi.h"
#include "mini12864.h"

//写指令

void write_cmd(uint8_t Cbyte)
{
	CS_ENABLE();
	A0_ENABLE();
	HAL_SPI_Transmit(&hspi1,&Cbyte,1,0xFFFFFF);
}

//写数据

void write_data(uint8_t Dbyte)
{
	CS_ENABLE();
	A0_DISABLE();
	HAL_SPI_Transmit(&hspi1,&Dbyte,1,0xFFFFFF);
}

/*
* 清屏；取模顺序是列行式，
* 从上到下，低位在前，从左到右；
* 先选择页地址0-7，再选择列0-127
* 页码是直接读取8位数据作为地址；
* 列是先读取高四位，后读取低四位；
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

//初始化

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
		write_cmd(0x20);//set pm: 通过改变这里的数值来改变电压
		write_cmd(0xaf);//set display enable
    LcmClear();
}

//显示程序

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
8*8字符，取模顺序是列行式，
从上到下，高位在前，从左到右；
先选择页地址0-7，再选择列0-130
页码是直接读取8位数据作为地址；
列是先读取高四位，后读取低四位；
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
8*16字符，取模顺序是列行式，
从上到下，高位在前，从左到右；
先选择页地址0-7，再选择列0-127
页码是直接读取8位数据作为地址；
列是先读取高四位，后读取低四位；
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
16*16字符，取模顺序是列行式，
从上到下，高位在前，从左到右；
先选择页地址0-7，再选择列0-127
页码是直接读取8位数据作为地址；
列是先读取高四位，后读取低四位；
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
24*24字符，取模顺序是列行式，
从上到下，高位在前，从左到右；
先选择页地址0-7，再选择列0-127
页码是直接读取8位数据作为地址；
列是先读取高四位，后读取低四位；
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
