========================================================================
    ACTIVE TEMPLATE LIBRARY : myatl2 Project Overview
========================================================================

AppWizard has created this myatl2 project for you to use as the starting point for
writing your Dynamic Link Library (DLL).

This file contains a summary of what you will find in each of the files that
make up your project.

myatl2.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

myatl2.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

myatl2.idl
    This file contains the IDL definitions of the type library, the interfaces
    and co-classes defined in your project.
    This file will be processed by the MIDL compiler to generate:
        C++ interface definitions and GUID declarations (myatl2.h)
        GUID definitions                                (myatl2_i.c)
        A type library                                  (myatl2.tlb)
        Marshaling code                                 (myatl2_p.c and dlldata.c)

myatl2.h
    This file contains the C++ interface definitions and GUID declarations of the
    items defined in myatl2.idl. It will be regenerated by MIDL during compilation.

myatl2.cpp
    This file contains the object map and the implementation of your DLL's exports.

myatl2.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.

myatl2.def
    This module-definition file provides the linker with information about the exports
    required by your DLL. It contains exports for:
        DllGetClassObject
        DllCanUnloadNow
        DllRegisterServer
        DllUnregisterServer
        DllInstall

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named myatl2.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file that defines resource IDs.

/////////////////////////////////////////////////////////////////////////////
Proxy/stub DLL project and module definition file:

myatl2ps.vcxproj
    This file is the project file for building a proxy/stub DLL if necessary.
	The IDL file in the main project must contain at least one interface and you must
	first compile the IDL file before building the proxy/stub DLL.	This process generates
	dlldata.c, myatl2_i.c and myatl2_p.c which are required
	to build the proxy/stub DLL.

myatl2ps.vcxproj.filters
    This is the filters file for the proxy/stub project. It contains information about the 
    association between the files in your project and the filters. This association is 
    used in the IDE to show grouping of files with similar extensions under a specific
    node (for e.g. ".cpp" files are associated with the "Source Files" filter).

myatl2ps.def
    This module definition file provides the linker with information about the exports
    required by the proxy/stub.

/////////////////////////////////////////////////////////////////////////////
Other notes:

	The COM+ 1.0 Support option builds the COM+ 1.0 library into your skeleton application,
	making COM+ 1.0 classes, objects, and functions available to you.

/////////////////////////////////////////////////////////////////////////////
