// dllmain.h : Declaration of module class.

class CaltbhoModule : public CAtlDllModuleT< CaltbhoModule >
{
public :
	DECLARE_LIBID(LIBID_altbhoLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ALTBHO, "{10192EB0-B65A-456D-88BC-B525203664E1}")
};

extern class CaltbhoModule _AtlModule;
