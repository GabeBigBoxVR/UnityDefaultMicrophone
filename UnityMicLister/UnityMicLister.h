#ifdef UNITYMICLISTER_EXPORTS
#define UNITYMICLISTER_API __declspec(dllexport)
#else
#define UNITYMICLISTER_API __declspec(dllimport)
#endif

extern "C" {
	UNITYMICLISTER_API HRESULT GetDefaultMicrophoneName(LPWSTR *data);
}
