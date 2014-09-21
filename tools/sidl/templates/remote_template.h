/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: %=sidl_filename%
 */

#ifndef __%=sidl_basename%_h__
#define __%=sidl_basename%_h__

#if defined(BINDER_SERVICE)

 /*py
for ctx in sidl_context:
    if isinstance(ctx,Include):
        output(ctx.output()+"\n")
py*/

///< call this api loop for ever and star service
int %=sidl_basename%_service_serv();

///< call this api to only add this service
int %=sidl_basename%_service_add();

//--------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/*py
for ctx in sidl_context:
    if isinstance(ctx,Function):
        arglist = ""
        calllist = ""
        idx = 1
        for arg in ctx.getArguments():
            qualifier = arg.getQualifier()
            typ = arg.getType()
            isPtr = arg.isPtr()
            star = "*" if isPtr else ""
            name = arg.getName()
            if name == "":
                name = "_arg"+str(idx)
                idx += 1

            arglist += "%(qualifier)s%(typ)s%(star)s %(name)s, " % {"qualifier":qualifier,"typ":typ,"name":name,"star":star}
        arglist = arglist[:-2]
        calllist = calllist[:-2]

        if arglist == "":
            calllist = arglist = "void"

        #return info
        result = ctx.getReturn()
        retQualifier = result.getQualifier()
        retTyp = result.getType()
        retIsPtr = result.isPtr()
        retStar = "*" if retIsPtr else ""
        retTags = result.getTags();

        output("""
///<implent this api to call real function on service
%(qualifier)s%(typ)s%(star)s %(name)s_stub( %(arglist)s );
""" % {"qualifier":retQualifier,"typ":retTyp,"name":ctx.getName(),"star":retStar,"arglist":arglist, "calllist":calllist} )

py*/

#ifdef __cplusplus
}
#endif

#elif defined(BINDER_CLIENT)
 #error This file is only used on server
#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif

#endif