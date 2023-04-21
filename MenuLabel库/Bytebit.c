#include "Bytebit.h"

//�ֽڱȽ�
bool ByteContrast(Byte* SourceByte, Byte* TargetByte,size_t ByteLenght) {
	
	bool result;
	
	if (SourceByte != NULL && TargetByte != NULL && ByteLenght > 0) {

		//��ʼ�Ƚ�
		while (*SourceByte == *TargetByte && ByteLenght > 0) {
			SourceByte++;
			TargetByte++;
			ByteLenght--;
		}

		if (ByteLenght > 0) {
			result = false;
		}
		else {
			result = true;
		}
	}
	else {
		result = false;
	}

	return result;
}

//�ֽڸ���
bool ByteCopy(Byte* SourceByte, Byte* TargetByte, size_t ByteLenght) {
	
	bool result = false;

	if (SourceByte != NULL && TargetByte != NULL && ByteLenght > 0) {

		//��ʼ����
		while (ByteLenght > 0) {
			*TargetByte++ = *SourceByte++;
			ByteLenght--;
		}
		result = true;
	}
	
	return result;
}

//�ڴ�ռ�����
void* ByteSpaceApply(void* Address, size_t Size) {

	if (Address == NULL) {
		Address = malloc(Size);
	}
	else {

		void* TmpAddress = realloc(Address, Size);
		if (TmpAddress == NULL) {
			free(Address);
		}
		Address = TmpAddress;

	}
	return Address;
}