#include "main.h"
#include "calibration.h"


/* USER CODE BEGIN 1 */
//��ȡADCֵ


float ADC_value1=0;
float ADC_value2=0;


float ADC_GetValue(void)
{

	float BAT=0;
	int32_t ADC_value=0;
	
	//����ʱ��ѡ���������׼ȷ
//	hadc.Init.SamplingTime = ADC_SAMPLETIME_160CYCLES_5;
	
	//����ADCУ׼
	HAL_ADCEx_Calibration_Start(&hadc1);
	//����ADCת��
	HAL_ADC_Start(&hadc1);										//first conv
	//�ȴ�ת�����
	if(HAL_ADC_PollForConversion(&hadc1, 200)== HAL_OK)
	{
		//��ȡ�ڵ�ǰ���������µ�ADC����ֵ
		if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
		{
			ADC_value = HAL_ADC_GetValue(&hadc1);
//			printf("%d\n",ADC_value);
			BAT=(float)(3.3*ADC_value/4096);
		}
	}		
	//ֹͣADCת��
	HAL_ADC_Stop(&hadc1);										//stop conv
//	printf("%.02f\n",BAT);
	return BAT;
}



float firstOrderFilter(float newValue, float oldValue, float a)
{
	return a * newValue + (1-a) * oldValue;
}



float GetValue(int N)
{
	
	float ADC_value[N];	
	for(int i=0;i<N;i++)
	{
	   ADC_value[i] = ADC_GetValue();	
	}
//	for(int i=0;i<N;i++)
//	{
//	printf("%.3f\n",ADC_value[i]);
//	}			
    int j,k;
	float temp;	
    for(j = 0 ; j < N; ++j)
    {
        for(k = 0; k < N-j-1; ++k)
        {
            //��С��������ð�ݷ�����
            if(ADC_value[k] > ADC_value[k+1])
            {
                temp = ADC_value[k];
                ADC_value[k] = ADC_value[k+1];
                ADC_value[k+1] = temp;
            }
        }
    }
//for(int i=0;i<9;i++)
//	{
//	printf("%.3f\n",ADC_value[i]);
//	}	
  return ADC_value[(N-1)/2];

}	
float GetValue2(int N)
{
	float BAT=0;
	if(ADC_value1==0)
	{
		ADC_value1=GetValue(N);		
	}
//	printf("ADC_value1:%.3f\n",ADC_value1);
    ADC_value2=GetValue(N);	
//	printf("ADC_value2:%.3f\n",ADC_value2);
    BAT=firstOrderFilter(ADC_value2, ADC_value1, 0.2);	
//	printf("BAT:%.3f\n",BAT);
    ADC_value1=ADC_value2;
    return  BAT;
}

/* USER CODE END 1 */


