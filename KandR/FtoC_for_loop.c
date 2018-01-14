/**
 * File              : FtoC_for_loop.c
 * Author            : John Gentile <johncgentile17@gmail.com>
 * Date              : 06.12.2017
 * Last Modified Date: 03.01.2018
 * Last Modified By  : John Gentile <johncgentile17@gmail.com>
 */
#include <stdio.h>

/* print Fahrenheit-Celsius table */
main ()
{
        int fahr;

        for (fahr = 0; fahr <= 300; fahr = fahr + 20)
                printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32.0));
}
