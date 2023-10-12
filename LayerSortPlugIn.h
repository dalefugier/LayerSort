#pragma once

class CLayerSortPlugIn : public CRhinoUtilityPlugIn
{
public:
  CLayerSortPlugIn();
  ~CLayerSortPlugIn() = default;

  // Required overrides
  
  const wchar_t* PlugInName() const override;
  const wchar_t* PlugInVersion() const override;
  GUID PlugInID() const override;
  
  // Additional overrides
  BOOL OnLoadPlugIn() override;
  void OnUnloadPlugIn() override;

private:
  ON_wString m_plugin_version;
};

CLayerSortPlugIn& LayerSortPlugIn();
