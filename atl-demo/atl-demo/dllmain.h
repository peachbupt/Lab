// dllmain.h : Declaration of module class.

class CatldemoModule : public CAtlDllModuleT< CatldemoModule >
{
public :
	DECLARE_LIBID(LIBID_atldemoLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLDEMO, "{22070A58-53C4-4BE7-9176-FEA7E0F6622A}")
};

extern class CatldemoModule _AtlModule;
