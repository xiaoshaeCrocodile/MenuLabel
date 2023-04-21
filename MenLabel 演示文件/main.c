#include <stdio.h>
#include <locale.h>
#include <windows.h>   //该库只能在Windows环境下运行，不可以移植到linux中
#include "Utf8.h"
#include "MenuLabel.h"

int main(void) {

	//UTF8兼容设置
	
	//程序中的所有字符编码使用utf8格式进行存储，包括输入输出等等
	setlocale(LC_ALL, "zh_CN.UTF-8");

	//设置终端支持utf8编码格式
	
	//设置windows的终端字符编码
	// 设置终端输出编码格式为 UTF-8
	SetConsoleOutputCP(CP_UTF8);
	// 设置终端输入编码格式为 UTF-8
	SetConsoleCP(CP_UTF8);

	//--------------------------------------

	//程序开始

	
	MenuLabel Chinese = CreateMenuLabel(u8"开始");
	

	MenuLabelCreateBranch(Chinese, u8"", u8"欢迎");

	MenuLabelCreateSeed(Chinese, u8">欢迎", u8"问候");
	MenuLabelAlterStorage(Chinese, u8">欢迎|问候", (void*)u8"你好，欢迎使用复读机！");
	MenuLabelCreateBranch(Chinese, u8">欢迎|问候", u8"语言提醒");
	MenuLabelAlterStorage(Chinese, u8">欢迎|问候>语言提醒", (void*)u8"你目前使用的是中文，修改请用菜单选项1。");

	MenuLabelCreateBranch(Chinese, u8">欢迎", u8"交互");
	MenuLabelAlterStorage(Chinese, u8">欢迎>交互", u8">>>");

	MenuLabelCreateSeed(Chinese, u8">欢迎>交互", u8"错误");
	MenuLabelAlterStorage(Chinese, u8">欢迎>交互|错误", u8"错误:命令输出错误！");

	MenuLabelCreateBranch(Chinese, u8">欢迎>交互", u8"菜单");
	MenuLabelAlterStorage(Chinese, u8">欢迎>交互>菜单", u8"菜单");
	MenuLabelCreateSeed(Chinese, u8">欢迎>交互>菜单", u8"语言选项");
	MenuLabelAlterStorage(Chinese, u8">欢迎>交互>菜单|语言选项", u8"一.设置语言");

	MenuLabelCreateBranch(Chinese, u8">欢迎>交互>菜单|语言选项", u8"中文");
	MenuLabelAlterStorage(Chinese, u8">欢迎>交互>菜单|语言选项>中文", u8"1.设置中文是 \"set chinese\"");

	MenuLabelCreateSeed(Chinese, u8">欢迎>交互>菜单|语言选项>中文", u8"成功");
	MenuLabelAlterStorage(Chinese, u8">欢迎>交互>菜单|语言选项>中文|成功", u8"成功:语言设置为中文！");

	MenuLabelCreateBranch(Chinese, u8">欢迎>交互>菜单|语言选项>中文", u8"英文");
	MenuLabelAlterStorage(Chinese, u8">欢迎>交互>菜单|语言选项>中文>英文", u8"2.设置英文是 \"set english\"");

	MenuLabelCreateSeed(Chinese, u8">欢迎>交互>菜单|语言选项>中文>英文", u8"成功");
	MenuLabelAlterStorage(Chinese, u8">欢迎>交互>菜单|语言选项>中文>英文|成功", u8"Success: The language is set to English!");//


	MenuLabel English = CreateMenuLabel(u8"开始");

	MenuLabelCreateBranch(English, u8"", u8"欢迎");

	MenuLabelCreateSeed(English, u8">欢迎", u8"问候");
	MenuLabelAlterStorage(English, u8">欢迎|问候", (void*)u8"Hello, welcome to use the repeater!"); //
	MenuLabelCreateBranch(English, u8">欢迎|问候", u8"语言提醒");
	MenuLabelAlterStorage(English, u8">欢迎|问候>语言提醒", (void*)u8"You are currently using Chinese, please use menu option 1 to modify it.");//

	MenuLabelCreateBranch(English, u8">欢迎", u8"交互");
	MenuLabelAlterStorage(English, u8">欢迎>交互", u8">>>");//

	MenuLabelCreateSeed(English, u8">欢迎>交互", u8"错误");
	MenuLabelAlterStorage(English, u8">欢迎>交互|错误", u8"Error: Command output error!");//

	MenuLabelCreateBranch(English, u8">欢迎>交互", u8"菜单");
	MenuLabelAlterStorage(English, u8">欢迎>交互>菜单", u8"Menu");//
	MenuLabelCreateSeed(English, u8">欢迎>交互>菜单", u8"语言选项");
	MenuLabelAlterStorage(English, u8">欢迎>交互>菜单|语言选项", u8"One..Set Language");//

	MenuLabelCreateBranch(English, u8">欢迎>交互>菜单|语言选项", u8"中文");
	MenuLabelAlterStorage(English, u8">欢迎>交互>菜单|语言选项>中文", u8"1.Set Chinese  is \"set chinese\"");//

	MenuLabelCreateSeed(English, u8">欢迎>交互>菜单|语言选项>中文", u8"成功");
	MenuLabelAlterStorage(English, u8">欢迎>交互>菜单|语言选项>中文|成功", u8"成功:语言设置为中文！");//no

	MenuLabelCreateBranch(English, u8">欢迎>交互>菜单|语言选项>中文", u8"英文");
	MenuLabelAlterStorage(English, u8">欢迎>交互>菜单|语言选项>中文>英文", u8"2.Set English is \"set english\""); //

	MenuLabelCreateSeed(English, u8">欢迎>交互>菜单|语言选项>中文>英文", u8"成功");
	MenuLabelAlterStorage(English, u8">欢迎>交互>菜单|语言选项>中文>英文|成功", u8"Success: The language is set to English!");//

	
	MenuLabel Language = Chinese;

	
	//printf("----------------------------------\n");
	//MenuLabelTraversal(Chinese,u8"");

	//欢迎信息
	printf("%s\n",(char*)MenuLabelGetStorage(Language, u8">欢迎|问候"));
	printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">欢迎|问候>语言提醒"));

	printf("\n\n");

	while (1) {

		//菜单
		printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">欢迎>交互>菜单"));

		printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">欢迎>交互>菜单|语言选项"));
		printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">欢迎>交互>菜单|语言选项>中文"));
		printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">欢迎>交互>菜单|语言选项>中文>英文"));

		printf("\n\n");

		//命令交互提示
		printf("%s", (char*)MenuLabelGetStorage(Language, u8">欢迎>交互"));
		
		//输入命令
		Utf8 Get[100];
		gets(Get);

		printf("\n");

		if (Utf8StrContrast(Get, u8"set chinese") == true) {  //设置语言为中文
			printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">欢迎>交互>菜单|语言选项>中文|成功"));
			Language = Chinese;
		}
		else if (Utf8StrContrast(Get, u8"set english") == true) {  //设置语言为英文
			printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">欢迎>交互>菜单|语言选项>中文>英文|成功"));
			Language = English;
		}
		else {  //命令错误
			printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">欢迎>交互|错误"));
		}
		
		printf("\n");
	}
	
	return 0;
}