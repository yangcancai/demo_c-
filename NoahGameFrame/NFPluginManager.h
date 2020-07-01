//
// Created by Administrator on 2020/6/26.
//

#ifndef DEBUG_DEAD_LOCK_NFPLUGINMANAGER_H
#define DEBUG_DEAD_LOCK_NFPLUGINMANAGER_H
#include "NFIPlugin.h"
#include "NFIPluginManager.h"
class NFPluginManager : public NFIPluginManager
{
public:
    NFPluginManager();
    ~NFPluginManager();
    bool Awake() override ;
    bool Init() override ;
    bool AfterInit() override ;
    bool ReadyExecute() override ;
    bool Execute() override ;
    bool BeforeShut() override ;
    bool Shut() override ;
    bool OnReloadPlugin() override ;
    bool Registed(NFIPlugin* pPlugin) override ;
    bool UnRegisted(NFIPlugin* pPlugin) override ;
    bool AddModule(const std::string& name, NFIModule* pModule) override ;
    void RemoveModule(const std::string &strModuleName) override;
    NFIModule * FindModule(const std::string &strModuleName) override;
private:
    std::map<std::string, NFIPlugin*> mPlugins;
    std::map<std::string, NFIModule*> mModules;
};
#endif //DEBUG_DEAD_LOCK_NFPLUGINMANAGER_H
