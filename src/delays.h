#ifndef DELAYS_H
#define	DELAYS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define OSC_FREQ    200000000U
#define US_COUNT    ((OSC_FREQ / 2U) / 1000000U)
#define MS_COUNT    ((OSC_FREQ / 2U) / 1000)

    void delay_us(unsigned int us);
    void delay_ms(unsigned int ms);


#ifdef	__cplusplus
}
#endif

#endif	/* DELAYS_H */

