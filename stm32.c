@@name printf �ض���

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

@@name cmsisrtos �̴߳���
//��������
osThreadId xxxHandle;//�������

static void xxx(void const *argument);//�̺߳���
//os init ������
osThreadDef(THREAD_1,xxx,osPriorityNormal, 0,configMINIMAL_STACK_SIZE);//�Զ��߳������߳�ʵ�ʺ�����os���ȼ���ʵ����ջ��С
xxxHandle = osThreadCreate(osThread(THREAD_1),NULL);//�����߳�

@@end

@@name cmsisrtos �����̺߳���

osStatus osThreadSuspend (osThreadId thread_id)//Suspend execution of a thread.
osStatus osThreadResume (osThreadId thread_id)//Resume execution of a suspended thread.


@@end

@@name hal_spi

HAL_SPI_Transmit(&hspi1,&Cbyte,1,0xFFFFFF);

@@end

@@name Tim pwm

htim3.Instance = TIM3;
htim3.Init.Prescaler = 71;//Ԥ��Ƶ,ʵ��+1
htim3.Init.CounterMode = TIM_COUNTERMODE_UP;//����ģʽ
htim3.Init.Period = 1999;//����,ʵ��+1
htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

sConfigOC.OCMode = TIM_OCMODE_PWM1;//pwnģʽ 

// TIM_OCMode_PWM1��TIM_OCMode_PWM2������
// 	TIM_OCMode_PWM1ģʽ�£���������ʱ����ʱ���ļ���ֵTIMx_CNT<CCCR1_ValΪ��Ч��ƽ������Ϊ��Ч��ƽ���ڼ�����ʱ����ʱ���ļ���ֵTIMx_CNT>CCCR1_ValΪ��Ч��ƽ������Ϊ��Ч��ƽ��
// 	TIM_OCMode_PWM2ģʽ�£���������ʱ����ʱ���ļ���ֵTIMx_CNT<CCCR1_ValΪ��Ч��ƽ������Ϊ��Ч��ƽ���ڼ�����ʱ����ʱ���ļ���ֵTIMx_CNT>CCCR1_ValΪ��Ч��ƽ������Ϊ��Ч��ƽ��
// 	��Ч����Ч��ƽ��TIM_OCInitStructure.TIM_OCPolarity������
// TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High ��ߵ�ƽΪ��Ч��ƽ���͵�ƽΪ��Ч��ƽ��
// TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low ��ߵ�ƽΪ��Ч��ƽ���͵�ƽΪ��Ч��ƽ��

sConfigOC.Pulse = 150;//�������
sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;//����
sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,180);//����pwm����
// Sets the TIM Capture Compare Register value on runtime without 
// calling another time ConfigChannel function.


@@end

@@name ���

htim3.Init.Prescaler = 71;//Ԥ��Ƶ,ʵ��+1
htim3.Init.Period = 1999;//����,ʵ��+1
sConfigOC.OCMode = TIM_OCMODE_PWM1;//pwnģʽ 


    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,180);//����
    HAL_Delay(500);
    
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,180+175);//�м�
    HAL_Delay(500);
		
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,530);//����
    HAL_Delay(500);

@end