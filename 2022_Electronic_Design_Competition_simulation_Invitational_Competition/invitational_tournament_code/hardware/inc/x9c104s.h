#include "sysinit.h"

void x9c104s_init(void);

#define C_S(n)     (n?GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5):GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN5))
#define INC(n)     (n?GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN6):GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6))
#define U_D(n)     (n?GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN7):GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN7))

