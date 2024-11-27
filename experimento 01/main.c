#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"

void IOToggle(void);

int main(void)
{

	SystemInit();

	IOToggle();

	while(1)
    {
    }
}

