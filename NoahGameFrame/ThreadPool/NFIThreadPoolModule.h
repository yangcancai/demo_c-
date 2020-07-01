//
// Created by Administrator on 2020/6/29.
//

#ifndef DEBUG_DEAD_LOCK_NFITHREADPOOLMODULE_H
#define DEBUG_DEAD_LOCK_NFITHREADPOOLMODULE_H
#include "../NFIModule.h"
#include "../NFGUID.h"
class NFThreadTask;
typedef  std::function<void(NFThreadTask&)> TASK_PROCESS_FUNCTOR;
typedef  NF_SHARED_PTR<TASK_PROCESS_FUNCTOR> TASK_PROCESS_FUNCTOR_PTR;
class NFThreadTask{
public:
    NFGUID nTaskID;
    std::string data;
    TASK_PROCESS_FUNCTOR_PTR xThreadFunc;
    TASK_PROCESS_FUNCTOR_PTR xEndFunc;
};
class NFIThreadPoolModule : public NFIModule{
public:
    NFIThreadPoolModule(NFIPluginManager* pPluginManager):NFIModule(pPluginManager){}
    ~NFIThreadPoolModule(){};
    virtual void SetCpu(const int cpuCount) = 0;
    virtual int GetThreadCount() = 0 ;
    template<typename BaseType>
    void DoAsyncTask(const NFGUID taskID, const std::string& data, BaseType* pBase, void (BaseType::*handler_begin)(NFThreadTask&&)){
    TASK_PROCESS_FUNCTOR functor_begin = std::bind(handler_begin, pBase, std::placeholders::_1);
    TASK_PROCESS_FUNCTOR_PTR functorPtr_begin(new TASK_PROCESS_FUNCTOR(functor_begin));
    DoAsyncTask(taskID, data, functorPtr_begin, nullptr);
    }
    template<typename BaseType>
    void DoAsyncTask(const NFGUID taskID, const std::string& data, BaseType* pBase, void (BaseType::*handler_begin)(NFThreadTask&&), void (BaseType::*handler_end)(NFThreadTask&&))
    {
        TASK_PROCESS_FUNCTOR functor_begin = std::bind(handler_begin, pBase, std::placeholders::_1);
        TASK_PROCESS_FUNCTOR_PTR functorPtr_begin(new TASK_PROCESS_FUNCTOR(functor_begin));

        TASK_PROCESS_FUNCTOR functor_end = std::bind(handler_end, pBase, std::placeholders::_1);
        TASK_PROCESS_FUNCTOR_PTR functorPtr_end(new TASK_PROCESS_FUNCTOR(functor_end));

        DoAsyncTask(taskID, data, functorPtr_begin, functorPtr_end);
    }

    void DoAsyncTask(const NFGUID taskID, const std::string& data, TASK_PROCESS_FUNCTOR asyncFunctor)
    {
        TASK_PROCESS_FUNCTOR_PTR functorPtr_begin(new TASK_PROCESS_FUNCTOR(asyncFunctor));

        DoAsyncTask(taskID, data, functorPtr_begin, nullptr);
    }

    void DoAsyncTask(const NFGUID taskID, const std::string& data, TASK_PROCESS_FUNCTOR asyncFunctor, TASK_PROCESS_FUNCTOR functor_end)
    {
        TASK_PROCESS_FUNCTOR_PTR functorPtr_begin(new TASK_PROCESS_FUNCTOR(asyncFunctor));
        TASK_PROCESS_FUNCTOR_PTR functorPtr_end(new TASK_PROCESS_FUNCTOR(functor_end));

        DoAsyncTask(taskID, data, functorPtr_begin, functorPtr_end);
    }
    virtual void DoAsyncTask(const NFGUID taskID, const std::string& data, TASK_PROCESS_FUNCTOR_PTR asyncFunctor, TASK_PROCESS_FUNCTOR_PTR functor_end) = 0;
    /////repush the result
    virtual void TaskResult(const NFThreadTask& task) = 0;
};
#endif //DEBUG_DEAD_LOCK_NFITHREADPOOLMODULE_H
