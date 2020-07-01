//
// Created by Administrator on 2020/6/24.
//
#include <iostream>
using namespace std;
#define D_STR(str) #str
#define D_PRINT(i, format) \
        printf(D_STR(i) " = %" D_STR(format) "\n", i);
#define D_PRINT1(i) \
        D_PRINT(x##i, d)

class abc{
public:
    template<typename T>
    const std::string FindModule(){
                   return D_STR(T);
    }
};
int main(){
    abc* p= new abc();
    cout << p->FindModule<abc>() << endl;
    int i = 20;
    float f = 30.12;
    char *str = "hello";
    D_PRINT(i, d);// printf("i=%d",i)
    D_PRINT(f, f);// printf("f=%f",f)
    D_PRINT(str, s);// printf("str=%s",str)
    int x1=1,x2=2,x3=3;
    D_PRINT1(1);// D_PRINT(x1,d) -> printf("x1=%d",x1)
    D_PRINT1(2);// D_PRINT(x2,d) -> printf("x2=%d",x2)
    D_PRINT1(3);// D_PRINT(x3,d) -> printf("x3=%d",x3)
    return 0;
}