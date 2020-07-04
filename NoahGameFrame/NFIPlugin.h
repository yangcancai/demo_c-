//
// Created by Administrator on 2020/6/28.
//

#ifndef DEBUG_DEAD_LOCK_NFIPLUGIN_H
#define DEBUG_DEAD_LOCK_NFIPLUGIN_H
#include "NFIModule.h"
#include <iostream>
#include <map>
#include <assert.h>

#define REGISTER_MODULE(pManager, classBaseName, className)  \
	assert((TIsDerived<classBaseName, NFIModule>::Result));	\
	assert((TIsDerived<className, classBaseName>::Result));	\
	NFIModule* pRegisterModule##className= new className(pManager); \
    pRegisterModule##className->strName = (#className); \
    pManager->AddModule( #classBaseName, pRegisterModule##className );\
    this->AddElement( #classBaseName, pRegisterModule##className );

#define REGISTER_PLUGIN(pPluginManager, className)\
    NFIPlugin* pPlugin##className = NF_NEW className(pPluginManager);\
    pPluginManager->Registed(pPlugin##className);
class NFIPlugin : public NFIModule{
public:
    NFIPlugin(NFIPluginManager* pPluginManager):NFIModule(pPluginManager){
    }
    ~NFIPlugin(){}
    virtual const std::string GetPluginName() = 0;
    virtual bool Install() = 0;
    virtual bool UnInstall() = 0;
    virtual bool Init(){
        for (auto it: mModules){
            NFIModule* pModule = it.second;
            pModule->Init();
        }
       return true;
    }
    virtual bool AfterInit(){
        for (auto it: mModules){
            NFIModule* pModule = it.second;
            pModule->AfterInit();
        }
        return true;
    }
    virtual bool Execute(){
        for (auto it: mModules){
            NFIModule* pModule = it.second;
            pModule->Execute();
        }
        return true;
    }
    virtual bool Shut(){return true;}
    virtual void AddElement(const std::string& name, NFIModule* pModule){
        mModules[name] = pModule;
    };

private:
    std::map<std::string, NFIModule*> mModules;
};
#endif //DEBUG_DEAD_LOCK_NFIPLUGIN_H
