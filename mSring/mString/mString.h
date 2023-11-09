#pragma once
#include <windows.h>
#include <vector>
//ASCII��ʽ���ַ�����
class mString
{
private:
	char* pStringBuffer; //ָ���ַ�����������ָ��
	size_t stringLen; //�ַ�������
	std::vector<mString*> mStringPtrVector;//mStringPtrVector
private:
	/*
	  ��������: ����ѿռ䲢��д���ַ���
	  ����1: д���ַ�����ָ��
	  ����ֵ: �ɹ����� ture,���򷵻� false
	*/
	bool AllocAndWriteString(IN const char* pString);
	/*
	  ��������:�ͷ�����Ķѿռ�
	  ����1: �޲�
	  ����ֵ:�ɹ����� ture,���򷵻� false
	*/
	void FreeStringBuffer(void);
	
	/*
	 ��������: �ַ����������Ƿ�Ϊ��
	 ����1: �޲�
	 ����ֵ ��Ϊ�շ���ture,���򷵻� false
	*/
	bool IsStringBufferEmpty();
	/*
	 ��������: �ַ��������Ƿ�Ϊ0
	 ����1: �޲�
	 ����ֵ:��Ϊ0����ture,���򷵻� false
	*/
	bool IsStringLengthZero();
	/*
	 ��������: ��������ѿռ�
	 ����1: Ҫ����ռ�Ĵ�С
	 ����ֵ: �����¿ռ�ĵ�ַ
	*/
	bool Reallocate(IN size_t size);
	/*
	 �������ƣ��ַ���ƴ��
	 ����: Ҫƴ�ӵ��ַ���
	 ����ֵ: ����ƴ�Ӻ���ַ���ָ��
	*/
	char* mSplicing(const char* pSourceString);
	/*
	 ��������: �ַ�������
	 ����1: Ҫ���ҵ��ַ���
	 ����ֵ: ���ز��ҵ����ַ����±�
	*/
	int mSearch(const char* pString);
	/*
	 ��������: �ַ�������
	 ����1: Ҫ���ҵ��ַ���
	 ����ֵ: ����ֵ���ҵ����ַ����±�
	*/
	int mReverseSearch(const char* pString);
	
public:
	mString();
	mString(IN const char* pString);
	mString(IN mString& stringObject);
	~mString();
	/*
	 ��������: ��ȡ�ַ���
	 ����1: �޲�
	 ����ֵ: �����ַ�����ָ��
	*/
	const char* GetString(void);
	/*
	 ��������: �ַ�������
	 ����1: ָ��Դ�ַ���ָ��
	 ����ֵ: ���ؿ������ַ�����ָ��  
	*/
	char* Copy(IN const char* pSourceString);
	/*
	 ��������: �ַ�������
	 ����1: ָ��Դ�ַ���ָ��
	 ����2: Ҫ�������ַ�������,�������ַ�'\0'
	 ����ֵ: ���ؿ������ַ�����ָ��
	*/
	char* Copy(IN const char* pSourceString,IN size_t sourceStringLen);
	/*
	 ��������: ƴ���ַ���
	 ����1: ָ��Դ�ַ�����ָ��
	 ����ֵ: ����ƴ�Ӻ���ַ���ָ�� 
	*/
	char* Splicing(IN const char* pSoureceString);
	/*
	 ��������: ƴ���ַ�
	 ����1: Դ�ַ�
	 ����ֵ: ����ƴ�Ӻ���ַ���ָ��
	*/
	char* Splicing(IN char soureceChar);
	/*
	 ��������: ƴ������
	 ����1: Դ����
	 ����ֵ: ����ƴ�Ӻ���ַ���ָ��
	*/
	char* Splicing(IN int soureceInt);
	/*
	 ��������: ƴ��С��
	 ����1: ԴС��
	 ����ֵ: ����ƴ�Ӻ���ַ���ָ��
	*/
	char* Splicing(IN float soureceFloat);
	/*
	 ������: ��ȡ�ַ�
	 ����1: �ַ��±�
	 ����ֵ: ���ز��ҵ����ַ�  
	*/
	char GetChar(IN int charIndex);
	/*
	 ������: �����ַ���
	 ����1: ָ��Ҫ�����ַ�����ָ��
	 ����ֵ: �������������ַ������±�
	*/
	int Search(IN const char* pString);
	/*
	 ������: �����ַ���
	 ����1:  Ҫ�������ַ�������
	 ����ֵ: �������������ַ������±�
	*/
	int Search(IN mString& stringObject);
	/*
	 ������: �����ַ�
	 ����1: Ҫ�������ַ�
	 ����ֵ: �����������ַ����±�
	*/
	int Search(IN char ch);
	/*
	 ������: ���������ַ���
	 ����1: ָ��Ҫ�����ַ�����ָ��
	 ����ֵ: �������������ַ������±�
	*/
	int ReverseSearch(IN const char* pString);
	/*
	 ������: ���������ַ���
	 ����1: Ҫ�������ַ�������
	 ����ֵ: �������������ַ������±�
	*/
	int ReverseSearch(IN mString& stringObject);
	/*
	 ������: ���������ַ�
	 ����1: ָ��Ҫ�����ַ�
	 ����ֵ: �������������ַ����±�
	*/
	int ReverseSearch(IN char ch);
	/*
	 ������: �ַ����ָ�
	 ����1: �ָ�ĸ�ʽ
	 ����ֵ: ���طָ����ַ�����ָ��
	*/
	void Split(IN const char* pFormatString);
	/*
	 ������: �ַ����ָ�
	 ����1: �ָ�ĸ�ʽ
	 ����ֵ: ���طָ����ַ�����ָ��
	*/
	void Split(IN mString& stringObject);
	/*
	 ������: �ַ����Ƚ�
	 ����1: Ҫ�Ƚϵ��ַ���
	 ����ֵ:
	 ��� str1 ���� str2���� StringCmp ����0��
     ��� str1 С�� str2���� StringCmp ����һ����������ͨ��Ϊ-1����
     ��� str1 ���� str2���� StringCmp ����һ����������ͨ��Ϊ1����
	*/
	int Cmp(IN const char* pString);
	/*
	 ������:��ӡ�ַ���
	 ����1: ָ��Ҫ������ı���ʽ
	 ����2: ...��ʡ�Ժű�ʾ�����ж����������Щ������ pformat �ַ����еĸ�ʽռλ����ƥ�䡣
	 ����ֵ: ��������ַ����ĳ���,�������ַ�'\0'
	*/
	int mPrintf(IN const char* pForamt, ...);
	
		
};