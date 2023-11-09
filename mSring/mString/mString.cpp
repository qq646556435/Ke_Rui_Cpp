#include "mString.h"
#include <iostream>
#include <cstdarg>
#include <stdio.h>
#include <stdarg.h>


bool mString::AllocAndWriteString(IN const char* pString)
{
	//�ַ�������
	size_t sLen = strlen(pString);

	if (!sLen) //���������ַ���Ϊ��
	{
		return false;
	}
	//�����ַ����ĳ���
	this->stringLen = sLen ;
	//����ѿռ�
	this->pStringBuffer = new char[sLen+1];
	if (!this->pStringBuffer) //�������ʧ��
	{
		return false;
	}
	
	//д���ַ���
	if (strcpy_s(pStringBuffer, sLen+1, pString))//���д���ַ���û�гɹ�
	{
		return false;
	}
	

	return true;
}

void mString::FreeStringBuffer(void)
{
	//�ͷ��ַ���������
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
	if (!this->pStringBuffer)//���������Ϊ��
	{
		return false;
	}

	return true;
}

bool mString::IsStringLengthZero()
{
	if (!this->stringLen) //����ַ�������Ϊ0
	{
		return false;
	}
	return true;
}

bool mString::Reallocate(IN size_t size)
{
	//�ͷŵ�ǰ�ַ���������
	FreeStringBuffer();

	if (IsStringBufferEmpty() && IsStringLengthZero()) //����ַ������������ַ������ȶ���Ϊ��
	{
		return false;
	}
	//��������
	this->pStringBuffer = new char[size+1];
	if (!this->pStringBuffer) //�������ʧ��
	{
		return false;
	}

	return true;
}

char* mString::mSplicing(const char* pSourceString)
{
	char* pOriginalStringBuffer = new char[this->stringLen + 1]; //ԭ�ַ���������
	strcpy_s(pOriginalStringBuffer, this->stringLen + 1, this->pStringBuffer);//����ԭ�ַ���
	size_t originalStringLen = this->stringLen;//ԭ�ַ�������

	//���·����ڴ�
	Reallocate(originalStringLen + strlen(pSourceString));
	//����ƴ��
	if (memcpy_s(this->pStringBuffer, originalStringLen + strlen(pSourceString), pOriginalStringBuffer, originalStringLen))
	{
		return nullptr;
	}
	if (memcpy_s(this->pStringBuffer + originalStringLen, originalStringLen + strlen(pSourceString), pSourceString, strlen(pSourceString) + 1))
	{
		return nullptr;
	}

	//�����ַ�������
	this->stringLen = strlen(this->pStringBuffer);

	delete[] pOriginalStringBuffer;
	return this->pStringBuffer;
}

int mString::mSearch(const char* pString)
{
	size_t SearchStringLen = strlen(pString);//�����ַ����ĳ���
	for (size_t i = 0; i < this->stringLen; ++i) //ѭ������
	{
		if (!strncmp(this->pStringBuffer + i, pString, SearchStringLen)) //����ҵ���
		{
			return i;
		}
	}
	return 0;
}

int mString::mReverseSearch(const char* pString)
{
	size_t SearchStringLen = strlen(pString);//�����ַ����ĳ���
	for (size_t i = this->stringLen; i > -1 && i <= this->stringLen; --i) //ѭ������
	{
		if (!strncmp(this->pStringBuffer + i, pString, SearchStringLen)) //����ҵ���
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
    //����ռ䲢��д���ַ���
	if (!AllocAndWriteString(pString)) //���ʧ��
	{
		FreeStringBuffer();
	}
	
}

mString::mString(IN mString& stringObject)
{
	//�ͷ�ԭ�е��ַ���������
	FreeStringBuffer();
	//����ռ䲢��д���ַ���
	if (!AllocAndWriteString(stringObject.pStringBuffer)) //���ʧ��
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
	if (IsStringBufferEmpty() && IsStringLengthZero()) //�����������Ϊ�ղ����ַ������Ȳ�Ϊ0
	{
		if (!strcpy_s(this->pStringBuffer, strlen(pSourceString)+1, pSourceString)) //����ɹ�
		{
			return this->pStringBuffer;
		}
	}

	return nullptr;
}

char* mString::Copy(IN const char* pSourceString, IN size_t sourceStringLen)
{
	if (IsStringBufferEmpty() && IsStringLengthZero()) //�����������Ϊ�ղ����ַ������Ȳ�Ϊ0
	{
		if (!strcpy_s(this->pStringBuffer, sourceStringLen+1, pSourceString)) //����ɹ�
		{
			return this->pStringBuffer;
		}
	}

	return nullptr;
}
	
char* mString::Splicing(IN const char* pSoureceString)
{
    
	char* pTemporaryStringBuffer = mSplicing(pSoureceString);//��ʱ�ַ���������
	if (!pTemporaryStringBuffer)
	{
		return nullptr;
	}
	
	return pTemporaryStringBuffer;
}

char* mString::Splicing(IN char soureceChar)
{
	//ת���ַ���
	char TemporaryStringBuffer[sizeof(char)+1] = {0}; //��ʱ�ַ���������
	sprintf_s(TemporaryStringBuffer, sizeof(char) +1, "%c", soureceChar);

	char* pTemporaryStringBuffer = mSplicing(TemporaryStringBuffer);//��ʱ�ַ���������
	if (!pTemporaryStringBuffer)
	{
		return nullptr;
	}

	return pTemporaryStringBuffer;
}

char* mString::Splicing(IN int soureceInt)
{
	//ת���ַ���
	char TemporaryStringBuffer[sizeof(int)+1] = {0}; //��ʱ�ַ���������
	sprintf_s(TemporaryStringBuffer, sizeof(int) + 1, "%d", soureceInt);

	char* pTemporaryStringBuffer = mSplicing(TemporaryStringBuffer);//��ʱ�ַ���������
	if (!pTemporaryStringBuffer)
	{
		return nullptr;
	}

	return pTemporaryStringBuffer;
}

char* mString::Splicing(IN float soureceFloat)
{
	//ת���ַ���
	char TemporaryStringBuffer[sizeof(double) + 1] = { 0 }; //��ʱ�ַ���������
	sprintf_s(TemporaryStringBuffer, sizeof(double) + 1, "%f", soureceFloat);

	char* pTemporaryStringBuffer = mSplicing(TemporaryStringBuffer);//��ʱ�ַ���������
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
	char pTemporaryBuffer[sizeof(char) + 1] = {ch,0}; //��ʱ�ַ���������
	

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
	char pTemporaryBuffer[sizeof(char) + 1] = { ch,0 }; //��ʱ�ַ���������


	return mReverseSearch(pTemporaryBuffer);
	
}

void mString::Split(IN const char* pFormatString)
{
	char* pTemporaryStringBuffer = new char[this->stringLen+1];//��ʱ����������
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
	char* pTemporaryStringBuffer = new char[this->stringLen + 1];//��ʱ����������
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
	va_list args; // ����һ���䳤�����б�
	va_start(args, pForamt); // ��ʼ�䳤�����б�

	char buffer[256]; // �������������Ȳ�����256���ַ�
	int result = vsnprintf(buffer, sizeof(buffer), pForamt, args); // ʹ��vsprintf������ʽ���ַ���

	va_end(args); // �����䳤�����б�

	if (result >= 0) {
		std::cout << buffer;
		return result;
	}
	else {
		std::cerr << "��ʽ���ַ�������" << std::endl;
		return -1;
	}

	
}

