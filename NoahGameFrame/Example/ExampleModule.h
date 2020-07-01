//
// Created by Administrator on 2020/6/28.
//

#ifndef DEBUG_DEAD_LOCK_EXAMPLEMODULE_H
#define DEBUG_DEAD_LOCK_EXAMPLEMODULE_H

#include "../NFIModule.h"
#include "../NFIPluginManager.h"
#include "../ThreadPool/NFIThreadPoolModule.h"
class ExampleModule : public NFIModule{
public:
    ExampleModule(NFIPluginManager* pPluginMananger):NFIModule(pPluginMananger){}
    ~ExampleModule(){}
    virtual bool Init();
    virtual bool Execute();
    void test(NFThreadTask& task);
private:
   NFIThreadPoolModule* m_pThreadPoolModule = nullptr;
};


#endif //DEBUG_DEAD_LOCK_EXAMPLEMODULE_H
