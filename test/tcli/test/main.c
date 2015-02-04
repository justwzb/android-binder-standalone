#include "tos_tcli.h"
#include <stdio.h>

static void run_my_cmd(int i,char* s) {
    tos_tcli_printf("i=%d\n",i);
    tos_tcli_printf("s=%s\n",s);
}
TOS_TCLI_COMMAND(mycmd,"my command","long help\n of my command\n","is",run_my_cmd);


static void my_output(const char* prompt,void* userdata) {
    printf("[CLI]%s",prompt);
}

int main(int argc,char* argv[]) {
    printf("-----------\n");
    tos_tcli_executeByargs(argc-1,argv+1,my_output,NULL);
    printf("-----------\n");
}