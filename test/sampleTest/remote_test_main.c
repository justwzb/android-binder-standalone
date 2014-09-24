#include <stdio.h>

#include "sample_module.h"

#if defined(BINDER_SERVICE)

#include "remote_sample_module.h"

int main(int arg, char** argv) {
    return remote_sample_module_service_init();
}

#elif defined(BINDER_CLIENT)

int main(int arg, char** argv) {

    int in = 1;
    int pin = 2;
    int pout = 3;
    int pinout = 4;

    int ret = sample_int_prt_1(in,&pin,&pout,&pinout);
    printf("test sample_int_prt_1 in=%d,pin=%d,pout=%d,pinout=%d,ret=%d\n",in,pin,pout,pinout,ret);
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif