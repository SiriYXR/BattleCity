/*

Athena Classes Library For Microsoft Visual C++

Copyright @2016 CDU INnoVation Studio
All rights reserved.

文件名称：AFormat.h
摘要：
1.本文件含有格式处理类AFormat的声明，实现在aformat.cpp中。
2.AFormat类的对象能实现各种数据之间的转换，如字符串到浮点数等。
3.除了std::array，没有调用任何标准库函数，全部功能为自己实现。
4.提供strLen、memCpy等静态函数，用法与标准库中的对应函数一致。
5.pow函数只用于计算10的幂，不适用于其它情况，因此作为私有成员，不对外公开。

当前版本：V1.1
作者：余悦、刘智睿
e-mail：1397011447@qq.com
创建日期：2016年07月10日
更新日期：2016年12月29日

修正日志：
V1.1，修正了numToBin和numToHex的逻辑错误。

*/

#pragma once

#include <array>
#include "ACore.h"

ATHENA_BEGIN

class AFormat final
{
public:
	typedef unsigned long long bigInt;
	AFormat();
	~AFormat();

	int printf(char *,const char *,...);

	/*字符串相关*/
	const char *iToStr(int, char *container = nullptr);
	const char *lToStr(long long, char *container = nullptr);
	const char *uiToStr(unsigned int, char *container = nullptr);
	const char *ulToStr(bigInt, char *container = nullptr);
	const char *fToText(double, int digit = 6, char *container = nullptr);
	const char *fToStr(double, int digit = 6, char *container = nullptr);
	const char *fToE(double, int digit = 6, char *container = nullptr, bool isLower = true);
	long long strToInt(const char *);
	double strToDouble(const char*);

	/*二进制相关*/
	template<class T>
	const char* numToBin(T, char *container = nullptr);
	char binToChar(const char *);
	short binToShort(const char *);
	int binToInt(const char *);
	float binToFloat(const char *);
	double binToDouble(const char *);
	long long binToBigInt(const char *);

	/*十六进制相关*/
	template<class T>
	const char* numToHex(T, char *container = nullptr, bool isLower = false);
	const char* ptrToAddress(void *, char *container = nullptr, bool isLower = false);
	char hexToChar(const char *);
	short hexToShort(const char *);
	int hexToInt(const char *);
	float hexToFloat(const char *);
	double hexToDouble(const char *);
	long long hexToBigInt(const char *);

	/*八进制相关*/
	const char *numToOct(bigInt, char *container = nullptr);
	bigInt octToNum(const char*);

	/*系统相关*/
	bool isLittle();
	bool isX64();

	/*静态函数*/
	static bool isNum(char);
	static char *strUpr(char *);
	static char *strLwr(char *);
	static int strLen(const char *);
	static void *memSet(void *, char, size_t);
	static void *memCpy(void *, const void *, size_t);
private:
	void testFun();
	enum dataType
	{
		null,ch,str,inte,floa,e,g,hex,oct,bin,mod,ptr
	};
	struct formatInfo
	{
		dataType type;//格式类型
		int digit;//精度
		int len;//长度
		char fillChar;//填充字符 0 空格 用于填充空白部分
		bool isLeftAlign;//是否是右对齐，缺省为否
		bool isPreFix;//是否使用0x	 0前缀
		bool isPlus;//是否使用+前缀
		bool isLong;//是否是长型
		bool isUp;//是否大写
		bool isUnsigned;//是否无符号
		void reSet()
		{
			type = null;
			digit = 6;
			len = -1;
			fillChar = ' ';
			isUnsigned=isLeftAlign = isPreFix = isPlus = isLong = isUp = false;
		}
	};
	bool islittle;
	bool isx64;
	template <class T>
	const char * integerToStr(T, int, char *container);
	template<class T>
	T binToNum(T, int, const char *);
	template<class T>
	T hexToNum(T, int, const char*);
	void strHandle(char *&, char *&, char *&);
	void flagHandle(char *&, formatInfo &);
	void digitHandle(char *&,int &,int &);
	void typeHandle(char *&, formatInfo &);
	void integerHandle(char *&,formatInfo &,arg &,charBuffer &);
	void floatHandle(char *&, formatInfo &, arg &, charBuffer &);
	void chHandle(char *&, formatInfo &, arg &, charBuffer &);
	void hexHandle(char *&, formatInfo &, arg &, charBuffer &);
	void octHandle(char *&, formatInfo &, arg &, charBuffer &);
	void binHandle(char *&, formatInfo &, arg &, charBuffer &);
	void ptrHandle(char *&, formatInfo &, arg &, charBuffer &);
	void strHandle(char *&, formatInfo &, arg &);
	double pow( double);
	std::array<char, 16> hexChar;
	std::array<bigInt, 20> powNum;
	std::array<char, 256> buffer;
};

extern AFormat format;

ATHENA_END