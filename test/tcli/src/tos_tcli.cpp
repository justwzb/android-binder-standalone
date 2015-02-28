#include "tos_tcli.h"
#include "clog.h"

#include <utils/Mutex.h>
#include <cutils/hashmap.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

using namespace android;

typedef void (*_tcli_func)(int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10);

class TCLICommand;

static Mutex s_mutex(Mutex::RECURSIVE, "tcli");
static Hashmap* s_cmdTable = NULL;
static tos_tcli_onOutput s_output = NULL;
static void* s_userdata = NULL;
static const TCLICommand* s_runningCmd = NULL;
static int s_runningCmdArgCount = -1;

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

    const char* getName() const {
        return _name;
    }

    const _tcli_func getFunc() const {
        return _func;
    }

    const char* getArgParse() const {
        return _argParse;
    }

    void exec(int argc,const char* argv[]) {
        int args[TOS_TCLI_MAX_ARGS];
        memset(args,0,sizeof(args));

        int argCnt = strlen(_argParse);
        CLOGI("argc=%d wants argCnt(%d)\n",argCnt,argc);
        argCnt = SITA_MIN(argCnt,argc);
        argCnt = SITA_MIN(argCnt,TOS_TCLI_MAX_ARGS);

        for(int i=0;i<argCnt;i++) {
            switch (_argParse[i]) {
                case 'i': {
                    if(argv[i] != NULL) {
                        args[i] = atoi(argv[i]);
                    }
                }
                break;

                case 's': {
                    args[i] = (int)argv[i];
                }
                break;

                default: {
                    CLOG_ASSERT(0,"_argParse error %s[%d]",_argParse,i);
                }
                break;
            }
        }

        tos_tcli_printf("Run %s\n",_name);
        s_runningCmd = this;
        s_runningCmdArgCount = argCnt;
        _func(args[0],args[1],args[2],args[3],args[4],args[5],args[6],args[7],args[8],args[9]);
        s_runningCmd = NULL;
        s_runningCmdArgCount = -1;
        tos_tcli_printf("Run %s end\n",_name);
    }

    void showshortHelp(void) {
        tos_tcli_printf("\t%-32s -\t%s\n",_name,_shortHelp==NULL?"":_shortHelp);
    }

    void showlongHelp(void) {
        tos_tcli_printf("%s : %s\n",_name,_shortHelp==NULL?"":_shortHelp);
        if(_longHelp != NULL) {
            tos_tcli_printf("%s\n",_longHelp);
        }
    }
};

static int _hash(void* key) {
    return hashmapHash(key,strlen((char*)key));
}

static bool _equals(void* keyA, void* keyB) {
    return (0 == strcmp((char*)keyA,(char*)keyB));
}

static int _tcli_init(void) {
    CLOGI("%s...\n",__FUNCTION__);
    Mutex::Autolock _l(s_mutex);

    if (sizeof(int) != sizeof(void*)) {
        CLOG_ASSERT(sizeof(int) == sizeof(void*),"tcli can not run on this platform ,%d != %d!!!",sizeof(int),sizeof(void*));
        return SITA_FAILED;
    }

    if(s_cmdTable == NULL) {
        s_cmdTable = hashmapCreate(16,_hash,_equals);
        CLOG_ASSERT(s_cmdTable != NULL,"s_cmdTable create failed");
    }

    CLOGI("%s...success\n",__FUNCTION__);
    return SITA_SUCCESS;
}

void tos_tcli_printf(const char* fmt,...) {
    Mutex::Autolock _l(s_mutex);

    char buf[1024];
    va_list arg;
    va_start(arg,fmt);
    vsnprintf(buf,sizeof(buf),fmt,arg);
    va_end(arg);

    if(s_output != NULL) {
        s_output(buf,s_userdata);
        CLOGCLI("%s",buf);
    }
}

int tos_tcli_addCommand(const char* name,const char *shortHelp,const char *longHelp,const char *argParse, void *func) {
    CLOGI("%s...%s [%s] %p\n",__FUNCTION__,name,argParse,func);

    if(name == NULL || argParse == NULL || func == NULL ) {
        CLOGW_WITHCODE(SITA_EINVAL, "%s %s:func 0x%p,argParse:%s failed\n",__FUNCTION__,name,func,argParse);
        return SITA_EINVAL;
    }

    int argCnt = strlen(argParse);
    if(argCnt > TOS_TCLI_MAX_ARGS) {
        CLOGW_WITHCODE(SITA_EINVAL, "%s %s:argParse(%s) too long\n",__FUNCTION__,name,argParse);
        return SITA_EINVAL;
    }

    for(int i=0;i<argCnt;i++)
    {
        if(argParse[i] != 'i' && argParse[i] != 's')
        {
            CLOGW_WITHCODE(SITA_EINVAL, "%s %s:argParse(%s) error, must 'i' or 's' only\n",__FUNCTION__,name,argParse);
            return SITA_EINVAL;
        }
    }

    Mutex::Autolock _l(s_mutex);

    int err = _tcli_init();
    if(err != SITA_SUCCESS) {
        return err;
    }

    TCLICommand* cmd = new TCLICommand(name,shortHelp,longHelp,argParse,func);
    if(cmd == NULL) {
        CLOG_ASSERT(cmd != NULL,"new TCLICommand for %s failed",name);
        return SITA_ENOMEM;
    }

    TCLICommand* oldcmd = (TCLICommand*)hashmapPut(s_cmdTable,(void*)name,cmd);
    if(oldcmd != NULL) {
        CLOGW("cmd %s replaced %p ==> %p\n",name,oldcmd->getFunc(),func);
        delete oldcmd;
        oldcmd = NULL;
    }

    CLOGI("%s...name=%s success\n",__FUNCTION__,name);
    return SITA_SUCCESS;
}

int tos_tcli_executeByargs(int argc,const char* argv[],tos_tcli_onOutput out,void* userdata) {
    CLOGI("%s...\n",__FUNCTION__);
    if(argc < 1 || argv == NULL) {
        CLOGW_WITHCODE(SITA_EINVAL, "%s argc=%d argv=%p error\n",__FUNCTION__,argc,argv);
        return SITA_EINVAL;
    }

    if(argv[0] == NULL) {
        CLOGW_WITHCODE(SITA_EINVAL, "%s cmd null\n",__FUNCTION__,argc,argv);
        return SITA_EINVAL;
    }

    CLOGV("%s argc=%d\n",__FUNCTION__,argc);
    for(int i=0;i<argc;i++) {
        CLOGV("     argv[%d]=[%s]\n",i,argv[i]);
    }

    Mutex::Autolock _l(s_mutex);

    int err = _tcli_init();
    if(err != SITA_SUCCESS) {
        return err;
    }
    
    const char* cmdstr = argv[0];

    TCLICommand* cmd = (TCLICommand*)hashmapGet(s_cmdTable,(void*)cmdstr);
    if(cmd == NULL) {
        CLOGW_WITHCODE(SITA_EINVAL, "%s cmd(%s) not found\n",__FUNCTION__,cmdstr);
        if (out != NULL){
        	  s_output = out;
				    s_userdata = userdata;
				    cmd->exec(argc-1,argv+1);
				    s_output = NULL;
				    s_userdata = NULL;
        }
        return SITA_EINVAL;
    }

    s_output = out;
    s_userdata = userdata;
    cmd->exec(argc-1,argv+1);
    s_output = NULL;
    s_userdata = NULL;

    CLOGI("%s...success\n",__FUNCTION__);
    return SITA_SUCCESS;
}

int tos_tcli_execute(const char* cmd,tos_tcli_onOutput out,void* userdata) {
    CLOGI("%s...\n",__FUNCTION__);
    if(cmd == NULL) {
        CLOGW_WITHCODE(SITA_EINVAL, "%s cmd null\n",__FUNCTION__);
        return SITA_EINVAL;
    }

    char cmdcopy[TOS_TCLI_CMD_MAX_LEN];
    strncpy(cmdcopy,cmd,TOS_TCLI_CMD_MAX_LEN);
    cmdcopy[TOS_TCLI_CMD_MAX_LEN-1] = 0;
    CLOGI("%s cmd=[%s]\n",__FUNCTION__,cmdcopy);

    int argc = 0;
    const char* argv[16] = {NULL};
    const char delim[] = " \t";
    char *token;
    
    token = strtok(cmdcopy, delim);
    while( token != NULL ) {
        argv[argc++] = token;

        token = strtok(NULL, delim);
    }

    return tos_tcli_executeByargs(argc,argv,out,userdata);
}

static bool _show_short_help(void* key, void* value, void* context) {
    TCLICommand* cmd = (TCLICommand*)value;
    if(cmd != NULL) {
        cmd->showshortHelp();
    }
    return true;
}

static void _showhelp(char* cmd) {
    Mutex::Autolock _l(s_mutex);

    if(cmd == NULL) {
        tos_tcli_printf("TCL command-line interface client, version 1.0.0\n");
        tos_tcli_printf("Type 'help <command>' for help on a specific command.\n");
        tos_tcli_printf("Available commands:\n");

        hashmapForEach(s_cmdTable,_show_short_help,NULL);
    }
    else {
        TCLICommand* ccmd = (TCLICommand*)hashmapGet(s_cmdTable,(void*)cmd);
        if(ccmd == NULL) {
            tos_tcli_printf("Unknown command: '%s'\n",cmd);
            tos_tcli_printf("Type 'help' for usage.\n");
        }
        else {
            ccmd->showlongHelp();
        }
    }
}
TOS_TCLI_COMMAND(help,
    "list all commands and show their helps.",
    "Type 'help' to list all commands\nType 'help <command>' for help on a specific command.",
    "s",_showhelp);


/*---hidden apis for remote_tos_tcli.cpp---*/
int tos_tcli_removeCommand(const char* name) {
    CLOGI("%s...%s\n",__FUNCTION__,name);

    if(name == NULL) {
        CLOGW_WITHCODE(SITA_EINVAL, "%s name null\n",__FUNCTION__);
        return SITA_EINVAL;
    }

    Mutex::Autolock _l(s_mutex);

    TCLICommand* cmd = (TCLICommand*)hashmapRemove(s_cmdTable,(void*)name);
    if(cmd == NULL) {
        CLOGW_WITHCODE(SITA_EINVAL, "%s name %s not found\n",__FUNCTION__,name);
        return SITA_EINVAL;
    }

    delete cmd;
    cmd = NULL;

    return SITA_SUCCESS;
}


const char* tos_tcli_getExecName() {
    if(s_runningCmd != NULL) {
        return s_runningCmd->getName();
    }
    return NULL;
}

const char* tos_tcli_getExecArgParse() {
    if(s_runningCmd != NULL) {
        return s_runningCmd->getArgParse();
    }
    return NULL;
}

int tos_tcli_getExecArgCount() {
    return s_runningCmdArgCount;
}
