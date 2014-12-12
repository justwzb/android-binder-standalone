#include <stdio.h>

#include "struct_module.h"

#if defined(BINDER_SERVICE)

#include "remote_struct_module.h"
#include "remote_upstruct_module.h"

int main(int arg, char** argv) {
    remote_upstruct_module_service_add();
    return remote_struct_module_service_serv();
}

#elif defined(BINDER_CLIENT)

static void dump(char* prmot,STRUCT_S* p) {
    printf("i=%d j=%d buf=0x%x 0x%x ... 0x%x\n",p->i,p->j,p->buf[0],p->buf[1],p->buf[sizeof(p->buf)-1]);
}

static void testStruct(void) {
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

    ret = struct_api_l(&in,&out,1);
    printf("struct_api_l ret=%d",ret);
    dump("in",&in);
    dump("out",&out);
}

static void testEnum(void) {
    ENUM_EM in = EM_1;
    ENUM_EM pin = EM_2;
    ENUM_EM pout = EM_MAX;

    ENUM_EM ret;
    ret = enum_api_1(in,&pin,&pout);
    printf("enum_api_1 ret=%d %d %d %d",ret,in,pin,pout);


    ret = enum_api_l(in,&pin,&pout,1);
    printf("enum_api_l ret=%d %d %d %d",ret,in,pin,pout);
}

int main(int arg, char** argv) {
    testStruct();
    testEnum();
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif