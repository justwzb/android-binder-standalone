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
    typeof(in) ret = in;\\
    if(pin!=NULL) ret += *pin;\\
    if(pinout!=NULL) ret += *pinout;\\
    int i;\\
    for(i=0;i<len;i++) {\\
        if(pout!=NULL) *(pout+i) = ret;\\
        if(pinout!=NULL) *(pinout+i) = ret;\\
    }\\
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
outfd.close()
outfd = None

