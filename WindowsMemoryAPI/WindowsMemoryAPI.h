#pragma once
#include "WMVDef.h"

namespace wm_api
{
	// Windows System Call을 이용해 Memory를 검증하는 함수
	class __WMV_API__ WindowsMemoryAPI
	{
	public:
		virtual ~WindowsMemoryAPI() = default;

		//////////////////////////////////////////////////////////////////////////
	public:
		/*
		GetVirtualFunctionTable : 해당 메모리의 주솟 값을 통해 Valid한 가상 함수 테이블의 주솟 값을 리턴하는 함수
			Param :
				void*  pMemoryAddr : 검사하고자 하는 메모리의 주소
			Return Value :
				True  : 가상 함수 테이블 주솟 값
				False : Valid 하지 않을 경우 false
		*/
		static void** GetVirtualFunctionTable(void *pMemoryAddr);

		// Pointer Validation
		static bool PointerIsValid(const void *ptr);
		static bool PointerIsNotValid(const void *ptr);

	protected:
		/*
		IsAvailableMemory : 1. 주어진 메모리 주소의 상태가 물리 주소로 확정되었는지 검사 (실제 사용을 위해 필요)
							2. 주어진 메모리의 보호 속성이 읽기나 쓰기가 가능한지 검사
			Param :
				void*  pMemoryAddr : 검사하고자 하는 메모리의 주소
			Return Value :
				ERROR_SUCCESS : System Error Code, 모든 것이 성공할 경우의 에러코드
				기타 값 : Read/Write 가능한 메모리가 아니면 해당 주소의 Protect Mode 를
						  나타내는 0이 아닌 값을 리턴함.
			Reference :
				1. https://docs.microsoft.com/en-us/previous-versions/aa915370(v=msdn.10)/
				2. https://docs.microsoft.com/en-us/windows/desktop/debug/system-error-codes--0-499-/
		*/
		static unsigned long IsAvailableMemory(void* pMemoryAddr);

		/*
		IsAvailableSystemMemory : 1. 주어진 메모리 주소의 상태가 물리 주소로 확정되었는지 검사 (실제 사용을 위해 필요)
								  2. System Memory는 사용이 좀 더 제한적임, 그러므로 물리 메모리에 확정되었는지만 검사
								  (보호 플래그 검사는 X, 즉 이걸 통과한다고 해서, 반드시 해당 데이터를 쓰거나 읽거나 실행할 수 있는 건 아님)
			Param :
				void*  pMemoryAddr : 검사하고자 하는 메모리의 주소
			Return Value :
				True  : 1) 기타 값 -> 해당 주소의 Protect Mode 를 나타내는 0이 아닌 값이 나오면 True.
				False : 1) 커널 영역일 경우 False.
						2) 물리 주소에 적재되지 않았을 경우 False.
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
