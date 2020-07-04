//
// Created by Administrator on 2020/6/28.
//

#ifndef DEBUG_DEAD_LOCK_NFIPLUGINMANAGER_H
#define DEBUG_DEAD_LOCK_NFIPLUGINMANAGER_H
#include "NFPlatform.h"
#include <assert.h>
#if NF_PLATFORM == NF_PLATFORM_WIN
#else
#include <cxxabi.h>
#endif
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
        NFIModule *pLogicModule = nullptr;
#if NF_PLATFORM == NF_PLATFORM_WIN
        pLogicModule = FindModule(covert_class(typeid(T).name()));
#else
        const std::type_info  &ti = typeid(T);
        int status = -1;
        char* realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);
        if (0 == status) {
            pLogicModule = FindModule(realname);
            free(realname);
        }else{
            assert(NULL);
            return NULL;
        }
#endif
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

private:
    std::string covert_class(std::string str, std::string match, bool& isMatch) {
        std::string::size_type pos = str.find(match);
        if (pos != std::string::npos) {
            isMatch = true;
            return str.substr(pos + match.length(), str.length() - match.length());
        }
        isMatch = false;
        return str;
    }
    std::string covert_class(const std::string &str) {
        bool isMatch = false;
        std::string really_name = covert_class(str, "class ", isMatch);
        if (!isMatch) {
            return covert_class(str, "struct ", isMatch);
        } else {
            return really_name;
        }
    }
};
#endif //DEBUG_DEAD_LOCK_NFIPLUGINMANAGER_H
