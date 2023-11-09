#include "mString.h"
#include <iostream>
#include <cstdarg>
#include <stdio.h>
#include <stdarg.h>


bool mString::AllocAndWriteString(IN const char* pString)
{
	//字符串长度
	size_t sLen = strlen(pString);

	if (!sLen) //如果传入的字符串为空
	{
		return false;
	}
	//更新字符串的长度
	this->stringLen = sLen ;
	//申请堆空间
	this->pStringBuffer = new char[sLen+1];
	if (!this->pStringBuffer) //如果申请失败
	{
		return false;
	}
	
	//写入字符串
	if (strcpy_s(pStringBuffer, sLen+1, pString))//如果写入字符串没有成功
	{
		return false;
	}
	

	return true;
}

void mString::FreeStringBuffer(void)
{
	//释放字符串缓冲区
	delete[] this->pStringBuffer;
	this->pStringBuffer = nullptr;
	if (!this->mStringPtrVector.size())
	{
		for (std::vector<mString*>::iterator it = this->mStringPtrVector.begin(); it != this->mStringPtrVector.end(); ++it)
		{
			delete* it;
		}
	}
	this->stringLen = 0;

}

bool mString::IsStringBufferEmpty()
{
	if (!this->pStringBuffer)//如果缓冲区为空
	{
		return false;
	}

	return true;
}

bool mString::IsStringLengthZero()
{
	if (!this->stringLen) //如果字符串长度为0
	{
		return false;
	}
	return true;
}

bool mString::Reallocate(IN size_t size)
{
	//释放当前字符串缓冲区
	FreeStringBuffer();

	if (IsStringBufferEmpty() && IsStringLengthZero()) //如果字符串缓冲区和字符串长度都不为空
	{
		return false;
	}
	//重新申请
	this->pStringBuffer = new char[size+1];
	if (!this->pStringBuffer) //如果申请失败
	{
		return false;
	}

	return true;
}

char* mString::mSplicing(const char* pSourceString)
{
	char* pOriginalStringBuffer = new char[this->stringLen + 1]; //原字符串缓冲区
	strcpy_s(pOriginalStringBuffer, this->stringLen + 1, this->pStringBuffer);//保存原字符串
	size_t originalStringLen = this->stringLen;//原字符串长度

	//重新分配内存
	Reallocate(originalStringLen + strlen(pSourceString));
	//进行拼接
	if (memcpy_s(this->pStringBuffer, originalStringLen + strlen(pSourceString), pOriginalStringBuffer, originalStringLen))
	{
		return nullptr;
	}
	if (memcpy_s(this->pStringBuffer + originalStringLen, originalStringLen + strlen(pSourceString), pSourceString, strlen(pSourceString) + 1))
	{
		return nullptr;
	}

	//更新字符串长度
	this->stringLen = strlen(this->pStringBuffer);

	delete[] pOriginalStringBuffer;
	return this->pStringBuffer;
}

int mString::mSearch(const char* pString)
{
	size_t SearchStringLen = strlen(pString);//查找字符串的长度
	for (size_t i = 0; i < this->stringLen; ++i) //循环查找
	{
		if (!strncmp(this->pStringBuffer + i, pString, SearchStringLen)) //如果找到了
		{
			return i;
		}
	}
	return 0;
}

int mString::mReverseSearch(const char* pString)
{
	size_t SearchStringLen = strlen(pString);//查找字符串的长度
	for (size_t i = this->stringLen; i > -1 && i <= this->stringLen; --i) //循环查找
	{
		if (!strncmp(this->pStringBuffer + i, pString, SearchStringLen)) //如果找到了
		{
			return i;
		}
	}
	
	return 0;
}

mString::mString()
{
	this->pStringBuffer = nullptr;
	this->stringLen = 0;
	this->mStringPtrVector = {0};
}


mString::mString(IN const char* pString)
{
    //申请空间并且写入字符串
	if (!AllocAndWriteString(pString)) //如果失败
	{
		FreeStringBuffer();
	}
	
}

mString::mString(IN mString& stringObject)
{
	//释放原有的字符串缓冲区
	FreeStringBuffer();
	//申请空间并且写入字符串
	if (!AllocAndWriteString(stringObject.pStringBuffer)) //如果失败
	{
		FreeStringBuffer();
	}
	
}

mString::~mString()
{
	FreeStringBuffer();
}

const char* mString::GetString(void)
{
	return this->pStringBuffer;
}

char* mString::Copy(IN const char* pSourceString)
{
	if (IsStringBufferEmpty() && IsStringLengthZero()) //如果缓冲区不为空并且字符串长度不为0
	{
		if (!strcpy_s(this->pStringBuffer, strlen(pSourceString)+1, pSourceString)) //如果成功
		{
			return this->pStringBuffer;
		}
	}

	return nullptr;
}

char* mString::Copy(IN const char* pSourceString, IN size_t sourceStringLen)
{
	if (IsStringBufferEmpty() && IsStringLengthZero()) //如果缓冲区不为空并且字符串长度不为0
	{
		if (!strcpy_s(this->pStringBuffer, sourceStringLen+1, pSourceString)) //如果成功
		{
			return this->pStringBuffer;
		}
	}

	return nullptr;
}
	
char* mString::Splicing(IN const char* pSoureceString)
{
    
	char* pTemporaryStringBuffer = mSplicing(pSoureceString);//临时字符串缓冲区
	if (!pTemporaryStringBuffer)
	{
		return nullptr;
	}
	
	return pTemporaryStringBuffer;
}

char* mString::Splicing(IN char soureceChar)
{
	//转换字符串
	char TemporaryStringBuffer[sizeof(char)+1] = {0}; //临时字符串缓冲区
	sprintf_s(TemporaryStringBuffer, sizeof(char) +1, "%c", soureceChar);

	char* pTemporaryStringBuffer = mSplicing(TemporaryStringBuffer);//临时字符串缓冲区
	if (!pTemporaryStringBuffer)
	{
		return nullptr;
	}

	return pTemporaryStringBuffer;
}

char* mString::Splicing(IN int soureceInt)
{
	//转换字符串
	char TemporaryStringBuffer[sizeof(int)+1] = {0}; //临时字符串缓冲区
	sprintf_s(TemporaryStringBuffer, sizeof(int) + 1, "%d", soureceInt);

	char* pTemporaryStringBuffer = mSplicing(TemporaryStringBuffer);//临时字符串缓冲区
	if (!pTemporaryStringBuffer)
	{
		return nullptr;
	}

	return pTemporaryStringBuffer;
}

char* mString::Splicing(IN float soureceFloat)
{
	//转换字符串
	char TemporaryStringBuffer[sizeof(double) + 1] = { 0 }; //临时字符串缓冲区
	sprintf_s(TemporaryStringBuffer, sizeof(double) + 1, "%f", soureceFloat);

	char* pTemporaryStringBuffer = mSplicing(TemporaryStringBuffer);//临时字符串缓冲区
	if (!pTemporaryStringBuffer)
	{
		return nullptr;
	}

	return pTemporaryStringBuffer;
}

char mString::GetChar(IN int charIndex)
{
	return this->pStringBuffer[charIndex];
}

int mString::Search(IN const char* pString)
{
	return mSearch(pString);
}

int mString::Search(IN mString& stringObject)
{
	
	return mSearch(stringObject.GetString());;
}

int mString::Search(IN char ch)
{
	char pTemporaryBuffer[sizeof(char) + 1] = {ch,0}; //临时字符串缓冲区
	

	return mSearch(pTemporaryBuffer);
}

int mString::ReverseSearch(IN const char* pString)
{
	return mReverseSearch(pString);
}

int mString::ReverseSearch(IN mString& stringObject)
{
	return mReverseSearch(stringObject.GetString());
}

int mString::ReverseSearch(IN char ch)
{
	char pTemporaryBuffer[sizeof(char) + 1] = { ch,0 }; //临时字符串缓冲区


	return mReverseSearch(pTemporaryBuffer);
	
}

void mString::Split(IN const char* pFormatString)
{
	char* pTemporaryStringBuffer = new char[this->stringLen+1];//临时缓冲区对象
	//strcpy_s(pTemporaryStringBuffer, strlen(pTemporaryStringBuffer), this->pStringBuffer);
	memcpy_s(pTemporaryStringBuffer, this->stringLen + 1, this->pStringBuffer, this->stringLen + 1);
	for (size_t i = 0; i < this->stringLen; ++i)
	{
		if (!strncmp(pTemporaryStringBuffer + i, pFormatString, strlen(pFormatString)))
		{
			*(pTemporaryStringBuffer + i) = '\0';
			
		}
	}
	for (size_t i = 0; i < this->stringLen; ++i)
	{
		this->mStringPtrVector.push_back(new mString(pTemporaryStringBuffer+i));
		i += strlen(pTemporaryStringBuffer);
	}

	
}

void mString::Split(IN mString& stringObject)
{
	char* pTemporaryStringBuffer = new char[this->stringLen + 1];//临时缓冲区对象
	memcpy_s(pTemporaryStringBuffer, this->stringLen + 1, this->pStringBuffer, this->stringLen + 1);

	for (size_t i = 0; i < this->stringLen; ++i)
	{
		if (!strncmp(pTemporaryStringBuffer + i, stringObject.GetString(), strlen(stringObject.GetString())))
		{
			*(pTemporaryStringBuffer + i) = '\0';

		}
	}
	for (size_t i = 0; i < this->stringLen; ++i)
	{
		this->mStringPtrVector.push_back(new mString(pTemporaryStringBuffer + i));
		i += strlen(pTemporaryStringBuffer);
	}

	
}

int mString::Cmp(IN const char* pString)
{
	
	return strncmp(this->pStringBuffer, pString,strlen(pString));
}

int mString::mPrintf(IN const char* pForamt, ...)
{
	va_list args; // 声明一个变长参数列表
	va_start(args, pForamt); // 开始变长参数列表

	char buffer[256]; // 假设最大输出长度不超过256个字符
	int result = vsnprintf(buffer, sizeof(buffer), pForamt, args); // 使用vsprintf函数格式化字符串

	va_end(args); // 结束变长参数列表

	if (result >= 0) {
		std::cout << buffer;
		return result;
	}
	else {
		std::cerr << "格式化字符串错误" << std::endl;
		return -1;
	}

	
}

