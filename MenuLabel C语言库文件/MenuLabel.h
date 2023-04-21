#ifndef MENULABEL

	#define MENULABEL

	#include "Utf8.h"

	struct InternalMenuLabelIntact {
		Utf8* title;  //���κ�ƽ̨�κα�������ֻռ��1���ֽ�
		void* storage;
		struct InternalMenuLabelIntact* branch;
		struct InternalMenuLabelIntact* seed;
	};

	typedef struct InternalMenuLabelIntact InternalMenuLabelIntact;
	typedef InternalMenuLabelIntact* PointMenuLabel;
	typedef PointMenuLabel* MenuLabel;

	//��ʼ��MenuLabel
	MenuLabel CreateMenuLabel(Utf8* NewTitle);

	//Label����
	//����·�������ش�����ǩ��MenuLabel��ַ
	MenuLabel MenuLabelGetDependent(MenuLabel VarMenuLabel, Utf8* Label);

	//����ָ����MenuLabel��ǩ
	bool MenuLabelTraversal(MenuLabel VarMenuLabel, Utf8* Label);

	//����֦��ǩ
	bool MenuLabelCreateBranch(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle);

	//�����ӱ�ǩ
	bool MenuLabelCreateSeed(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle);

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

#endif // !MENUTAB
