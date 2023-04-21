# MenuLabel 多模态语言管理系统



## 创作思想（创作背景、目的和意义）
在开发 MenuLabel 之前，我进行了充分的市场调研，并发现市场上的大部分软件存在一个核心问题：在切换语言后必须重启软件才能完成语言切换。另外，一些开发者在开发小软件时，没有适合的语言管理系统进行语言管理，只能使用字符串面量来展示软件中的信息。然而，这种方法在修改信息后需要重新编译程序，而且还会降低源代码的可阅读性和可移植性。

MenuLabel 多模态语言管理系统是一个基于 C 语言的第三方库，主要解决软件在切换语言后必须重启的问题，同时为小工具开发者提供了简单、灵活、高效的低成本语言管理系统，以进行语言管理。



## 创作过程（运用了哪些技术或技巧完成主题创作，哪些是得意之处）
基础框架:树形结构的使用

内存管理模块：MenuLabel中使用大量的指针，该模块用于管理程序中的指针，以及内存的分配和释放等操作，有效避免内存泄漏和内存溢出等常见问题。

索引机制：通过索引函数，建立标签库中从属标签的索引，无需从标签库中的根标签向下查找，直接使用索引变量进行查找，有效的提升了程序的灵活性和实用性。

多模态存储：MenuLabel支持存储文字、图片、语音、视频等格式的信息，因为在实际的开发中，软件中的信息不一定只有文本信息，例如：必须使用图片进行展示的特殊字符，以及用户在使用软件时点击按钮
可能会发出提示音等等，多模态的设计使得MenuLabel支持任何格式的信息。



## 制作用软件及运行环境
C语言集成开发环境：Visual Studio 2022专业版

操作系统：Windows 10专业版

运行终端：Windows 10专业版的命令提示符



## 其他说明（需要特别说明的问题）
在这个项目中，MenuLabel的标签存储名称采用了UTF8字符编码格式。为了保证程序能够正确运行，使用该C语言库的编译器和终端必须设置为UTF8字符编码格式。如果不进行设置，可能会导致乱码等问题。

需要注意的是，这个项目的作品并不是一个可执行的exe文件，而是一个C语言库。在文件夹中，标有“xxxxxxx（作品成果）”的文件夹是这个作品的成果。

版本迭代（正在设计的模块）：

字符编码自适应模块：该模块支持开发者使用任何字符编码，开发者无需再考虑字符编码问题。

语言文件客户端：开发者使用该客户端可以快速生成语言文件。

语言文件导入模块：该模块支持开发者导入语言文件。

优势（语言文件客户端和语言文件导入模块结合使用）

1.学习成本低，开发者和软件翻译员，只需要简单的了解，即可快速使用MenuLabel

2.软件翻译员无需阅读软件源代码即可快速完成软件的翻译（使用语言文件客户端制作其他语言的语言文件）

3.用户下载语言文件后，使用软件中的一键导入功能，即可在软件中使用该语言




# MenuLabel 使用文档



## 文档说明

注：该项目的目标群体为具有一定C语言开发能力的程序员，不是不具备计算机知识的人群

本文档为使用文档，而不是MenuLabel开发文档，介绍了MenuLabel中的常用函数，以及LabelPath等参数的使用方法，源文件中各个函数中都有详细的注释，在标识符的命名中也使用了统一的标准。

建议先看演示讲解视频，再看本说明文档。



## 源文件部分

在编写C语言代码之前请先确认包含头文件，以及4个头文件和3个源文件都存在。

7个文件分别为

MenuLabel.h

InternalMenuLabel.h

MenuLabel.c

Bytebit.c

Bytebit.h

Utf8.c

Utf8.h


包含头文件代码
#include "MenuLabel.h"



## 字符编码说明

设置C语言的编译环境和运行终端均为UTF8字符编码（Windows中的实现）
//UTF8兼容设置
setlocale(LC_ALL, "zh_CN.UTF-8");
SetConsoleOutputCP(CP_UTF8);
SetConsoleCP(CP_UTF8);



## 函数使用说明

创建MenuLabel变量。
MenuLabel Chinese;

//使用函数进行初始化。

Chinese = CreateMenuLabel(u8"开始");  

//必须提供“根标签”的标签名称，u8表示字符串使用UTF8编码

//返回NULL表示初始化失败，其他情况为成功。

MenuLabel Chinese= CreateMenuLabel(u8"开始");  //也可以选在创建变量时初始化。

MenuLabelAlterTitle(Chinese,””,”新标签名”);//修改标签名称，第二个参数为LabelPath

MenuLabelAlterStorage(Chinese,””,”新信息”);//修改了信息，实际上是存储一个指针

//以上两个函数，成功返回true失败返回false，程序使用了stdbool.h库

MenuLabelGetStorage(Chinese,””);

MenuLabelGetTitle(Chinese,””);

//第二个函数获取标签标题，第一个函数获取数据的首地址，获取失败返回NULL

//创建从属标签示例

MenuLabel Chinese = CreateMenuLabel(u8"开始");

MenuLabelCreateSeed(Chinese, u8"", u8"1子标签");//创建从属子标签

MenuLabelCreateSeed(Chinese, u8"|1子标签", u8"2子标签");//创建从属子标签

MenuLabelCreateSeed(Chinese, u8"|2子标签", u8"3子标签");//创建从属子标签


//获取从属子标签的标题

MenuLabelGetTitle (Chinese,“|1子标签”);//第一个

MenuLabelGetTitle (Chinese,“|1子标签|2子标签”);//第二个

MenuLabelGetTitle (Chinese,“|1子标签|2子标签|3子标签”);//第三个



//从属枝标签

MenuLabel Chinese = CreateMenuLabel(u8"开始");

MenuLabelCreateBranch (Chinese, u8"", u8"1枝标签");//创建从属枝标签

MenuLabelCreateBranch (Chinese, u8"|1枝标签", u8"2枝标签");//创建从属枝标签

MenuLabelCreateBranch (Chinese, u8"|2枝标签", u8"3枝标签");//创建从属枝标签


//获取从属子标签的标题

MenuLabelGetTitle (Chinese,“>1枝标签”);//第一个

MenuLabelGetTitle (Chinese,“>1枝标签>2枝标签”);//第二个

MenuLabelGetTitle (Chinese,“>1枝标签>2枝标签>3枝标签”);//第三个

//子标签和枝标签的交叉使用

MenuLabel Chinese = CreateMenuLabel(u8"开始");

MenuLabelCreateBranch (Chinese, u8"", u8"1枝标签");//创建从属枝标签

MenuLabelCreateSeed (Chinese, u8">1枝标签", u8"1子标签");//创建子属枝标签

MenuLabelCreateSeed (Chinese, u8">1枝标签|1子标签", u8"2子标签");//创建子属枝标签

MenuLabelCreateBranch (Chinese, u8">1枝标签|1子标签|2子标签", u8"2枝标签");//创建从属枝标签



//获取标签“2枝标签”的标题

MenuLabelGetTitle(Chinese,” ">1枝标签|1子标签|2子标签>2枝标签”);

LabelPath（标签路径）的使用

“”（空字符串）,”|”,”>”，这三个都表示标签本身，不回去获取子标签的内容

“|子标签”   //获取当前标签的子标签    这里面的“子标签”三个字表示的是标签的名称

“>枝标签”    //获取当前标签的枝标签

//   |  表示获取子标签，后面跟上子标签的名称，不能有空格

“|1子标签|2子标签|3子标签” //获取根标签的 子标签“1子标签” 的子标签“2子标签”的子标签“3子标签”   枝标签也是同理

//混合标签路径

">1枝标签|1子标签|2子标签>2枝标签"  //获取根标签的枝标签“1枝标签” 的 子标签 “1子标签” 的子标签 “2子标签” 的枝标签 “2枝标签”

//更复杂的LabelPath（标签路径）的使用，可以看MenuLabel 演示工具的源代码，在 作品成果 文件夹 的 MenuLabel 演示工具 （visual studio 项目源代码） 文件夹中。

//多模态的实现请观看演示讲解视频

//获取索引的函数MenuLabelGetDependent

例如：

MenuLabel Chinese = CreateMenuLabel("开始"); //创建中文标签库

MenuLabelCreateBranch(Chinese, "", "按钮"); //创建启动标签

MenuLabelCreateSeed(Chinese, ">按钮", "确认"); //创建启动标签

MenuLabelAlterStorage(Chinese, ">按钮|确认", (void*)"确认"); //设置标签的信息

//这里是建立索引

MenuLabel button = MenuLabelGetDependent(Chinese,">按钮"); //获取从属标签 按钮

//这两个获取到的信息一样

MenuLabelGetStorage(Chinese, ">按钮|确认"); 

MenuLabelGetStorage(button, "|确认");

//特殊的结构设计，可以通过LabelPath获取从属标签的信息，从而不需要在从根标签一级一级向下获取


//-------------------------------

下面是一个简单的完成程序示范：

因为MenuTable系统标签中使用的标题是Utf8进行存储，所以保证设置C程序编译和终端的字符编码格式为Utf8，否则可能会出现乱码等未定义的结果。

//程序
#include <stdio.h>

#include <locale.h>

#include <windows.h>  

#include "Utf8.h"

#include "MenuLabel.h"

int main(void) {

	
	setlocale(LC_ALL, "zh_CN.UTF-8");
	
	SetConsoleOutputCP(CP_UTF8);
	
	SetConsoleCP(CP_UTF8);
	
	
	MenuLabel Chinese = CreateMenuLabel(u8"开始");
	MenuLabelCreateBranch(Chinese, u8"", u8"欢迎");
	MenuLabelAlterStorage(Chinese, u8">欢迎", (void*)u8"你好！");
	MenuLabel English = CreateMenuLabel(u8"开始");
	MenuLabelCreateBranch(English, u8"", u8"欢迎");
	MenuLabelAlterStorage(English, u8">欢迎", (void*)u8"Hello！");
	MenuLabel Language = Chinese;  //用户设置为中文
	printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">欢迎")); 
	Language = English;  //用户设置为英文
	printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">欢迎")); 
	return 0;
}

输出结果:

你好！

Hello！

