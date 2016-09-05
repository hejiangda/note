@@name printf 重定向

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}
@@end

@@name cmsisrtos 线程创建
//声明定义
osThreadId xxxHandle;//创建句柄

static void xxx(void const *argument);//线程函数
//os init 函数中
osThreadDef(THREAD_1,xxx,osPriorityNormal, 0,configMINIMAL_STACK_SIZE);//自定线程名，线程实际函数，os优先级，实例，栈大小
xxxHandle = osThreadCreate(osThread(THREAD_1),NULL);//创建线程

@@end

@@name cmsisrtos 常用线程函数

osStatus osThreadSuspend (osThreadId thread_id)//Suspend execution of a thread.
osStatus osThreadResume (osThreadId thread_id)//Resume execution of a suspended thread.


@@end

@@name hal_spi

HAL_SPI_Transmit(&hspi1,&Cbyte,1,0xFFFFFF);

@@end

@@name Tim pwm

htim3.Instance = TIM3;
htim3.Init.Prescaler = 71;//预分频,实际+1
htim3.Init.CounterMode = TIM_COUNTERMODE_UP;//计数模式
htim3.Init.Period = 1999;//计数,实际+1
htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

sConfigOC.OCMode = TIM_OCMODE_PWM1;//pwn模式 

// TIM_OCMode_PWM1与TIM_OCMode_PWM2的区别：
// 	TIM_OCMode_PWM1模式下：在增计数时，定时器的计数值TIMx_CNT<CCCR1_Val为有效电平，否则为无效电平；在减计数时，定时器的计数值TIMx_CNT>CCCR1_Val为有效电平，否则为无效电平。
// 	TIM_OCMode_PWM2模式下：在增计数时，定时器的计数值TIMx_CNT<CCCR1_Val为无效电平，否则为有效电平；在减计数时，定时器的计数值TIMx_CNT>CCCR1_Val为无效电平，否则为有效电平。
// 	有效与无效电平由TIM_OCInitStructure.TIM_OCPolarity决定：
// TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High 则高电平为有效电平，低电平为无效电平。
// TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low 则高电平为有效电平，低电平为无效电平。

sConfigOC.Pulse = 150;//脉冲次数
sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;//极性
sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,180);//更新pwm脉冲
// Sets the TIM Capture Compare Register value on runtime without 
// calling another time ConfigChannel function.


@@end

@@name 舵机

htim3.Init.Prescaler = 71;//预分频,实际+1
htim3.Init.Period = 1999;//计数,实际+1
sConfigOC.OCMode = TIM_OCMODE_PWM1;//pwn模式 


    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,180);//最右
    HAL_Delay(500);
    
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,180+175);//中间
    HAL_Delay(500);
		
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,530);//最左
    HAL_Delay(500);

@end