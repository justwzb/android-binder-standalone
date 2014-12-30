#include <stdio.h>

#include "sample_module.h"
#include "service_manager.h"

#if defined(BINDER_SERVICE)

#include "remote_sample_module.h"

int main(int arg, char** argv) {
	ServiceManager_start();
    remote_sample_module_service_add();
    return sbinder_serv();
}

#elif defined(BINDER_CLIENT)

static void testint1(void) {
    int in = 1;
    int pin = 2;
    int pout = 3;
    int pinout = 4;

    int ret = sample_int_prt_1(in,&pin,&pout,&pinout);
    printf("test sample_int_prt_1 in=%d,pin=%d,pout=%d,pinout=%d,ret=%d\n",in,pin,pout,pinout,ret);
}

static void testint16l(void) {

	uint16_t in = 1;
	uint16_t pin[2] = {2,3};
	uint16_t pout[2] = {4,5};
	uint16_t pinout[2] = {5,6};
	
	uint16_t ret = sample_uint16_t_prt_len(in,pin,pout,pinout,2);
	
	printf("test sample_uint16_t_prt_len in=%d,pin=%d,%d,pout=%d,%d,pinout=%d,%d ret=%d\n",in,pin[0],pin[1],pout[0],pout[1],pinout[0],pinout[1],ret);
	
}

int main(int arg, char** argv) {
    sbinder_start();

	testint1();
	//testint16l();

    return sbinder_serv(); 
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif