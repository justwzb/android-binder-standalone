import os,sys

types = (
    "int",
    "int32_t",
    "unsigned int",
    "uint32_t",
    "short",
    "short int",
    "int16_t",
    "unsigned short",
    "unsigned short int",
    "uint16_t",
    "char",
    "int8_t",
    "unsigned char",
    "uint8_t",
    "long long",
    "int64_t",
    "unsigned long long",
    "uint64_t",
    )

outfd = open("sample_module.h","wb")
outfd.write("""\
#ifndef __SAMPLE_MODULE_H__
#define __SAMPLE_MODULE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
""")

for typ in types:
    tt = typ.replace(" ","_")
    outfd.write("""
%(typ)s sample_%(tt)s_prt_1(%(typ)s in,%(typ)s* pin,%(typ)s* pout,%(typ)s* pinout);
%(typ)s sample_%(tt)s_prt_len(%(typ)s in,%(typ)s* pin,%(typ)s* pout,%(typ)s* pinout,%(typ)s len);
""" % {"typ":typ,"tt":tt} )

outfd.write("""
void sample_void_oneshot(void);

void sample_cstring(const char* str);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
""")
outfd.close()
outfd = None



outfd = open("sample_module.c","wb")
outfd.write("""\
#include "sample_module.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SAMPLE_PTR(type,in,pin,pout,pinout,len)   {\\
    printf("%s:in=%d ",__FUNCTION__,(int)in);\\
    typeof(in) ret = in;\\
    if(pin!=NULL) {ret += *pin; printf("pin[0]=%d ",(int)pin[0]);}\\
    if(pinout!=NULL) {ret += *pinout; printf("pinout[0]=%d ",(int)pinout[0]);}\\
    printf("=\\n");\\
    int i;\\
    for(i=0;i<len;i++) {\\
        printf(".ret1=%d\\n",(int)ret);\\
        if(pout!=NULL) *(pout+i) = ret;\\
        printf(".ret2=%d\\n",(int)ret);\\
        if(pinout!=NULL) *(pinout+i) = ret;\\
    }\\
    printf("\\nret=%d len=%d\\n",(int)ret,sizeof(ret));\\
    return ret;}\\

""")

for typ in types:
    tt = typ.replace(" ","_")
    outfd.write("""
%(typ)s sample_%(tt)s_prt_1(%(typ)s in,%(typ)s* pin,%(typ)s* pout,%(typ)s* pinout) {
    SAMPLE_PTR(%(typ)s,in,pin,pout,pinout,1)
}
%(typ)s sample_%(tt)s_prt_len(%(typ)s in,%(typ)s* pin,%(typ)s* pout,%(typ)s* pinout,%(typ)s len) {
    SAMPLE_PTR(%(typ)s,in,pin,pout,pinout,len)
}
""" % {"typ":typ,"tt":tt} )

outfd.write("""
void sample_void_oneshot(void) {
    printf("sample_void_oneshot");
}

void sample_cstring(const char* str) {
    printf("sample_cstring[%s]\\n",str);
}
""")
outfd.close()
outfd = None



outfd = open("remote_sample_module.sidl","wb")
outfd.write("""\
#include "sample_module.h"

//{oneway}RetType{typedes} function_name(ParamType{typedes} ParamName,ParamType*{typedes}{inout}{len:length} ParamName)
""")


for typ in types:
    tt = typ.replace(" ","_")
    outfd.write("""
%(typ)s sample_%(tt)s_prt_1(%(typ)s in,%(typ)s{in}{len:1}* pin,%(typ)s{out}{len:1}* pout,%(typ)s{inout}{len:1}* pinout);
%(typ)s sample_%(tt)s_prt_len(%(typ)s in,%(typ)s{in}{len:len}* pin,%(typ)s{out}{len:len}* pout,%(typ)s{inout}{len:len}* pinout,%(typ)s len);
""" % {"typ":typ,"tt":tt} )

outfd.write("""
{oneway}void sample_void_oneshot(void);

void sample_cstring(const char*{in}{len:(strlen(str)+1)} str);

""")

outfd.close()
outfd = None

