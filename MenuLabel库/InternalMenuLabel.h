
#ifndef INTERNALMENULABEL

	#define INTERNALMENULABEL

	#include <stdint.h>
	#include <stdbool.h>
	#include <string.h>
	#include <stdio.h>
	#include "Utf8.h"
	#include "Bytebit.h"

	struct InternalMenuLabelIntact {
		Utf8* title;  //在任何平台任何编译器中只占用1个字节
		void* storage;
		struct InternalMenuLabelIntact* branch;
		struct InternalMenuLabelIntact* seed;
	};
	
	typedef struct InternalMenuLabelIntact InternalMenuLabelIntact;
	typedef InternalMenuLabelIntact* PointMenuLabel;
	typedef PointMenuLabel* MenuLabel;

	//MenuLabelIntact内存空间分配
	MenuLabel MenuLabelCreateMemoryIntact(void);

	//MenuLabel内存释放
	MenuLabel MenuLabelFree(MenuLabel PointMenuLabel);

	//MenuLabel*内存释放
	MenuLabel MenuLabelPointFree(MenuLabel* PointMenuLabel);

	//Size内存释放
	size_t* SizeFree(size_t* PointSize);

	//动态Label内存释放
	Utf8* LabelFree(Utf8* Label);

	//MenuLabelTraversal函数的依赖函数
	//扩建字符片段存储指针的函数
	MenuLabel* MenuLabelPointCreateMemory(MenuLabel* ppMenuLabel, size_t memorySize);

	//MenuLabelTraversal函数的依赖函数
	//创建动态的距离存储数组
	size_t* MenuLabelPointSizeCreateMemory(size_t* PointSize, size_t memorySize);

	//动态Label内存分配
	Utf8* LabelCreate(Utf8* Label, Utf8* NewLabel);

	//动态Label回归函数
	size_t LabelRegression(Utf8* Label, size_t RegressionLenght);

	//遍历指定的MenuLabel标签
	bool MenuLabelTraversal(MenuLabel VarMenuLabel, Utf8* Label);

	//初始化MenuLabel
	MenuLabel CreateMenuLabel(Utf8* NewTitle);

	//检查文件名是否符合文件名规则要求
	bool MenuLabelCheckTitle(const Utf8* Title);

	//MenuLabelGetDependent函数的依赖函数
	//扩建字符片段存储指针的函数
	Utf8** Utf8CreateMemory(Utf8** ppUtf8, size_t memorySize);

	//Label解析
	//传入路径，返回从属标签的MenuLabel地址
	MenuLabel MenuLabelGetDependent(MenuLabel VarMenuLabel, Utf8* Label);

	//创建枝标签
	bool MenuLabelCreateBranch(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle);

	//创建子标签
	bool MenuLabelCreateSeed(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle);

	//获取子标签地址
	MenuLabel MenuLabelGetSeed(MenuLabel VarMenuLabel, Utf8* Label);

	//获取枝标签地址
	MenuLabel MenuLabelGetBranch(MenuLabel VarMenuLabel, Utf8* Label);

	//获取数据地址
	void* MenuLabelGetStorage(MenuLabel VarMenuLabel, Utf8* Label);

	//获取标题
	Utf8* MenuLabelGetTitle(MenuLabel VarMenuLabel, Utf8* Label);

	//修改标题
	bool  MenuLabelAlterTitle(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle);

	//修改数据
	bool  MenuLabelAlterStorage(MenuLabel VarMenuLabel, Utf8* Label, void* NewStorage);

	//修改枝标签
	bool MenuLabelAlterBranch(MenuLabel VarMenuLabel, Utf8* Label, MenuLabel* NewBranch);

	//修改子标签
	bool MenuLabelAlterSeed(MenuLabel VarMenuLabel, Utf8* Label, MenuLabel* NewSeed);

	//修改标题，数据，枝标签，子标签
	bool MenuLabelAlterAll(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle, void* NewStorage, MenuLabel* NewBranch, MenuLabel* NewSeed);


#endif

