#include "stdafx.h"

//---------------------------------------[Crack ���� - dll injection �˻�� ����]-------------------------------------------------
// dll injection�� ���� SetupDiEnumDeviceInfo() �Լ� ������ �߻��ϴ��� �˻��ϱ� ���� ������ ���� 
// ũ���� ���� dll(mad.dll) �� Load�Ǳ� ���� ���õǾ�� �ϹǷ� dll ��������� ���� ���ʿ� �ִ� dll�� �ڵ� �ݿ�.
#include <SetupAPI.h>
#pragma comment(lib, "SetupAPI.lib")

const int CONST_SIZE_COMP_FUNC_BIN = 4;
__declspec(dllexport) char g_StDiEDevIf[CONST_SIZE_COMP_FUNC_BIN]; //SetupDiEnumDeviceInfo() �� ���� binary 4 ����Ʈ
inline BOOL initSetupDiEnumDeviceInfo()
{
	typedef BOOL(WINAPI *pfnSetupDiEnumDeviceInfo)(_In_ HDEVINFO DeviceInfoSet, _In_ DWORD MemberIndex, _Out_ PSP_DEVINFO_DATA DeviceInfoData);
	pfnSetupDiEnumDeviceInfo pFuncSetupDiEnumDeviceInfo = SetupDiEnumDeviceInfo;
	memcpy_s(g_StDiEDevIf, CONST_SIZE_COMP_FUNC_BIN, pFuncSetupDiEnumDeviceInfo, CONST_SIZE_COMP_FUNC_BIN);

	return TRUE;
}
BOOL g_bInitStDiEDevIf = initSetupDiEnumDeviceInfo();
//----------------------------------------------------------------------------------------------------------------------------------