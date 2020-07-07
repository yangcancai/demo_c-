//
// Created by Administrator on 2020/7/1.
//

#ifndef DEBUG_DEAD_LOCK_NFKERNELPLUGIN_H
#define DEBUG_DEAD_LOCK_NFKERNELPLUGIN_H

#include "NFIPlugin.h"
#include "NFIPluginManager.h"
class NFKernelPlugin : public NFIPlugin{
public:
    NFKernelPlugin(NFIPluginManager* pPluginManager);
    ~NFKernelPlugin();
    virtual const std::string GetPluginName() override;
    virtual bool Install() override;
    virtual bool UnInstall() override;

};
#endif //DEBUG_DEAD_LOCK_NFKERNELPLUGIN_H
