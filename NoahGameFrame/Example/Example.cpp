//
// Created by Administrator on 2020/6/28.
//

#include "Example.h"
#include "ExampleModule.h"
Example::Example(NFIPluginManager* pPluginManager):NFIPlugin(pPluginManager){

}
Example::~Example() {

}
bool Example::Install() {
    REGISTER_MODULE(pPluginManager,ExampleModule, ExampleModule);
   return true;
}
bool Example::UnInstall() {
   return true;
}
const std::string Example::GetPluginName() {
    return GET_CLASS_NAME(Example) ;
}