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
#include <pthread.h>

static int _cb_callback(int param) {
	
    printf("%s callback sleep start param=%d\n",__FUNCTION__,param);
	sleep(20);
	printf("%s callback sleep overt param=%d\n",__FUNCTION__,param);
    return 0;
}

static int _cb_callback1(int param) {
    printf("%s param=%d\n",__FUNCTION__,param);
    return 1;
}


void* _thread(void* arg) {

	printf("%s arg = %d\n",__FUNCTION__,(int)arg);
	int ret = cb_invoke2((int)arg);

    return NULL;
}


void startThread(int num){
	pthread_t t;
	pthread_create(&t,NULL,_thread,(void*)num);

}

int main(int arg, char** argv) {

    sbinder_start();

    int ret;

    ret = cb_add(_cb_callback);
    printf("main 1ret = %d\n",ret);

    ret = cb_add(_cb_callback1);
    printf("main 2ret = %d\n",ret);

    ret = cb_invoke(10);
    printf("main 3ret = %d\n",ret);

    sleep(5);

    ret = cb_invoke(11);
    printf("main 4ret = %d\n",ret);

    sleep(5);

    ret = cb_remove(_cb_callback1);
    printf("main 5ret = %d\n",ret);


	startThread(13);
    printf("main 6ret = %d\n",ret);
	startThread(14);
    printf("main 7ret = %d\n",ret);
	startThread(15);
    printf("main 8ret = %d\n",ret);
	startThread(16);
    printf("main 9ret = %d\n",ret);
	startThread(17);
    printf("main 10ret = %d\n",ret);

    ret = cb_invoke(12);
    printf("main 11ret = %d\n",ret);

    return sbinder_serv();
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif
