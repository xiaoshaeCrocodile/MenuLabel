#include "Utf8.h"
#include "Bytebit.h"

//获取utf8字符串的长度,获取过程中检查字符出是否位Utf8编码格式
size_t Utf8Lenght(const Utf8* Utf8Str) {

	size_t Utf8CharQuantity = 0; //存储Utf8字符串 字符个数

	while (*Utf8Str != '\0') { //未到结尾
		Utf8 Utf8CharPresent = *Utf8Str; //获取当前位

		if ((Utf8CharPresent & 0b10000000) == 0) { //如果首位为0，表示该字符为单字节字符
			Utf8CharQuantity++; //个数
			Utf8Str++;
		}
		else {//如果首位不为0

			//如果是一个单字节字符，则首位为0
			//如果是多字节字符，则第一个字节的高位表示该字符占用几个字节
			//1字节字符   0xxxxxxx
			//2字节字符   110xxxxx
			//3字节字符   1110xxxx
			//4字节字符   11110xxx

			//该字符 <=4 
			uint8_t BitQuantity = 0; //记录高位有几个1，也就是当前字符所占的字节数

			//注意 是要==128，而不是1，因为判断的是最高位，最高位为128
			while (BitQuantity <= 4 && ((Utf8CharPresent & 0b10000000) == 128)) {
				BitQuantity++;
				Utf8CharPresent <<= 1;
			}
			if (BitQuantity <= 4) {
				Utf8Str++;
				Utf8CharPresent = *Utf8Str;
				while (BitQuantity > 1) { //判断是否位Utf8编码格式
					if (((Utf8CharPresent & 0b11000000) != 128)) { //不是Utf8 10xxxxxx
						Utf8CharQuantity = 0;
						break;
					}
					Utf8Str++;
					Utf8CharPresent = *Utf8Str;
					BitQuantity--;
				}
				if (BitQuantity > 1) { //不是Utf8
					break;
				}

				//是Utf8，个数自增1；
				Utf8CharQuantity++;
			}
			else {  //所占用的字节数大于4，不可能出现这种情况，不是Utf8
				Utf8CharQuantity = 0;
				break;
			}
		}
	}
	//如果值为0表示长度为0或者出现错误，为正数为正常返回 
	return Utf8CharQuantity;
}

//检查字符串是否为utf8格式
bool Utf8Check(const Utf8* Utf8Str) {

	bool result = true;

	while (*Utf8Str != '\0') { //未到结尾
		Utf8 Utf8CharPresent = *Utf8Str; //获取当前位

		if ((Utf8CharPresent & 0b10000000) == 0) { //如果首位为0，表示该字符为单字节字符
			Utf8Str++;
		}
		else {//如果首位不为0

			//如果是一个单字节字符，则首位为0
			//如果是多字节字符，则第一个字节的高位表示该字符占用几个字节
			//1字节字符   0xxxxxxx
			//2字节字符   110xxxxx
			//3字节字符   1110xxxx
			//4字节字符   11110xxx
			uint8_t BitLenght = 0; //记录高位有几个1，也就是当前字符所占的字节数

			//注意 是要==128，而不是1，因为判断的是最高位，最高位为128
			while (BitLenght <= 4 && ((Utf8CharPresent & 0b10000000) == 128)) {
				BitLenght++;
				Utf8CharPresent <<= 1;
			}
			if (BitLenght <= 4) {//判断后面的是否为10xxxxxx
				Utf8Str++;
				Utf8CharPresent = *Utf8Str;
				while (BitLenght > 1) {
					if ((Utf8CharPresent & 0b11000000) != 128) { //不是utf8 10xxxxxx
						result = false;
						break;
					}
					Utf8Str++;
					Utf8CharPresent = *Utf8Str;
					BitLenght--;
				}
			}
			else {  //所占用的字节数大于4，不可能出现这种情况
				result = false;
				break;
			}
			if (result == false) {
				break;
			}
		}
	}
	//如果值为0表示长度为0或者出现错误，为正数为正常返回 
	return result;
}

//将SourceUtf8Str拼接到TargetUtf8Str后面
Utf8* Utf8Cat(Utf8* TargetUtf8Str,Utf8* SourceUtf8Str) {

	Utf8* resultUtf8Str = TargetUtf8Str;

	if (TargetUtf8Str != NULL && SourceUtf8Str != NULL ) {

		TargetUtf8Str += strlen(TargetUtf8Str);

		//拼接
		for (size_t i = strlen(TargetUtf8Str); *SourceUtf8Str != '\0'; i++) {
			*TargetUtf8Str = *SourceUtf8Str;
			TargetUtf8Str++;
			SourceUtf8Str++;
		}

		//结束符
		*TargetUtf8Str = '\0';
	}
	else {
		resultUtf8Str = NULL;
	}

	return resultUtf8Str;
}

//生成Utf8字符串副本
Utf8* Utf8Duplicate(const Utf8* Utf8Str) {


	Utf8* NewUtf8Str;

	//地址是否为空字符编码长度是否大于0，获取长度过程中会检查 字符串编码格式是否为Utf8
	if (Utf8Str != NULL && Utf8Lenght(Utf8Str) > 0) {

		//申请内存空间
		NewUtf8Str = (Utf8*)malloc(strlen(Utf8Str) + 1);

		if (NewUtf8Str != NULL) {

			//复制字符串
			Utf8* DuplicateUtf8Str = NewUtf8Str;
			while (*Utf8Str != '\0') {
				*DuplicateUtf8Str = *Utf8Str;
				Utf8Str++;
				DuplicateUtf8Str++;
			}


			//结尾补上结束符
			*DuplicateUtf8Str = *Utf8Str;
		}

		//申请内存失败，返回NULL
	}else {  //Utf8Lenght返回参数为0，字符串不正常
		NewUtf8Str = NULL;
	}

	//返回新地址
	return NewUtf8Str;
}

//生成Utf8字符串副本  设定长度
Utf8* Utf8DuplicateLenght(const Utf8* Utf8Str,size_t Utf8StrLenght) {

	Utf8* NewUtf8Str;

	//地址是否为空字符编码长度是否大于0，获取长度过程中会检查 字符串编码格式是否为Utf8
	if (Utf8Str != NULL && Utf8Lenght(Utf8Str) > 0) {

		//申请内存空间
		NewUtf8Str = (Utf8*)malloc(strlen(Utf8Str) + 1);

		if (NewUtf8Str != NULL) {

			//复制字符串
			Utf8* DuplicateUtf8Str = NewUtf8Str;

			//复制指定的字符个数
			while (Utf8StrLenght > 0) {
				*DuplicateUtf8Str = *Utf8Str;
				Utf8Str++;
				DuplicateUtf8Str++;
				Utf8StrLenght--;
			}


			//结尾补上结束符
			*DuplicateUtf8Str = '\0';
		}

		//申请内存失败，返回NULL
	}
	else {  //Utf8Lenght返回参数为0，字符串不正常
		NewUtf8Str = NULL;
	}

	//返回新地址
	return NewUtf8Str;
}


//释放Utf8副本字符串的内存空间
Utf8* Utf8Free(const Utf8* Utf8Str) {
	free(Utf8Str);
	return (Utf8*)NULL;
}

//Utf8字符串比较
bool Utf8StrContrast(Utf8* SourceUtf8Str, Utf8* TargetUtf8Str) {

	bool result;

	//判断是否指向NULL
	if (SourceUtf8Str == NULL || TargetUtf8Str == NULL) {
		result = false;
	}//长度一样，且都为Utf8编码格式
	else if (strlen(SourceUtf8Str) == strlen(TargetUtf8Str) && Utf8Check(SourceUtf8Str) == Utf8Check(TargetUtf8Str)) {
		//字节比较  返回false 或 true
		result = ByteContrast(SourceUtf8Str, TargetUtf8Str, strlen(SourceUtf8Str));
	}
	else {
		result = false;
	}

	return result;
}