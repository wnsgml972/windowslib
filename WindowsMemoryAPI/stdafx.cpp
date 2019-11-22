#include "stdafx.h"

//---------------------------------------[Crack 방지 - dll injection 검사용 세팅]-------------------------------------------------
// dll injection에 의해 SetupDiEnumDeviceInfo() 함수 변조가 발생하는지 검사하기 위한 데이터 세팅 
// 크랙용 변조 dll(mad.dll) 이 Load되기 전에 세팅되어야 하므로 dll 연관관계상 제일 안쪽에 있는 dll에 코드 반영.
#include <SetupAPI.h>
#pragma comment(lib, "SetupAPI.lib")

const int CONST_SIZE_COMP_FUNC_BIN = 4;
__declspec(dllexport) char g_StDiEDevIf[CONST_SIZE_COMP_FUNC_BIN]; //SetupDiEnumDeviceInfo() 의 시작 binary 4 바이트
inline BOOL initSetupDiEnumDeviceInfo()
{
	typedef BOOL(WINAPI *pfnSetupDiEnumDeviceInfo)(_In_ HDEVINFO DeviceInfoSet, _In_ DWORD MemberIndex, _Out_ PSP_DEVINFO_DATA DeviceInfoData);
	pfnSetupDiEnumDeviceInfo pFuncSetupDiEnumDeviceInfo = SetupDiEnumDeviceInfo;
	memcpy_s(g_StDiEDevIf, CONST_SIZE_COMP_FUNC_BIN, pFuncSetupDiEnumDeviceInfo, CONST_SIZE_COMP_FUNC_BIN);

	return TRUE;
}
BOOL g_bInitStDiEDevIf = initSetupDiEnumDeviceInfo();
//----------------------------------------------------------------------------------------------------------------------------------