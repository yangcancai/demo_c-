//
// Created by Administrator on 2020/6/26.
//

#include "NFPluginServer.h"
#include "Example/Example.h"
#include "NFKernel/NFKernelPlugin.h"
void RegisterPlugin(NFIPluginManager* pPluginManager){
    REGISTER_PLUGIN(pPluginManager, NFKernelPlugin);
    REGISTER_PLUGIN(pPluginManager, Example);
}
int main()
{
   NF_SHARED_PTR<NFPluginServer> server = NF_SHARED_PTR<NFPluginServer>(NF_NEW NFPluginServer());
    server->SetRegisterPlugin(RegisterPlugin);
   server->Init();
   while (true){
        std::this_thread::sleep_for(std::chrono::milliseconds (1));
       server->Execute();
   }
   return 0;
}
