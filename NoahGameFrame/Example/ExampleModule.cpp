//
// Created by Administrator on 2020/6/28.
//

#include "ExampleModule.h"
bool ExampleModule::Init() {
    m_pThreadPoolModule = pPluginManager->FindModule<NFIThreadPoolModule>();
    return true;
}
bool ExampleModule::AfterInit() {
    m_pThreadPoolModule->DoAsyncTask<ExampleModule>(NFGUID(), "", this, &ExampleModule::test);
    return true;
}
bool ExampleModule::Execute() {
    return true;
}
void ExampleModule::test(NFThreadTask& task) {
 std::cout << "hello test!!!" << std::endl;
}