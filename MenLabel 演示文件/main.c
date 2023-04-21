#include <stdio.h>
#include <locale.h>
#include <windows.h>   //�ÿ�ֻ����Windows���������У���������ֲ��linux��
#include "Utf8.h"
#include "MenuLabel.h"

int main(void) {

	//UTF8��������
	
	//�����е������ַ�����ʹ��utf8��ʽ���д洢��������������ȵ�
	setlocale(LC_ALL, "zh_CN.UTF-8");

	//�����ն�֧��utf8�����ʽ
	
	//����windows���ն��ַ�����
	// �����ն���������ʽΪ UTF-8
	SetConsoleOutputCP(CP_UTF8);
	// �����ն���������ʽΪ UTF-8
	SetConsoleCP(CP_UTF8);

	//--------------------------------------

	//����ʼ

	
	MenuLabel Chinese = CreateMenuLabel(u8"��ʼ");
	

	MenuLabelCreateBranch(Chinese, u8"", u8"��ӭ");

	MenuLabelCreateSeed(Chinese, u8">��ӭ", u8"�ʺ�");
	MenuLabelAlterStorage(Chinese, u8">��ӭ|�ʺ�", (void*)u8"��ã���ӭʹ�ø�������");
	MenuLabelCreateBranch(Chinese, u8">��ӭ|�ʺ�", u8"��������");
	MenuLabelAlterStorage(Chinese, u8">��ӭ|�ʺ�>��������", (void*)u8"��Ŀǰʹ�õ������ģ��޸����ò˵�ѡ��1��");

	MenuLabelCreateBranch(Chinese, u8">��ӭ", u8"����");
	MenuLabelAlterStorage(Chinese, u8">��ӭ>����", u8">>>");

	MenuLabelCreateSeed(Chinese, u8">��ӭ>����", u8"����");
	MenuLabelAlterStorage(Chinese, u8">��ӭ>����|����", u8"����:�����������");

	MenuLabelCreateBranch(Chinese, u8">��ӭ>����", u8"�˵�");
	MenuLabelAlterStorage(Chinese, u8">��ӭ>����>�˵�", u8"�˵�");
	MenuLabelCreateSeed(Chinese, u8">��ӭ>����>�˵�", u8"����ѡ��");
	MenuLabelAlterStorage(Chinese, u8">��ӭ>����>�˵�|����ѡ��", u8"һ.��������");

	MenuLabelCreateBranch(Chinese, u8">��ӭ>����>�˵�|����ѡ��", u8"����");
	MenuLabelAlterStorage(Chinese, u8">��ӭ>����>�˵�|����ѡ��>����", u8"1.���������� \"set chinese\"");

	MenuLabelCreateSeed(Chinese, u8">��ӭ>����>�˵�|����ѡ��>����", u8"�ɹ�");
	MenuLabelAlterStorage(Chinese, u8">��ӭ>����>�˵�|����ѡ��>����|�ɹ�", u8"�ɹ�:��������Ϊ���ģ�");

	MenuLabelCreateBranch(Chinese, u8">��ӭ>����>�˵�|����ѡ��>����", u8"Ӣ��");
	MenuLabelAlterStorage(Chinese, u8">��ӭ>����>�˵�|����ѡ��>����>Ӣ��", u8"2.����Ӣ���� \"set english\"");

	MenuLabelCreateSeed(Chinese, u8">��ӭ>����>�˵�|����ѡ��>����>Ӣ��", u8"�ɹ�");
	MenuLabelAlterStorage(Chinese, u8">��ӭ>����>�˵�|����ѡ��>����>Ӣ��|�ɹ�", u8"Success: The language is set to English!");//


	MenuLabel English = CreateMenuLabel(u8"��ʼ");

	MenuLabelCreateBranch(English, u8"", u8"��ӭ");

	MenuLabelCreateSeed(English, u8">��ӭ", u8"�ʺ�");
	MenuLabelAlterStorage(English, u8">��ӭ|�ʺ�", (void*)u8"Hello, welcome to use the repeater!"); //
	MenuLabelCreateBranch(English, u8">��ӭ|�ʺ�", u8"��������");
	MenuLabelAlterStorage(English, u8">��ӭ|�ʺ�>��������", (void*)u8"You are currently using Chinese, please use menu option 1 to modify it.");//

	MenuLabelCreateBranch(English, u8">��ӭ", u8"����");
	MenuLabelAlterStorage(English, u8">��ӭ>����", u8">>>");//

	MenuLabelCreateSeed(English, u8">��ӭ>����", u8"����");
	MenuLabelAlterStorage(English, u8">��ӭ>����|����", u8"Error: Command output error!");//

	MenuLabelCreateBranch(English, u8">��ӭ>����", u8"�˵�");
	MenuLabelAlterStorage(English, u8">��ӭ>����>�˵�", u8"Menu");//
	MenuLabelCreateSeed(English, u8">��ӭ>����>�˵�", u8"����ѡ��");
	MenuLabelAlterStorage(English, u8">��ӭ>����>�˵�|����ѡ��", u8"One..Set Language");//

	MenuLabelCreateBranch(English, u8">��ӭ>����>�˵�|����ѡ��", u8"����");
	MenuLabelAlterStorage(English, u8">��ӭ>����>�˵�|����ѡ��>����", u8"1.Set Chinese  is \"set chinese\"");//

	MenuLabelCreateSeed(English, u8">��ӭ>����>�˵�|����ѡ��>����", u8"�ɹ�");
	MenuLabelAlterStorage(English, u8">��ӭ>����>�˵�|����ѡ��>����|�ɹ�", u8"�ɹ�:��������Ϊ���ģ�");//no

	MenuLabelCreateBranch(English, u8">��ӭ>����>�˵�|����ѡ��>����", u8"Ӣ��");
	MenuLabelAlterStorage(English, u8">��ӭ>����>�˵�|����ѡ��>����>Ӣ��", u8"2.Set English is \"set english\""); //

	MenuLabelCreateSeed(English, u8">��ӭ>����>�˵�|����ѡ��>����>Ӣ��", u8"�ɹ�");
	MenuLabelAlterStorage(English, u8">��ӭ>����>�˵�|����ѡ��>����>Ӣ��|�ɹ�", u8"Success: The language is set to English!");//

	
	MenuLabel Language = Chinese;

	
	//printf("----------------------------------\n");
	//MenuLabelTraversal(Chinese,u8"");

	//��ӭ��Ϣ
	printf("%s\n",(char*)MenuLabelGetStorage(Language, u8">��ӭ|�ʺ�"));
	printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">��ӭ|�ʺ�>��������"));

	printf("\n\n");

	while (1) {

		//�˵�
		printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">��ӭ>����>�˵�"));

		printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">��ӭ>����>�˵�|����ѡ��"));
		printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">��ӭ>����>�˵�|����ѡ��>����"));
		printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">��ӭ>����>�˵�|����ѡ��>����>Ӣ��"));

		printf("\n\n");

		//�������ʾ
		printf("%s", (char*)MenuLabelGetStorage(Language, u8">��ӭ>����"));
		
		//��������
		Utf8 Get[100];
		gets(Get);

		printf("\n");

		if (Utf8StrContrast(Get, u8"set chinese") == true) {  //��������Ϊ����
			printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">��ӭ>����>�˵�|����ѡ��>����|�ɹ�"));
			Language = Chinese;
		}
		else if (Utf8StrContrast(Get, u8"set english") == true) {  //��������ΪӢ��
			printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">��ӭ>����>�˵�|����ѡ��>����>Ӣ��|�ɹ�"));
			Language = English;
		}
		else {  //�������
			printf("%s\n", (char*)MenuLabelGetStorage(Language, u8">��ӭ>����|����"));
		}
		
		printf("\n");
	}
	
	return 0;
}