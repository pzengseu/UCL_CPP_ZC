# UCL动态链接库使用方法
## 头文件及动态链接库
头文件及动态链接库均存在ucl.tgz中
```
tar -zxf ucl.tgz 
cp -R ucl /usr/share
```
## clion工程配置
新建clion工程，在clion工程的CMakeLists.txt文件最后增加：
```
include_directories(
        /usr/share/ucl/include
)
target_link_libraries(hellotest /usr/share/ucl/lib/libUCL_CPP_ZC.so)
target_link_libraries(hellotest ssl crypto)
```
 解压ct.tgz将code目录和tools目录复制到工程根目录下。
示例代码如下：
```
#include "test/test.h"

int main() {
    testCommand();
    return 0;
}
```

## 头文件及动态链接库生成（如已生成忽略此部分）
```
mkdir build
cd build
cmake ..
make 
make install
```