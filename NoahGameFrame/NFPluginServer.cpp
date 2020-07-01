//
// Created by Administrator on 2020/6/26.
//

#include "NFPluginServer.h"
NFPluginServer::NFPluginServer()
{

}
NFPluginServer::~NFPluginServer()
{
    Final();
}
void NFPluginServer::Init()
{
    pPlugManager = NF_SHARED_PTR<NFIPluginManager>(NF_NEW NFPluginManager());
    if (mRegisterPlugin){
        mRegisterPlugin.operator()(pPlugManager.get());
    }
    pPlugManager->Awake();
    pPlugManager->Init();
    pPlugManager->AfterInit();
    pPlugManager->ReadyExecute();
    return ;
}
void NFPluginServer::Execute()
{
   pPlugManager->Execute();
   return;
}
void NFPluginServer::Final()
{
   return;
}
void NFPluginServer::SetRegisterPlugin(std::function<void (NFIPluginManager *)> fun) {
    mRegisterPlugin = fun;
}