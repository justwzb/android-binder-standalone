/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: %=sidl_filename%
 */
 /*py
s_type_map = {
    "int"                   : "Int32",
    "int32_t"               : "Int32",
    "unsigned int"          : "Int32",
    "uint32_t"              : "Int32",
    "short"                 : "Int32",
    "short int"             : "Int32",
    "int16_t"               : "Int32",
    "unsigned short"        : "Int32",
    "unsigned short int"    : "Int32",
    "uint16_t"              : "Int32",
    "char"                  : "Int32",
    "int8_t"                : "Int32",
    "unsigned char"         : "Int32",
    "uint8_t"               : "Int32",
    "long long"             : "Int64",
    "int64_t"               : "Int64",
    "unsigned long long"    : "Int64",
    "uint64_t"              : "Int64",
}
def get_parcelType(typ,tags):
    #print("typ="+typ)
    #print("tags="+str(tags))

    global s_type_map
    if s_type_map.has_key(typ):
        return s_type_map[typ]

    if "int32" in tags:
        return "Int32"
    elif "int64" in tags:
        return "Int64"
    else:
        return None
py*/

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

            if get_parcelType(typ,tags) != None:
                parcelType = get_parcelType(typ,tags);

                if not isPtr:
                    output("""
                %(qualifier)s%(typ)s %(name)s = (%(qualifier)s%(typ)s)data.read%(parcelType)s();  //%(typ)s as input paramter
""" % {"qualifier":qualifier,"typ":typ,"name":name,"parcelType":parcelType})
                else:
                    output("""
                int _%(name)s_len = data.readInt32(); //read length, only 32bits length support yet
                %(qualifier)s%(typ)s* %(name)s = NULL;
                if(_%(name)s_len > 0) {
                    Parcel::ReadableBlob _%(name)s_rblob;
                    data.readBlob(_%(name)s_len,&_%(name)s_rblob);
                    %(name)s = %(qualifier)s(%(typ)s*)_%(name)s_rblob.data();//Fixme: this data can not write, add api in Parcel
                }
""" % {"qualifier":qualifier,"typ":typ,"name":name})
            else:
                output("""
                #error not support this type of paramter %(qualifier)s%(typ)s %(name)s yet, please add code yourself
""" % {"qualifier":qualifier,"typ":typ,"name":name,"parcelType":parcelType})

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
        oneway = "oneway" in retTags

        if retTyp == "void":
            output("""
                %(name)s_stub( %(calllist)s );
""" % {"qualifier":result.getQualifier(),"typ":retTyp,"name":ctx.getName(),"star":retStar,"calllist":calllist } )
        else:
            output("""
                %(qualifier)s%(typ)s%(star)s _result = %(name)s_stub( %(calllist)s );
""" % {"qualifier":result.getQualifier(),"typ":retTyp,"name":ctx.getName(),"star":retStar,"calllist":calllist } )

        if not oneway:
            output("""
                reply->writeNoException(); //fixed check
""")

            if get_parcelType(retTyp,retTags) != None:
                retParcelType = get_parcelType(retTyp,retTags);

                if not retIsPtr:
                    output("""
                reply->write%(parcelType)s(_result); //%(typ)s as return value
""" % { "parcelType":retParcelType,"typ":retTyp} )
                else:
                    output("""
                #error not support this type of return yet, please add code for '%(name)s' yourself
""" % {"qualifier":result.getQualifier(),"typ":retTyp,"name":ctx.getName(),"star":retStar,"arglist":arglist } )
            elif retTyp == "void":
                pass
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


                if isPtr and outflag:
                    if get_parcelType(typ,tags) != None:
                        parcelType = get_parcelType(typ,tags);
                        output("""
                if(_%(name)s_len > 0) {
                    reply->writeInt32(_%(name)s_len);
                    Parcel::WritableBlob _%(name)s_wblob;
                    reply->writeBlob(_%(name)s_len,&_%(name)s_wblob);
                    memcpy(_%(name)s_wblob.data(),%(name)s,_%(name)s_len);
                }
""" % {"qualifier":qualifier,"typ":typ,"name":name,"star":star})
                    else:
                        output("""
                #error not support output paramter %(typ)s %(name)s yet, please add code for '%(name)s' yourself
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

%=sidl_basename%_service* %=sidl_basename%_service::_instance = NULL;

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
        oneway = "oneway" in retTags
        binderFlag = "IBinder::FLAG_ONEWAY" if oneway else "0"

        output("""
    %(qualifier)s%(typ)s%(star)s %(name)s( %(arglist)s ) {
        Parcel data, reply;

        /*-- add you code for %(name)s here --*/\
""" % {"qualifier":retQualifier ,"typ":retTyp,"name":ctx.getName(),"star":retStar,"arglist":arglist } )

        if retTyp != "void":
            output("""
        %(qualifier)s%(typ)s%(star)s _result;\
""" % {"qualifier":retQualifier ,"typ":retTyp,"name":ctx.getName(),"star":retStar,"arglist":arglist } )

        output("""
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

            if get_parcelType(typ,tags) != None:
                parcelType = get_parcelType(typ,tags);

                if not isPtr:
                    output("""
            data.write%(parcelType)s(%(name)s);  //%(typ)s as input paramter
""" % {"qualifier":qualifier,"typ":typ,"name":name,"parcelType":parcelType})
                else:
                    output("""
            //for out only, alloc buffer without copy; for in, alloc and copy
            if (%(name)s == NULL) {
                data.writeInt32(-1);
            }
            else {
                data.writeInt32((int)%(len)s * sizeof(%(typ)s));//write length, only support 32 bits length yet
                Parcel::WritableBlob _%(name)s_wblob;
                data.writeBlob(%(len)s,&_%(name)s_wblob);""" % {"qualifier":qualifier,"typ":typ,"name":name,"star":star,"len":len})
                    if inflag:
                        output("""
                memcpy(_%(name)s_wblob.data(),%(name)s,%(len)s* sizeof(%(typ)s));
            }
""" % {"qualifier":qualifier,"typ":typ,"name":name,"star":star,"len":len})
                    else:
                        output("""
            }
""")
            else:
                output("""
            #error not support this type of paramter %(qualifier)s%(typ)s %(name)s yet, please add code yourself
""" % {"qualifier":qualifier,"typ":typ,"name":name,"star":star,"len":len})


        output("""
            _binder->transact(TRANSACTION_%s,data, &reply,%s);
""" % (ctx.getName(),binderFlag))

        if not oneway:
            output("""
            if(reply.readExceptionCode() == 0) {//fix check
""")
            if retTyp != "void":
                pass
            elif get_parcelType(retTyp,retTags) != None:
                retParcelType = get_parcelType(typ,tags);
                if not retIsPtr:
                    output("""
                _result = reply.read%(parcelType)s();//int as return value
""" % {"parcelType":retParcelType})
                else:
                    output("""
                #error not support generate code for int* return, please add code yourself
""")
            else:
                output(""" #error not support this type of return yet, please add code for '%(name)s' yourself
""" % {"qualifier":result.getQualifier(),"typ":retTyp,"name":ctx.getName(),"star":retStar,"arglist":arglist } )

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

                if isPtr and outflag:
                    if get_parcelType(typ,tags) != None:
                        parcelType = get_parcelType(typ,tags);
                        output("""
                if (%(name)s != NULL) {
                    int _%(name)s_len = data.readInt32(); //read length, only 32bits length support yet
                    Parcel::ReadableBlob _%(name)s_rblob;
                    data.readBlob(_%(name)s_len,&_%(name)s_rblob);
                    memcpy(%(name)s,_%(name)s_rblob.data(),_%(name)s_len);
                }""" % {"qualifier":qualifier,"typ":typ,"name":name})
                    else:
                        output("""
                #error not support this type of output paramter %(qualifier)s%(typ)s %(name)s yet, please add code yourself
""" % {"qualifier":qualifier,"typ":typ,"name":name,"star":star,"len":len})

            output("""
            }""")
        output("""
        }catch(...) {
            ALOGW(SERVICE_NAME"_client sample_base_api error");
        }

        %s
        /*-- add you code for sample_base_api here --*/
    }
""" % ("return _result;" if retTyp != "void" else ""))

output("""};

%=sidl_basename%_client* %=sidl_basename%_client::_instance = NULL;
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
    return %=sidl_basename%_client::Instance()->%(name)s(%(calllist)s);
}""" % {"qualifier":retQualifier,"typ":retTyp,"name":ctx.getName(),"star":retStar,"arglist":arglist, "calllist":calllist} )

py*/

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif
