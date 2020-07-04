//
// Created by Administrator on 2020/6/28.
//

#ifndef DEBUG_DEAD_LOCK_NFIMODULE_H
#define DEBUG_DEAD_LOCK_NFIMODULE_H
#include "NFIPluginManager.h"
class NFIModule
{
public:
    NFIModule(NFIPluginManager* pPluginManager){
        this->pPluginManager = pPluginManager;
    }
    ~NFIModule(){}
    virtual bool Execute() = 0;
    virtual bool Init() {return true;}
    virtual bool AfterInit() {return true;}
    virtual bool Shut() {return true;}
    std::string strName;
protected:
   NFIPluginManager* pPluginManager = nullptr;
};
#endif //DEBUG_DEAD_LOCK_NFIMODULE_H
