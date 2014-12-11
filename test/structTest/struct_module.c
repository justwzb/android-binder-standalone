#include "struct_module.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int struct_api_1(STRUCT_S* pin,STRUCT_S* pout) {
    if(pin != NULL && pout != NULL) {

        pout->i = pin->i+1;
        pout->j = pin->j+1;

        memset(pout->buf,pin->i+pin->j,sizeof(pout->buf));
        return 0;
    }

    return -1;
}

int struct_api_l(STRUCT_S* pin,STRUCT_S* pout,int len) {
    int i;
    int ret = 0;
    for(i=0;i<len;i++) {
        ret += struct_api_1(&pin[i],&pout[i]);
    }

    return ret;
}