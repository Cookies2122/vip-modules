#pragma once

#include <schemasystem/schemasystem.h>
#include <utlstring.h>
#include <string.h>

#include "CBaseEntity.h"

#ifdef _WIN32
#define CHL_SERVER_MODULE "server.dll"
#else
#define CHL_SERVER_MODULE "libserver.so"
#endif

#define CHL_MAX_INTERNED 1024
#define CHL_MAX_SLOTS 64

struct CHudLayoutColl_t
{
	int offset = -1;
	SchemaCollectionManipulatorFn_t fn = nullptr;

	bool IsValid() const { return offset >= 0 && fn != nullptr; }
};

struct CHudLayoutSchema_t
{
	bool resolved = false;
	bool ok = false;

	int captureOffset = -1;
	int globalStateOffset = -1;

	CHudLayoutColl_t states;
	CHudLayoutColl_t panelIds;
	CHudLayoutColl_t classNames;
	CHudLayoutColl_t varNames;
	CHudLayoutColl_t hasClasses;
	CHudLayoutColl_t dialogVars;

	int hcPanel = 0;
	int hcClass = 2;
	int hcStatus = 4;

	int dvPanel = 8;
	int dvVar = 10;
	int dvValue = 16;
	int dvIsSet = 24;
};

inline CHudLayoutSchema_t& CHudLayout_Schema()
{
	static CHudLayoutSchema_t s;
	return s;
}

inline SchemaClassInfoData_t* CHudLayout_FindClass(const char* pszName)
{
	if (!g_pSchemaSystem) return nullptr;

	if (CSchemaSystemTypeScope* pScope = g_pSchemaSystem->FindTypeScopeForModule(CHL_SERVER_MODULE))
		if (SchemaClassInfoData_t* pInfo = pScope->FindDeclaredClass(pszName).Get())
			return pInfo;

	if (CSchemaSystemTypeScope* pGlobal = g_pSchemaSystem->GlobalTypeScope())
		if (SchemaClassInfoData_t* pInfo = pGlobal->FindDeclaredClass(pszName).Get())
			return pInfo;

	return nullptr;
}

inline SchemaClassFieldData_t* CHudLayout_FindField(SchemaClassInfoData_t* pInfo, const char* pszName)
{
	if (!pInfo) return nullptr;

	for (int i = 0; i < pInfo->m_nFieldCount; ++i)
		if (pInfo->m_pFields[i].m_pszName && !strcmp(pInfo->m_pFields[i].m_pszName, pszName))
			return &pInfo->m_pFields[i];

	return nullptr;
}

inline int CHudLayout_FieldOffset(SchemaClassInfoData_t* pInfo, const char* pszName, int iFallback)
{
	SchemaClassFieldData_t* pField = CHudLayout_FindField(pInfo, pszName);
	return pField ? pField->m_nSingleInheritanceOffset : iFallback;
}

inline CHudLayoutColl_t CHudLayout_MakeColl(SchemaClassInfoData_t* pInfo, const char* pszName)
{
	CHudLayoutColl_t coll;

	SchemaClassFieldData_t* pField = CHudLayout_FindField(pInfo, pszName);
	if (!pField) return coll;

	coll.offset = pField->m_nSingleInheritanceOffset;

	CSchemaType* pType = pField->m_pType;
	if (pType && pType->m_eTypeCategory == SCHEMA_TYPE_ATOMIC && pType->m_eAtomicCategory == SCHEMA_ATOMIC_COLLECTION_OF_T)
		coll.fn = static_cast<CSchemaType_Atomic_CollectionOfT*>(pType)->m_pfnManipulator;

	return coll;
}

inline bool CHudLayout_Resolve()
{
	CHudLayoutSchema_t& s = CHudLayout_Schema();
	if (s.resolved) return s.ok;

	if (!g_pSchemaSystem) return false;
	s.resolved = true;

	SchemaClassInfoData_t* pLayout = CHudLayout_FindClass("CCSCustomHudLayout");
	SchemaClassInfoData_t* pState = CHudLayout_FindClass("CCSCustomHudLayoutState");
	if (!pLayout || !pState) return false;

	s.captureOffset = CHudLayout_FieldOffset(pState, "m_bInputCaptureEnabled", -1);
	s.globalStateOffset = CHudLayout_FieldOffset(pLayout, "m_globalLayoutState", -1);

	s.states = CHudLayout_MakeColl(pLayout, "m_vecPlayerLayoutStates");
	s.panelIds = CHudLayout_MakeColl(pLayout, "m_vecPanelIds");
	s.classNames = CHudLayout_MakeColl(pLayout, "m_vecClassNames");
	s.varNames = CHudLayout_MakeColl(pLayout, "m_vecDialogVariableNames");
	s.hasClasses = CHudLayout_MakeColl(pState, "m_vecHasClasses");
	s.dialogVars = CHudLayout_MakeColl(pState, "m_vecDialogVariableStrings");

	SchemaClassInfoData_t* pHasClass = CHudLayout_FindClass("HUDPanelHasClass_t");
	s.hcPanel = CHudLayout_FieldOffset(pHasClass, "m_nPanelIdIndex", s.hcPanel);
	s.hcClass = CHudLayout_FieldOffset(pHasClass, "m_nClassNameIndex", s.hcClass);
	s.hcStatus = CHudLayout_FieldOffset(pHasClass, "m_eClassStatus", s.hcStatus);

	SchemaClassInfoData_t* pDialogVar = CHudLayout_FindClass("HUDPanelDialogVariableString_t");
	s.dvPanel = CHudLayout_FieldOffset(pDialogVar, "m_nPanelIdIndex", s.dvPanel);
	s.dvVar = CHudLayout_FieldOffset(pDialogVar, "m_nDialogVariableIndex", s.dvVar);
	s.dvValue = CHudLayout_FieldOffset(pDialogVar, "m_sValue", s.dvValue);
	s.dvIsSet = CHudLayout_FieldOffset(pDialogVar, "m_bIsSet", s.dvIsSet);

	s.ok = s.captureOffset >= 0 && s.states.IsValid() && s.panelIds.IsValid() && s.classNames.IsValid()
		&& s.varNames.IsValid() && s.hasClasses.IsValid() && s.dialogVars.IsValid();

	return s.ok;
}

template <typename T>
inline T& CHudLayout_Field(void* pElement, int iOffset)
{
	return *reinterpret_cast<T*>((uintptr_t)pElement + iOffset);
}

inline void* CHudLayout_CollPtr(void* pOwner, const CHudLayoutColl_t& coll)
{
	return reinterpret_cast<void*>((uintptr_t)pOwner + coll.offset);
}

inline int CHudLayout_Count(void* pOwner, const CHudLayoutColl_t& coll)
{
	return (int)(intptr_t)coll.fn(SCHEMA_COLLECTION_MANIPULATOR_ACTION_GET_COUNT, CHudLayout_CollPtr(pOwner, coll), 0, 0);
}

inline void* CHudLayout_At(void* pOwner, const CHudLayoutColl_t& coll, int index)
{
	return coll.fn(SCHEMA_COLLECTION_MANIPULATOR_ACTION_GET_ELEMENT, CHudLayout_CollPtr(pOwner, coll), index, 0);
}

inline void* CHudLayout_Append(void* pOwner, const CHudLayoutColl_t& coll)
{
	const int count = CHudLayout_Count(pOwner, coll);

	coll.fn(SCHEMA_COLLECTION_MANIPULATOR_ACTION_SET_COUNT, CHudLayout_CollPtr(pOwner, coll), count + 1, 0);

	if (CHudLayout_Count(pOwner, coll) != count + 1)
		return nullptr;

	return CHudLayout_At(pOwner, coll, count);
}

class CCSCustomHudLayout : public CBaseEntity
{
public:
	void SetHasClass(int iSlot, CUtlString szPanelId, CUtlString szClassName, bool bHasClass)
	{
		ApplyHasClass(GetState(iSlot), szPanelId.Get(), szClassName.Get(), bHasClass);
	}

	void SetInputCaptureEnabled(int iSlot, bool bEnabled)
	{
		ApplyInputCapture(GetState(iSlot), bEnabled);
	}

	bool GetInputCaptureEnabled(int iSlot)
	{
		void* pState = GetState(iSlot);
		if (!pState) return false;

		return CHudLayout_Field<bool>(pState, CHudLayout_Schema().captureOffset);
	}

	void SetDialogVariableString(int iSlot, CUtlString szPanelId, CUtlString szVariableName, CUtlString szValue)
	{
		ApplyDialogVariable(GetState(iSlot), szPanelId.Get(), szVariableName.Get(), szValue.Get());
	}

	const char* GetDialogVariableString(int iSlot, CUtlString szPanelId, CUtlString szVariableName)
	{
		CHudLayoutSchema_t& s = CHudLayout_Schema();

		void* pState = GetState(iSlot);
		if (!pState) return "";

		const int iPanel = Find(s.panelIds, szPanelId.Get());
		const int iVar = Find(s.varNames, szVariableName.Get());
		if (iPanel < 0 || iVar < 0) return "";

		void* pEntry = FindEntry(pState, s.dialogVars, s.dvPanel, s.dvVar, iPanel, iVar);
		if (!pEntry || !CHudLayout_Field<bool>(pEntry, s.dvIsSet)) return "";

		const char* pszValue = CHudLayout_Field<CUtlString>(pEntry, s.dvValue).Get();
		return pszValue ? pszValue : "";
	}

	void SetGlobalHasClass(const char* pszPanelId, const char* pszClassName, bool bHasClass)
	{
		ApplyHasClass(GetGlobalState(), pszPanelId, pszClassName, bHasClass);
	}

	void SetGlobalInputCaptureEnabled(bool bEnabled)
	{
		ApplyInputCapture(GetGlobalState(), bEnabled);
	}

	void SetGlobalDialogVariableString(const char* pszPanelId, const char* pszVariableName, const char* pszValue)
	{
		ApplyDialogVariable(GetGlobalState(), pszPanelId, pszVariableName, pszValue);
	}

private:
	void* GetState(int iSlot)
	{
		if (iSlot < 0 || iSlot >= CHL_MAX_SLOTS) return nullptr;
		if (!CHudLayout_Resolve()) return nullptr;

		CHudLayoutSchema_t& s = CHudLayout_Schema();

		const int count = CHudLayout_Count(this, s.states);
		if (count <= 0 || count > 128 || iSlot >= count) return nullptr;

		return CHudLayout_At(this, s.states, iSlot);
	}

	void* GetGlobalState()
	{
		if (!CHudLayout_Resolve()) return nullptr;

		CHudLayoutSchema_t& s = CHudLayout_Schema();
		if (s.globalStateOffset < 0) return nullptr;

		return reinterpret_cast<void*>((uintptr_t)this + s.globalStateOffset);
	}

	void ApplyHasClass(void* pState, const char* pszPanelId, const char* pszClassName, bool bHasClass)
	{
		if (!pState) return;

		CHudLayoutSchema_t& s = CHudLayout_Schema();

		const int iPanel = Intern(s.panelIds, pszPanelId);
		const int iClass = Intern(s.classNames, pszClassName);
		if (iPanel < 0 || iClass < 0) return;

		if (void* pEntry = FindEntry(pState, s.hasClasses, s.hcPanel, s.hcClass, iPanel, iClass))
		{
			CHudLayout_Field<int32>(pEntry, s.hcStatus) = bHasClass ? 1 : 0;
			return;
		}

		void* pEntry = CHudLayout_Append(pState, s.hasClasses);
		if (!pEntry) return;

		CHudLayout_Field<uint16>(pEntry, s.hcPanel) = (uint16)iPanel;
		CHudLayout_Field<uint16>(pEntry, s.hcClass) = (uint16)iClass;
		CHudLayout_Field<int32>(pEntry, s.hcStatus) = bHasClass ? 1 : 0;
	}

	void ApplyInputCapture(void* pState, bool bEnabled)
	{
		if (!pState) return;

		CHudLayout_Field<bool>(pState, CHudLayout_Schema().captureOffset) = bEnabled;
	}

	void ApplyDialogVariable(void* pState, const char* pszPanelId, const char* pszVariableName, const char* pszValue)
	{
		if (!pState) return;

		CHudLayoutSchema_t& s = CHudLayout_Schema();

		const int iPanel = Intern(s.panelIds, pszPanelId);
		const int iVar = Intern(s.varNames, pszVariableName);
		if (iPanel < 0 || iVar < 0) return;

		if (void* pEntry = FindEntry(pState, s.dialogVars, s.dvPanel, s.dvVar, iPanel, iVar))
		{
			CHudLayout_Field<CUtlString>(pEntry, s.dvValue) = pszValue ? pszValue : "";
			CHudLayout_Field<bool>(pEntry, s.dvIsSet) = true;
			return;
		}

		void* pEntry = CHudLayout_Append(pState, s.dialogVars);
		if (!pEntry) return;

		CHudLayout_Field<uint16>(pEntry, s.dvPanel) = (uint16)iPanel;
		CHudLayout_Field<uint16>(pEntry, s.dvVar) = (uint16)iVar;
		CHudLayout_Field<CUtlString>(pEntry, s.dvValue) = pszValue ? pszValue : "";
		CHudLayout_Field<bool>(pEntry, s.dvIsSet) = true;
	}

	int Find(const CHudLayoutColl_t& pool, const char* pszName)
	{
		if (!pszName) return -1;

		const int count = CHudLayout_Count(this, pool);
		for (int i = 0; i < count; ++i)
		{
			CUtlString* pStr = static_cast<CUtlString*>(CHudLayout_At(this, pool, i));
			const char* pszValue = pStr ? pStr->Get() : nullptr;
			if (pszValue && !strcmp(pszValue, pszName)) return i;
		}

		return -1;
	}

	int Intern(const CHudLayoutColl_t& pool, const char* pszName)
	{
		if (!pszName) return -1;

		const int index = Find(pool, pszName);
		if (index >= 0) return index;

		const int count = CHudLayout_Count(this, pool);
		if (count >= CHL_MAX_INTERNED) return -1;

		CUtlString* pStr = static_cast<CUtlString*>(CHudLayout_Append(this, pool));
		if (!pStr) return -1;

		*pStr = pszName;
		return count;
	}

	void* FindEntry(void* pState, const CHudLayoutColl_t& coll, int iOffsetA, int iOffsetB, int a, int b)
	{
		const int count = CHudLayout_Count(pState, coll);
		for (int i = 0; i < count; ++i)
		{
			void* pEntry = CHudLayout_At(pState, coll, i);
			if (!pEntry) continue;

			if (CHudLayout_Field<uint16>(pEntry, iOffsetA) == (uint16)a
				&& CHudLayout_Field<uint16>(pEntry, iOffsetB) == (uint16)b)
				return pEntry;
		}

		return nullptr;
	}
};
