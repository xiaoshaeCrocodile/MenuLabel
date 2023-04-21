#ifndef UTF8DEF

	#define UTF8DEF

	#include <stdint.h>
	#include <stdbool.h>
	#include <string.h>
	#include <stdlib.h>

	typedef uint8_t Utf8;

	size_t Utf8Lenght(const Utf8* Utf8Str);   //计算Utf8的长度
	bool Utf8Check(const Utf8* Utf8Str); //检查字符串是否为Utf8编码
	Utf8* Utf8Duplicate(const Utf8* Utf8Str);  //生成Utf8字符串副本
	Utf8* Utf8Free(const Utf8* Utf8Str);  //释放Utf8字符串副本
	bool Utf8StrContrast(Utf8* SourceUtf8Str, Utf8* TargetUtf8Str);//字符串比较
	Utf8* Utf8DuplicateLenght(const Utf8* Utf8Str, size_t Utf8StrLenght);//字符串副本，指定长度。
	Utf8* Utf8Cat(Utf8* TargetUtf8Str, Utf8* SourceUtf8Str);//字符串拼接

#endif // !UTF8DEF
