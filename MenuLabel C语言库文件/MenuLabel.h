#ifndef MENULABEL

	#define MENULABEL

	#include "Utf8.h"

	struct InternalMenuLabelIntact {
		Utf8* title;  //在任何平台任何编译器中只占用1个字节
		void* storage;
		struct InternalMenuLabelIntact* branch;
		struct InternalMenuLabelIntact* seed;
	};

	typedef struct InternalMenuLabelIntact InternalMenuLabelIntact;
	typedef InternalMenuLabelIntact* PointMenuLabel;
	typedef PointMenuLabel* MenuLabel;

	//初始化MenuLabel
	MenuLabel CreateMenuLabel(Utf8* NewTitle);

	//Label解析
	//传入路径，返回从属标签的MenuLabel地址
	MenuLabel MenuLabelGetDependent(MenuLabel VarMenuLabel, Utf8* Label);

	//遍历指定的MenuLabel标签
	bool MenuLabelTraversal(MenuLabel VarMenuLabel, Utf8* Label);

	//创建枝标签
	bool MenuLabelCreateBranch(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle);

	//创建子标签
	bool MenuLabelCreateSeed(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle);

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

#endif // !MENUTAB
