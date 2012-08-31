// dllmain.h : Declaration of module class.

class Cmyatl2Module : public ATL::CAtlDllModuleT< Cmyatl2Module >
{
public :
	DECLARE_LIBID(LIBID_myatl2Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MYATL2, "{7600B054-2784-43A9-B6B8-A0C4E35418E0}")
};

extern class Cmyatl2Module _AtlModule;
