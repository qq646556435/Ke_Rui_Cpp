#pragma once
#include <windows.h>
#include <vector>
//ASCII格式的字符串类
class mString
{
private:
	char* pStringBuffer; //指向字符串缓冲区的指针
	size_t stringLen; //字符串长度
	std::vector<mString*> mStringPtrVector;//mStringPtrVector
private:
	/*
	  函数名称: 申请堆空间并且写入字符串
	  参数1: 写入字符串的指针
	  返回值: 成功返回 ture,否则返回 false
	*/
	bool AllocAndWriteString(IN const char* pString);
	/*
	  函数名称:释放申请的堆空间
	  参数1: 无参
	  返回值:成功返回 ture,否则返回 false
	*/
	void FreeStringBuffer(void);
	
	/*
	 函数名称: 字符串缓冲区是否为空
	 参数1: 无参
	 返回值 不为空返回ture,否则返回 false
	*/
	bool IsStringBufferEmpty();
	/*
	 函数名称: 字符串长度是否为0
	 参数1: 无参
	 返回值:不为0返回ture,否则返回 false
	*/
	bool IsStringLengthZero();
	/*
	 函数名称: 重新申请堆空间
	 参数1: 要申请空间的大小
	 返回值: 返回新空间的地址
	*/
	bool Reallocate(IN size_t size);
	/*
	 函数名称：字符串拼接
	 参数: 要拼接的字符串
	 返回值: 返回拼接后的字符串指针
	*/
	char* mSplicing(const char* pSourceString);
	/*
	 函数名称: 字符串查找
	 参数1: 要查找的字符串
	 返回值: 返回查找到的字符串下标
	*/
	int mSearch(const char* pString);
	/*
	 函数名称: 字符串倒查
	 参数1: 要查找的字符串
	 返回值: 返回值查找到的字符串下标
	*/
	int mReverseSearch(const char* pString);
	
public:
	mString();
	mString(IN const char* pString);
	mString(IN mString& stringObject);
	~mString();
	/*
	 函数名称: 获取字符串
	 参数1: 无参
	 返回值: 返回字符串的指针
	*/
	const char* GetString(void);
	/*
	 函数名称: 字符串拷贝
	 参数1: 指向源字符的指针
	 返回值: 返回拷贝后字符串的指针  
	*/
	char* Copy(IN const char* pSourceString);
	/*
	 函数名称: 字符串拷贝
	 参数1: 指向源字符的指针
	 参数2: 要拷贝的字符串长度,不包含字符'\0'
	 返回值: 返回拷贝后字符串的指针
	*/
	char* Copy(IN const char* pSourceString,IN size_t sourceStringLen);
	/*
	 函数名称: 拼接字符串
	 参数1: 指向源字符串的指针
	 返回值: 返回拼接后的字符串指针 
	*/
	char* Splicing(IN const char* pSoureceString);
	/*
	 函数名称: 拼接字符
	 参数1: 源字符
	 返回值: 返回拼接后的字符串指针
	*/
	char* Splicing(IN char soureceChar);
	/*
	 函数名称: 拼接整数
	 参数1: 源整数
	 返回值: 返回拼接后的字符串指针
	*/
	char* Splicing(IN int soureceInt);
	/*
	 函数名称: 拼接小数
	 参数1: 源小数
	 返回值: 返回拼接后的字符串指针
	*/
	char* Splicing(IN float soureceFloat);
	/*
	 函数名: 获取字符
	 参数1: 字符下标
	 返回值: 返回查找到的字符  
	*/
	char GetChar(IN int charIndex);
	/*
	 函数名: 搜索字符串
	 参数1: 指向要搜索字符串的指针
	 返回值: 返回搜索到的字符串的下标
	*/
	int Search(IN const char* pString);
	/*
	 函数名: 搜索字符串
	 参数1:  要搜索的字符串对象
	 返回值: 返回搜索到的字符串的下标
	*/
	int Search(IN mString& stringObject);
	/*
	 函数名: 搜索字符
	 参数1: 要搜索的字符
	 返回值: 返回搜索到字符的下标
	*/
	int Search(IN char ch);
	/*
	 函数名: 反向搜索字符串
	 参数1: 指向要搜索字符串的指针
	 返回值: 返回搜索到的字符串的下标
	*/
	int ReverseSearch(IN const char* pString);
	/*
	 函数名: 反向搜索字符串
	 参数1: 要搜索的字符串对象
	 返回值: 返回搜索到的字符串的下标
	*/
	int ReverseSearch(IN mString& stringObject);
	/*
	 函数名: 反向搜索字符
	 参数1: 指向要搜索字符
	 返回值: 返回搜索到的字符的下标
	*/
	int ReverseSearch(IN char ch);
	/*
	 函数名: 字符串分割
	 参数1: 分割的格式
	 返回值: 返回分割后的字符串的指针
	*/
	void Split(IN const char* pFormatString);
	/*
	 函数名: 字符串分割
	 参数1: 分割的格式
	 返回值: 返回分割后的字符串的指针
	*/
	void Split(IN mString& stringObject);
	/*
	 函数名: 字符串比较
	 参数1: 要比较的字符串
	 返回值:
	 如果 str1 等于 str2，则 StringCmp 返回0。
     如果 str1 小于 str2，则 StringCmp 返回一个负整数（通常为-1）。
     如果 str1 大于 str2，则 StringCmp 返回一个正整数（通常为1）。
	*/
	int Cmp(IN const char* pString);
	/*
	 函数名:打印字符串
	 参数1: 指定要输出的文本格式
	 参数2: ...：省略号表示可以有多个参数，这些参数与 pformat 字符串中的格式占位符相匹配。
	 返回值: 返回输出字符串的长度,不包含字符'\0'
	*/
	int mPrintf(IN const char* pForamt, ...);
	
		
};