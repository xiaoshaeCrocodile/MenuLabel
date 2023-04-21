#include "InternalMenuLabel.h"

//MenuLabelIntact�ڴ�ռ����
MenuLabel MenuLabelCreateMemoryIntact(void) {

	MenuLabel NewVarMenuLabel = (MenuLabel)malloc(sizeof(InternalMenuLabelIntact));

	return NewVarMenuLabel;
}


//MenuLabel�ڴ��ͷ�
MenuLabel MenuLabelFree(MenuLabel PointMenuLabel) {
	free(PointMenuLabel);
	return NULL;
}

//MenuLabel*�ڴ��ͷ�
MenuLabel MenuLabelPointFree(MenuLabel* PointMenuLabel) {
	free(PointMenuLabel);
	return NULL;
}

//size_t*�ڴ��ͷ�
size_t* SizeFree(size_t* PointSize) {
	free(PointSize);
	return NULL;
}

//*�ڴ��ͷ�
Utf8* LabelFree(Utf8* Label) {
	free(Label);
	return NULL;
}


//MenuLabelTraversal��������������
//�����ַ�Ƭ�δ洢ָ��ĺ���
MenuLabel* MenuLabelPointCreateMemory(MenuLabel* ppMenuLabel, size_t memorySize) {

	if (ppMenuLabel == NULL) {  //û�з����ڴ�ռ�
		ppMenuLabel = (MenuLabel*)malloc(memorySize);  //��һ�η����ڴ�ռ�
	}
	else {
		MenuLabel* TmpMenuLabel = (MenuLabel*)realloc(ppMenuLabel, memorySize); //��չ�ڴ�ռ�
		if (TmpMenuLabel == NULL) {  //��չʧ��

			//�˺����᷵��NULL�������ͷŴ�ŵ�ppMenuLabel����ν 
			ppMenuLabel = MenuLabelPointFree(ppMenuLabel);//�ͷ�
			//MenuLabelPointFree(ppMenuLabel);   ����ע����һ��
		}
		ppMenuLabel = TmpMenuLabel;  //���ʧ�ܣ�����ΪNULL������ɹ�����Ϊ�ɹ��ĵ�ַ
	}

	return ppMenuLabel;
}

//MenuLabelTraversal��������������
//������̬�ľ���洢����
size_t* MenuLabelPointSizeCreateMemory(size_t* PointSize, size_t memorySize) {

	if (PointSize == NULL) {  //û�з����ڴ�ռ�
		PointSize = (size_t*)malloc(memorySize);  //��һ�η����ڴ�ռ�
	}
	else {
		size_t* TmpSize = (size_t*)realloc(PointSize, memorySize); //��չ�ڴ�ռ�
		if (TmpSize == NULL) {  //��չʧ��

			//�˺����᷵��NULL�������ͷŴ�ŵ�PointSize����ν 
			PointSize = SizeFree(PointSize);//�ͷ�
			//MenuLabelPointFree(PointSize);   ����ע����һ��
		}
		PointSize = TmpSize;  //���ʧ�ܣ�����ΪNULL������ɹ�����Ϊ�ɹ��ĵ�ַ
	}

	return PointSize;
}

//��̬Label�ڴ����
Utf8* LabelCreate(Utf8* Label,Utf8* NewLabel) {

	size_t NewLabelLenght = strlen(NewLabel);

	if (NewLabel != NULL && NewLabelLenght >0) {

		size_t LabelLenght;

		if (Label == NULL) {  //û�з����ڴ�ռ�

			Label = (Utf8*)malloc(NewLabelLenght+1);  //��һ�η����ڴ�ռ�

			if (Label != NULL) {
				*Label = '\0';  //���ø��ַ����Ľ�β
				LabelLenght = 0; //�����ַ�������
			}

		}
		else {//���·����ڴ�ռ�

			LabelLenght = strlen(Label);

			Utf8* TmpLabel = (Utf8*)realloc(Label, LabelLenght + NewLabelLenght + 1); //��չ�ڴ�ռ�
			if (TmpLabel == NULL) {  //��չʧ��
				
				//�˺����᷵��NULL�������ͷŴ�ŵ�Label����ν 
				Label = LabelFree(Label);//�ͷ�
				//LabelFree(Label);   ����ע����һ��
			}
			Label = TmpLabel;  //���ʧ�ܣ�����ΪNULL������ɹ�����Ϊ�ɹ��ĵ�ַ
		}

		if (Label != NULL) {

			Label = Utf8Cat(Label, NewLabel);

		}
	}

	return Label;
}

//��̬Label�ع麯��
size_t LabelRegression(Utf8* Label, size_t RegressionLenght) {

	
	size_t RemoveByte = 0;//ɾ�����ֽ���

	size_t LabelLenght = strlen(Label) - 1, OldLabelLenght = LabelLenght;

	if (Label != NULL && RegressionLenght != 0) {

		
		for (size_t i = 0; i < RegressionLenght && LabelLenght >= 0; i++) {

			while (Label[LabelLenght] != ':' && LabelLenght >= 0) {
				LabelLenght--;
			}

			//ɾ��_Branch:
			if (Label[LabelLenght - 1] == 'h') {
				LabelLenght -= 8;
			}
			else {//ɾ��_Seed:
				LabelLenght -= 6;
			}

		}

		//�ɹ���ɾ����
		if (LabelLenght >= 0) {
			RemoveByte = OldLabelLenght - LabelLenght;
			Label[LabelLenght + 1] = '\0';
		}
		else {
			RemoveByte = 0;
		}
		
	}

	//����ɾ���˶��ٸ��ֽ�
	return RemoveByte;
}

//����ָ����MenuLabel��ǩ
bool MenuLabelTraversal(MenuLabel VarMenuLabel, Utf8* Label) {



	bool result = false;

	//����Label
	VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

	//VarMenuLabel���ֲ���
	
	//TmpMenuLabel���б䶯
	MenuLabel TmpMenuLabel = VarMenuLabel;

	size_t RegressionMenuLabelQuantity = 0;  //�ȴ��ع��ǩ�ڵ�ĸ���
	MenuLabel* RegressionMenuLabel = NULL;   //����ȴ��ع�ı�ǩ�ڵ�
	size_t* RegressionLabel = NULL; //���� ��ǰ��ǩ ���� �ع��ǩ�� ����
	size_t RegressionLabelLenght = 0;


	RegressionMenuLabel = MenuLabelPointCreateMemory(RegressionMenuLabel, (RegressionMenuLabelQuantity + 2) * sizeof(void*)); //���䱣��ȴ��ع�ڵ���ڴ�
	RegressionLabel = MenuLabelPointSizeCreateMemory(RegressionLabel, (RegressionMenuLabelQuantity + 2) * sizeof(size_t)); //��������ڴ�

	if (VarMenuLabel != NULL && RegressionMenuLabel != NULL && RegressionLabel != NULL) { //�ڴ����ɹ�
		RegressionMenuLabel[RegressionMenuLabelQuantity] = NULL; //������һ��λ�ã��ع鵽0����ʾ�������
		RegressionLabel[RegressionMenuLabelQuantity] = 0; //������λ��
		RegressionMenuLabelQuantity++;

		Utf8* DynamicLabel = NULL;

		while (TmpMenuLabel != NULL && RegressionMenuLabelQuantity > 0) {

			if (TmpMenuLabel != RegressionMenuLabel[RegressionMenuLabelQuantity - 1]) {

				//��ȡ����
				Utf8* Title = MenuLabelGetTitle(TmpMenuLabel, u8"");

				//��ȡ����
				void* Storage = MenuLabelGetStorage(TmpMenuLabel, u8"");

				if (TmpMenuLabel != VarMenuLabel) {

					//��ӱ���
					DynamicLabel = LabelCreate(DynamicLabel, Title);

				}
				//��ӡ����     �������ṩ����
				printf("Title:%s\n", Title);

				//��ӡ����	   �����ṩ����
				printf("Storage:%p\n", Storage);

				//��ӡλ��     �����ṩλ��
				printf("Label:%s\n", DynamicLabel);

				//����
				printf("\n\n");

				//�������ӽڵ�
				if (MenuLabelGetSeed(TmpMenuLabel, u8"") != NULL) {
					DynamicLabel = LabelCreate(DynamicLabel, u8"_Seed:");
				}//���������ӽڵ㣬������֦�ڵ�
				else if (MenuLabelGetBranch(TmpMenuLabel, u8"") != NULL) {
					DynamicLabel = LabelCreate(DynamicLabel, u8"_Branch:");
				}//�����ڵ���������������ӽڵ㣬��������֦�ڵ㣬���ÿ���
			}

			//----------------------------------------------------
			// 
			//�ñ�ǩ�ڵ���Ҫ���лع飬ǰ���ӽڵ�
			if (MenuLabelGetSeed(TmpMenuLabel, u8"") != NULL && MenuLabelGetBranch(TmpMenuLabel, u8"") != NULL
				&& RegressionMenuLabel[RegressionMenuLabelQuantity - 1] != TmpMenuLabel) {

				//����ñ�ǩ�ڵ�  ����λ��
				RegressionMenuLabel[RegressionMenuLabelQuantity] = TmpMenuLabel;
				RegressionLabel[RegressionMenuLabelQuantity] = RegressionLabelLenght; 
				RegressionMenuLabelQuantity++;

				//���·���  ��ǩ�ڵ� �� �ع�λ�� �ڴ�ռ�
				RegressionMenuLabel = MenuLabelPointCreateMemory(RegressionMenuLabel, (RegressionMenuLabelQuantity + 1) * sizeof(void*));
				RegressionLabel = MenuLabelPointSizeCreateMemory(RegressionLabel, (RegressionMenuLabelQuantity + 1) * sizeof(size_t)); //��������ڴ�

				//��ǩ�ڵ� �� �ع�λ�� �ڴ����ʧ��  
				if (RegressionMenuLabel == NULL || RegressionLabel == NULL) {
					result = false;
					break;
				}

				//ȥ���ӽڵ�
				TmpMenuLabel = MenuLabelGetSeed(TmpMenuLabel, u8"");

			}//�ñ�ǩ�ڵ㲻��Ҫ�ع飬ȥ���ӽڵ�
			else if (MenuLabelGetSeed(TmpMenuLabel, u8"") != NULL && MenuLabelGetBranch(TmpMenuLabel, u8"") == NULL) {

				//ȥ���ӽڵ�
				TmpMenuLabel = MenuLabelGetSeed(TmpMenuLabel, u8"");


			}//�ñ�ǩ�ڵ��Ѿ������������ڽ����˻ع�
			else if (RegressionMenuLabel[RegressionMenuLabelQuantity - 1] == TmpMenuLabel) {

				//������� RegressionLabelLenght - RegressionLabel[RegressionMenuLabelQuantity -1]

				size_t RemoveByte = RegressionLabelLenght - RegressionLabel[RegressionMenuLabelQuantity - 1];
				
				//�ع�ǰ
				//printf(u8"\n�ع�ǰ%s\n", DynamicLabel);

				//���ú�������̬Label���л���
				RemoveByte = LabelRegression(DynamicLabel, RemoveByte);

				//��Ҫ���̴洢�ռ䣬�ٴε���LabelCreate����  ʱ���Զ������ڴ���С

				//�ع��
				//printf(u8"\n�ع��%s\n", DynamicLabel);

				//��ǩ�ع��ˣ�����ҲҪ����
				RegressionLabelLenght = RegressionLabel[RegressionMenuLabelQuantity - 1];

				//ɾ���ع��¼  �� ����洢
				--RegressionMenuLabelQuantity;
				RegressionMenuLabel[RegressionMenuLabelQuantity] = NULL;
				RegressionLabel[RegressionMenuLabelQuantity] = 0;

				//���·���  ��ǩ�ڵ� �� �ع�λ�� �ڴ�ռ�
				RegressionMenuLabel = MenuLabelPointCreateMemory(RegressionMenuLabel, (RegressionMenuLabelQuantity + 1) * sizeof(void*));
				RegressionLabel = MenuLabelPointSizeCreateMemory(RegressionLabel, (RegressionMenuLabelQuantity + 1) * sizeof(size_t)); //��������ڴ�
				
				//��ǩ�ڵ� �� �ع�λ�� �ڴ����ʧ��  
				if (RegressionMenuLabel == NULL || RegressionLabel == NULL) {
					result = false;
					break;
				}

				DynamicLabel = LabelCreate(DynamicLabel, u8"_Branch:");

				TmpMenuLabel = MenuLabelGetBranch(TmpMenuLabel, u8"");

			}//�ñ�ǩ�ڵ㲻��Ҫ���лع飬ǰ��֦�ڵ�
			else if (MenuLabelGetBranch(TmpMenuLabel, u8"") != NULL) {

				//ǰ��֦�ڵ�
				TmpMenuLabel = MenuLabelGetBranch(TmpMenuLabel, u8"");

			}
			else { //�ñ�ǩ�ڵ��Ѿ�������ɣ���ǩ�ڵ���лع�

				//�ع�
				TmpMenuLabel = RegressionMenuLabel[RegressionMenuLabelQuantity - 1];

				//�ع鵽NULL ��ʾ�Ѿ����������ˣ������ɹ���
				if (RegressionMenuLabel[RegressionMenuLabelQuantity - 1] == NULL) {
					result = true;  //�ɹ�
				}

				RegressionLabelLenght--; //�ع鲻��Ҫ����
			}

			RegressionLabelLenght++;//��������


		}

	}
	else {
		result = false;
	}
	
	//�����ɹ����ͷ��ڴ�
	if (result == true) {
		MenuLabelPointFree(RegressionMenuLabel);
		free(RegressionLabel);
	}

	return result;
}

//��ʼ��MenuLabel
MenuLabel CreateMenuLabel(Utf8* NewTitle) {

	//�����ڴ�ռ�
	MenuLabel NewVarMenuLabel = MenuLabelCreateMemoryIntact();

	if (NewVarMenuLabel != NULL) {

		//�������,���ݣ�֦�ڵ㣬�ӽڵ�
		if (MenuLabelAlterAll(NewVarMenuLabel, u8"", NewTitle, NULL, NULL, NULL) == false) {
			//����ʧ��
			NewVarMenuLabel = MenuLabelFree(NewVarMenuLabel);  //�ͷ��ڴ�,�˺����᷵��NULL
		}

	}
	return NewVarMenuLabel;
}

//����ļ����Ƿ�����ļ�������Ҫ��
bool MenuLabelCheckTitle(const Utf8* Title) {

	bool result = true;

	uint8_t i, j;
	Utf8 special_chars[9] = { '\\', '/', ':', '*', '?', '\"', '<', '>', '|' }; // ��Ҫ���������ַ�

	size_t VarUtf8Lenght = Utf8Lenght(Title);//��ȡ���ⳤ��

	if (VarUtf8Lenght > 0 && VarUtf8Lenght <= 100) {//���ⳤ����ȷ

		for (i = 0; Title[i] != '\0'; i++) {
			for (j = 0; j < 9; j++) {

				if (Title[i] == special_chars[j]) {
					result = false;//�ļ���������Ҫ��
					break;
				}

			}
		}
	}
	else {//���ƹ���

		result = false;

	}

	

	return result;
}

//MenuLabelGetDependent��������������
//�����ַ�Ƭ�δ洢ָ��ĺ���
Utf8** Utf8CreateMemory(Utf8** ppUtf8, size_t memorySize) {

	if (ppUtf8 == NULL) {  //û�з����ڴ�ռ�
		ppUtf8 = (Utf8**)malloc(memorySize);  //��һ�η����ڴ�ռ�
	}
	else {
		Utf8** TMPppUtf8 = (Utf8**)realloc(ppUtf8, memorySize); //��չ�ڴ�ռ�
		if (TMPppUtf8 == NULL) {  //��չʧ��

			size_t FragmentStrQuantity = memorySize / sizeof(void*);

			//�ַ�Ƭ������洢�� FragmentStrQuantity ���ַ��������ֱ���ͷ��ַ�Ƭ��
			//������ַ������޷������ˣ�Ҳ�޷��ͷţ�������ڴ�й¶

			for (size_t i = 0; i < FragmentStrQuantity;i++) {
				ppUtf8[i] = Utf8Free(ppUtf8[i]);  //�Ƿ��ַ���������NULL
			}

			//�˺����᷵��NULL�������ͷŴ�ŵ�ppUtf8����ν
			ppUtf8 = Utf8Free(ppUtf8); //�ͷ�
			//Utf8Free(ppUtf8);   ����ע����һ��
		}
		ppUtf8 = TMPppUtf8;  //���ʧ�ܣ�����ΪNULL������ɹ�����Ϊ�ɹ��ĵ�ַ
	}

	return ppUtf8;
}

//Label����
//����·�������ش�����ǩ��MenuLabel��ַ
MenuLabel MenuLabelGetDependent(MenuLabel VarMenuLabel, Utf8* Label) {

	MenuLabel NewMenuLabel = VarMenuLabel; //�ñ���Ϊ���صĴ�����ǩ��ַ�������ڻ���ִ��󷵻�NULL

	if (VarMenuLabel == NULL) {
		NewMenuLabel = NULL;
	}
	else if (strlen(Label) == 0) {
		;
	}
	else if (*Label != '|' && *Label != '>') {
		NewMenuLabel = NULL;
	}//���Ѱ�����·������"|"���Ϳ�ʼѰ�ң�"|"��ʾ����ֱ�ӷ��ش���ı�ǩ
	else if (!(strlen(Label) == 1)) {

		size_t first = 0, end = 0, FragmentStrQuantity = 0; //�ַ��ο�ʼ���ַ��ν������ַ�������
		Utf8** FragmentStr = NULL;//���ڴ洢 �ַ�Ƭ�� �Ķ���ָ��

		while (Label[end] != '\0') {  //�ַ���û�е�ĩβ

			//�ַ���û������ > �� | �� ĩβ
			while (Label[end + 1] != '>' && Label[end + 1] != '|' && Label[end + 1]) {
				end++;
			}

			//����first��ʼ�������ַ�������
			Utf8* FragmentStrTmp = Utf8DuplicateLenght(Label + first,end - first + 1);

			//�ַ�����������ʧ��
			if (FragmentStrTmp == NULL) {
				NewMenuLabel = NULL;
				break;
			}

			//�ж��ַ����Ƿ����Ҫ�������жϳ���
			//�ж��ַ��Ƿ����1��,�����Ƿ����Ҫ�󣬳����Ƿ�С�ڵ���20
			if (end - first >= 1 && MenuLabelCheckTitle(FragmentStrTmp + 1) == 1) {

				// ȫ������Ҫ��

				//�ַ���������+1
				FragmentStrQuantity++;

				//�����ַ���
				FragmentStr = Utf8CreateMemory(FragmentStr, FragmentStrQuantity * sizeof(void*));

				//�ɹ�
				if (FragmentStr != NULL) {
					FragmentStr[FragmentStrQuantity - 1] = FragmentStrTmp;
					first = end += 1;
				}//ʧ��
				else {
					NewMenuLabel = NULL;
					break;
				}

			}
			else { //�ַ�Ƭ�Σ�������Ҫ��
				NewMenuLabel = NULL;
				break;
			}

		}

		//�����ַ�Ƭ����ȡ�ɹ�
		if (NewMenuLabel != NULL) {


			//�����ַ�Ƭ�ζ�λ������ǩָ��
			for (size_t i = 0; i < FragmentStrQuantity; i++) {

				//�ӱ�ǩ
				if (FragmentStr[i][0] == '|') {

					//��ǩ�ı���һ��
					if (Utf8StrContrast(MenuLabelGetTitle(MenuLabelGetSeed(NewMenuLabel,u8""),u8""), FragmentStr[i] + 1)) {
						//��ȡ�ӱ�ǩ
						NewMenuLabel = MenuLabelGetSeed(NewMenuLabel,u8"");
					}
					else {
						NewMenuLabel = NULL;
					}

				}//֦��ǩ
				else if (FragmentStr[i][0] == '>') {

					//��ǩ�ı���һ��
					if (Utf8StrContrast(MenuLabelGetTitle(MenuLabelGetBranch(NewMenuLabel, u8""), u8""), FragmentStr[i] + 1)) {
						//��ȡ֦��ǩ
						NewMenuLabel = MenuLabelGetBranch(NewMenuLabel, u8"");
					}
					else {
						NewMenuLabel = NULL;
					}

				}

				//δ��ȡ��
				if (NewMenuLabel == NULL) {

					//�ͷŷ���������ַ�Ƭ�Σ�������
					while (i < FragmentStrQuantity) {
						FragmentStr[i] = Utf8Free(FragmentStr[i]);  //�Ƿ��ַ���������NULL
						i++;
					}

					break;
				}
				else {//��ȡ���ˣ��ͷŵ�ǰƬ��
					FragmentStr[i] = Utf8Free(FragmentStr[i]);
				}

			}
		}

		//�ͷű��������ַ�Ƭ�ε�ַ��ָ��
		if (FragmentStr != NULL) {
			FragmentStr = Utf8Free(FragmentStr);
		}

	}

	return NewMenuLabel;
}


//����֦��ǩ
bool MenuLabelCreateBranch(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle) {

	bool result = false;

	//����Label���ж�λ
	VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

	//��λ�ɹ�
	if (VarMenuLabel != NULL) {

		//����֦��ǩ
		MenuLabel NewVarMenuLabel = MenuLabelCreateMemoryIntact();

		//֦��ǩ�����ɹ�
		if (NewVarMenuLabel != NULL) {

			//�������,���ݣ�֦�ڵ㣬�ӽڵ�
			if (MenuLabelAlterAll(NewVarMenuLabel, u8"", NewTitle, NULL, NULL, NULL) == false) {
				//����ʧ��
				NewVarMenuLabel = MenuLabelFree(NewVarMenuLabel);  //�ͷ��ڴ�,�˺����᷵��NULL
			}
			else {
				//���µ�֦��ǩ�洢
				MenuLabelAlterBranch(VarMenuLabel, u8"", NewVarMenuLabel);
				result = true;
			}

		}

	}//��λʧ�ܣ�����ʧ��

	return result;
}

//�����ӱ�ǩ
bool MenuLabelCreateSeed(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle) {

	bool result = false;

	//����Label���ж�λ
	VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

	//��λ�ɹ�
	if (VarMenuLabel != NULL) {

		//����֦��ǩ
		MenuLabel NewVarMenuLabel = MenuLabelCreateMemoryIntact();

		//֦��ǩ�����ɹ�
		if (NewVarMenuLabel != NULL) {

			//�������,���ݣ�֦�ڵ㣬�ӽڵ�
			if (MenuLabelAlterAll(NewVarMenuLabel, u8"", NewTitle, NULL, NULL, NULL) == false) {
				//����ʧ��
				NewVarMenuLabel = MenuLabelFree(NewVarMenuLabel);  //�ͷ��ڴ�,�˺����᷵��NULL
			}
			else {
				//���µ��ӱ�ǩ�洢
				MenuLabelAlterSeed(VarMenuLabel, u8"", NewVarMenuLabel);
				result = true;
			}

		}

	}//��λʧ�ܣ�����ʧ��

	return result;
}

//���ص�ǰ��ǩ���ӱ�ǩ
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

//���ص�ǰ��ǩ��֦��ǩ
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

//���ص�ǰ��ǩ������
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

//���ص�ǰ��ǩ�ı���
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


//�޸ı���
bool  MenuLabelAlterTitle(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle) { //�޸�MenuLabel�ı���

	bool result = false;

	if (VarMenuLabel != NULL && Label != NULL && NewTitle != NULL) {

		if (Utf8Check(NewTitle) == 0) {//�жϱ����ַ����Ƿ�Ϊutf8����
			;  //����utf8����
		}
		else {//��Utf8����

			//����Label��ȡ������ǩMenuLabel��ַ
			VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

			if (VarMenuLabel != NULL) { //��ȡ�ɹ�

				

				if (MenuLabelCheckTitle(NewTitle) == true) {//�����ʽ��ȷ 

					NewTitle = Utf8Duplicate(NewTitle);//Ϊ����ı��ⴴ������

					//���������ɹ�
					if (NewTitle != NULL) {
						((PointMenuLabel)VarMenuLabel)->title = Utf8Duplicate(NewTitle);//�����±���
						result = true; //�����޸ĳɹ�
					}
				}

			}
		}
	}

	return result;
}

//�޸�����
bool  MenuLabelAlterStorage(MenuLabel VarMenuLabel, Utf8* Label, void* NewStorage) {  //�޸�MenuLabel������

	bool result = false;


	if (VarMenuLabel != NULL && Label != NULL) {

		//����Label��ȡ������ǩMenuLabel��ַ
		VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

		if (VarMenuLabel != NULL) { //��ȡ�ɹ�

			((PointMenuLabel)VarMenuLabel)->storage = NewStorage;//����������
			result = true; //�����޸ĳɹ�


		}

	}

	return result;
}

//�޸�֦��ǩ
bool MenuLabelAlterBranch(MenuLabel VarMenuLabel, Utf8* Label, MenuLabel* NewBranch) {

	bool result = false;

	if (VarMenuLabel != NULL && Label != NULL) {

		//����Label��ȡ������ǩMenuLabel��ַ
		VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

		if (VarMenuLabel != NULL) { //��ȡ�ɹ�

			((PointMenuLabel)VarMenuLabel)->branch = NewBranch;//�޸���֦��ǩ
			result = true; //�����޸ĳɹ�


		}

	}

	return result;

}

//�޸��ӱ�ǩ
bool MenuLabelAlterSeed(MenuLabel VarMenuLabel, Utf8* Label, MenuLabel* NewSeed) {

	bool result = false;

	if (VarMenuLabel != NULL && Label != NULL) {

		//����Label��ȡ������ǩMenuLabel��ַ
		VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

		if (VarMenuLabel != NULL) { //��ȡ�ɹ�

			((PointMenuLabel)VarMenuLabel)->seed = NewSeed;//�޸����ӱ�ǩ
			result = true; //�����޸ĳɹ�


		}

	}

	return result;

}

//�޸ı��⡢���ݡ�֦��ǩ���ӱ�ǩ
bool  MenuLabelAlterAll(MenuLabel VarMenuLabel, Utf8* Label, Utf8* NewTitle, void* NewStorage, MenuLabel* NewBranch, MenuLabel* NewSeed) { //�޸�MenuLabel�ı��������

	bool  result = true;

	if (VarMenuLabel != NULL && Label != NULL && NewTitle != NULL) {

		//����Label��ȡ������ǩMenuLabel��ַ
		VarMenuLabel = MenuLabelGetDependent(VarMenuLabel, Label);

		if (VarMenuLabel != NULL) {

			//�޸ı���
			result = MenuLabelAlterTitle(VarMenuLabel, u8"", NewTitle);   //Label������ַ�����ʾ�������Label����

			//�޸ı���ɹ�
			if (result == true) {
				result = MenuLabelAlterStorage(VarMenuLabel, u8"", NewStorage); // �޸�����
				result = MenuLabelAlterBranch(VarMenuLabel, u8"", NewBranch);// �޸�֦��ǩ
				result = MenuLabelAlterSeed(VarMenuLabel, u8"", NewSeed);// �޸��ӱ�ǩ
			}

		}
		else {
			result = false;
		}

	}

	return result;
}