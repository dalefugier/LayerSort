#include "stdafx.h"
#include "LayerSortApp.h"

BEGIN_MESSAGE_MAP(CLayerSortApp, CWinApp)
END_MESSAGE_MAP()

// The one and only CLayerSortApp object
static class CLayerSortApp theApp;

// CLayerSortApp initialization

BOOL CLayerSortApp::InitInstance()
{
	CWinApp::InitInstance();
	return TRUE;
}

int CLayerSortApp::ExitInstance()
{
  return CWinApp::ExitInstance();
}
