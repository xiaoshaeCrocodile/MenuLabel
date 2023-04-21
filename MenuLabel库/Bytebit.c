#include "Bytebit.h"

//字节比较
bool ByteContrast(Byte* SourceByte, Byte* TargetByte,size_t ByteLenght) {
	
	bool result;
	
	if (SourceByte != NULL && TargetByte != NULL && ByteLenght > 0) {

		//开始比较
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

//字节复制
bool ByteCopy(Byte* SourceByte, Byte* TargetByte, size_t ByteLenght) {
	
	bool result = false;

	if (SourceByte != NULL && TargetByte != NULL && ByteLenght > 0) {

		//开始复制
		while (ByteLenght > 0) {
			*TargetByte++ = *SourceByte++;
			ByteLenght--;
		}
		result = true;
	}
	
	return result;
}

//内存空间申请
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