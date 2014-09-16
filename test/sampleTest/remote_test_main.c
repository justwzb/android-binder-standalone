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
    int out = 0;

    int ret = sample_base_api(in,&out);
    printf("test sample_base_api 1 in=%d,out=%d,ret=%d\n",in,out,ret);

    in = 2;
    ret = sample_base_api(in,NULL);
    printf("test sample_base_api 2 in=%d,out=<null>,ret=%d\n",in,ret);
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif