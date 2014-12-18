#include "callback_module.h"

#include <stdio.h>
#include <pthread.h>
#include <utils/Log.h>
#include <utils/Mutex.h>

using namespace android;

static Mutex s_mutex("cbmm");
static int s_param = -1;
static int s_first = 1;
static cb_callback s_cbs[16];

static void _do_invoke() {
    Mutex::Autolock _l(s_mutex);

    ALOGE("_do_invoke s_param = %d",s_param);
    int size = sizeof(s_cbs)/sizeof(s_cbs[0]);
    for(int i=0;i<size;i++) {
        if(s_cbs[i] != NULL) {
            int ret = s_cbs[i](s_param);
            ALOGE("ret %d = %d",i,ret);
        }
    }

    s_param = -1;
}

static void* _thread(void* arg) {

    while(true) {
        sleep(1);

        if(s_param != -1) {
            _do_invoke();
        }
    }

    return NULL;
}

int cb_invoke(int p) {
    Mutex::Autolock _l(s_mutex);

    s_param = p;
    ALOGE("%s p = %d",__FUNCTION__,p);
}

int cb_add(cb_callback cb) {
    if(cb == NULL) {
        return -1;
    }

    Mutex::Autolock _l(s_mutex);

    if(s_first) {
        s_first = 0;

        memset(s_cbs,0,sizeof(s_cbs));

        pthread_t t;
        pthread_create(&t,NULL,_thread,NULL);
    }

    int size = sizeof(s_cbs)/sizeof(s_cbs[0]);
    for(int i=0;i<size;i++) {
        if(s_cbs[i] == NULL) {
            s_cbs[i] = cb;
            return 0;
        }
    }

    return -2;
}

int cb_remove(cb_callback cb) {
    if(cb == NULL) {
        return -1;
    }

    Mutex::Autolock _l(s_mutex);

    int size = sizeof(s_cbs)/sizeof(s_cbs[0]);
    for(int i=0;i<size;i++) {
        if(s_cbs[i] == cb) {
            s_cbs[i] = NULL;
            return 0;
        }
    }

    return -2;
}


