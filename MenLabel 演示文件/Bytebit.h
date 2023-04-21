#ifndef BYTEBITDEF

	#define BYTEBITDEF

	#include <stdbool.h>
	#include <stdint.h>
	#include <stdlib.h>

	typedef uint8_t Byte;

	bool ByteContrast(Byte* SourceByte, Byte* TargetByte, size_t ByteLenght); //字节比较
	bool ByteCopy(Byte* SourceByte, Byte* TargetByte, size_t ByteLenght);  //字节复制
	void* ByteSpaceApply(void* Address, size_t Size); //字节空间申请

#endif // !BYTEBITDEF