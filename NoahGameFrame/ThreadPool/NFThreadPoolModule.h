//
// Created by Administrator on 2020/6/29.
//

#ifndef DEBUG_DEAD_LOCK_NFTHREADPOOLMODULE_H
#define DEBUG_DEAD_LOCK_NFTHREADPOOLMODULE_H

#include "NFIThreadPoolModule.h"
#include "NFQueue.hpp"
class NFThreadCell
{
public:
    NFThreadCell(NFIThreadPoolModule* p)
    {
        m_pThreadPoolModule = p;
        mThread = NF_SHARED_PTR<std::thread>(NF_NEW std::thread(&NFThreadCell::Execute, this));
    }
    void AddTask(const NFThreadTask& task)
    {
        mTaskList.Push(task);
    }
protected:
    void Execute()
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            //pick the first task and do it
            NFThreadTask task;
            if (mTaskList.Pop(task))
            {
                task.xThreadFunc->operator()(task);

                //repush the result to the main thread
                //and, do we must to tell the result?
                if (task.xEndFunc)
                {
                    m_pThreadPoolModule->TaskResult(task);
                }
            }
        }
    }

private:
    NFQueue<NFThreadTask> mTaskList;
    NF_SHARED_PTR<std::thread> mThread;
    NFIThreadPoolModule* m_pThreadPoolModule;
};
class NFThreadPoolModule : public NFIThreadPoolModule{
public:
    NFThreadPoolModule(NFIPluginManager* pPluginManager);
    ~NFThreadPoolModule();
    virtual void SetCpu(const int cpuCount) override ;
    virtual int GetThreadCount() override ;
    virtual void DoAsyncTask(const NFGUID taskID, const std::string& data, TASK_PROCESS_FUNCTOR_PTR asyncFunctor, TASK_PROCESS_FUNCTOR_PTR functor_end) override;
    virtual void TaskResult(const NFThreadTask& task) override;
    virtual bool Execute();
    virtual bool Init();

protected:
    void ExecuteTaskResult();
private:
    int mCPUCount = 0;
    NFQueue<NFThreadTask> mTaskResult;
    std::vector<NF_SHARED_PTR<NFThreadCell>> mThreadPool;
};
#endif //DEBUG_DEAD_LOCK_NFTHREADPOOLMODULE_H
