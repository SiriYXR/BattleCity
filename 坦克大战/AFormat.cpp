#include "aformat.h"

#pragma warning(disable:4244)
#pragma warning(disable:4146)
#pragma warning(disable:4715)

ATHENA_BEGIN

AFormat format;

AFormat::~AFormat()
{

}

AFormat::AFormat()
{
	powNum = { { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000,
		100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000, 10000000000000000,
		100000000000000000, 1000000000000000000, 10000000000000000000 } };

	hexChar = { { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' } };

	int t = 10;
	char *p = reinterpret_cast<char *>(&t);
	if (*p == 10)
	{
		islittle = true;
	}
	else
	{
		islittle = false;
	}

	if (sizeof(p) == 8)
	{
		isx64 = true;
	}
	else
	{
		isx64 = false;
	}

}

int AFormat::printf(char *des, const char *fStr, ...)
{
	arg args(&fStr);
	char *tempBuffer ;
	if (des == nullptr)
	{
		throw ANULL("printf(char *,const char *,...):Pointer Can't Be NULL");
	}
	tempBuffer = des;

	formatInfo info ;
	charBuffer tempStr;

	char *s = const_cast<char *>(fStr);
	char *q = s;	

	while (*s!=0)
	{
		q = s;
		/*处理普通字符串*/
		strHandle(q, s, tempBuffer);

		/*遇到格式控制字符*/
		if (*s == '%')
		{
			s++;
			info.reSet();
			int len=0,digit=0;

			/*flag区段*/
			flagHandle(s, info);

			/*精度、长度区段*/
			digitHandle(s, len, digit);
			info.len = (len==0)?(-1):len;
			info.digit = (digit == 0) ? (6) : digit;

			/*是否无符号*/
			if (*s == 'u')
			{
				info.isUnsigned = true;
				info.type = inte;
				s++;
			}

			/*是否为“长”型*/
			if (*s == 'l')
			{
				info.isLong = true;
				s++;
			}
	
			/*具体控制字符*/
			typeHandle(s, info);

			/*处理格式分析结果*/
			if (info.type == inte)
			{
				integerHandle(tempBuffer, info, args,tempStr);
			}
			else if (info.type == ch)
			{
				chHandle(tempBuffer, info, args, tempStr);
			}
			else if (info.type == str)
			{
				strHandle(tempBuffer, info, args);
			}
			else if (info.type == floa)
			{
				floatHandle(tempBuffer, info, args, tempStr);
			}
			else if (info.type == e)
			{
				floatHandle(tempBuffer, info, args, tempStr);
			}
			else if (info.type == g)
			{
				floatHandle(tempBuffer, info, args, tempStr);
			}
			else if (info.type == ptr)
			{
				ptrHandle(tempBuffer, info, args, tempStr);
			}
			else if (info.type ==hex )
			{
				hexHandle(tempBuffer, info, args, tempStr);
			}
			else if (info.type == oct)
			{
				octHandle(tempBuffer, info, args, tempStr);
			}
			else if (info.type == bin)
			{
				binHandle(tempBuffer, info, args, tempStr);
			}
			else if (info.type == mod)
			{
				*tempBuffer = '%';
				tempBuffer++;
				*tempBuffer = 0;
			}

		}
	}

	return tempBuffer-des;
}

void AFormat::strHandle(char *&tempBuffer, formatInfo &info, arg &args)
{

	char *p = reinterpret_cast<char *>(args.getPointer());

	int size = strLen(p), len = info.len;
	if (size> info.len)
	{
		memCpy(tempBuffer, p, size + 1);
		tempBuffer += size;
	}
	else
	{
		if (info.isLeftAlign)
		{
			memCpy(tempBuffer, p, size);
			memSet(tempBuffer + size, info.fillChar, len - size);
			tempBuffer[len] = 0;
			tempBuffer += len;
		}
		else
		{
			memSet(tempBuffer, info.fillChar, len - size);
			memCpy(tempBuffer + len - size, p, size + 1);
			tempBuffer += len;
		}
	}


}

void AFormat::ptrHandle(char *&tempBuffer, formatInfo &info, arg &args, charBuffer &tempStr)
{

	char *container = tempStr.data();

	void *p = args.getPointer();

	ptrToAddress(p, container);

	int size = strLen(tempStr.data()), len = info.len;
	if (size> info.len)
	{
		memCpy(tempBuffer, tempStr.data(), size + 1);
		tempBuffer += size;
	}
	else
	{
		if (info.isLeftAlign)
		{
			memCpy(tempBuffer, tempStr.data(), size);
			memSet(tempBuffer + size, info.fillChar, len - size);
			tempBuffer[len] = 0;
			tempBuffer += len;
		}
		else
		{
			memSet(tempBuffer, info.fillChar, len - size);
			memCpy(tempBuffer + len - size, tempStr.data(), size + 1);
			tempBuffer += len;
		}
	}

}

void AFormat::binHandle(char *&tempBuffer, formatInfo &info, arg &args, charBuffer &tempStr)
{
	char *container = tempStr.data();

	if (info.isPreFix)
	{
		*container = 'b';
		container++;
	}

	if (info.isLong)
	{
		long long t = args.getLong();
		numToBin(t, container);
	}
	else
	{
		int t = args.getInt();
		numToBin(t, container);
	}

	int size = strLen(tempStr.data()), len = info.len;
	if (size> info.len)
	{
		memCpy(tempBuffer, tempStr.data(), size + 1);
		tempBuffer += size;
	}
	else
	{
		if (info.isLeftAlign)
		{
			memCpy(tempBuffer, tempStr.data(), size);
			memSet(tempBuffer + size, info.fillChar, len - size);
			tempBuffer[len] = 0;
			tempBuffer += len;
		}
		else
		{
			memSet(tempBuffer, info.fillChar, len - size);
			memCpy(tempBuffer + len - size, tempStr.data(), size + 1);
			tempBuffer += len;
		}
	}

}

void AFormat::octHandle(char *&tempBuffer, formatInfo &info, arg &args, charBuffer &tempStr)
{

	char *container = tempStr.data();

	if (info.isPreFix)
	{
		*container = '0';
		container++;
	}

	if (info.isLong)
	{
		long long t = args.getLong();
		numToOct(t, container);
	}
	else
	{
		int t = args.getInt();
		numToOct(t, container);
	}

	int size = strLen(tempStr.data()), len = info.len;
	if (size> info.len)
	{
		memCpy(tempBuffer, tempStr.data(), size + 1);
		tempBuffer += size;
	}
	else
	{
		if (info.isLeftAlign)
		{
			memCpy(tempBuffer, tempStr.data(), size);
			memSet(tempBuffer + size, info.fillChar, len - size);
			tempBuffer[len] = 0;
			tempBuffer += len;
		}
		else
		{
			memSet(tempBuffer, info.fillChar, len - size);
			memCpy(tempBuffer + len - size, tempStr.data(), size + 1);
			tempBuffer += len;
		}
	}

}

void AFormat::hexHandle(char *&tempBuffer, formatInfo &info, arg &args, charBuffer &tempStr)
{
	char *container = tempStr.data();
	
	if (info.isPreFix)
	{
		*container = '0';
		container++;
		if (info.isUp)
		{
			*container = 'X';
		}
		else
		{
			*container = 'x';
		}
		container++;
	}

	if (info.isLong)
	{
		long long t = args.getLong();
		numToHex(t, container,!info.isUp);
	}
	else
	{
		int t = args.getInt();
		numToHex(t, container, !info.isUp);
	}

	int size = strLen(tempStr.data()), len = info.len;
	if (size> info.len)
	{
		memCpy(tempBuffer, tempStr.data(), size + 1);
		tempBuffer += size;
	}
	else
	{
		if (info.isLeftAlign)
		{
			memCpy(tempBuffer, tempStr.data(), size);
			memSet(tempBuffer + size, info.fillChar, len - size);
			tempBuffer[len] = 0;
			tempBuffer += len;
		}
		else
		{
			memSet(tempBuffer, info.fillChar, len - size);
			memCpy(tempBuffer + len - size, tempStr.data(), size + 1);
			tempBuffer += len;
		}
	}

}

void AFormat::floatHandle(char *&tempBuffer, formatInfo &info, arg &args, charBuffer &tempStr)
{
	char *container = tempStr.data();
	double t = args.getFloat();

	if (info.type == floa)
	{
		fToStr(t, info.digit, container);
	}
	else if (info.type == e)
	{
		fToE(t, info.digit, container);
	}
	else if (info.type == g)
	{
		fToText(t, info.digit, container);
	}

	int size = strLen(tempStr.data()), len = info.len;
	if (size> info.len)
	{
		memCpy(tempBuffer, tempStr.data(), size + 1);
		tempBuffer += size;
	}
	else
	{
		if (info.isLeftAlign)
		{
			memCpy(tempBuffer, tempStr.data(), size);
			memSet(tempBuffer + size, info.fillChar, len - size);
			tempBuffer[len] = 0;
			tempBuffer += len;
		}
		else
		{
			memSet(tempBuffer,info.fillChar,len-size);
			memCpy(tempBuffer + len - size, tempStr.data(), size + 1);
			tempBuffer += len;
		}
	}

}

void AFormat::chHandle(char *&tempBuffer, formatInfo &info, arg &args, charBuffer &tempStr)
{
	char temp = args.getCh();

	int size =1, len = info.len;
	if (size>=info.len)
	{
		*tempBuffer = temp;
		tempBuffer++;
		*tempBuffer = 0;
	}
	else
	{
		if (info.isLeftAlign)
		{
			*tempBuffer = temp;
			memSet(tempBuffer + size, info.fillChar, len - size);
			tempBuffer[len] = 0;
			tempBuffer += len;
		}
		else
		{
			memSet(tempBuffer, info.fillChar, len - size);
			tempBuffer[len - size] = temp;
			tempBuffer += len;
			*tempBuffer = 0;
		}
	}

}

void AFormat::integerHandle(char *&tempBuffer, formatInfo &info,arg &args,charBuffer &tempStr)
{
	char *container = tempStr.data();

	if (info.isUnsigned)
	{
		if (info.isLong)
		{
			bigInt t = args.getLong();
			if (info.isPlus)
			{
				*container = '+';
				container++;
			}
			integerToStr(t, 19, container);
		}
		else
		{
			unsigned int t = args.getInt();
			if (info.isPlus)
			{
				*container = '+';
				container++;
			}
			integerToStr(t, 10, container);
		}
	}
	else
	{
		if (info.isLong)
		{
			long long t = args.getLong();
			if (info.isPlus&&t>0)
			{
				*container = '+';
				container++;
			}
			integerToStr(t, 19, container);
		}
		else
		{
			int t = args.getInt();
			if (info.isPlus&&t>0)
			{
				*container = '+';
				container++;
			}
			integerToStr(t, 10, container);
		}
	}

	int size = strLen(tempStr.data()),len=info.len;
	if ( size> info.len)
	{
		memCpy(tempBuffer,tempStr.data(),size+1 );
		tempBuffer+=size;
	}
	else
	{
		if (info.isLeftAlign)
		{
			memCpy(tempBuffer , tempStr.data(), size);
			memSet(tempBuffer + size, info.fillChar, len - size);
			tempBuffer[len] = 0;
			tempBuffer += len;
			
		}
		else
		{
			memSet(tempBuffer, info.fillChar, len - size);
			memCpy(tempBuffer + len - size, tempStr.data(), size + 1);
			tempBuffer += len;
		}
	}

}

void AFormat::digitHandle(char *&s, int &len, int &digit)
{

	while (isNum(*s) && *s != 0)
	{
		len = len * 10 + (*s - '0');
		s++;
	}

	if (*s == '.')
	{
		s++;
		while (isNum(*s) && *s != 0)
		{
			digit = digit * 10 + (*s - '0');
			s++;
		}
	}

}

void AFormat::typeHandle(char *&s, formatInfo &info)
{

	if (*s == 'd' || *s == 'i')
	{
		info.type = inte;
	}
	else if (*s == 's')
	{
		info.type = str;
	}
	else if (*s == 'c')
	{
		info.type = ch;
	}
	else if (*s == 'f')
	{
		info.type = floa;
	}
	else if (*s == 'p')
	{
		info.type = ptr;
	}
	else if (*s == 'e')
	{
		info.type = e;
	}
	else if (*s == 'g')
	{
		info.type = g;
	}
	else if (*s == 'o')
	{
		info.type = oct;
	}
	else if (*s == 'O')
	{
		info.type = oct;
		info.isUp = true;
	}
	else if (*s == 'x')
	{
		info.type = hex;
	}
	else if (*s == 'X')
	{
		info.type = hex;
		info.isUp = true;
	}
	else if (*s == 'b')
	{
		info.type = bin;
	}
	else if (*s == '%')
	{
		info.type = mod;
	}
	else
	{
		info.type =(info.type==inte)?inte:null;
	}
	s++;

}

void AFormat::flagHandle(char *&s, formatInfo &info)
{

	while (*s != 0)
	{
		if (*s == '-')
		{
			info.isLeftAlign = true;
		}
		else if (*s == '+')
		{
			info.isPlus = true;
		}
		else if (*s == '0')
		{
			info.fillChar = '0';
		}
		else if (*s == '#')
		{
			info.isPreFix = true;
		}
		else
		{
			break;
		}
		s++;
	}

}

void AFormat::strHandle(char *&s, char *&q, char *&tempBuffer)
{

	while (*s != '%'&&*s != 0)
	{
		s++;
	}

	if (s != q)
	{
		while (q<s)
		{
			*tempBuffer = *q;
			tempBuffer++;
			q++;
		}
		*tempBuffer = 0;
	}

}

AFormat::bigInt AFormat::octToNum(const char *str)
{
	if (str == nullptr)
	{
		throw ANULL("octToNum(const char *):Pointer Can't Be NULL");
	}

	bigInt result = 0;
	char *temp = const_cast<char *>(str);
	temp += strLen(temp) - 1;
	bigInt currentPow = 1;

	for (; temp >= str; temp--)
	{
		result += currentPow*(*temp - '0');
		currentPow *= 8;
	}

	return result;

}

template<class T>
const char *AFormat::numToHex(T num, char *container, bool isLower)
{

	char *temp;
	if (container == nullptr)
	{
		temp = buffer.data();
	}
	else
	{
		temp = container;
	}

	if (num == 0)
	{
		temp[0] = '0';
		temp[1] = 0;
		return temp;
	}

	char *iterator = reinterpret_cast<char *>(&num);
	int size = sizeof(T), currentIndex = 0, start = 0;
	int flag;
	if (islittle)
	{
		flag = -1;
		iterator += size - 1;
		char *p = iterator;
		for (; *p == 0; p--)
		{
			iterator += flag;
			start++;
		}
	}
	else
	{
		flag = 1;
		char *p = iterator;
		for (; *p == 0; p++)
		{
			iterator += flag;
			start++;
		}
	}

	char num1[5], num2[9];
	num1[4] = 0;

	for (int i = start; i < size; i++)
	{
		numToBin(*iterator, num2);
		memCpy(num1, num2, 4);
		temp[currentIndex++] = hexChar[binToShort(num1)];
		temp[currentIndex++] = hexChar[binToShort(num2 + 4)];
		iterator += flag;
	}

	temp[currentIndex] = 0;

	if (!isLower)
	{
		strUpr(temp);
	}

	char *check = temp;
	while (*check == '0')
	{
		check++;
	}
	if (check != temp)
	{
		memCpy(temp, check, strlen(check) + 1);
	}
	return temp;
}

const char *AFormat::numToOct(bigInt num, char *container)
{

	char *temp;
	if (container == nullptr)
	{
		temp = buffer.data();
	}
	else
	{
		temp = container;
	}

	int currentIndex = 0, bit;
	charBuffer octStack(100);
	char *sta = octStack.data();
	for (;num>0;)
	{
		bit = num % 8;
		sta[currentIndex++] = bit + '0';
		num /= 8;
	}

	for (int i = 0; i < currentIndex; i++)
	{
		temp[i] = sta[currentIndex - i-1];
	}

	temp[currentIndex] = 0;
	return temp;
}

template<class T>
const char *AFormat::numToBin(T num, char *container)
{
	char *temp;
	if (container == nullptr)
	{
		temp = buffer.data();
	}
	else
	{
		temp = container;
	}

	unsigned char *iterator = reinterpret_cast<unsigned char *>(&num);
	int bits = sizeof(num), currentIndex = 0, flag = 1;
	if (islittle)
	{
		iterator += bits - 1;
		flag = -1;
	}

	unsigned char tempBit;
	for (int i = 0; i < bits; i++)
	{
		tempBit = 128;
		for (int j = 0; j < 8; j++)
		{
			if ((tempBit&(*iterator)) == tempBit)
			{
				temp[currentIndex] = '1';
			}
			else
			{
				temp[currentIndex] = '0';
			}
			currentIndex++;
			tempBit >>= 1;
		}
		iterator += flag;
	}
	temp[currentIndex] = 0;
	return temp;
}


template<class T>
T AFormat::hexToNum(T result, int bits, const char* hexChar)
{
	int flag = 1;
	unsigned char *iterator = reinterpret_cast<unsigned char *>(&result);
	if (!islittle)
	{
		flag = -1;
		iterator += bits - 1;
	}

	int len = strLen(hexChar);

	memCpy(buffer.data(), hexChar, len);
	char *hexIterrator = buffer.data(), *p = hexIterrator;

	strUpr(hexIterrator);
	hexIterrator += len - 1;
	unsigned char tempResult;
	for (; hexIterrator >= p;)
	{
		tempResult = 0;
		if (hexIterrator - p >= 1)
		{
			if (isNum(*hexIterrator))
			{
				tempResult = *hexIterrator - '0';
			}
			else
			{
				tempResult = *hexIterrator - 'A' + 10;
			}
			hexIterrator--;
			if (isNum(*hexIterrator))
			{
				tempResult += (*hexIterrator - '0') * 16;
			}
			else
			{
				tempResult += (*hexIterrator - 'A' + 10) * 16;
			}
			hexIterrator--;
			*iterator = tempResult;
			iterator += flag;
		}
		else
		{
			if (isNum(*hexIterrator))
			{
				tempResult = *hexIterrator - '0';
			}
			else
			{
				tempResult = *hexIterrator - 'A' + 10;
			}
			*iterator = tempResult;
			hexIterrator--;
			iterator += flag;
		}
	}

	return result;
}

const char *AFormat::ptrToAddress(void *ptr, char *container, bool isLower)
{
	char *temp;
	if (container == nullptr)
	{
		temp = buffer.data();
	}
	else
	{
		temp = container;
	}

	char tempStr[16];
	numToHex(ptr, tempStr, isLower);
	int size = strLen(tempStr);

	if (isx64)
	{
		memSet(temp, '0', 8);
		memCpy(temp + 16 - size, tempStr, size + 1);
	}
	else
	{
		memSet(temp, '0', 4);
		memCpy(temp + 8 - size, tempStr, size + 1);
	}

	return temp;
}

const char *AFormat::fToText(double num, int digit, char *container)
{
	char *temp;
	if (container == nullptr)
	{
		temp = buffer.data();
	}
	else
	{
		temp = container;
	}

	char indexStr[12];
	memSet(indexStr, '0', 12);
	indexStr[11] = 0;
	int flag;
	unsigned char *iterator = reinterpret_cast<unsigned char *>(&num);
	int currentIndex = 0;

	if (islittle)
	{
		flag = -1;
		iterator += 7;
	}
	else
	{
		flag = 1;
	}

	unsigned char tempBit = 1 << 6;
	for (int i = 0; i < 7; i++, currentIndex++)
	{
		if ((*iterator&tempBit) == tempBit)
		{
			indexStr[currentIndex] = '1';
		}
		tempBit >>= 1;
	}

	iterator += flag;

	tempBit = 1 << 7;
	for (int i = 0; i < 4; i++, currentIndex++)
	{
		if ((*iterator&tempBit) == tempBit)
		{
			indexStr[currentIndex] = '1';
		}
		tempBit >>= 1;
	}

	int index = binToInt(indexStr) - 1023;

	if (index < -14 || index >= 10)
	{
		return fToE(num, digit, temp);
	}

	return fToStr(num, digit, temp);
}

const char *AFormat::fToE(double num, int digit, char *container, bool isLower)
{
	char *temp, *q;
	if (container == nullptr)
	{
		temp = buffer.data();
	}
	else
	{
		temp = container;
	}
	q = temp;

	if (num < 0)
	{
		temp[0] = '-';
		temp++;
		num = -num;
	}

	int index = 0;
	if (num >= 10)
	{
		for (; num >= 10; index++)
		{
			num /= 10;
		}
	}
	else if (num<1)
	{
		for (; num<1; index--)
		{
			num *= 10;
		}
	}

	fToStr(num, digit, temp);
	temp += strLen(temp);
	*temp = isLower ? 'e' : 'E';
	temp++;
	integerToStr(index, 2, temp);

	return q;
}

const char *AFormat::fToStr(double num, int digit, char *container)
{
	char *temp, *q;
	if (container == nullptr)
	{
		temp = buffer.data();
	}
	else
	{
		temp = container;
	}
	q = temp;

	if (num < 0)
	{
		temp[0] = '-';
		temp++;
		num = -num;
	}

	bigInt integer = static_cast<bigInt>(num);

	if (digit <= 0)
	{
		num -= integer;
		if (num > 0.5)
		{
			integer++;
		}
		integerToStr(integer, 19, temp);
		return temp;
	}

	integerToStr(integer, 19, temp);
	num -= integer;
	temp += strLen(temp);

	*temp = '.';
	temp++;
	integer = 0;

	int bit;
	for (int i = 0; i < digit; i++)
	{
		num *= 10;
		bit = static_cast<int>(num);
		num -= bit;
		integer *= 10;
		integer += bit;
	}

	if (num > 0.5)
	{
		integer += 1;
	}
	integerToStr(integer, 19, temp);

	int realDigit = strLen(temp);
	if (realDigit < digit)
	{
		for (; realDigit < digit; realDigit++)
		{
			temp[realDigit] = '0';
		}
		temp[digit] = 0;
	}

	return q;
}

template<class T>
T AFormat::binToNum(T result, int bits, const char *bin)
{
	int flag = 1;
	unsigned char *iterator = reinterpret_cast<unsigned char *>(&result);
	if (!islittle)
	{
		iterator += bits - 1;
		flag = -1;
	}

	char *currentPosition = const_cast<char *>(bin + strLen(bin) - 1);
	unsigned char tempBit;

	for (int i = 0; i < bits; i++)
	{
		tempBit = 1;
		for (int j = 0; j<8; j++)
		{
			if (*currentPosition == '1')
			{
				*iterator |= tempBit;
			}
			tempBit <<= 1;
			currentPosition--;
			if (currentPosition == bin - 1)
			{
				return result;
			}
		}
		iterator += flag;
	}
}

double AFormat::strToDouble(const char *str)
{
	if (str == nullptr)
	{
		throw ANULL("strToDouble(const char *):Pointer Can't Be NULL");
	}

	double integer = 0, floating = 0, power = 1, index = 0;
	int i = 0;

	for (;; i++)
	{
		if (!isNum(str[i]))
		{
			break;
		}
		integer *= 10;
		integer += str[i] - '0';
	}

	if (str[i] == '.')
	{
		i++;
		for (;; i++)
		{
			if (!isNum(str[i]))
			{
				break;
			}
			power *= 10;
			floating *= 10;
			floating += str[i] - '0';
		}
	}

	if (str[i] == 'e' || str[i] == 'E')
	{
		i++;
		index = strToDouble(str + i);
	}

	return (integer + floating / power)*pow(index);
}

long long AFormat::strToInt(const char *str)
{
	if (str == nullptr)
	{
		throw ANULL("strToInt(const char *):Pointer Can't Be NULL");
	}

	long long num = 0;
	bool flag = false;
	int currentIndex = 0;

	if (str[currentIndex] == '-')
	{
		flag = true;
		currentIndex++;
	}

	for (;; currentIndex++)
	{
		if (!isNum(str[currentIndex]))
		{
			break;
		}
		num *= 10;
		num += str[currentIndex] - '0';
	}

	if (flag)
	{
		num = -num;
	}

	return num;
}

template <class T>
const char *AFormat::integerToStr(T num, int bits, char *container)
{
	char *temp;
	if (container == nullptr)
	{
		temp = buffer.data();
	}
	else
	{
		temp = container;
	}

	int maxPow = bits;
	int currentIndex = 0;
	int tempNum;

	if (num == 0)
	{
		temp[0] = '0';
		temp[1] = 0;
		return temp;
	}

	if (num < 0)
	{
		temp[currentIndex++] = '-';
		num = -num;
	}

	for (; maxPow >= 0; maxPow--)
	{
		if (num / powNum[maxPow] != 0)
		{
			break;
		}
	}

	for (; maxPow >= 0; maxPow--)
	{
		tempNum = num / powNum[maxPow];
		temp[currentIndex] = tempNum + '0';
		num -= tempNum*powNum[maxPow];
		currentIndex++;
	}

	temp[currentIndex] = 0;

	return temp;
}

/*pow函数的作者是刘智睿*/
double AFormat::pow(double m)
{
	int i, j;
	double result = 0, x, tmpm = 1;
	double num = 10;
	x = 1 / num;
	x--;
	m = -m;
	for (i = 1; tmpm>1e-12 || tmpm < -1e-12; i++)
	{
		for (j = 1, tmpm = 1; j <= i; j++)
			tmpm *= (m - j + 1)*x / j;
		result += tmpm;
	}
	result += 1;
	return result;
}

void *AFormat::memCpy(void *des, const void  *src, size_t count)
{
	if (des == nullptr || src == nullptr)
	{
		throw ANULL("memSet(void *,const void *,size_t):Pointer Can't Be NULL");
	}

	const char *p = reinterpret_cast<const char *>(src);
	char *q = reinterpret_cast<char *>(des);

	if ((p > q) || (p + count < q))//src与des无重叠的情况
	{
		for (size_t i = 0; i < count; i++)
		{
			q[i] = p[i];
		}
	}
	else//src与des有重叠
	{
		for (size_t i = count - 1; i <count; i--)
		{
			q[i] = p[i];
		}
	}

	return des;
}

void AFormat::testFun()
{
	numToBin((char )100);
	numToBin((unsigned char)100);
	numToBin((short)100);
	numToBin((unsigned short)100);
	numToBin((int)100);
	numToBin((unsigned int)100);
	numToBin((long)100);
	numToBin((unsigned long)100);
	numToBin((long long)100);
	numToBin((unsigned long long)100);
	numToBin((float)100);
	numToBin((double)100);
	numToBin((long double)100);
	numToBin((bool)100);

	numToHex((char)100);
	numToHex((unsigned char)100);
	numToHex((short)100);
	numToHex((unsigned short)100);
	numToHex((int)100);
	numToHex((unsigned int)100);
	numToHex((long)100);
	numToHex((unsigned long)100);
	numToHex((long long)100);
	numToHex((unsigned long long)100);
	numToHex((float)100);
	numToHex((double)100);
	numToHex((long double)100);
	numToHex((bool)100);
}

void *AFormat::memSet(void *des, char val, size_t count)
{
	if (des == nullptr)
	{
		throw ANULL("memSet(void *,char,size_t):Pointer Can't Be NULL");
	}

	char *p = reinterpret_cast<char *>(des);
	for (size_t i = 0; i < count; i++)
	{
		p[i] = val;
	}
	return des;
}

int AFormat::strLen(const char *str)
{
	if (str == nullptr)
	{
		throw ANULL("strLen(const char *):Pointer Can't Be NULL");
	}

	int len = 0;
	for (; *str != 0; str++, len++);
	return len;
}

char *AFormat::strLwr(char *str)
{
	if (str == nullptr)
	{
		throw ANULL("strUpr(char *):Pointer Can't Be NULL");
	}

	for (int i = 0; str[i] != 0; i++)
	{
		if (str[i] >= 'A'&&str[i] <= 'Z')
		{
			str[i] += 32;
		}
	}
	return str;
}

char *AFormat::strUpr(char *str)
{
	if (str == nullptr)
	{
		throw ANULL("strUpr(char *):Pointer Can't Be NULL");
	}

	for (int i = 0; str[i] != 0; i++)
	{
		if (str[i] >= 'a'&&str[i] <= 'z')
		{
			str[i] -= 32;
		}
	}
	return str;
}

bool AFormat::isNum(char ch)
{
	return ch >= '0'&&ch <= '9';
}

bool AFormat::isX64()
{
	return isx64;
}

bool AFormat::isLittle()
{
	return islittle;
}

char AFormat::hexToChar(const char *str)
{
	if (str == nullptr)
	{
		throw ANULL("hexToChar(const char *):Pointer Can't Be NULL");
	}

	char temp = 0;
	return hexToNum(temp, sizeof(temp), str);
}

short AFormat::hexToShort(const char *str)
{
	if (str == nullptr)
	{
		throw ANULL("hexToShort(const char *):Pointer Can't Be NULL");
	}

	short temp = 0;
	return hexToNum(temp, sizeof(temp), str);
}

int AFormat::hexToInt(const char *str)
{
	if (str == nullptr)
	{
		throw ANULL("hexToInt(const char *):Pointer Can't Be NULL");
	}

	int temp = 0;
	return hexToNum(temp, sizeof(temp), str);
}

float AFormat::hexToFloat(const char *str)
{
	if (str == nullptr)
	{
		throw ANULL("hexToFloat(const char *):Pointer Can't Be NULL");
	}

	float temp = 0;
	return hexToNum(temp, sizeof(temp), str);
}

double AFormat::hexToDouble(const char *str)
{
	if (str == nullptr)
	{
		throw ANULL("hexToDouble(const char *):Pointer Can't Be NULL");
	}

	double temp = 0;
	return hexToNum(temp, sizeof(temp), str);
}

long long AFormat::hexToBigInt(const char *str)
{
	if (str == nullptr)
	{
		throw ANULL("hexToBigInt(const char *):Pointer Can't Be NULL");
	}

	long long temp = 0;
	return hexToNum(temp, sizeof(temp), str);
}

const char *AFormat::iToStr(int num, char *container)
{
	return integerToStr(num, 10, container);
}

const char *AFormat::lToStr(long long num, char *container)
{
	return integerToStr(num, 19, container);
}

const char *AFormat::uiToStr(unsigned int num, char *container)
{
	return integerToStr(num, 10, container);
}

const char *AFormat::ulToStr(bigInt num, char *container)
{
	return integerToStr(num, 19, container);
}

char AFormat::binToChar(const char *bin)
{
	if (bin == nullptr)
	{
		throw ANULL("binToChar(const char *):Pointer Can't Be NULL");
	}

	char temp = 0;
	return binToNum(temp, sizeof(temp), bin);
}

short AFormat::binToShort(const char *bin)
{
	if (bin == nullptr)
	{
		throw ANULL("binToShort(const char *):Pointer Can't Be NULL");
	}

	short temp = 0;
	return binToNum(temp, sizeof(temp), bin);
}

int AFormat::binToInt(const char *bin)
{
	if (bin == nullptr)
	{
		throw ANULL("binToInt(const char *):Pointer Can't Be NULL");
	}

	int temp = 0;
	return binToNum(temp, sizeof(temp), bin);
}

float AFormat::binToFloat(const char *bin)
{
	if (bin == nullptr)
	{
		throw ANULL("binToFloat(const char *):Pointer Can't Be NULL");
	}

	float temp = 0;
	return binToNum(temp, sizeof(temp), bin);
}

double AFormat::binToDouble(const char *bin)
{
	if (bin == nullptr)
	{
		throw ANULL("binToDouble(const char *):Pointer Can't Be NULL");
	}

	double temp = 0;
	return binToNum(temp, sizeof(temp), bin);
}

long long AFormat::binToBigInt(const char *bin)
{
	if (bin == nullptr)
	{
		throw ANULL("binToBigInt(const char *):Pointer Can't Be NULL");
	}

	long long temp = 0;
	return binToNum(temp, sizeof(temp), bin);
}

#pragma warning(default:4244)
#pragma warning(default:4146)
#pragma warning(default:4715)

ATHENA_END
