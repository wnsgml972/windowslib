#include <memory>
#include "../WindowsMemoryAPI/WindowsMemoryAPI.h"

// 1. 테스트 시 WindowsMemoryAPI 프로젝트 참조 추가 할 것

class TestClass
{
public:
	TestClass() = default;
	virtual ~TestClass() = default;

public:
	virtual void testVirtualFunc() { int test = 3; }

	int ab;
};

int main()
{
	std::shared_ptr<TestClass> pData = std::make_shared<TestClass>();

	// Example 1.
	bool test1Result{}; // expected true
	{

		void **dpVftable = wm_api::WindowsMemoryAPI::GetVirtualFunctionTable(pData.get());
		if (dpVftable)  // result is testCirtualFunc Pointer
		{
			// 가상 함수를 사용한 데이터 클래스
			test1Result = true;
		}
	}

	// Example 2.
	bool test2Result{}; // expected true
	bool test3Result{}; // expected false
	char *pChar{};
	{
		test2Result = wm_api::WindowsMemoryAPI::PointerIsValid(pData.get());
		test3Result = wm_api::WindowsMemoryAPI::PointerIsValid(pChar);
	}
}