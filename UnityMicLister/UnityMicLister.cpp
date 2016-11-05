#include "stdafx.h"
#include "windows.h"
#include "Mmsystem.h"
#include "UnityMicLister.h"
#include <Mmdeviceapi.h>
#include <Functiondiscoverykeys_devpkey.h>
#pragma comment(lib, "strmiids")

#define EXIT_ON_ERROR(hr)  \
              if (FAILED(hr)) { goto Exit; }
#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

UNITYMICLISTER_API HRESULT GetDefaultMicrophoneName(LPWSTR *data)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT::COINIT_MULTITHREADED);
	bool destroyCom = SUCCEEDED(hr);

	IMMDeviceEnumerator *pEnumerator = NULL;
	IMMDevice *pDevice = NULL;
	IPropertyStore *pProps = NULL;
	EDataFlow flow = EDataFlow::eCapture;
	ERole role = ERole::eConsole;

	// Get the enumerator for the audio endpoint devices on this system.
	hr = CoCreateInstance(
		__uuidof(MMDeviceEnumerator),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator),
		(void**)&pEnumerator);
	EXIT_ON_ERROR(hr);

	// Get the audio endpoint device with the specified data-flow
	// direction (eRender or eCapture) and device role.
	hr = pEnumerator->GetDefaultAudioEndpoint(flow, role, &pDevice);
	EXIT_ON_ERROR(hr);

	hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);
	EXIT_ON_ERROR(hr);

	PROPVARIANT varName;
	PropVariantInit(&varName);

	hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);
	EXIT_ON_ERROR(hr)

	// This will probably leak, should fix at some point
	*data = varName.pwszVal;

	Exit:
	SAFE_RELEASE(pDevice);
	SAFE_RELEASE(pProps);
	SAFE_RELEASE(pEnumerator);

	if (destroyCom) 
	{
		CoUninitialize();
	}

	return hr;
}