#include <stdio.h>

#include "struct_module.h"

#if defined(BINDER_SERVICE)

#include "remote_struct_module.h"

int main(int arg, char** argv) {
    return remote_struct_module_service_serv();
}

#elif defined(BINDER_CLIENT)

static void dump(char* prmot,STRUCT_S* p) {
    printf("i=%d j=%d buf=0x%x 0x%x ... 0x%x\n",p->i,p->j,p->buf[0],p->buf[1],p->buf[sizeof(p->buf)-1]);
}

int main(int arg, char** argv) {
    STRUCT_S in;
    STRUCT_S out;
    int ret;

    in.i=0;
    in.j=1;
    memset(&in.buf,2,sizeof(in.buf));

    ret = struct_api_1(&in,&out);
    printf("struct_api_1 ret=%d",ret);
    dump("in",&in);
    dump("out",&out);
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif