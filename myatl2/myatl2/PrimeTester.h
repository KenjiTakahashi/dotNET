// PrimeTester.h : Declaration of the PrimeTester

#pragma once
#include "myatl2_i.h"
#include "resource.h"       // main symbols
#include <comsvcs.h>

using namespace ATL;



// PrimeTester

class ATL_NO_VTABLE PrimeTester :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<PrimeTester, &CLSID_PrimeTester>,
	public IDispatchImpl<IPrimeTester, &IID_IPrimeTester, &LIBID_myatl2Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	PrimeTester()
	{
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PRIMETESTER)

DECLARE_NOT_AGGREGATABLE(PrimeTester)

BEGIN_COM_MAP(PrimeTester)
	COM_INTERFACE_ENTRY(IPrimeTester)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()




// IPrimeTester
public:
	STDMETHOD(IsPrime)(int number, int *state);
	STDMETHOD(IsPrime2)(int number, int* state);
};

OBJECT_ENTRY_AUTO(__uuidof(PrimeTester), PrimeTester)
