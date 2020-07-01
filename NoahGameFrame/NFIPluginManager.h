//
// Created by Administrator on 2020/6/28.
//

#ifndef DEBUG_DEAD_LOCK_NFIPLUGINMANAGER_H
#define DEBUG_DEAD_LOCK_NFIPLUGINMANAGER_H
#include "NFPlatform.h"
#include <assert.h>
#include <cxxabi.h>
#define FIND_MODULE(className) \
    dynamic_cast<className*>(pPluginManager->FindModule(#className));
class NFIPlugin;
class NFIModule;
class NFIPluginManager;
template<typename DerivedType, typename BaseType>
class TIsDerived
{
public:
    static int AnyFunction(BaseType* base)
    {
        return 1;
    }

    static  char AnyFunction(void* t2)
    {
        return 0;
    }

    enum
    {
        Result = (sizeof(int) == sizeof(AnyFunction((DerivedType*)NULL))),
    };
};


class NFIPluginManager {
public:
    virtual bool Awake() = 0;

    virtual bool Init() = 0;

    virtual bool AfterInit() = 0;

    virtual bool ReadyExecute() = 0;

    virtual bool Execute() = 0;

    virtual bool BeforeShut() = 0;

    virtual bool Shut() = 0;

    virtual bool OnReloadPlugin() = 0;

    virtual bool Registed(NFIPlugin *pPlugin) = 0;

    virtual bool UnRegisted(NFIPlugin *pPlugin) = 0;

    virtual bool AddModule(const std::string &name, NFIModule *pModule) = 0;

    virtual void RemoveModule(const std::string &strModuleName) = 0;

    virtual NFIModule *FindModule(const std::string &strModuleName) = 0;

    template<typename T>
    T *FindModule() {
        // typeid
        const std::type_info  &ti = typeid(T);
        char* realname = abi::__cxa_demangle(ti.name(), 0, 0, nullptr);
        NFIModule *pLogicModule = FindModule(realname);
        if (pLogicModule) {
            if (!TIsDerived<T, NFIModule>::Result) {
                return NULL;
            }
            //TODO OSX上dynamic_cast返回了NULL
#if NF_PLATFORM == NF_PLATFORM_APPLE
            T *pT = (T *) pLogicModule;
#else
            T* pT = dynamic_cast<T*>(pLogicModule);
#endif
            assert(NULL != pT);

            return pT;
        }
        assert(NULL);
        return NULL;
    }

};
#endif //DEBUG_DEAD_LOCK_NFIPLUGINMANAGER_H
