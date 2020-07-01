//
// Created by Administrator on 2020/6/29.
//

#include "NFThreadPoolModule.h"
NFThreadPoolModule::NFThreadPoolModule(NFIPluginManager *pPluginManager):NFIThreadPoolModule(pPluginManager) {

}
NFThreadPoolModule::~NFThreadPoolModule() {

}
void NFThreadPoolModule::DoAsyncTask(const NFGUID taskID, const std::string &data, TASK_PROCESS_FUNCTOR_PTR asyncFunctor, TASK_PROCESS_FUNCTOR_PTR functor_end) {
    NFThreadTask task;
    task.nTaskID = taskID;
    task.data = data;
    task.xThreadFunc = asyncFunctor;
    task.xEndFunc = functor_end;

    int index = 0;
    if (!taskID.IsNull())
    {
        index = taskID.nData64 % mThreadPool.size();
    }

    NF_SHARED_PTR<NFThreadCell> threadobject = mThreadPool[index];
    threadobject->AddTask(task);
}
void NFThreadPoolModule::TaskResult(const NFThreadTask &task) {
    mTaskResult.Push(task);
}
void NFThreadPoolModule::SetCpu(const int cpuCount) {
    if (mCPUCount < cpuCount) {
        mCPUCount = cpuCount;
        for (int i = mThreadPool.size(); i < cpuCount * 2; i++) {
            mThreadPool.push_back(NF_SHARED_PTR<NFThreadCell>(NF_NEW NFThreadCell(this)));
        }
    }
}
int NFThreadPoolModule::GetThreadCount() {
    return mThreadPool.size();
}
bool NFThreadPoolModule::Execute() {
    ExecuteTaskResult();
    return true;
}
bool NFThreadPoolModule::Init() {
    SetCpu(1);
    return true;
}
void NFThreadPoolModule::ExecuteTaskResult() {
  NFThreadTask xMsg;
  while (mTaskResult.Pop(xMsg)){
      if (xMsg.xEndFunc){
          xMsg.xEndFunc->operator()(xMsg);
      }
  }
}