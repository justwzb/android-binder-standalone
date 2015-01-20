#include "struct_module.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void dump(char* prmot,STRUCT_S* p) {
    printf("i=%d j=%d buf=0x%x 0x%x ... 0x%x\n",p->i,p->j,p->buf[0],p->buf[1],p->buf[sizeof(p->buf)-1]);
}

int struct_api_1(STRUCT_S* pin,STRUCT_S* pout) {
    printf("struct_api_1\n");
    if(pin != NULL && pout != NULL) {

        dump("pin",pin);

        pout->i = pin->i+1;
        pout->j = pin->j+1;
        memset(pout->buf,pin->i+pin->j,sizeof(pout->buf));


        dump("pout",pout);
        return 0;
    }

    return -1;
}

int struct_api_l(STRUCT_S* pin,STRUCT_S* pout,int len) {
    printf("struct_api_l = %d\n",len);
    int i;
    int ret = 0;
    for(i=0;i<len;i++) {
        ret += struct_api_1(&pin[i],&pout[i]);
    }

    return ret;
}

ENUM_EM enum_api_1(ENUM_EM in,ENUM_EM* pin,ENUM_EM* pout){
    printf("enum_api_1\n");
    if(pin != NULL && pout != NULL) {
        *pout = in;
        printf("%d %d %d\n",in,*pin,*pout);
        return *pin;
    }

    return in;
}

ENUM_EM enum_api_l(ENUM_EM in,ENUM_EM* pin,ENUM_EM* pout,int len){
    printf("struct_api_l = %d\n",len);
    int i;
    int ret;
    for(i=0;i<len;i++) {
        ret = enum_api_1(in,&pin[i],&pout[i]);
    }

    return ret;
}

static char s_buf[8];
int unflag_struct_api(STRUCT_UNFLAT_S* pin,STRUCT_UNFLAT_S* pout) {
    printf("unflag_struct_api\n");
    if(pin != NULL && pout != NULL) {
        printf("%d %d %d \n",pin->i,pin->j,pin->len);

        int i;
        for(i=0;i<pin->len;i++) {
            printf("%s ",pin->buf);
        }
        printf("\n");

        pout->i=1;
        pout->j=2;
        pout->len=sizeof(s_buf);
        pout->buf = s_buf;
    }

    return 0;
}


