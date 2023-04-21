#include "InternalMenuLabel.h"

//MenuLabelIntact内存空间分配
MenuLabel MenuLabelCreateMemoryIntact(void) {

	MenuLabel NewVarMenuLabel = (MenuLabel)malloc(sizeof(InternalMenuLabelIntact));

	return NewVarMenuLabel;
}


//MenuLabel内存释放
MenuLabel MenuLabelFree(MenuLabel PointMenuLabel) {
	free(PointMenuLabel);
	return NULL;
}

//MenuLabel*内存释放
MenuLabel MenuLabelPointFree(MenuLabel* PointMenuLabel) {
	free(PointMenuLabel);
	return NULL;
}

//size_t*内存释放
size_t* SizeFree(size_t* PointSize) {
	free(PointSize);
	return NULL;
}

//*内存释放
Utf8* LabelFree(Utf8* Label) {
	free(Label);
	return NULL;
}


//MenuLabelTraversal函数的依赖函数
//扩建字符片段存储指针的函数
MenuLabel* MenuLabelPointCreateMemory(MenuLabel* ppMenuLabel, size_t memorySize) {

	if (ppMenuLabel == NULL) {  //没有分配内存空间
		ppMenuLabel = (MenuLabel*)malloc(memorySize);  //第一次分配内存空间
	}
	else {
		MenuLabel* TmpMenuLabel = (MenuLabel*)realloc(ppMenuLabel, memorySize); //扩展内存空间
		if (TmpMenuLabel == NULL) {  //扩展失败

			//此函数会返回NULL，这里释放存放到ppMenuLabel无所谓 
			ppMenuLabel = MenuLabelPointFree(ppMenuLabel);//释放
			//MenuLabelPointFree(ppMenuLabel);   或者注释这一条
		}
		ppMenuLabel = TmpMenuLabel;  //如果失败，设置为NULL，如果成功设置为成功的地址
	}

	return ppMenuLabel;
}

//MenuLabelTraversal函数的依赖函数
//创建动态的距离存储数组
size_t* MenuLabelPointSizeCreateMemory(size_t* PointSize, size_t memorySize) {

	if (PointSize == NULL) {  //没有分配内存空间
		PointSize = (size_t*)malloc(memorySize);  //第一次分配内存空间
	}
	else {
		size_t* TmpSize = (size_t*)realloc(PointSize, memorySize); //扩展内存空间
		if (TmpSize == NULL) {  //扩展失败

			//此函数会返回NULL，这里释放存放到PointSize无所谓 
			PointSize = SizeFree(PointSize);//释放
			//MenuLabelPointFree(PointSize);   或者注释这一条
		}
		PointSize = TmpSize;  //如果失败，设置为NULL，如果成功设置为成功的地址
	}

	return PointSize;
}

//动态Label内存分配
Utf8* LabelCreate(Utf8* Label,Utf8* NewLabel) {

	size_t NewLabelLenght = strlen(NewLabel);

	if (NewLabel != NULL && NewLabelLenght >0) {

		size_t LabelLenght;

		if (Label == NULL) {  //没有分配内存空间

			Label = (Utf8*)malloc(NewLabelLenght+1);  //第一次分配内存空间

			if (Label != NULL) {
				*Label = '\0';  //设置该字符串的结尾
				LabelLenght = 0; //设置字符串长度
			}

		}
		else {//重新分配内存空间

			LabelLenght = strlen(Label);

			Utf8* TmpLabel = (Utf8*)realloc(Label, LabelLenght + NewLabelLenght + 1); //扩展内存空间
			if (TmpLabel == NULL) {  //扩展失败
				
				//此函数会返回NULL，这里释放存放到Label无所谓 
				Label = LabelFree(Label);//释放
				//LabelFree(Label);   或者注释这一条
			}
			Label = TmpLabel;  //如果失败，设置为NULL，如果成功设置为成功的地址
		}

		if (Label != NULL) {

			Label = Utf8Cat(Label, NewLabel);

		}
	}

	return Label;
}

//动态Label回归函数
size_t LabelRegression(Utf8* Label, size_t RegressionLenght) {

	
	size_t RemoveByte = 0;//删除的字节数

	size_t LabelLenght = strlen(Label) - 1, OldLabelLenght = LabelLenght;

	if (Label != NULL && RegressionLenght != 0) {

		
		for (size_t i = 0; i < RegressionLenght && LabelLenght >= 0; i++) {

			while (Label[LabelLenght] != ':' && LabelLenght >= 0) {
				LabelLenght--;
			}

			//删除_Branch:
			if (Label[LabelLenght - 1] == 'h') {
				LabelLenght -= 8;
			}
			else {//删除_Seed:
				LabelLenght -= 6;
			}

		}

		//成功的删除了
		if (LabelLenght >= 0) {
			RemoveByte = OldLabelLenght - LabelLenght;
			Label[LabelLenght + 1] = '\0';
		}
		else {
			RemoveByte = 0;
		}
		
	}

	//返回删除了多少个字节
	return RemoveByte;
}

//遍历指定的MenuLabel标签
bool MenuLabelTraversal(MenuLabel VarMenuLabel, Utf8* Label) {



	bool result = false;

	//解释Label
	VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

	//VarMenuLabel保持不变
	
	//TmpMenuLabel进行变动
	MenuLabel TmpMenuLabel = VarMenuLabel;

	size_t RegressionMenuLabelQuantity = 0;  //等待回归标签节点的个数
	MenuLabel* RegressionMenuLabel = NULL;   //保存等待回归的标签节点
	size_t* RegressionLabel = NULL; //保存 当前标签 距离 回归标签的 长度
	size_t RegressionLabelLenght = 0;


	RegressionMenuLabel = MenuLabelPointCreateMemory(RegressionMenuLabel, (RegressionMenuLabelQuantity + 2) * sizeof(void*)); //分配保存等待回归节点的内存
	RegressionLabel = MenuLabelPointSizeCreateMemory(RegressionLabel, (RegressionMenuLabelQuantity + 2) * sizeof(size_t)); //分配距离内存

	if (VarMenuLabel != NULL && RegressionMenuLabel != NULL && RegressionLabel != NULL) { //内存分配成功
		RegressionMenuLabel[RegressionMenuLabelQuantity] = NULL; //舍弃的一个位置，回归到0，表示遍历完成
		RegressionLabel[RegressionMenuLabelQuantity] = 0; //舍弃的位置
		RegressionMenuLabelQuantity++;

		Utf8* DynamicLabel = NULL;

		while (TmpMenuLabel != NULL && RegressionMenuLabelQuantity > 0) {

			if (TmpMenuLabel != RegressionMenuLabel[RegressionMenuLabelQuantity - 1]) {

				//获取标题
				Utf8* Title = MenuLabelGetTitle(TmpMenuLabel, u8"");

				//获取数据
				void* Storage = MenuLabelGetStorage(TmpMenuLabel, u8"");

				if (TmpMenuLabel != VarMenuLabel) {

					//添加标题
					DynamicLabel = LabelCreate(DynamicLabel, Title);

				}
				//打印标题     这里提提供标题
				printf("Title:%s\n", Title);

				//打印数据	   这里提供数据
				printf("Storage:%p\n", Storage);

				//打印位置     这里提供位置
				printf("Label:%s\n", DynamicLabel);

				//换行
				printf("\n\n");

				//可以向子节点
				if (MenuLabelGetSeed(TmpMenuLabel, u8"") != NULL) {
					DynamicLabel = LabelCreate(DynamicLabel, u8"_Seed:");
				}//不可以向子节点，可以向枝节点
				else if (MenuLabelGetBranch(TmpMenuLabel, u8"") != NULL) {
					DynamicLabel = LabelCreate(DynamicLabel, u8"_Branch:");
				}//不存在的情况，不可以向子节点，不可以向枝节点，不用考虑
			}

			//----------------------------------------------------
			// 
			//该标签节点需要进行回归，前往子节点
			if (MenuLabelGetSeed(TmpMenuLabel, u8"") != NULL && MenuLabelGetBranch(TmpMenuLabel, u8"") != NULL
				&& RegressionMenuLabel[RegressionMenuLabelQuantity - 1] != TmpMenuLabel) {

				//保存该标签节点  保存位置
				RegressionMenuLabel[RegressionMenuLabelQuantity] = TmpMenuLabel;
				RegressionLabel[RegressionMenuLabelQuantity] = RegressionLabelLenght; 
				RegressionMenuLabelQuantity++;

				//重新分配  标签节点 或 回归位置 内存空间
				RegressionMenuLabel = MenuLabelPointCreateMemory(RegressionMenuLabel, (RegressionMenuLabelQuantity + 1) * sizeof(void*));
				RegressionLabel = MenuLabelPointSizeCreateMemory(RegressionLabel, (RegressionMenuLabelQuantity + 1) * sizeof(size_t)); //分配距离内存

				//标签节点 或 回归位置 内存分配失败  
				if (RegressionMenuLabel == NULL || RegressionLabel == NULL) {
					result = false;
					break;
				}

				//去往子节点
				TmpMenuLabel = MenuLabelGetSeed(TmpMenuLabel, u8"");

			}//该标签节点不需要回归，去往子节点
			else if (MenuLabelGetSeed(TmpMenuLabel, u8"") != NULL && MenuLabelGetBranch(TmpMenuLabel, u8"") == NULL) {

				//去往子节点
				TmpMenuLabel = MenuLabelGetSeed(TmpMenuLabel, u8"");


			}//该标签节点已经遍历过，现在进行了回归
			else if (RegressionMenuLabel[RegressionMenuLabelQuantity - 1] == TmpMenuLabel) {

				//计算距离 RegressionLabelLenght - RegressionLabel[RegressionMenuLabelQuantity -1]

				size_t RemoveByte = RegressionLabelLenght - RegressionLabel[RegressionMenuLabelQuantity - 1];
				
				//回归前
				//printf(u8"\n回归前%s\n", DynamicLabel);

				//调用函数，动态Label进行回退
				RemoveByte = LabelRegression(DynamicLabel, RemoveByte);

				//还要缩短存储空间，再次调用LabelCreate函数  时会自动调整内存块大小

				//回归后
				//printf(u8"\n回归后%s\n", DynamicLabel);

				//标签回归了，距离也要缩短
				RegressionLabelLenght = RegressionLabel[RegressionMenuLabelQuantity - 1];

				//删除回归记录  和 距离存储
				--RegressionMenuLabelQuantity;
				RegressionMenuLabel[RegressionMenuLabelQuantity] = NULL;
				RegressionLabel[RegressionMenuLabelQuantity] = 0;

				//重新分配  标签节点 或 回归位置 内存空间
				RegressionMenuLabel = MenuLabelPointCreateMemory(RegressionMenuLabel, (RegressionMenuLabelQuantity + 1) * sizeof(void*));
				RegressionLabel = MenuLabelPointSizeCreateMemory(RegressionLabel, (RegressionMenuLabelQuantity + 1) * sizeof(size_t)); //分配距离内存
				
				//标签节点 或 回归位置 内存分配失败  
				if (RegressionMenuLabel == NULL || RegressionLabel == NULL) {
					result = false;
					break;
				}

				DynamicLabel = LabelCreate(DynamicLabel, u8"_Branch:");

				TmpMenuLabel = MenuLabelGetBranch(TmpMenuLabel, u8"");

			}//该标签节点不需要进行回归，前往枝节点
			else if (MenuLabelGetBranch(TmpMenuLabel, u8"") != NULL) {

				//前往枝节点
				TmpMenuLabel = MenuLabelGetBranch(TmpMenuLabel, u8"");

			}
			else { //该标签节点已经遍历完成，标签节点进行回归

				//回归
				TmpMenuLabel = RegressionMenuLabel[RegressionMenuLabelQuantity - 1];

				//回归到NULL 表示已经遍历结束了，遍历成功了
				if (RegressionMenuLabel[RegressionMenuLabelQuantity - 1] == NULL) {
					result = true;  //成功
				}

				RegressionLabelLenght--; //回归不需要增加
			}

			RegressionLabelLenght++;//距离增加


		}

	}
	else {
		result = false;
	}
	
	//遍历成功，释放内存
	if (result == true) {
		MenuLabelPointFree(RegressionMenuLabel);
		free(RegressionLabel);
	}

	return result;
}

//初始化MenuLabel
MenuLabel CreateMenuLabel(Utf8* NewTitle) {

	//分配内存空间
	MenuLabel NewVarMenuLabel = MenuLabelCreateMemoryIntact();

	if (NewVarMenuLabel != NULL) {

		//插入标题,数据，枝节点，子节点
		if (MenuLabelAlterAll(NewVarMenuLabel, u8"", NewTitle, NULL, NULL, NULL) == false) {
			//插入失败
			NewVarMenuLabel = MenuLabelFree(NewVarMenuLabel);  //释放内存,此函数会返回NULL
		}

	}
	return NewVarMenuLabel;
}

//检查文件名是否符合文件名规则要求
bool MenuLabelCheckTitle(const Utf8* Title) {

	bool result = true;

	uint8_t i, j;
	Utf8 special_chars[9] = { '\\', '/', ':', '*', '?', '\"', '<', '>', '|' }; // 需要检查的特殊字符

	size_t VarUtf8Lenght = Utf8Lenght(Title);//获取标题长度

	if (VarUtf8Lenght > 0 && VarUtf8Lenght <= 100) {//标题长度正确

		for (i = 0; Title[i] != '\0'; i++) {
			for (j = 0; j < 9; j++) {

				if (Title[i] == special_chars[j]) {
					result = false;//文件名不符合要求
					break;
				}

			}
		}
	}
	else {//名称过长

		result = false;

	}

	

	return result;
}

//MenuLabelGetDependent函数的依赖函数
//扩建字符片段存储指针的函数
Utf8** Utf8CreateMemory(Utf8** ppUtf8, size_t memorySize) {

	if (ppUtf8 == NULL) {  //没有分配内存空间
		ppUtf8 = (Utf8**)malloc(memorySize);  //第一次分配内存空间
	}
	else {
		Utf8** TMPppUtf8 = (Utf8**)realloc(ppUtf8, memorySize); //扩展内存空间
		if (TMPppUtf8 == NULL) {  //扩展失败

			size_t FragmentStrQuantity = memorySize / sizeof(void*);

			//字符片段里面存储了 FragmentStrQuantity 个字符串，如果直接释放字符片段
			//里面的字符串就无法访问了，也无法释放，造成了内存泄露

			for (size_t i = 0; i < FragmentStrQuantity;i++) {
				ppUtf8[i] = Utf8Free(ppUtf8[i]);  //是否字符串，返回NULL
			}

			//此函数会返回NULL，这里释放存放到ppUtf8无所谓
			ppUtf8 = Utf8Free(ppUtf8); //释放
			//Utf8Free(ppUtf8);   或者注释这一条
		}
		ppUtf8 = TMPppUtf8;  //如果失败，设置为NULL，如果成功设置为成功的地址
	}

	return ppUtf8;
}

//Label解析
//传入路径，返回从属标签的MenuLabel地址
MenuLabel MenuLabelGetDependent(MenuLabel VarMenuLabel, Utf8* Label) {

	MenuLabel NewMenuLabel = VarMenuLabel; //该变量为返回的从属标签地址，不存在或出现错误返回NULL

	if (VarMenuLabel == NULL) {
		NewMenuLabel = NULL;
	}
	else if (strlen(Label) == 0) {
		;
	}
	else if (*Label != '|' && *Label != '>') {
		NewMenuLabel = NULL;
	}//如果寻求传入的路径不是"|"，就开始寻找，"|"表示本身，直接返回传入的标签
	else if (!(strlen(Label) == 1)) {

		size_t first = 0, end = 0, FragmentStrQuantity = 0; //字符段开始，字符段结束，字符段数量
		Utf8** FragmentStr = NULL;//用于存储 字符片段 的二级指针

		while (Label[end] != '\0') {  //字符串没有到末尾

			//字符串没有遇到 > 和 | 和 末尾
			while (Label[end + 1] != '>' && Label[end + 1] != '|' && Label[end + 1]) {
				end++;
			}

			//将从first开始，创建字符串副本
			Utf8* FragmentStrTmp = Utf8DuplicateLenght(Label + first,end - first + 1);

			//字符串副本创建失败
			if (FragmentStrTmp == NULL) {
				NewMenuLabel = NULL;
				break;
			}

			//判断字符串是否符合要求，首先判断长度
			//判断字符是否大于1个,名称是否符合要求，长度是否小于等于20
			if (end - first >= 1 && MenuLabelCheckTitle(FragmentStrTmp + 1) == 1) {

				// 全部符合要求

				//字符串段数量+1
				FragmentStrQuantity++;

				//扩大字符串
				FragmentStr = Utf8CreateMemory(FragmentStr, FragmentStrQuantity * sizeof(void*));

				//成功
				if (FragmentStr != NULL) {
					FragmentStr[FragmentStrQuantity - 1] = FragmentStrTmp;
					first = end += 1;
				}//失败
				else {
					NewMenuLabel = NULL;
					break;
				}

			}
			else { //字符片段，不符合要求
				NewMenuLabel = NULL;
				break;
			}

		}

		//所欲字符片段提取成功
		if (NewMenuLabel != NULL) {


			//根据字符片段定位从属标签指针
			for (size_t i = 0; i < FragmentStrQuantity; i++) {

				//子标签
				if (FragmentStr[i][0] == '|') {

					//标签的标题一致
					if (Utf8StrContrast(MenuLabelGetTitle(MenuLabelGetSeed(NewMenuLabel,u8""),u8""), FragmentStr[i] + 1)) {
						//获取子标签
						NewMenuLabel = MenuLabelGetSeed(NewMenuLabel,u8"");
					}
					else {
						NewMenuLabel = NULL;
					}

				}//枝标签
				else if (FragmentStr[i][0] == '>') {

					//标签的标题一致
					if (Utf8StrContrast(MenuLabelGetTitle(MenuLabelGetBranch(NewMenuLabel, u8""), u8""), FragmentStr[i] + 1)) {
						//获取枝标签
						NewMenuLabel = MenuLabelGetBranch(NewMenuLabel, u8"");
					}
					else {
						NewMenuLabel = NULL;
					}

				}

				//未获取到
				if (NewMenuLabel == NULL) {

					//释放分配的所有字符片段，并结束
					while (i < FragmentStrQuantity) {
						FragmentStr[i] = Utf8Free(FragmentStr[i]);  //是否字符串，返回NULL
						i++;
					}

					break;
				}
				else {//获取到了，释放当前片段
					FragmentStr[i] = Utf8Free(FragmentStr[i]);
				}

			}
		}

		//释放保存所有字符片段地址的指针
		if (FragmentStr != NULL) {
			FragmentStr = Utf8Free(FragmentStr);
		}

	}

	return NewMenuLabel;
}


//创建枝标签
bool MenuLabelCreateBranch(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle) {

	bool result = false;

	//解释Label进行定位
	VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

	//定位成功
	if (VarMenuLabel != NULL) {

		//创建枝标签
		MenuLabel NewVarMenuLabel = MenuLabelCreateMemoryIntact();

		//枝标签创建成功
		if (NewVarMenuLabel != NULL) {

			//插入标题,数据，枝节点，子节点
			if (MenuLabelAlterAll(NewVarMenuLabel, u8"", NewTitle, NULL, NULL, NULL) == false) {
				//插入失败
				NewVarMenuLabel = MenuLabelFree(NewVarMenuLabel);  //释放内存,此函数会返回NULL
			}
			else {
				//将新的枝标签存储
				MenuLabelAlterBranch(VarMenuLabel, u8"", NewVarMenuLabel);
				result = true;
			}

		}

	}//定位失败，创建失败

	return result;
}

//创建子标签
bool MenuLabelCreateSeed(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle) {

	bool result = false;

	//解释Label进行定位
	VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

	//定位成功
	if (VarMenuLabel != NULL) {

		//创建枝标签
		MenuLabel NewVarMenuLabel = MenuLabelCreateMemoryIntact();

		//枝标签创建成功
		if (NewVarMenuLabel != NULL) {

			//插入标题,数据，枝节点，子节点
			if (MenuLabelAlterAll(NewVarMenuLabel, u8"", NewTitle, NULL, NULL, NULL) == false) {
				//插入失败
				NewVarMenuLabel = MenuLabelFree(NewVarMenuLabel);  //释放内存,此函数会返回NULL
			}
			else {
				//将新的子标签存储
				MenuLabelAlterSeed(VarMenuLabel, u8"", NewVarMenuLabel);
				result = true;
			}

		}

	}//定位失败，创建失败

	return result;
}

//返回当前标签的子标签
MenuLabel MenuLabelGetSeed(MenuLabel VarMenuLabel, Utf8* Label) {

	MenuLabel* Seed;

	VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

	if (VarMenuLabel != NULL) {
		Seed = ((PointMenuLabel)VarMenuLabel)->seed;
	}
	else {
		Seed = NULL;
	}

	return Seed;
}

//返回当前标签的枝标签
MenuLabel MenuLabelGetBranch(MenuLabel VarMenuLabel, Utf8* Label) {

	MenuLabel* Branch;

	VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

	if (VarMenuLabel != NULL) {
		Branch = ((PointMenuLabel)VarMenuLabel)->branch;
	}
	else {
		Branch = NULL;
	}

	return Branch;
}

//返回当前标签的数据
void* MenuLabelGetStorage(MenuLabel VarMenuLabel, Utf8* Label) {

	void* Storage;

	VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

	if (VarMenuLabel != NULL) {
		Storage = ((PointMenuLabel)VarMenuLabel)->storage;
	}
	else {
		Storage = NULL;
	}

	return Storage;
}

//返回当前标签的标题
Utf8* MenuLabelGetTitle(MenuLabel VarMenuLabel, Utf8* Label) {

	Utf8* Title;

	VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

	if (VarMenuLabel != NULL) {
		Title = ((PointMenuLabel)VarMenuLabel)->title;
	}
	else {
		Title = NULL;
	}

	return Title;
}


//修改标题
bool  MenuLabelAlterTitle(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle) { //修改MenuLabel的标题

	bool result = false;

	if (VarMenuLabel != NULL && Label != NULL && NewTitle != NULL) {

		if (Utf8Check(NewTitle) == 0) {//判断标题字符串是否为utf8编码
			;  //不是utf8编码
		}
		else {//是Utf8编码

			//解析Label获取从属标签MenuLabel地址
			VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

			if (VarMenuLabel != NULL) { //获取成功

				

				if (MenuLabelCheckTitle(NewTitle) == true) {//标题格式正确 

					NewTitle = Utf8Duplicate(NewTitle);//为插入的标题创建副本

					//副本创建成功
					if (NewTitle != NULL) {
						((PointMenuLabel)VarMenuLabel)->title = Utf8Duplicate(NewTitle);//插入新标题
						result = true; //返回修改成功
					}
				}

			}
		}
	}

	return result;
}

//修改数据
bool  MenuLabelAlterStorage(MenuLabel VarMenuLabel, Utf8* Label, void* NewStorage) {  //修改MenuLabel的数据

	bool result = false;


	if (VarMenuLabel != NULL && Label != NULL) {

		//解析Label获取从属标签MenuLabel地址
		VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

		if (VarMenuLabel != NULL) { //获取成功

			((PointMenuLabel)VarMenuLabel)->storage = NewStorage;//插入新数据
			result = true; //返回修改成功


		}

	}

	return result;
}

//修改枝标签
bool MenuLabelAlterBranch(MenuLabel VarMenuLabel, Utf8* Label, MenuLabel* NewBranch) {

	bool result = false;

	if (VarMenuLabel != NULL && Label != NULL) {

		//解析Label获取从属标签MenuLabel地址
		VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

		if (VarMenuLabel != NULL) { //获取成功

			((PointMenuLabel)VarMenuLabel)->branch = NewBranch;//修改新枝标签
			result = true; //返回修改成功


		}

	}

	return result;

}

//修改子标签
bool MenuLabelAlterSeed(MenuLabel VarMenuLabel, Utf8* Label, MenuLabel* NewSeed) {

	bool result = false;

	if (VarMenuLabel != NULL && Label != NULL) {

		//解析Label获取从属标签MenuLabel地址
		VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

		if (VarMenuLabel != NULL) { //获取成功

			((PointMenuLabel)VarMenuLabel)->seed = NewSeed;//修改新子标签
			result = true; //返回修改成功


		}

	}

	return result;

}

//修改标题、数据、枝标签、子标签
bool  MenuLabelAlterAll(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle, void* NewStorage, MenuLabel* NewBranch, MenuLabel* NewSeed) { //修改MenuLabel的标题和数据

	bool  result = true;

	if (VarMenuLabel != NULL && Label != NULL && NewTitle != NULL) {

		//解析Label获取从属标签MenuLabel地址
		VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

		if (VarMenuLabel != NULL) {

			//修改标题
			result = MenuLabelAlterTitle(VarMenuLabel, u8"", NewTitle);   //Label传入空字符串表示无需进行Label解析

			//修改标题成功
			if (result == true) {
				result = MenuLabelAlterStorage(VarMenuLabel, u8"", NewStorage); // 修改数据
				result = MenuLabelAlterBranch(VarMenuLabel, u8"", NewBranch);// 修改枝标签
				result = MenuLabelAlterSeed(VarMenuLabel, u8"", NewSeed);// 修改子标签
			}

		}
		else {
			result = false;
		}

	}

	return result;
}