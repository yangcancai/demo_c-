//
// Created by Administrator on 2020/6/28.
//

#ifndef DEBUG_DEAD_LOCK_EXAMPLE_H
#define DEBUG_DEAD_LOCK_EXAMPLE_H

#include "NFIPlugin.h"
#include "NFIPluginManager.h"
class Example : public NFIPlugin
{
public:
    Example(NFIPluginManager* pPluginManager);
    ~Example();
    virtual const std::string GetPluginName() override ;
    virtual bool Install() override;
    virtual bool UnInstall() override ;
};


#endif //DEBUG_DEAD_LOCK_EXAMPLE_H
