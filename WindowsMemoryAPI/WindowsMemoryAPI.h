#pragma once
#include "WMVDef.h"

namespace wm_api
{
	// Windows System Call�� �̿��� Memory�� �����ϴ� �Լ�
	class __WMV_API__ WindowsMemoryAPI
	{
	public:
		virtual ~WindowsMemoryAPI() = default;

		//////////////////////////////////////////////////////////////////////////
	public:
		/*
		GetVirtualFunctionTable : �ش� �޸��� �ּ� ���� ���� Valid�� ���� �Լ� ���̺��� �ּ� ���� �����ϴ� �Լ�
			Param :
				void*  pMemoryAddr : �˻��ϰ��� �ϴ� �޸��� �ּ�
			Return Value :
				True  : ���� �Լ� ���̺� �ּ� ��
				False : Valid ���� ���� ��� false
		*/
		static void** GetVirtualFunctionTable(void *pMemoryAddr);

		// Pointer Validation
		static bool PointerIsValid(const void *ptr);
		static bool PointerIsNotValid(const void *ptr);

	protected:
		/*
		IsAvailableMemory : 1. �־��� �޸� �ּ��� ���°� ���� �ּҷ� Ȯ���Ǿ����� �˻� (���� ����� ���� �ʿ�)
							2. �־��� �޸��� ��ȣ �Ӽ��� �б⳪ ���Ⱑ �������� �˻�
			Param :
				void*  pMemoryAddr : �˻��ϰ��� �ϴ� �޸��� �ּ�
			Return Value :
				ERROR_SUCCESS : System Error Code, ��� ���� ������ ����� �����ڵ�
				��Ÿ �� : Read/Write ������ �޸𸮰� �ƴϸ� �ش� �ּ��� Protect Mode ��
						  ��Ÿ���� 0�� �ƴ� ���� ������.
			Reference :
				1. https://docs.microsoft.com/en-us/previous-versions/aa915370(v=msdn.10)/
				2. https://docs.microsoft.com/en-us/windows/desktop/debug/system-error-codes--0-499-/
		*/
		static unsigned long IsAvailableMemory(void* pMemoryAddr);

		/*
		IsAvailableSystemMemory : 1. �־��� �޸� �ּ��� ���°� ���� �ּҷ� Ȯ���Ǿ����� �˻� (���� ����� ���� �ʿ�)
								  2. System Memory�� ����� �� �� ��������, �׷��Ƿ� ���� �޸𸮿� Ȯ���Ǿ������� �˻�
								  (��ȣ �÷��� �˻�� X, �� �̰� ����Ѵٰ� �ؼ�, �ݵ�� �ش� �����͸� ���ų� �аų� ������ �� �ִ� �� �ƴ�)
			Param :
				void*  pMemoryAddr : �˻��ϰ��� �ϴ� �޸��� �ּ�
			Return Value :
				True  : 1) ��Ÿ �� -> �ش� �ּ��� Protect Mode �� ��Ÿ���� 0�� �ƴ� ���� ������ True.
				False : 1) Ŀ�� ������ ��� False.
						2) ���� �ּҿ� ������� �ʾ��� ��� False.
			Reference :
				1. https://docs.microsoft.com/en-us/previous-versions/aa915370(v=msdn.10)/
				2. https://docs.microsoft.com/en-us/windows/desktop/debug/system-error-codes--0-499-/
		*/
		static bool IsAvailableSystemMemory(void* pMemoryAddr);

	private:
		// No Copyable
		WindowsMemoryAPI() = default;
		WindowsMemoryAPI(const WindowsMemoryAPI &) = delete;
		WindowsMemoryAPI &operator=(const WindowsMemoryAPI &) = delete;
	};
}
