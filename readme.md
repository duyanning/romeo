juliet 朱丽叶,这是Java编写的服务器,是个IntelliJ IDEA项目.

diagram 这是个Qt项目,从一本Qt教材上找的GUI程序,适合改造为使用罗密欧框架.

(deleted)QtClient 一个Qt项目,用于开发罗密欧框架. 自从有了diagram,这个就废弃了.里面的东西过时了.

Enclave1 飞地dll,目前还没有什么内容.因为飞地提供什么接口还不好确定.

SampleEnclave 从C:\Program Files (x86)\Intel\IntelSGXSDK\src复制来的例子(C盘权限限制,不好就地用visual studio打开)







# Qt项目diagram

如果是用vs中的qt插件直接打开diagram.pro,产生的vc项目就是x86的,怎么增加x64的内容,比较费事.

我选择从qt的64位命令行下通过 qmake -tp vc diagram.pro 生成vc的项目文件.

(如果之前已经有.sln跟.vcxproj就删掉)

不过这样产生的vc项目中的属性中看不到Qt相关的选项.







# Qt项目中使用飞地动态库

将飞地动态库作为一个project与Qt project放在同一个solution下,这样右键单击Qt project才可以选择import Enclave.



Enclave_u.c的编译会报错,这是因为包含了Qt的头文件.

对Enclave_u.c设置属性,光设置Not Using Precompiled Headers是不够的,还要在C++ > Advanced中将Forced Include File里的东西全部删掉才行.





安装Spectre-mitigated libraries

C:\Program Files (x86)\Intel\IntelSGXSDK\src

1>C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Microsoft\VC\v160\Microsoft.CppBuild.targets(486,5): error MSB8040: Spectre-mitigated libraries are required for this project. Install them from the Visual Studio installer (Individual components tab) for any toolsets and architectures being used. Learn more: https://aka.ms/Ofhn4c

在安装程序的搜索框中输入spectre, 注意别选成mfc跟atl的了. 

选最新版.



# 创建飞地时的错误返回值

## 16388(0x4004)	/* Enclave has no privilege to get launch token */



sgx_create_enclave的第二个参数给1就ok了.

参考:  https://community.intel.com/t5/Intel-Software-Guard-Extensions/What-does-the-error-code-0x4004-mean/td-p/1164027



## 8207(0x200f),     /* Can't open enclave file. */

将

Enclave.signed.dll

改为绝对路径

```
F:\\romeo\\diagram\\x64\\Debug\\Enclave.signed.dll
```

就好了.



