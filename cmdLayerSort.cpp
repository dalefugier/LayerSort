#include "stdafx.h"
#include "LayerSortPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN LayerSort command
//

#pragma region LayerSort command

class CCommandLayerSort : public CRhinoCommand
{
public:
  CCommandLayerSort() = default;
  ~CCommandLayerSort() = default;
  UUID CommandUUID() override
  {
    // {66422D76-0700-473D-B91A-010B145B8A76}
    static const GUID LayerSortCommand_UUID = 
    {0x66422d76,0x0700,0x473d,{0xb9,0x1a,0x01,0x0b,0x14,0x5b,0x8a,0x76}};
    return LayerSortCommand_UUID;
  }
  const wchar_t* EnglishCommandName() override { return L"LayerSort"; }
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;

  bool GetSortAscending() const;
  bool UseLogicalSort() const;

private:
  bool m_bSortAscending = true;
  bool m_bLogicalSort = true;
};

static class CCommandLayerSort theLayerSortCommand;

static int cull(const CRhinoLayer* a, void*)
{
  if (nullptr == a)
    return true;
  if (a->IsDeleted())
    return true;
  return false;
}

static int compare(const CRhinoLayer* a, const CRhinoLayer* b, void*)
{
  if ((nullptr == a && nullptr == b))
    return 0;
  if (nullptr != a && nullptr == b)
    return 1;
  if (nullptr == a && nullptr != b)
    return -1;

  const CRhinoLayer* p1 = b;
  const CRhinoLayer* p2 = a;

  const bool bIsRef1 = p1->IsReference();
  const bool bIsRef2 = p2->IsReference();
  if (bIsRef1 || bIsRef2)
  {
    // Reference layers from linked instance definition and worksession
    // reference models are always last in the list.
    if (bIsRef1 && !bIsRef2)
      return -1;

    if (!bIsRef1 && bIsRef2)
      return 1;

    if (bIsRef1 && bIsRef2)
    {
      // Linked instance definition layers in the active model
      // always appear before worksession reference layers.
      const unsigned int ws1 = p1->WorksessionReferenceModelSerialNumber();
      const unsigned int ws2 = p2->WorksessionReferenceModelSerialNumber();
      if (0 == ws1 && 0 != ws2)
        return 1;
      if (0 == ws2 && 0 != ws1)
        return -1;
    }
  }

  // At this point we have either two ordinary layers or two reference layers
  // of the same type. The "ordinary" layer attributes are used for sorting.

  if (theLayerSortCommand.GetSortAscending())
  {
    p1 = a;
    p2 = b;
  }

  if (theLayerSortCommand.UseLogicalSort())
    return StrCmpLogicalW(p1->Name(), p2->Name());

  return ON_ModelComponent::CompareName(*p1, *p2);
}

CRhinoCommand::result CCommandLayerSort::RunCommand(const CRhinoCommandContext& context)
{
  if (context.m_doc.m_layer_table.LayerCount() <= 1)
  {
    RhinoApp().Print(L"Layer sorting requires more than one layer.\n");
    return CRhinoCommand::success;
  }

  CRhinoGetOption go;
  go.SetCommandPrompt(L"Choose layer sort option");
  int ascending = go.AddCommandOption(RHCMDOPTNAME(L"Ascending"));
  int decending = go.AddCommandOption(RHCMDOPTNAME(L"Decending"));
  int method = go.AddCommandOptionToggle(RHCMDOPTNAME(L"Method"), RHCMDOPTVALUE(L"Simple"), RHCMDOPTVALUE(L"Logical"), m_bLogicalSort, &m_bLogicalSort);
  for (;;)
  {
    go.GetOption();
    if (go.CommandResult() != CRhinoCommand::success)
      return go.CommandResult();

    const CRhinoCommandOption* pOption = go.Option();
    if (pOption)
    {
      bool rc = false;
      if (pOption->m_option_index == ascending)
      {
        m_bSortAscending = true;
        rc = true;
      }
      else if (pOption->m_option_index == decending)
      {
        m_bSortAscending = false;
        rc = true;
      }
      else if (pOption->m_option_index == method)
      {
        continue;
      }
      if (rc)
      {
        context.m_doc.m_layer_table.Sort(compare, cull, nullptr);
      }
      break;
    }
  }

  return CRhinoCommand::success;
}

bool CCommandLayerSort::GetSortAscending() const
{
  return m_bSortAscending;
}

bool CCommandLayerSort::UseLogicalSort() const
{
  return m_bLogicalSort;
}

#pragma endregion

//
// END LayerSort command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
