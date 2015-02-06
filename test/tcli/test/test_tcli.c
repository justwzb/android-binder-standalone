#include "tos_tcli.h"
#include <stdio.h>
#include <string.h>

#if defined(BINDER_SERVICE)

#include <sbinder/sbinderServ.h>
#include "service_manager.h"

static void run_my_cmd(int i,char* s) {
    tos_tcli_printf("i=%d\n",i);
    tos_tcli_printf("s=%s\n",s);
}
TOS_TCLI_COMMAND(mycmd,"my command","long help\n of my command\n","is",run_my_cmd);

static int s_myvalue = 0;
TOS_TCLI_INTERGER(s_myvalue,"short help of s_currentValue","long help\nof s_currentValue");

int main(int arg, char** argv) {
    ServiceManager_start();
    remote_tos_tcli_service_add();
    return sbinder_serv();
}

#elif defined(BINDER_CLIENT)

static void my_output(const char* prompt,void* userdata) {
    printf("%s",prompt);
}


static int _endwith(const char *str, const char *substr) {
    int nsub_len = strlen (substr);
    int nlen = strlen (str);

    if (nsub_len > nlen)
    {
        return 0;
    }

    if (memcmp (str + nlen - nsub_len, substr, nsub_len) == 0)
    {
        return 1;
    }
    return 0;
}

int main(int argc,char* argv[]) {
    if(_endwith(argv[0],"/tcli") || strcmp(argv[0],"tcli") == 0) {
        return tos_tcli_executeByargs(argc-1,(const char**)argv+1,my_output,NULL);
    }
    else {
        return tos_tcli_executeByargs(argc,(const char**)argv,my_output,NULL);
    }
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif
