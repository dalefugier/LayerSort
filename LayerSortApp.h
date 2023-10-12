#pragma once

#include "resource.h" // main symbols

class CLayerSortApp : public CWinApp
{
public:
	CLayerSortApp() = default;
	BOOL InitInstance() override;
	int ExitInstance() override;
	DECLARE_MESSAGE_MAP()
};
