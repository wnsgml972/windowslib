#include "stdafx.h"
#include "WindowsMemoryAPI.h"


void** wm_api::WindowsMemoryAPI::GetVirtualFunctionTable(void *pMemoryAddr)
{
	void **pvftable = (void **)(*(__int64 *)pMemoryAddr);

	bool existVirtualTable = IsAvailableSystemMemory(pvftable);
	if (!existVirtualTable)
		return {};

	return pvftable;
}

bool wm_api::WindowsMemoryAPI::PointerIsValid(const void *ptr)
{
	if (WindowsMemoryAPI::IsAvailableMemory((void*)ptr) != ERROR_SUCCESS)
		return false;

	return true;
}

bool wm_api::WindowsMemoryAPI::PointerIsNotValid(const void *ptr)
{
	if (WindowsMemoryAPI::IsAvailableMemory((void*)ptr) == ERROR_SUCCESS)
		return false;

	return true;
}

unsigned long wm_api::WindowsMemoryAPI::IsAvailableMemory(void* pMemoryAddr)
{
	MEMORY_BASIC_INFORMATION MemInfo = { 0, };
	SIZE_T nResult = 0;

	nResult = VirtualQuery(pMemoryAddr, &MemInfo, sizeof(MemInfo));

	if (nResult == 0) // 커널 영역인 경우 VirtualQuery 자체가 Fail함.  
	{
		return -1;
	}
	else if (!(MemInfo.State & MEM_COMMIT)) // 애초에 할당도 안됨
	{
		return MemInfo.State;
	}
	else if ((MemInfo.Protect & (PAGE_READWRITE | PAGE_EXECUTE_READWRITE)))
	{
		return  ERROR_SUCCESS;
	}
	else
	{
		return  MemInfo.Protect;
	}
}

bool wm_api::WindowsMemoryAPI::IsAvailableSystemMemory(void* pMemoryAddr)
{
	bool validSystemMemory = false;

	MEMORY_BASIC_INFORMATION MemInfo = { 0, };
	SIZE_T nResult = 0;

	nResult = VirtualQuery(pMemoryAddr, &MemInfo, sizeof(MemInfo));

	if (nResult == 0) // 커널 영역인 경우 VirtualQuery 자체가 Fail함.  
	{
		validSystemMemory = false;
	}
	else if (!(MemInfo.State & MEM_COMMIT)) // 애초에 할당도 안됨
	{
		validSystemMemory = false;
	}
	else
	{
		validSystemMemory = true;
	}

	return validSystemMemory;
}
