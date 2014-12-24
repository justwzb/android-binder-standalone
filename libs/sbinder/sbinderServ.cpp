#define LOG_TAG     "sbinder_serv"

#include <binder/IPCThreadState.h>
#include <sbinder/sbinderServ.h>

using namespace android;

int sbinder_serv()
{
    sp<ProcessState> proc(ProcessState::self());

    ProcessState::self()->startThreadPool();
    ALOGV("server -> enter loop ...");
    IPCThreadState::self()->joinThreadPool();
    ALOGV("server -> return");
    return 0;
}