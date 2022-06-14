#include <avr/io.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */
#include <avr/pgmspace.h>   /* required by usbdrv.h */

#include "peri.h"
#include "usbdrv.h"

#define RQ_GET_SOUND       0
#define RQ_DETECT_SOUND	   1

/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */
usbMsgLen_t usbFunctionSetup(uint8_t data[8])
{
    usbRequest_t *rq = (void *)data;

    static uint16_t sound_value;  
	static uint8_t led_status;

    if (rq->bRequest == RQ_GET_SOUND)
    {
        sound_value = read_adc(PC0);
        usbMsgPtr = (uchar*) &sound_value;
        return sizeof(sound_value);
    }
	else if (rq->bRequest == RQ_DETECT_SOUND)
	{
		led_status = SOUND_DETECTED();

		usbMsgPtr = &led_status;

		return 1;
	}


    return 0;
}

/* ------------------------------------------------------------------------- */

int main(void)
{
    init_peri();

    usbInit();

    usbDeviceDisconnect();
    _delay_ms(300);
    usbDeviceConnect();

    sei();

    for(;;)
    {
        usbPoll();

		int val = read_adc(PC0);
		if (val > 100) {
			set_led(1,1);
		}
		else {
			set_led(1,0);
		}
    }

    return 0;
}
