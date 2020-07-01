//
// Created by Administrator on 2020/6/28.
//

#include "ExampleModule.h"
bool ExampleModule::Init() {
    m_pThreadPoolModule = pPluginManager->FindModule<NFIThreadPoolModule>();
    return true;
}
bool ExampleModule::Execute() {
    ExampleModule* module = this;
   m_pThreadPoolModule->DoAsyncTask(NFGUID(), "",
           [&module](NFThreadTask &task) -> void {
                                                       {
                                                           module->test(task);
                                                       }
                                                   });
    return true;
}
void ExampleModule::test(NFThreadTask& task) {
 std::cout << "hello test!!!" << std::endl;
}