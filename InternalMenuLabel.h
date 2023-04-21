
#ifndef INTERNALMENULABEL

	#define INTERNALMENULABEL

	#include <stdint.h>
	#include <stdbool.h>
	#include <string.h>
	#include <stdio.h>
	#include "Utf8.h"
	#include "Bytebit.h"

	struct InternalMenuLabelIntact {
		Utf8* title;  //���κ�ƽ̨�κα�������ֻռ��1���ֽ�
		void* storage;
		struct InternalMenuLabelIntact* branch;
		struct InternalMenuLabelIntact* seed;
	};
	
	typedef struct InternalMenuLabelIntact InternalMenuLabelIntact;
	typedef InternalMenuLabelIntact* PointMenuLabel;
	typedef PointMenuLabel* MenuLabel;

	//MenuLabelIntact�ڴ�ռ����
	MenuLabel MenuLabelCreateMemoryIntact(void);

	//MenuLabel�ڴ��ͷ�
	MenuLabel MenuLabelFree(MenuLabel PointMenuLabel);

	//MenuLabel*�ڴ��ͷ�
	MenuLabel MenuLabelPointFree(MenuLabel* PointMenuLabel);

	//Size�ڴ��ͷ�
	size_t* SizeFree(size_t* PointSize);

	//��̬Label�ڴ��ͷ�
	Utf8* LabelFree(Utf8* Label);

	//MenuLabelTraversal��������������
	//�����ַ�Ƭ�δ洢ָ��ĺ���
	MenuLabel* MenuLabelPointCreateMemory(MenuLabel* ppMenuLabel, size_t memorySize);

	//MenuLabelTraversal��������������
	//������̬�ľ���洢����
	size_t* MenuLabelPointSizeCreateMemory(size_t* PointSize, size_t memorySize);

	//��̬Label�ڴ����
	Utf8* LabelCreate(Utf8* Label, Utf8* NewLabel);

	//��̬Label�ع麯��
	size_t LabelRegression(Utf8* Label, size_t RegressionLenght);

	//����ָ����MenuLabel��ǩ
	bool MenuLabelTraversal(MenuLabel VarMenuLabel, Utf8* Label);

	//��ʼ��MenuLabel
	MenuLabel CreateMenuLabel(Utf8* NewTitle);

	//����ļ����Ƿ�����ļ�������Ҫ��
	bool MenuLabelCheckTitle(const Utf8* Title);

	//MenuLabelGetDependent��������������
	//�����ַ�Ƭ�δ洢ָ��ĺ���
	Utf8** Utf8CreateMemory(Utf8** ppUtf8, size_t memorySize);

	//Label����
	//����·�������ش�����ǩ��MenuLabel��ַ
	MenuLabel MenuLabelGetDependent(MenuLabel VarMenuLabel, Utf8* Label);

	//����֦��ǩ
	bool MenuLabelCreateBranch(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle);

	//�����ӱ�ǩ
	bool MenuLabelCreateSeed(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle);

	//��ȡ�ӱ�ǩ��ַ
	MenuLabel MenuLabelGetSeed(MenuLabel VarMenuLabel, Utf8* Label);

	//��ȡ֦��ǩ��ַ
	MenuLabel MenuLabelGetBranch(MenuLabel VarMenuLabel, Utf8* Label);

	//��ȡ���ݵ�ַ
	void* MenuLabelGetStorage(MenuLabel VarMenuLabel, Utf8* Label);

	//��ȡ����
	Utf8* MenuLabelGetTitle(MenuLabel VarMenuLabel, Utf8* Label);

	//�޸ı���
	bool  MenuLabelAlterTitle(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle);

	//�޸�����
	bool  MenuLabelAlterStorage(MenuLabel VarMenuLabel, Utf8* Label, void* NewStorage);

	//�޸�֦��ǩ
	bool MenuLabelAlterBranch(MenuLabel VarMenuLabel, Utf8* Label, MenuLabel* NewBranch);

	//�޸��ӱ�ǩ
	bool MenuLabelAlterSeed(MenuLabel VarMenuLabel, Utf8* Label, MenuLabel* NewSeed);

	//�޸ı��⣬���ݣ�֦��ǩ���ӱ�ǩ
	bool MenuLabelAlterAll(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle, void* NewStorage, MenuLabel* NewBranch, MenuLabel* NewSeed);


#endif

