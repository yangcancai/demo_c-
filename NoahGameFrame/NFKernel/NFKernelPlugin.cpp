//
// Created by Administrator on 2020/7/1.
//

#include "NFKernelPlugin.h"
#include "../ThreadPool/NFThreadPoolModule.h"
NFKernelPlugin::NFKernelPlugin(NFIPluginManager *pPluginManager):NFIPlugin(pPluginManager) {

}
NFKernelPlugin::~NFKernelPlugin() {

}
const std::string NFKernelPlugin::GetPluginName() {
    return GET_CLASS_NAME(NFKernelPlugin);
}
bool NFKernelPlugin::Install() {
    REGISTER_MODULE(pPluginManager, NFIThreadPoolModule, NFThreadPoolModule);
    return true;
}
bool NFKernelPlugin::UnInstall() {
    return true;
}
