# PlaneLights
LED light control for scale models with [STM32F103(aka bluepill)](https://www.google.com/search?q=stm32f103%20blue%20pill&sxsrf=ACYBGNRSP6mU8k8uJItMLN4o1QfBQV-gVw:1581764239331&tbm=isch&source=iu&ictx=1&fir=620Ic6sRwhuLFM%253A%252C0t7gj5vYG7ezPM%252C_&vet=1&usg=AI4_-kSa3hg2I-jlwu04PseySnm7-Sbzgw&sa=X&ved=2ahUKEwjD6un8stPnAhUKSBUIHXqpBTwQ9QEwA3oECAkQCg#imgrc=620Ic6sRwhuLFM:)

Control your scaled model lights using PWM signals from small microcontroller.

It's recomendded to add a transistor(BJT or MosFET) to drive the landing lights
if the current from the MCU is more than 10mA, otherwise you could damage the MCU.

Wiring information:
Logo Lights -> PB9
Strobe Lights -> PA6
Beacon Lights -> PA7
Navigation Lights -> PB8
Landing Lights Left -> PB7
Landing Lights Right -> PB6

