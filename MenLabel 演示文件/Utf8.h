#ifndef UTF8DEF

	#define UTF8DEF

	#include <stdint.h>
	#include <stdbool.h>
	#include <string.h>
	#include <stdlib.h>

	typedef uint8_t Utf8;

	size_t Utf8Lenght(const Utf8* Utf8Str);   //����Utf8�ĳ���
	bool Utf8Check(const Utf8* Utf8Str); //����ַ����Ƿ�ΪUtf8����
	Utf8* Utf8Duplicate(const Utf8* Utf8Str);  //����Utf8�ַ�������
	Utf8* Utf8Free(const Utf8* Utf8Str);  //�ͷ�Utf8�ַ�������
	bool Utf8StrContrast(Utf8* SourceUtf8Str, Utf8* TargetUtf8Str);//�ַ����Ƚ�
	Utf8* Utf8DuplicateLenght(const Utf8* Utf8Str, size_t Utf8StrLenght);//�ַ���������ָ�����ȡ�
	Utf8* Utf8Cat(Utf8* TargetUtf8Str, Utf8* SourceUtf8Str);//�ַ���ƴ��

#endif // !UTF8DEF
