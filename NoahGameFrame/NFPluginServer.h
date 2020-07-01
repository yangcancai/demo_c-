//
// Created by Administrator on 2020/6/26.
//

#ifndef DEBUG_DEAD_LOCK_NFPLUGINSERVER_H
#define DEBUG_DEAD_LOCK_NFPLUGINSERVER_H
#include "NFPluginManager.h"
class NFPluginServer {
public:
    NFPluginServer();
    ~NFPluginServer();
    void Init();
    void Execute();
    void Final();
    void SetRegisterPlugin(std::function<void (NFIPluginManager*)> fun);

private:
    NF_SHARED_PTR<NFIPluginManager> pPlugManager;
    std::function<void (NFIPluginManager*)> mRegisterPlugin = nullptr;
};


#endif //DEBUG_DEAD_LOCK_NFPLUGINSERVER_H
