#pragma once
#include "CBaseEntity.h"
#include "globaltypes.h"

class CSkyCamera : public CBaseEntity
{
public:
	DECLARE_SCHEMA_CLASS(CSkyCamera)
	SCHEMA_FIELD(CUtlStringToken, m_skyboxSlotToken);
};

class CEnvSky : public CBaseModelEntity
{
public:
	DECLARE_SCHEMA_CLASS(CEnvSky)

	SCHEMA_FIELD(uint64_t, m_hSkyMaterial)
	SCHEMA_FIELD(uint64_t, m_hSkyMaterialLightingOnly)
	SCHEMA_FIELD(Color, m_vTintColor)
	SCHEMA_FIELD(float32, m_flBrightnessScale)
};