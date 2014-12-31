#include <stdio.h>
#include <string.h>

#include "struct_module.h"
#include "service_manager.h"

#if defined(BINDER_SERVICE)

#include "remote_struct_module.h"
#include "remote_upstruct_module.h"

int main(int arg, char** argv) {
    ServiceManager_start();
    remote_struct_module_service_add();
    remote_upstruct_module_service_add();
    return sbinder_serv();
}

#elif defined(BINDER_CLIENT)

static void dump(char* prmot,STRUCT_S* p) {
    printf("[%s]i=%d j=%d buf=0x%x 0x%x ... 0x%x\n",prmot,p->i,p->j,p->buf[0],p->buf[1],p->buf[sizeof(p->buf)-1]);
}

static void dump1(char* prmot,STRUCT_UNFLAT_S* p) {
    printf("[%s]i=%d j=%d len=%d\n",prmot,p->i,p->j,p->len);

    if(p->buf != NULL) {
        printf("buf=0x%x 0x%x ... 0x%x",p->buf[0],p->buf[1],p->buf[sizeof(p->buf)-1]);
    }
    else {
        printf("NULL");
    }
}

static void testStruct(void) {
    STRUCT_S in;
    STRUCT_S out;
    int ret;

    in.i=0;
    in.j=1;
    memset(&(in.buf),2,sizeof(in.buf));

    ret = struct_api_1(&in,&out);
    printf("c struct_api_1 ret=%d",ret);
    dump("in",&in);
    dump("out",&out);

    ret = struct_api_l(&in,&out,1);
    printf("c struct_api_l ret=%d",ret);
    dump("in",&in);
    dump("out",&out);
}

static void testEnum(void) {
    ENUM_EM in = EM_1;
    ENUM_EM pin = EM_2;
    ENUM_EM pout = EM_MAX;

    ENUM_EM ret;
    ret = enum_api_1(in,&pin,&pout);
    printf("c enum_api_1 ret=%d %d %d %d",ret,in,pin,pout);


    ret = enum_api_l(in,&pin,&pout,1);
    printf("c enum_api_l ret=%d %d %d %d",ret,in,pin,pout);
}

static void testupStruct() {
    char inbuf[]="abcdefghij";
    STRUCT_UNFLAT_S pin;
    pin.i = 1;
    pin.j = 2;
    pin.len = sizeof(inbuf);
    pin.buf = inbuf;

    STRUCT_UNFLAT_S pout;
    memset(&pout,0,sizeof(pout));

    int ret = unflag_struct_api(&pin,&pout);
    printf("c unflag_struct_api");
    dump1("pin",&pin);
    dump1("pout",&pout);
}

int main(int arg, char** argv) {
    sbinder_start();

    testStruct();
    testEnum();
    testupStruct();

    return sbinder_serv(); 
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif