#ifndef BYTEBITDEF

	#define BYTEBITDEF

	#include <stdbool.h>
	#include <stdint.h>
	#include <stdlib.h>

	typedef uint8_t Byte;

	bool ByteContrast(Byte* SourceByte, Byte* TargetByte, size_t ByteLenght); //�ֽڱȽ�
	bool ByteCopy(Byte* SourceByte, Byte* TargetByte, size_t ByteLenght);  //�ֽڸ���
	void* ByteSpaceApply(void* Address, size_t Size); //�ֽڿռ�����

#endif // !BYTEBITDEF