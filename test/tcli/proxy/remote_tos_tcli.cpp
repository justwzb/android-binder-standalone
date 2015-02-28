/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: remote_tos_tcli.sidl
 */
 

#define LOG_TAG     "remote_tos_tcli"

#include <string.h>
#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <cutils/hashmap.h>

#include "tos_tcli.h"
#include "clog.h"


#define SERVICE_DESCRIPTOR                      "e1ba72ba-ade3-11e4-9426-7831c1c50d90"
#define SERVICE_NAME                            "remote_tos_tcli"

#define FIRST_CALL_TRANSACTION                  (1)
#define TRANSACTION_tos_tcli_printf FIRST_CALL_TRANSACTION + 1
#define TRANSACTION_tos_tcli_addCommand FIRST_CALL_TRANSACTION + 2
#define TRANSACTION_tos_tcli_execute FIRST_CALL_TRANSACTION + 3
#define TRANSACTION_tos_tcli_executeByargs FIRST_CALL_TRANSACTION + 4

#define TRANSACTION_CALLBACK_outputcallback FIRST_CALL_TRANSACTION + 100
#define TRANSACTION_CALLBACK_cmdcallback FIRST_CALL_TRANSACTION + 101

using namespace android;


typedef void (*_tcli_func)(int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10);


#if defined(BINDER_SERVICE)

#include <stdlib.h>
#include "remote_tos_tcli.h"
#include <sbinder/RemoteCallbackList.h>

extern int tos_tcli_removeCommand(const char* name);
extern const char* tos_tcli_getExecName();
extern const char* tos_tcli_getExecArgParse();
extern int tos_tcli_getExecArgCount();

class TCLICommand {
private:
    const char * _name;                   /* the command name */
    const char * _shortHelp;              /* short help string */
    const char * _longHelp;               /* long help string */
    const char * _argParse;               /* a string of s (string) or i (integer) */
    _tcli_func _func;                     /* function pointer for command */

public:
    TCLICommand(const char* name,const char *shortHelp,const char *longHelp,const char *argParse, void *func){
        _name = strdup(name);
		_shortHelp = strdup(shortHelp);
		_longHelp = strdup(longHelp);
		_argParse = strdup(argParse);
		_func = (_tcli_func)func;
		
    }

	~TCLICommand(){
		free((void*)_name);
		free((void*)_shortHelp);
		free((void*)_longHelp);
		free((void*)_argParse);
		_func = NULL;
	}

	const char* getName(){
		return _name;
	}

	const char* getShortHelp(){
		return _shortHelp;

	}

	const char* getLongHelp(){
		return _longHelp;

	}

	const char* getArgParse(){
		return _argParse;

	}

    const _tcli_func getFunc() const {
        return _func;
    }
};

class remote_tos_tcli_service : public BBinder  
{  
private:
    static remote_tos_tcli_service* _instance;

    class tos_tcli_RemoteCallbackList : public RemoteCallbackList {
        void onCallbackDied(sp<IBinder> binder,void* cookie) {
			TCLICommand* tmpTcliCmd = (TCLICommand* )cookie;
            tos_tcli_removeCommand(tmpTcliCmd->getName());
			if (tmpTcliCmd != NULL)
				delete tmpTcliCmd;
        }
    };

    tos_tcli_RemoteCallbackList _cbList;

    remote_tos_tcli_service(){
        CLOGI(SERVICE_NAME"_service create\n");
    }
    
    virtual ~remote_tos_tcli_service() {
        CLOGI(SERVICE_NAME"_service destory\n");
    }

    static void tcli_output(const char* prompt,void* userdata) {
        IBinder* binder = (IBinder*)userdata;
        if(binder != NULL && binder->isBinderAlive()) {
            Parcel data, reply;
            data.writeInterfaceToken(String16(SERVICE_NAME"_OutputCallback"));
            data.writeCString(prompt);
            binder->transact(TRANSACTION_CALLBACK_outputcallback, data, &reply, 0);

            if(reply.readExceptionCode() == 0) {//fix check
            }
            else {
                CLOGW(SERVICE_NAME"_servce tos_tcli_onOutput exception");
            }
        }
        else {
            CLOGW(SERVICE_NAME"_servce tos_tcli_onOutput error");
        }
    }

    static void tcli_cmd(int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10) {
        CLOGI(SERVICE_NAME"_service tcli_cmd");

        RemoteCallbackList* rcbl = &(_instance->_cbList);

        const char* cmd = tos_tcli_getExecName();
        const char* argParse = tos_tcli_getExecArgParse();
        int argCount = tos_tcli_getExecArgCount();

        if(cmd == NULL || argParse == NULL || argCount<0) {
            CLOGW(SERVICE_NAME"_servce cmd(%s) or argParse(%s) or argCount(%d) null",cmd,argParse,argCount);
            return;
        }

        int size = rcbl->beginBroadcast();
		CLOGI(SERVICE_NAME"_service tcli_cmd size = %d\n",size);
        for(int i=0;i<size;i++) {

            sp<IBinder> binder = rcbl->getBroadcastItem(i);
            TCLICommand* tmpTcliCmd = (TCLICommand* )rcbl->getBroadcastCookie(i);

            if(binder != NULL && strcmp(cmd,tmpTcliCmd->getName()) == 0) {
                Parcel data, reply;
                data.writeInterfaceToken(String16(SERVICE_NAME"_CmdCallback"));

                int args[TOS_TCLI_MAX_ARGS];
                args[0] = a1;
                args[1] = a2;
                args[2] = a3;
                args[3] = a4;
                args[4] = a5;
                args[5] = a6;
                args[6] = a7;
                args[7] = a8;
                args[8] = a9;
                args[9] = a10;

                data.writeInt32(argCount);
                data.writeCString(argParse);
                for(int i=0;i<argCount;i++) {
                    switch (argParse[i]) {
                        case 'i': {
                            data.writeInt32(args[i]);
                        }
                        break;

                        case 's': {
                            data.writeCString((const char*)args[i]);
                        }
                        break;

                        default: {
                            CLOGW("argParse error %s[%d]",argParse,i);
                        }
                        break;
                    }
                }
				CLOGI(SERVICE_NAME"_service tcli_cmd TRANSACTION_CALLBACK_cmdcallback\n");

                binder->transact(TRANSACTION_CALLBACK_cmdcallback, data, &reply, 0);
				CLOGI(SERVICE_NAME"_service tcli_cmd TRANSACTION_CALLBACK_cmdcallback 111\n");

                if(reply.readExceptionCode() == 0) {//fix check
                }
                break;
            }
        }
        rcbl->finishBroadcast();

        CLOGI(SERVICE_NAME"_service tcli_cmd end");
    }

public:  
    static int Instance() {
        if(_instance == NULL) {
            _instance = new remote_tos_tcli_service();
            int ret = defaultServiceManager()->addService(  
                String16(SERVICE_NAME), _instance );  
            CLOGI(SERVICE_NAME"_service Instance %d\n",ret);
            return ret;  
        }

        return -1;
    }
    
    virtual status_t onTransact(uint32_t code , const Parcel& data , Parcel* reply, uint32_t flags) {
        CLOGI(SERVICE_NAME"_service - onTransact code=%d",code);

        switch(code)  {
            case TRANSACTION_tos_tcli_printf:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for tos_tcli_printf here, will auoto generated but may change yourself if need --

                //skip Exception and result first to write output paramters
                reply->writeNoException();
                //skip Exception and result first end

                //begin paramters list
                const char* buf = data.readCString();

                tos_tcli_printf( buf );

                //-- end code for tos_tcli_printf here --
            }break;
            
            case TRANSACTION_tos_tcli_addCommand:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for tos_tcli_addCommand here, will auoto generated but may change yourself if need --

                //begin paramters list
                const char* name = data.readCString();

                int _shortHelp_len = data.readInt32(); //read length, only 32bits length support yet
                const char* shortHelp = NULL;
                if(_shortHelp_len > 0) {
                    shortHelp = data.readCString();
                }

                int _longHelp_len = data.readInt32(); //read length, only 32bits length support yet
                const char* longHelp = NULL;
                if(_longHelp_len > 0) {
                    longHelp = data.readCString();
                }

                const char* argParse = data.readCString();


				TCLICommand* tcliCmd = new TCLICommand(name,shortHelp,longHelp,argParse,(void*)tcli_cmd);

                sp<IBinder> binder = data.readStrongBinder();

                if(binder != NULL) {

                    int _result = tos_tcli_addCommand( tcliCmd->getName(), tcliCmd->getShortHelp(), tcliCmd->getLongHelp()
						, tcliCmd->getArgParse(), (void*)tcliCmd->getFunc());

                    if(_result == 0) {
                        if(_cbList.registerCallback(binder,(void*)tcliCmd)) {
                            reply->writeNoException();
                            reply->writeInt32(_result); //int as return value
                        }
                        else {
                            reply->writeInt32(-3);//Exception
							tos_tcli_removeCommand(tcliCmd->getName());
							delete tcliCmd;
                        }
                    }
                    else {
                        reply->writeInt32(-2);//Exception
                        delete tcliCmd;
                    }
                }
                else {
                    reply->writeInt32(-1);//Exception
                    delete tcliCmd;
                }

                //-- end code for tos_tcli_addCommand here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_tos_tcli_execute:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for tos_tcli_execute here, will auoto generated but may change yourself if need --

                //skip Exception and result first to write output paramters
                reply->writeNoException();
                //skip Exception and result first end

                //begin paramters list
                const char* cmd = data.readCString();

                sp<IBinder> binder = data.readStrongBinder();

                int _result = tos_tcli_execute( cmd, remote_tos_tcli_service::tcli_output, binder.get() );

                reply->writeInt32(_result); //int as return value

                //-- end code for tos_tcli_execute here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_tos_tcli_executeByargs:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for tos_tcli_executeByargs here, will auoto generated but may change yourself if need --

                //skip Exception and result first to write output paramters
                reply->writeNoException();
                //skip Exception and result first end

                //begin paramters list
                int argc = (int)data.readInt32();  //int as input paramter

                const char* argv[16];//max 16 is OK
                memset(argv,0,sizeof(argv));
                for(int i=0;i<argc;i++) {
                    if(data.readInt32() > 0) {
                        argv[i] = data.readCString();
                    }
                    else {
                        argv[i] = NULL;
                    }
					CLOGD("TRANSACTION_tos_tcli_executeByargs argv[%d] = %s\n",i,argv[i]);
                }
                
                sp<IBinder> binder = data.readStrongBinder();

                int _result = tos_tcli_executeByargs( argc, argv, remote_tos_tcli_service::tcli_output, binder.get() );

                reply->writeInt32(_result); //int as return value

                //-- end code for tos_tcli_executeByargs here --
                return NO_ERROR;
            } break;
            
            default:  
                return BBinder::onTransact(code, data, reply, flags);
        
        }

        CLOGI(SERVICE_NAME"_service end");
		return NO_ERROR;
    }
}; 

int remote_tos_tcli_service_add() {
    remote_tos_tcli_service::Instance();
    return 0;
}

remote_tos_tcli_service* remote_tos_tcli_service::_instance = NULL;

#elif defined(BINDER_CLIENT)
#include <stdarg.h>
#include <sbinder/ICallbackList.h>
#include <cutils/hashmap.h>


class remote_tos_tcli_client  
{  
private:
    static remote_tos_tcli_client* _instance;
    sp<IBinder> _binder;
    ICallbackList _CmdList;

    class OutputCallback : public ICallbackList::ICallback {
    public:
        OutputCallback(void* cb,void* cookie)
            :ICallback(cb,cookie) {
            _descriptor = String16(SERVICE_NAME"_OutputCallback");
        }

        ~OutputCallback() {
        }

        virtual status_t onTransact( uint32_t code,
                const Parcel& data,Parcel* reply,uint32_t flags = 0) {
                
            CLOGI(SERVICE_NAME"_client onTransact code=%d\n",code);

            switch (code){
            case TRANSACTION_CALLBACK_outputcallback:
            {
                if (!data.checkInterface(this)) {
                    CLOGW(SERVICE_NAME"_client onTransact Interface error\n");
                    return -1;
                }

                if(_callback != NULL) {
                    const char* prompt = data.readCString();

                    ((tos_tcli_onOutput)_callback)(prompt,_cookie);

                    reply->writeNoException();
                }
                else {
                    reply->writeInt32(-1);//Exception
                }
                break;
            }

            default:
                return BBinder::onTransact(code, data, reply, flags);
            }

            return NO_ERROR;
        }
    };

    class CmdCallback : public ICallbackList::ICallback {
    public:
        CmdCallback(void* cb,void* cookie)
            :ICallback(cb,cookie) {
            _descriptor = String16(SERVICE_NAME"_CmdCallback");
        }

        ~CmdCallback() {
        }

        virtual status_t onTransact( uint32_t code,
                const Parcel& data,Parcel* reply,uint32_t flags = 0) {
            CLOGI(SERVICE_NAME"_client onTransact code=%d\n",code);

            switch (code){
            case TRANSACTION_CALLBACK_cmdcallback:
            {
                if (!data.checkInterface(this)) {
                    CLOGW(SERVICE_NAME"_client onTransact Interface error\n");
                    return -1;
                }
				CLOGI(SERVICE_NAME"_service tcli_cmd ontransaction\n");

                if(_callback != NULL) {
					CLOGI(SERVICE_NAME"_service tcli_cmd ontransaction _callback != NULL\n");
                    int argCount = data.readInt32();
                    const char* argParse = data.readCString();
                    int args[TOS_TCLI_MAX_ARGS];
                    memset(args,0,sizeof(args));

                    for(int i=0;i<argCount;i++) {
                        switch (argParse[i]) {
                            case 'i': {
                                args[i] = data.readInt32();
                            }
                            break;

                            case 's': {
                                args[i] = (int)data.readCString();
                            }
                            break;

                            default: {
                                CLOGW("argParse error %s[%d]",argParse,i);
                            }
                            break;
                        }
                    }
					CLOGI(SERVICE_NAME"_service tcli_cmd ontransaction 111\n");

                    ((_tcli_func)_callback)(args[0],args[1],args[2],args[3],args[4],args[5],args[6],args[7],args[8],args[9]);

                    reply->writeNoException();
                }
                else {
                    reply->writeInt32(-1);//Exception
                }
                break;
            }

            default:
                return BBinder::onTransact(code, data, reply, flags);
            }

            return NO_ERROR;
        }
    };

    remote_tos_tcli_client()
        :_binder(NULL) {
        CLOGI(SERVICE_NAME"_client create\n");
        getService();
    }
    
    virtual ~remote_tos_tcli_client() {
        CLOGI(SERVICE_NAME"_client destory\n");
    }

    inline bool getService(void) {
        if(_binder == NULL) {
            sp<IServiceManager> sm = defaultServiceManager();
            _binder = sm->getService(String16(SERVICE_NAME));
        }

        if(_binder == NULL) {
            CLOGW(SERVICE_NAME"_client getFailed!\n");
        }

        return (_binder != NULL);
    }

public:  
    static remote_tos_tcli_client* Instance() {
        if(_instance == NULL) {
            CLOGI(SERVICE_NAME"_client Instance");
            _instance = new remote_tos_tcli_client();
        }

        return _instance;
    }

    void tos_tcli_printf( const char* buf ) {
        Parcel data, reply;

        /*-- add you code for tos_tcli_printf here --*/
        if(!getService()) {
            return;
        }

        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            data.writeCString(buf);

            _binder->transact(TRANSACTION_tos_tcli_printf,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check

            } else {
                CLOGW(SERVICE_NAME"_client tos_tcli_printf error");
            }
        }catch(...) {
            CLOGW(SERVICE_NAME"_client tos_tcli_printf error");
        }

        
        /*-- add you code for tos_tcli_printf here --*/
    }

    int tos_tcli_addCommand( const char* name, const char* shortHelp, const char* longHelp, const char* argParse, void* func ) {
        Parcel data, reply;

        /*-- add you code for tos_tcli_addCommand here --*/
        int _result = -1;
        if(name == NULL || argParse == NULL || func == NULL || !getService()) {
            CLOGW(SERVICE_NAME"_client tos_tcli_addCommand paramters error");
            return _result;
        }

        if(_CmdList.findCallback((void*)func,(void*)name) != NULL) {
            CLOGE(SERVICE_NAME"_client cmd %s arleady added",name);
            return _result;
        }

        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

			char buf[512];
			snprintf(buf, sizeof(buf),"%s.%d", name, getpid());
            data.writeCString(buf);

            if (shortHelp == NULL) {
                data.writeInt32(-1);
            }
            else {
                data.writeInt32(1);
                data.writeCString(shortHelp);
            }

            if (longHelp == NULL) {
                data.writeInt32(-1);
            }
            else {
                data.writeInt32(1);
                data.writeCString(longHelp);
            }

            data.writeCString(argParse);


            sp<CmdCallback> ccmd = new CmdCallback((void*)func,(void*)NULL);
            data.writeStrongBinder(ccmd);

            _binder->transact(TRANSACTION_tos_tcli_addCommand,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check
                _result = (typeof(_result))reply.readInt32();//int as return value

                if(_result == 0) {
                    _CmdList.addCallback(ccmd);
                }

            } else {
                CLOGW(SERVICE_NAME"_client tos_tcli_addCommand error");
            }
        }catch(...) {
            CLOGW(SERVICE_NAME"_client tos_tcli_addCommand error");
        }

        return _result;
        /*-- add you code for tos_tcli_addCommand here --*/
    }

    int tos_tcli_execute( const char* cmd, tos_tcli_onOutput out, void* userdata ) {
        Parcel data, reply;

        /*-- add you code for tos_tcli_execute here --*/
        int _result = -1;
        if(cmd == NULL || !getService()) {
            return _result;
        }

        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            data.writeCString(cmd);

            sp<OutputCallback> cout = new OutputCallback((void*)out,userdata);
            data.writeStrongBinder(cout);

            _binder->transact(TRANSACTION_tos_tcli_execute,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check

                _result = (typeof(_result))reply.readInt32();//int as return value

            } else {
                CLOGW(SERVICE_NAME"_client tos_tcli_execute error");
            }
        }catch(...) {
            CLOGW(SERVICE_NAME"_client tos_tcli_execute error");
        }

        return _result;
        /*-- add you code for tos_tcli_execute here --*/
    }

    int tos_tcli_executeByargs( int argc, const char* argv[], tos_tcli_onOutput out, void* userdata ) {
        Parcel data, reply;

        /*-- add you code for tos_tcli_executeByargs here --*/
        int _result;
        if(argc <= 0 || argv == NULL || !getService()) {
			CLOGW("arg <=0 or NULL or service not ok!\n");
            return _result;
        }

        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            data.writeInt32(argc);
            for(int i=0;i<argc;i++) {
                if(argv[i] != NULL) {
                    data.writeInt32(1);
                    data.writeCString(argv[i]);
                }
                else {
                    data.writeInt32(-1);
                }
            }

            sp<OutputCallback> cout = new OutputCallback((void*)out,userdata);
            data.writeStrongBinder(cout);

            _binder->transact(TRANSACTION_tos_tcli_executeByargs,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check

                _result = (typeof(_result))reply.readInt32();//int as return value

            } else {
                CLOGW(SERVICE_NAME"_client tos_tcli_executeByargs error");
            }
        }catch(...) {
            CLOGW(SERVICE_NAME"_client tos_tcli_executeByargs error");
        }

        return _result;
        /*-- add you code for tos_tcli_executeByargs here --*/
    }
};

remote_tos_tcli_client* remote_tos_tcli_client::_instance = NULL;


void tos_tcli_printf(const char* fmt,...) {
    char buf[TOS_TCLI_CMD_MAX_LEN];
    va_list arg;
    va_start(arg,fmt);
    vsnprintf(buf,sizeof(buf),fmt,arg);
    va_end(arg);
    buf[sizeof(buf)-1]=0;
    return remote_tos_tcli_client::Instance()->tos_tcli_printf(buf);
}

int _do_tos_tcli_addCommand( const char* name, const char* shortHelp, const char* longHelp, const char* argParse, void* func ) {
    return remote_tos_tcli_client::Instance()->tos_tcli_addCommand(name, shortHelp, longHelp, argParse, func);
}

int tos_tcli_execute( const char* cmd, tos_tcli_onOutput out, void* userdata ) {
    return remote_tos_tcli_client::Instance()->tos_tcli_execute(cmd, out, userdata);
}
int tos_tcli_executeByargs( int argc, const char* argv[], tos_tcli_onOutput out, void* userdata ) {
	return remote_tos_tcli_client::Instance()->tos_tcli_executeByargs(argc, argv, out, userdata);
}

/**
由于静态变量和__attribute__((constructor))属性的初始化顺序是不一定的
我们不能在constructor函数中调用binder接口进行远程通信,因为远程通信依赖大量static变量.
为此,我们不得不先将他们添加到一个列表中,然后在客户端的proxy_init中真正添加它们.
*/
static Hashmap* s_tmpCmdTable = NULL;

class TCLICommand {
private:
    const char * _name;                   /* the command name */
    const char * _shortHelp;              /* short help string */
    const char * _longHelp;               /* long help string */
    const char * _argParse;               /* a string of s (string) or i (integer) */
    _tcli_func _func;                     /* function pointer for command */

public:
    TCLICommand(const char* name,const char *shortHelp,const char *longHelp,const char *argParse, void *func)
        :_name(name)
        ,_shortHelp(shortHelp)
        ,_longHelp(longHelp)
        ,_argParse(argParse)
        ,_func((_tcli_func)func) {
    }

    void addself() {
        _do_tos_tcli_addCommand(_name,_shortHelp,_longHelp,_argParse,(void*)_func);
    }

    const _tcli_func getFunc() const {
        return _func;
    }
};

static int _hash(void* key) {
    return hashmapHash(key,strlen((char*)key));
}

static bool _equals(void* keyA, void* keyB) {
    return (0 == strcmp((char*)keyA,(char*)keyB));
}

int tos_tcli_addCommand( const char* name, const char* shortHelp, const char* longHelp, const char* argParse, void* func ) {
    if(s_tmpCmdTable == (Hashmap*)1) {
        //after _tos_tcli_init
        return _do_tos_tcli_addCommand(name,shortHelp,longHelp,argParse,func);
    }
    else if(s_tmpCmdTable == NULL) {
        s_tmpCmdTable = hashmapCreate(16,_hash,_equals);
        CLOG_ASSERT(s_tmpCmdTable != NULL,"s_cmdTable create failed");
    }

    TCLICommand* cmd = new TCLICommand(name,shortHelp,longHelp,argParse,func);
    if(cmd == NULL) {
        CLOG_ASSERT(cmd != NULL,"new TCLICommand for %s failed",name);
        return SITA_ENOMEM;
    }

    TCLICommand* oldcmd = (TCLICommand*)hashmapPut(s_tmpCmdTable,(void*)name,cmd);
    if(oldcmd != NULL) {
        CLOGW("cmd %s replaced %p ==> %p\n",name,oldcmd->getFunc(),func);
        delete oldcmd;
        oldcmd = NULL;
    }

    return SITA_SUCCESS;
}

static bool _do_add_cmd(void* key, void* value, void* context) {
    TCLICommand* cmd = (TCLICommand*)value;
    if(cmd != NULL) {
        cmd->addself();
        delete cmd;
        cmd = NULL;
    }
    return true;
}

//hidden api for proxy client
extern "C" int _tos_tcli_init() {
    if(s_tmpCmdTable != NULL) {
        hashmapForEach(s_tmpCmdTable,_do_add_cmd,NULL);

        hashmapFree(s_tmpCmdTable);
        s_tmpCmdTable = (Hashmap*)1;
    }

    return SITA_SUCCESS;
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif
