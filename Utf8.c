#include "Utf8.h"
#include "Bytebit.h"

//��ȡutf8�ַ����ĳ���,��ȡ�����м���ַ����Ƿ�λUtf8�����ʽ
size_t Utf8Lenght(const Utf8* Utf8Str) {

	size_t Utf8CharQuantity = 0; //�洢Utf8�ַ��� �ַ�����

	while (*Utf8Str != '\0') { //δ����β
		Utf8 Utf8CharPresent = *Utf8Str; //��ȡ��ǰλ

		if ((Utf8CharPresent & 0b10000000) == 0) { //�����λΪ0����ʾ���ַ�Ϊ���ֽ��ַ�
			Utf8CharQuantity++; //����
			Utf8Str++;
		}
		else {//�����λ��Ϊ0

			//�����һ�����ֽ��ַ�������λΪ0
			//����Ƕ��ֽ��ַ������һ���ֽڵĸ�λ��ʾ���ַ�ռ�ü����ֽ�
			//1�ֽ��ַ�   0xxxxxxx
			//2�ֽ��ַ�   110xxxxx
			//3�ֽ��ַ�   1110xxxx
			//4�ֽ��ַ�   11110xxx

			//���ַ� <=4 
			uint8_t BitQuantity = 0; //��¼��λ�м���1��Ҳ���ǵ�ǰ�ַ���ռ���ֽ���

			//ע�� ��Ҫ==128��������1����Ϊ�жϵ������λ�����λΪ128
			while (BitQuantity <= 4 && ((Utf8CharPresent & 0b10000000) == 128)) {
				BitQuantity++;
				Utf8CharPresent <<= 1;
			}
			if (BitQuantity <= 4) {
				Utf8Str++;
				Utf8CharPresent = *Utf8Str;
				while (BitQuantity > 1) { //�ж��Ƿ�λUtf8�����ʽ
					if (((Utf8CharPresent & 0b11000000) != 128)) { //����Utf8 10xxxxxx
						Utf8CharQuantity = 0;
						break;
					}
					Utf8Str++;
					Utf8CharPresent = *Utf8Str;
					BitQuantity--;
				}
				if (BitQuantity > 1) { //����Utf8
					break;
				}

				//��Utf8����������1��
				Utf8CharQuantity++;
			}
			else {  //��ռ�õ��ֽ�������4�������ܳ����������������Utf8
				Utf8CharQuantity = 0;
				break;
			}
		}
	}
	//���ֵΪ0��ʾ����Ϊ0���߳��ִ���Ϊ����Ϊ�������� 
	return Utf8CharQuantity;
}

//����ַ����Ƿ�Ϊutf8��ʽ
bool Utf8Check(const Utf8* Utf8Str) {

	bool result = true;

	while (*Utf8Str != '\0') { //δ����β
		Utf8 Utf8CharPresent = *Utf8Str; //��ȡ��ǰλ

		if ((Utf8CharPresent & 0b10000000) == 0) { //�����λΪ0����ʾ���ַ�Ϊ���ֽ��ַ�
			Utf8Str++;
		}
		else {//�����λ��Ϊ0

			//�����һ�����ֽ��ַ�������λΪ0
			//����Ƕ��ֽ��ַ������һ���ֽڵĸ�λ��ʾ���ַ�ռ�ü����ֽ�
			//1�ֽ��ַ�   0xxxxxxx
			//2�ֽ��ַ�   110xxxxx
			//3�ֽ��ַ�   1110xxxx
			//4�ֽ��ַ�   11110xxx
			uint8_t BitLenght = 0; //��¼��λ�м���1��Ҳ���ǵ�ǰ�ַ���ռ���ֽ���

			//ע�� ��Ҫ==128��������1����Ϊ�жϵ������λ�����λΪ128
			while (BitLenght <= 4 && ((Utf8CharPresent & 0b10000000) == 128)) {
				BitLenght++;
				Utf8CharPresent <<= 1;
			}
			if (BitLenght <= 4) {//�жϺ�����Ƿ�Ϊ10xxxxxx
				Utf8Str++;
				Utf8CharPresent = *Utf8Str;
				while (BitLenght > 1) {
					if ((Utf8CharPresent & 0b11000000) != 128) { //����utf8 10xxxxxx
						result = false;
						break;
					}
					Utf8Str++;
					Utf8CharPresent = *Utf8Str;
					BitLenght--;
				}
			}
			else {  //��ռ�õ��ֽ�������4�������ܳ����������
				result = false;
				break;
			}
			if (result == false) {
				break;
			}
		}
	}
	//���ֵΪ0��ʾ����Ϊ0���߳��ִ���Ϊ����Ϊ�������� 
	return result;
}

//��SourceUtf8Strƴ�ӵ�TargetUtf8Str����
Utf8* Utf8Cat(Utf8* TargetUtf8Str,Utf8* SourceUtf8Str) {

	Utf8* resultUtf8Str = TargetUtf8Str;

	if (TargetUtf8Str != NULL && SourceUtf8Str != NULL ) {

		TargetUtf8Str += strlen(TargetUtf8Str);

		//ƴ��
		for (size_t i = strlen(TargetUtf8Str); *SourceUtf8Str != '\0'; i++) {
			*TargetUtf8Str = *SourceUtf8Str;
			TargetUtf8Str++;
			SourceUtf8Str++;
		}

		//������
		*TargetUtf8Str = '\0';
	}
	else {
		resultUtf8Str = NULL;
	}

	return resultUtf8Str;
}

//����Utf8�ַ�������
Utf8* Utf8Duplicate(const Utf8* Utf8Str) {


	Utf8* NewUtf8Str;

	//��ַ�Ƿ�Ϊ���ַ����볤���Ƿ����0����ȡ���ȹ����л��� �ַ��������ʽ�Ƿ�ΪUtf8
	if (Utf8Str != NULL && Utf8Lenght(Utf8Str) > 0) {

		//�����ڴ�ռ�
		NewUtf8Str = (Utf8*)malloc(strlen(Utf8Str) + 1);

		if (NewUtf8Str != NULL) {

			//�����ַ���
			Utf8* DuplicateUtf8Str = NewUtf8Str;
			while (*Utf8Str != '\0') {
				*DuplicateUtf8Str = *Utf8Str;
				Utf8Str++;
				DuplicateUtf8Str++;
			}


			//��β���Ͻ�����
			*DuplicateUtf8Str = *Utf8Str;
		}

		//�����ڴ�ʧ�ܣ�����NULL
	}else {  //Utf8Lenght���ز���Ϊ0���ַ���������
		NewUtf8Str = NULL;
	}

	//�����µ�ַ
	return NewUtf8Str;
}

//����Utf8�ַ�������  �趨����
Utf8* Utf8DuplicateLenght(const Utf8* Utf8Str,size_t Utf8StrLenght) {

	Utf8* NewUtf8Str;

	//��ַ�Ƿ�Ϊ���ַ����볤���Ƿ����0����ȡ���ȹ����л��� �ַ��������ʽ�Ƿ�ΪUtf8
	if (Utf8Str != NULL && Utf8Lenght(Utf8Str) > 0) {

		//�����ڴ�ռ�
		NewUtf8Str = (Utf8*)malloc(strlen(Utf8Str) + 1);

		if (NewUtf8Str != NULL) {

			//�����ַ���
			Utf8* DuplicateUtf8Str = NewUtf8Str;

			//����ָ�����ַ�����
			while (Utf8StrLenght > 0) {
				*DuplicateUtf8Str = *Utf8Str;
				Utf8Str++;
				DuplicateUtf8Str++;
				Utf8StrLenght--;
			}


			//��β���Ͻ�����
			*DuplicateUtf8Str = '\0';
		}

		//�����ڴ�ʧ�ܣ�����NULL
	}
	else {  //Utf8Lenght���ز���Ϊ0���ַ���������
		NewUtf8Str = NULL;
	}

	//�����µ�ַ
	return NewUtf8Str;
}


//�ͷ�Utf8�����ַ������ڴ�ռ�
Utf8* Utf8Free(const Utf8* Utf8Str) {
	free(Utf8Str);
	return (Utf8*)NULL;
}

//Utf8�ַ����Ƚ�
bool Utf8StrContrast(Utf8* SourceUtf8Str, Utf8* TargetUtf8Str) {

	bool result;

	//�ж��Ƿ�ָ��NULL
	if (SourceUtf8Str == NULL || TargetUtf8Str == NULL) {
		result = false;
	}//����һ�����Ҷ�ΪUtf8�����ʽ
	else if (strlen(SourceUtf8Str) == strlen(TargetUtf8Str) && Utf8Check(SourceUtf8Str) == Utf8Check(TargetUtf8Str)) {
		//�ֽڱȽ�  ����false �� true
		result = ByteContrast(SourceUtf8Str, TargetUtf8Str, strlen(SourceUtf8Str));
	}
	else {
		result = false;
	}

	return result;
}