//
// Created by Administrator on 2020/6/26.
//
#include "NFPluginManager.h"
NFPluginManager::NFPluginManager()
{

}
NFPluginManager::~NFPluginManager()
{

}
bool NFPluginManager::Init()
{
    for (auto it: mPlugins){
        it.second->Init();
    }
    return true;
}
bool NFPluginManager::AfterInit()
{
    return true;
}
bool NFPluginManager::ReadyExecute() {
    return true;
}
bool NFPluginManager::Execute()
{
    for (auto it: mPlugins){
        it.second->Execute();
    }
    return true;
}
bool NFPluginManager::Awake()
{
    return true;
}
bool NFPluginManager::BeforeShut() {
    return  true;
}
bool NFPluginManager::Shut() {
    return true;
}
bool NFPluginManager::OnReloadPlugin() {
    return true;
}
bool NFPluginManager::Registed(NFIPlugin *pPlugin) {
    mPlugins[pPlugin->GetPluginName()] = pPlugin;
    pPlugin->Install();
    return true;
}
bool NFPluginManager::UnRegisted(NFIPlugin *pPlugin) {
    return true;
}

bool NFPluginManager::AddModule(const std::string &name, NFIModule *pModule) {
    if (!FindModule(name)){
       mModules.insert(std::map<std::string,NFIModule*>::value_type(name, pModule));
    }
    return true;
}
void NFPluginManager::RemoveModule(const std::string &strModuleName) {
    if (FindModule(strModuleName)){
        mModules.erase(strModuleName);
    }
}
NFIModule * NFPluginManager::FindModule(const std::string &strModuleName) {
    auto it = mModules.find(strModuleName);
    if (it != mModules.end()){
        return it->second;
    }
    return nullptr;
}
