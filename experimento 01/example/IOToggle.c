/**
 ******************************************************************************
 * @file    GPIO/IOToggle/main.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    30-September-2011
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
 * @{
 */

/** @addtogroup IOToggle
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  GPIO pin toggle program
 * @param  None
 * @retval None
 */
void IOToggle(void)
{
	/*!< At this stage the microcontroller clock setting is already configured,
	 this is done through SystemInit() function which is called from startup
	 file (startup_stm32f4xx.s) before to branch to application main.
	 To reconfigure the default setting of SystemInit() function, refer to
	 system_stm32f4xx.c file
	 */

	/* GPIOD Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // configurando como saida
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //pushpull 0/1
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //Não tem pull up ou pull down
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // configurando como entrada
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;// Na placa já tem o resisto de pull down
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // configurando como entrada
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;// Na placa já tem o resisto de pull down
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// Variáveis
	uint32_t tempo = 5000000;  // Tempo inicial de delay (ritmo inicial)
	uint32_t max = 500000;     // Tempo mínimo de delay (máximo ritmo)
	uint32_t min = 5000000;    // Tempo máximo de delay (mínimo ritmo)
	int direcao = -1;          // Controla a direção da aceleração (1 = acelerando, -1 = desacelerando)

	int congela = 0;           // Flag para verificar se o ritmo está congelado
	int EstadoBTanterior = 1;  // Estado anterior do botão PB12 (inicialmente "não pressionado")
	int EstadoBTatual = 1;     // Estado atual do botão PB12



	while (1)
	{

		/*
		 //primeiro exercicio
		 if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == RESET)  // Verifica se foi pressionado o pino A0
		{
			//GPIO_WriteBit(GPIOD, GPIO_Pin_12, SET);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
			//GPIO_SetBits(GPIOD, GPIO_Pin_12);
		}
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == SET)  // Verifica se foi pressionado o pino A0
				{
					//GPIO_WriteBit(GPIOD, GPIO_Pin_12, SET);
					GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
					//GPIO_SetBits(GPIOD, GPIO_Pin_12);
				}
		Delay(10000000);
        GPIO_ToggleBits(GPIOD, GPIO_Pin_14);*/

		//------------------------------------------------------------------------------------------
		//segundo exercicio
		/*
		int32_t a = 5000000;
		int32_t estado;
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == SET)  // Verifica se foi pressionado o pino A0
		{
			if (estado == 0) //troca de estado
			{
				estado = 1;
			}else {
				estado = 0;
			}
		}

		if (estado == 1) //acende no sentido horario
		{
								GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
								Delay(a);
								GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
								GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
								Delay(a);
								GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
								GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
								Delay(a);
								GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
								GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
								Delay(a);
								GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
						}else{
						//acende no sentido anti-horario
								GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
								Delay(a);
								GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
								GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
								Delay(a);
								GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
								GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
								Delay(a);
								GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
								GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
								Delay(a);
								GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
						}
		 	 	 	 	 */
				//------------------------------------------------------------------------------------------
				//terceiro exercicio - acelerando o tempo de piscad

		// Parte da sequência de piscadas dos LEDs
		/*
		        GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		        Delay(tempo);
		        GPIO_ToggleBits(GPIOD, GPIO_Pin_12);

		        GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
		        Delay(tempo);
		        GPIO_ToggleBits(GPIOD, GPIO_Pin_13);

		        GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
		        Delay(tempo);
		        GPIO_ToggleBits(GPIOD, GPIO_Pin_14);

		        GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
		        Delay(tempo);
		        GPIO_ToggleBits(GPIOD, GPIO_Pin_15);

		        // Ajusta o tempo de delay para a próxima iteração
		                if (direcao == -1) {
		                    // Desacelerando, aumenta o delay (diminuindo a frequência)
		                	tempo += 100000;
		                    if (tempo >= min) {
		                    	direcao = 1; // Muda para acelerando
		                    }
		                } else {
		                    // Acelerando, diminui o delay (aumentando a frequência)
		                	tempo -= 100000;
		                    if (tempo <= max) {
		                    	direcao = -1; // Muda para desacelerando
		                    }
		                }*/
		        //------------------------------------------------------------------------------------------
		       //quarto exercicio - congela velocidade
		EstadoBTatual = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12); // Lê o estado do botão PB12

		// Verifica se o botão foi pressionado (borda de descida)
		if (EstadoBTatual == 0 && EstadoBTanterior == 1) {
		    congela = !congela; // Alterna o estado de congelamento
		    if (!congela) {
		        // Quando congela é 0 (descongelado), reinicia o tempo de delay para o valor inicial
		        tempo = 5000000;
		        direcao = -1; // Retorna para desaceleração (ritmo normal)
		    }
		}

		EstadoBTanterior = EstadoBTatual; // Atualiza o estado anterior

		// Parte da sequência de piscadas dos LEDs
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		Delay(tempo);
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);

		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
		Delay(tempo);
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);

		GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
		Delay(tempo);
		GPIO_ToggleBits(GPIOD, GPIO_Pin_14);

		GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
		Delay(tempo);
		GPIO_ToggleBits(GPIOD, GPIO_Pin_15);

		// Ajusta o tempo de delay para a próxima iteração, apenas se não estiver congelado
		if (!congela) {
		    if (direcao == -1) {
		        // Desacelerando, aumenta o delay (diminuindo a frequência)
		        tempo += 100000;
		        if (tempo >= min) {
		            direcao = 1; // Muda para acelerando
		        }
		    } else {
		        // Acelerando, diminui o delay (aumentando a frequência)
		        tempo -= 100000;
		        if (tempo <= max) {
		            direcao = -1; // Muda para desacelerando
		        }
		    }
		}

		}

    }


/**
 * @brief  Delay Function.
 * @param  nCount:specifies the Delay time length.
 * @retval None
 */

vu32 var16;

void Delay(__IO uint32_t nCount)
{
	while (nCount--)
	{
	}
}

/**
 * @}
 */

/**
 * @}
 */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
