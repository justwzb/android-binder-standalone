#include <stdio.h>
#include <sbinder/sbinderServ.h>

#if defined(BINDER_SERVICE)

#include "remote_callback_module.h"
#include "service_manager.h"

int main(int arg, char** argv) {
	ServiceManager_start();
    remote_callback_module_service_add();
    return sbinder_serv();
}

#elif defined(BINDER_CLIENT)
#include "callback_module.h"

static int _cb_callback(int param) {
    printf("%s param=%d\n",__FUNCTION__,param);
    return 0;
}

static int _cb_callback1(int param) {
    printf("%s param=%d\n",__FUNCTION__,param);
    return 1;
}

int main(int arg, char** argv) {

    sbinder_start();

    int ret;

    ret = cb_add(_cb_callback);
    printf("ret = %d\n",ret);

    ret = cb_add(_cb_callback1);
    printf("ret = %d\n",ret);

    ret = cb_invoke(10);
    printf("ret = %d\n",ret);

    sleep(5);

    ret = cb_invoke(11);
    printf("ret = %d\n",ret);

    sleep(5);

    ret = cb_remove(_cb_callback1);
    printf("ret = %d\n",ret);

    ret = cb_invoke(12);
    printf("ret = %d\n",ret);
    
    return sbinder_serv();
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif
