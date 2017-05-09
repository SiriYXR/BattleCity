/*

Athena Classes Library For Microsoft Visual C++

Copyright @2016 CDU INnoVation Studio
All rights reserved.

文件名称：ACore.h
摘要：
1.本文件含有athena程序库的一些核心内容的定义。

当前版本：V2.0
作者：余悦
e-mail：1397011447@qq.com
创建日期：2016年05月29日
更新日期：2016年07月11日

修正日志：
V2.0，新增变参函数处理类arg

*/

#pragma once

#ifndef __cplusplus

#error You must use this file in C++ compiler, or you need filename with '.cpp' suffix

#endif

#pragma warning(disable:4290)
#pragma warning(disable:4996)

#define ATHENA_BEGIN namespace athena {
#define ATHENA_END }
#define MSGLEN 100

ATHENA_BEGIN

class AException
{
public:
	AException(const char *info)
	{
		int i;
		for (i = 0; i < MSGLEN; i++)
		{
			msg[i] = info[i];
			if (info[i] == 0)
			{
				break;
			}
		}
		msg[MSGLEN - 1] = 0;
	}
	virtual ~AException(){}
	virtual const char *what() const
	{
		return msg;
	}
protected:
	char msg[MSGLEN];
};

class AOutOfRange :public AException
{
public:
	AOutOfRange(const char *info) :AException(info){}
	AOutOfRange() :AException("Index Out Of Range"){}
	virtual ~AOutOfRange(){};
};

class ABadAlloc :public AException
{
public:
	ABadAlloc(const char *info) :AException(info){}
	ABadAlloc() :AException("Memory Allocation Failed"){}
	virtual ~ABadAlloc(){};
};

class AEmpty :public AException
{
public:
	AEmpty(const char *info) :AException(info){}
	AEmpty() :AException("Container Is Empty"){}
	virtual ~AEmpty(){};
};

class ANULL :public AException
{
public:
	ANULL(const char *info) :AException(info) {}
	ANULL() :AException("Pointer Can't Be NULL") {}
	virtual ~ANULL() {};
};

//buffer类，对缓冲区的封装，new和delete操作对用户透明
template<class T>
class ABuffer
{
public:
	ABuffer() :ok(true)
	{
		try
		{
			origin = new T[size];
		}
		catch (std::bad_alloc &)
		{
			ok = false;
		}
	}
	ABuffer(int t) :ok(true)
	{
		try
		{
			origin = new T[t];
		}
		catch (std::bad_alloc &)
		{
			ok = false;
		}
	}
	virtual ~ABuffer()
	{
		delete[] origin;
	}
	T *data() 
	{
		return origin;
	}
	T &operator[](int index) 
	{
		return origin[index];
	}
	bool isOk() 
	{
		return ok;
	}
protected:
	static const int size = 256;
	bool ok;
	char *origin;
};

typedef ABuffer<char> charBuffer;
typedef ABuffer<int> intBuffer;

/*变参函数处理类*/
class arg final
{
public:
	template<class T>
	arg(T *p)
	{
		ptr = reinterpret_cast<char *>(p)+sizeof(T);
	}
	template<class T>
	void reSet(T *p)
	{
		ptr = reinterpret_cast<char *>(p)+sizeof(T);
	}
	char getCh()
	{
		int temp = *reinterpret_cast<int *>(ptr);
		ptr += sizeof(int);
		return static_cast<char>(temp);
	}
	int getInt()
	{
		int temp = *reinterpret_cast<int *>(ptr);
		ptr += sizeof(int);
		return temp;
	}
	double getFloat()
	{
		double temp = *reinterpret_cast<double *>(ptr);
		ptr += sizeof(double);
		return temp;
	}
	long long getLong()
	{
		long long temp = *reinterpret_cast<long long *>(ptr);
		ptr += sizeof(long long);
		return temp;
	}
	void * getPointer()
	{
		void * temp = *reinterpret_cast<void **>(ptr);
		ptr += sizeof(void *);
		return temp;
	}
private:
	char *ptr;
};

ATHENA_END

#pragma warning(default:4290)
#pragma warning(default:4996)