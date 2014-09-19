/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: %=sidl_filename%
 */

#define LOG_TAG     "%=sidl_basename%"

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>

/*py
for ctx in sidl_context:
    if isinstance(ctx,Include):
        output(ctx.output()+"\n")

import uuid
output('\n\n#define SERVICE_DESCRIPTOR                      "' + str(uuid.uuid1()) + '"')
py*/
#define SERVICE_NAME                            "%=sidl_basename%"

#define FIRST_CALL_TRANSACTION                  (1)
/*py
idx = 0
for ctx in sidl_context:
    if isinstance(ctx,Function):
        idx += 1
        output("#define TRANSACTION_%s FIRST_CALL_TRANSACTION + %d\r\n" % (ctx.getName(),idx))
py*/
using namespace android;

#if defined(BINDER_SERVICE)

#include <stdlib.h>
#include "%=sidl_basename%.h"

class %=sidl_basename%_service : public BBinder  
{  
private:
    static %=sidl_basename%_service* _instance;

    %=sidl_basename%_service(){
        ALOGV(SERVICE_NAME"_service create");
    }
    
    virtual ~%=sidl_basename%_service() {
        ALOGV(SERVICE_NAME"_service destory");
    }

public:  
    static int Instance() {
        if(_instance == NULL) {
            ALOGV(SERVICE_NAME"_service Instance");
            _instance = new %=sidl_basename%_service();
            int ret = defaultServiceManager()->addService(  
                String16(SERVICE_NAME), _instance );  
            ALOGV(SERVICE_NAME"_service ret = %d", ret);  
            return ret;  
        }

        return -1;
    }
    
    virtual status_t onTransact(uint32_t code , const Parcel& data , Parcel* reply, uint32_t flags) {
        ALOGV(SERVICE_NAME"_service - onTransact code=%d",code);

        switch(code)  {
/*py
for ctx in sidl_context:
    if isinstance(ctx,Function):
        output("""
            case TRANSACTION_%(funcname)s:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for %(funcname)s here, will auoto generated but may change yourself if need --
""" % {"funcname":ctx.getName()})

        idx = 1
        for arg in ctx.getArguments():
            #output("==="+str(arg)+"===\n")
            tags = arg.getTags()
            inflag = arg.hasInFlag()
            outflag = arg.hasOutFlag()
            typ = arg.getType()
            isPtr = arg.isPtr()
            star = "*" if isPtr else "" # error here
            qualifier = arg.getQualifier()
            name = arg.getName()
            len = arg.getPtrLen()
            if name == "":
                name = "_arg"+str(idx)
                idx += 1

            if ( 
                "int32" in tags
                or typ == "int"
                or typ == "int32_t"
                ):

                if not isPtr:
                    output("""
                %(qualifier)s%(typ)s %(name)s = data.readInt32();  //int as input paramter
""" % {"qualifier":qualifier,"typ":typ,"name":name})
                else:
                    output("""
                //TODO: use blob
                int _%(name)s_len = data.readInt32(); //read length
                %(typ)s* %(name)s = (%(typ)s*)malloc(sizeof(%(typ)s)*_%(name)s_len);""" % {"qualifier":qualifier,"typ":typ,"name":name})

                    if inflag:
                        output("""
                data.read(%(name)s,sizeof(%(typ)s)*_%(name)s_len)
""")
                    else:
                        output("""
                memset(%(name)s,0,sizeof(%(typ)s)*_%(name)s_len);
""" % {"qualifier":qualifier,"typ":typ,"name":name})
            else:
                pass

        #gen arglist for func call
        calllist = ""
        idx = 1
        for arg in ctx.getArguments():
            name = arg.getName()
            if name == "":
                name = "_arg"+str(idx)
                idx += 1
            calllist += "%s, " % (name)
        calllist = calllist[:-2]

        #return info
        result = ctx.getReturn()
        retTyp = result.getType()
        retIsPtr = result.isPtr()
        retStar = "*" if retIsPtr else ""
        retTags = result.getTags();

        output("""
                %(qualifier)s%(typ)s%(star)s _result = %(name)s_stub( %(calllist)s );
""" % {"qualifier":result.getQualifier(),"typ":retTyp,"name":ctx.getName(),"star":retStar,"calllist":calllist } )

        output("""
                reply->writeNoException(); //fixed check
""")

        if ( 
            "int32" in retTags
            or typ == "int"
            or typ == "int32_t"
            ):
                if not retIsPtr:
                    output("""
                reply->writeInt32(_result); //int as return value
""")
                else:
                    output("""
                #error not support this type of return yet, please add code for '%(name)s' yourself
""" % {"qualifier":result.getQualifier(),"typ":retTyp,"name":ctx.getName(),"star":retStar,"arglist":arglist } )


        idx = 1
        for arg in ctx.getArguments():
            tags = arg.getTags()
            inflag = arg.hasInFlag()
            outflag = arg.hasOutFlag()
            typ = arg.getType()
            isPtr = arg.isPtr()
            star = "*" if isPtr else ""
            qualifier = arg.getQualifier()
            name = arg.getName()
            if name == "":
                name = "_arg"+str(idx)
                idx += 1

            if ( 
                "int32" in tags
                or typ == "int"
                or typ == "int32_t"
                ):
                if isPtr:
                    if outflag:
                        output("""
                //TODO: use blob
                reply->writeInt32Array(_%(name)s_len,%(name)s);""" % {"qualifier":qualifier,"typ":typ,"name":name,"star":star})

                    output("""
                free(%(name)s);
                %(name)s = NULL;
""" % {"qualifier":qualifier,"typ":typ,"name":name,"star":star})

        output("""
                //-- end code for %(funcname)s here --
                return NO_ERROR;
            } break;
            """ % {"funcname":ctx.getName()})
py*/
            default:  
                return BBinder::onTransact(code, data, reply, flags);
        
        }

        ALOGV(SERVICE_NAME"_service end");
    }
}; 

int %=sidl_basename%_service_serv()
{
    sp<ProcessState> proc(ProcessState::self());

    int ret = %=sidl_basename%_service::Instance();
    ALOGV("server - %=sidl_basename%__service::Instance return %d", ret);

    ProcessState::self()->startThreadPool();
    ALOGV("server -> enter loop ...");
    IPCThreadState::self()->joinThreadPool();
    ALOGV("server -> return");
    return 0;
}

int %=sidl_basename%_service_add() {
    %=sidl_basename%_service::Instance();
}

#elif defined(BINDER_CLIENT)

class %=sidl_basename%_client  
{  
private:
    static %=sidl_basename%_client* _instance;
    sp<IBinder> _binder;

    %=sidl_basename%_client() {
        ALOGV(SERVICE_NAME"_client create\n");
        sp<IServiceManager> sm = defaultServiceManager();
        _binder = sm->getService(String16(SERVICE_NAME));
    }
    
    virtual ~%=sidl_basename%_client() {
        ALOGV(SERVICE_NAME"_client destory\n");
    }

public:  
    static %=sidl_basename%_client* Instance() {
        if(_instance == NULL) {
            ALOGE(SERVICE_NAME"_client Instance");
            _instance = new %=sidl_basename%_client();
        }

        return _instance;
    }
/*py

for ctx in sidl_context:
    if isinstance(ctx,Function):
        arglist = ""
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

        #return info
        result = ctx.getReturn()
        retQualifier = result.getQualifier()
        retTyp = result.getType()
        retIsPtr = result.isPtr()
        retStar = "*" if retIsPtr else ""
        retTags = result.getTags();

        output("""
    %(qualifier)s%(typ)s%(star)s %(name)s( %(arglist)s ) {
        Parcel data, reply;

        /*-- add you code for %(name)s here --*/
        %(qualifier)s%(typ)s%(star)s _result;
        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check
""" % {"qualifier":retQualifier ,"typ":retTyp,"name":ctx.getName(),"star":retStar,"arglist":arglist } )

        idx = 1
        for arg in ctx.getArguments():
            tags = arg.getTags()
            inflag = arg.hasInFlag()
            outflag = arg.hasOutFlag()
            typ = arg.getType()
            isPtr = arg.isPtr()
            star = "*" if isPtr else ""
            qualifier = arg.getQualifier()
            len = arg.getPtrLen()
            name = arg.getName()
            if name == "":
                name = "_arg"+str(idx)
                idx += 1

            if (
                "int32" in tags
                or typ == "int"
                or typ == "int32_t"
                ):

                if not isPtr:
                    output("""
            data.writeInt32(%(name)s);  //int as input paramter
""" % {"qualifier":qualifier,"typ":typ,"name":name})
                elif inflag:
                    #TODO: use blob
                    output("""
            data.writeInt32Array(%(len)s, %(name)s);  //int%(star)s as input paramter
""" % {"qualifier":qualifier,"typ":typ,"name":name,"star":star,"len":len})
                else:
                    output("""
            if ( %(name)s == NULL ) {
                data.writeInt32(-1);
            }
            else {
                data.writeInt32(%(len)s);
            }
""" % {"qualifier":qualifier,"typ":typ,"name":name,"star":star,"len":len})


        output("""
            _binder->transact(TRANSACTION_%s,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check
""" % (ctx.getName()))

        if ( 
            "int32" in retTags
            or retTyp == "int"
            or retTyp == "int32_t"
            ):
            if not retIsPtr:
                output("""
                _result = reply.readInt32();//int as return value
""")
            else:
                output("""
                #error not support generate code for int* return, please add code yourself
""")

        #output paramters
        idx = 1
        for arg in ctx.getArguments():
            tags = arg.getTags()
            inflag = arg.hasInFlag()
            outflag = arg.hasOutFlag()
            typ = arg.getType()
            isPtr = arg.isPtr()
            star = "*" if isPtr else ""
            qualifier = arg.getQualifier()
            len = arg.getPtrLen()
            name = arg.getName()
            if name == "":
                name = "_arg"+str(idx)
                idx += 1   

            if (
                "int32" in tags
                or typ == "int"
                or typ == "int32_t"
                ):
                if not isPtr:
                    pass
                elif outflag:
                    output("""
                reply.readInt32Array(%(len)s,%(name)s); //TODO need add this api
"""  % {"qualifier":qualifier,"typ":typ,"name":name,"star":star,"len":len} )

        output("""
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client sample_base_api error");
        }

        return _result;
        /*-- add you code for sample_base_api here --*/
    }
};
""")

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

            calllist += "%s, " % (name)
            arglist += "%(qualifier)s%(typ)s%(star)s %(name)s, " % {"qualifier":qualifier,"typ":typ,"name":name,"star":star}
        arglist = arglist[:-2]
        calllist = calllist[:-2]

        #return info
        result = ctx.getReturn()
        retQualifier = result.getQualifier()
        retTyp = result.getType()
        retIsPtr = result.isPtr()
        retStar = "*" if retIsPtr else ""
        retTags = result.getTags();

        output("""
%(qualifier)s%(typ)s%(star)s %(name)s( %(arglist)s ) {
    return %=sidl_basename%_client*::Instance->%(name)s(%(calllist)s);
}""" % {"qualifier":retQualifier,"typ":retTyp,"name":ctx.getName(),"star":retStar,"arglist":arglist, "calllist":calllist} )

py*/

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif
