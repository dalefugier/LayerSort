#include "stdafx.h"
#include "rhinoSdkPlugInDeclare.h"
#include "LayerSortPlugIn.h"
#include "Resource.h"

#pragma warning(push)
#pragma warning(disable : 4073)
#pragma init_seg(lib)
#pragma warning(pop)

// Rhino plug-in declarations
RHINO_PLUG_IN_DECLARE
RHINO_PLUG_IN_NAME(L"LayerSort");
RHINO_PLUG_IN_ID(L"C421F49C-FF2C-4CFA-B909-99D04F043712");
RHINO_PLUG_IN_VERSION(__DATE__ "  " __TIME__)
RHINO_PLUG_IN_DESCRIPTION(L"LayerSort plug-in for Rhinoceros®");
RHINO_PLUG_IN_ICON_RESOURCE_ID(IDI_ICON);

// Rhino plug-in developer declarations
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION(L"Robert McNeel & Associates");
RHINO_PLUG_IN_DEVELOPER_ADDRESS(L"Seattle, WA");
RHINO_PLUG_IN_DEVELOPER_COUNTRY(L"United States");
RHINO_PLUG_IN_DEVELOPER_PHONE(L"+1 (206) 545-7321");
RHINO_PLUG_IN_DEVELOPER_FAX(L"-");
RHINO_PLUG_IN_DEVELOPER_EMAIL(L"devsupport@mcneel.com");
RHINO_PLUG_IN_DEVELOPER_WEBSITE(L"https://www.rhino3d.com/");
RHINO_PLUG_IN_UPDATE_URL(L"https://www.rhino3d.com/");

// The one and only CLayerSortPlugIn object
static class CLayerSortPlugIn thePlugIn;

// CLayerSortPlugIn definition

CLayerSortPlugIn& LayerSortPlugIn()
{
	return thePlugIn;
}

CLayerSortPlugIn::CLayerSortPlugIn()
{
	m_plugin_version = RhinoPlugInVersion();
}

// Required overrides

const wchar_t* CLayerSortPlugIn::PlugInName() const
{
	return RhinoPlugInName();
}

const wchar_t* CLayerSortPlugIn::PlugInVersion() const
{
	return m_plugin_version;
}

GUID CLayerSortPlugIn::PlugInID() const
{
	// {C421F49C-FF2C-4CFA-B909-99D04F043712}
	return ON_UuidFromString(RhinoPlugInId());
}

// Additional overrides

BOOL CLayerSortPlugIn::OnLoadPlugIn()
{
	return TRUE;
}

void CLayerSortPlugIn::OnUnloadPlugIn()
{
}
