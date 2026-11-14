
#pragma once
#include <platform.h>
#include "schemasystem.h"
#include "soundflags.h"

enum CSRoundEndReason
{
	TargetBombed = 1,
	VIPEscaped,
	VIPKilled,
	TerroristsEscaped,
	CTStoppedEscape,
	TerroristsStopped,
	BombDefused,
	CTWin,
	TerroristWin,
	Draw,
	HostagesRescued,
	TargetSaved,
	HostagesNotRescued,
	TerroristsNotEscaped,
	VIPNotEscaped,
	GameStart,
	TerroristsSurrender,
	CTSurrender,
	TerroristsPlanted,
	CTsReachedHostage,
	SurvivalWin,
	SurvivalDraw
};

enum GamePhase : int32_t
{
	GAMEPHASE_WARMUP_ROUND,
	GAMEPHASE_PLAYING_STANDARD,
	GAMEPHASE_PLAYING_FIArenaT_HALF,
	GAMEPHASE_PLAYING_SECOND_HALF,
	GAMEPHASE_HALFTIME,
	GAMEPHASE_MATCH_ENDED,
	GAMEPHASE_MAX
};

enum InputBitMask_t : uint64_t
{
	IN_NONE = 0x0,
	IN_ALL = 0xffffffffffffffff,
	IN_ATTACK = 0x1,
	IN_JUMP = 0x2,
	IN_DUCK = 0x4,
	IN_FORWARD = 0x8,
	IN_BACK = 0x10,
	IN_USE = 0x20,
	IN_TURNLEFT = 0x80,
	IN_TURNRIGHT = 0x100,
	IN_MOVELEFT = 0x200,
	IN_MOVERIGHT = 0x400,
	IN_ATTACK2 = 0x800,
	IN_RELOAD = 0x2000,
	IN_SPEED = 0x10000,
	IN_JOYAUTOSPRINT = 0x20000,
	IN_FIRST_MOD_SPECIFIC_BIT = 0x100000000,
	IN_USEORRELOAD = 0x100000000,
	IN_SCORE = 0x200000000,
	IN_ZOOM = 0x400000000,
	IN_LOOK_AT_WEAPON = 0x800000000,
};

enum EInButtonState : uint32_t
{
	IN_BUTTON_UP = 0x0,
	IN_BUTTON_DOWN = 0x1,
	IN_BUTTON_DOWN_UP = 0x2,
	IN_BUTTON_UP_DOWN = 0x3,
	IN_BUTTON_UP_DOWN_UP = 0x4,
	IN_BUTTON_DOWN_UP_DOWN = 0x5,
	IN_BUTTON_DOWN_UP_DOWN_UP = 0x6,
	IN_BUTTON_UP_DOWN_UP_DOWN = 0x7,
	IN_BUTTON_STATE_COUNT = 0x8,
};

enum ParticleAttachment_t : uint32_t
{
	PATTACH_INVALID = 0xffffffff,
	PATTACH_ABSORIGIN = 0x0,
	PATTACH_ABSORIGIN_FOLLOW = 0x1,
	PATTACH_CUSTOMORIGIN = 0x2,
	PATTACH_CUSTOMORIGIN_FOLLOW = 0x3,
	PATTACH_POINT = 0x4,
	PATTACH_POINT_FOLLOW = 0x5,
	PATTACH_EYES_FOLLOW = 0x6,
	PATTACH_OVERHEAD_FOLLOW = 0x7,
	PATTACH_WORLDORIGIN = 0x8,
	PATTACH_ROOTBONE_FOLLOW = 0x9,
	PATTACH_RENDERORIGIN_FOLLOW = 0xa,
	PATTACH_MAIN_VIEW = 0xb,
	PATTACH_WATERWAKE = 0xc,
	PATTACH_CENTER_FOLLOW = 0xd,
	PATTACH_CUSTOM_GAME_STATE_1 = 0xe,
	PATTACH_HEALTHBAR = 0xf,
	MAX_PATTACH_TYPES = 0x10,
};

enum ObserverMode_t : uint8_t
{
	OBS_MODE_NONE = 0x0,
	OBS_MODE_FIXED = 0x1,
	OBS_MODE_IN_EYE = 0x2,
	OBS_MODE_CHASE = 0x3,
	OBS_MODE_ROAMING = 0x4,
	OBS_MODE_DIRECTED = 0x5,
	NUM_OBSERVER_MODES = 0x6,
};

#if !__has_include("schemacompiler/schemaoff.h")
typedef uint32 SoundEventGuid_t;
#endif
struct SndOpEventGuid_t
{
	SoundEventGuid_t m_nGuid;
	uint64 m_hStackHash;
};

enum gender_t : uint8
{
	GENDER_NONE = 0x0,
	GENDER_MALE = 0x1,
	GENDER_FEMALE = 0x2,
	GENDER_NAMVET = 0x3,
	GENDER_TEENGIRL = 0x4,
	GENDER_BIKER = 0x5,
	GENDER_MANAGER = 0x6,
	GENDER_GAMBLER = 0x7,
	GENDER_PRODUCER = 0x8,
	GENDER_COACH = 0x9,
	GENDER_MECHANIC = 0xA,
	GENDER_CEDA = 0xB,
	GENDER_CRAWLER = 0xC,
	GENDER_UNDISTRACTABLE = 0xD,
	GENDER_FALLEN = 0xE,
	GENDER_RIOT_CONTROL = 0xF,
	GENDER_CLOWN = 0x10,
	GENDER_JIMMY = 0x11,
	GENDER_HOSPITAL_PATIENT = 0x12,
	GENDER_BRIDE = 0x13,
	GENDER_LAST = 0x14,
};

enum DamageTypes_t : uint32_t
{
	DMG_GENERIC = 0x0,
	DMG_CRUSH = 0x1,
	DMG_BULLET = 0x2,
	DMG_SLASH = 0x4,
	DMG_BURN = 0x8,
	DMG_VEHICLE = 0x10,
	DMG_FALL = 0x20,
	DMG_BLAST = 0x40,
	DMG_CLUB = 0x80,
	DMG_SHOCK = 0x100,
	DMG_SONIC = 0x200,
	DMG_ENERGYBEAM = 0x400,
	DMG_DROWN = 0x4000,
	DMG_POISON = 0x8000,
	DMG_RADIATION = 0x10000,
	DMG_DROWNRECOVER = 0x20000,
	DMG_ACID = 0x40000,
	DMG_PHYSGUN = 0x100000,
	DMG_DISSOLVE = 0x200000,
	DMG_BLAST_SURFACE = 0x400000,
	DMG_BUCKSHOT = 0x1000000,
	DMG_LASTGENERICFLAG = 0x1000000,
	DMG_HEADSHOT = 0x2000000,
	DMG_DANGERZONE = 0x4000000,
};

enum TakeDamageFlags_t : uint32_t
{
	DFLAG_NONE = 0x0,
	DFLAG_SUPPRESS_HEALTH_CHANGES = 0x1,
	DFLAG_SUPPRESS_PHYSICS_FORCE = 0x2,
	DFLAG_SUPPRESS_EFFECTS = 0x4,
	DFLAG_PREVENT_DEATH = 0x8,
	DFLAG_FORCE_DEATH = 0x10,
	DFLAG_ALWAYS_GIB = 0x20,
	DFLAG_NEVER_GIB = 0x40,
	DFLAG_REMOVE_NO_RAGDOLL = 0x80,
	DFLAG_SUPPRESS_DAMAGE_MODIFICATION = 0x100,
	DFLAG_ALWAYS_FIRE_DAMAGE_EVENTS = 0x200,
	DFLAG_RADIUS_DMG = 0x400,
	DMG_LASTDFLAG = 0x400,
	DFLAG_IGNORE_ARMOR = 0x800,
};

struct EmitSound_t
{
	EmitSound_t() :
		m_pSoundName( 0 ),
		m_vecOrigin( 0.0f, 0.0f, 0.0f ),
		m_flVolume( VOL_NORM ),
		m_flSoundTime( 0.0f ),
		m_nSpeakerEntity( -1 ),
		m_nForceGuid( 0 ),
		m_nSourceSoundscape( 0 ),
		m_nPitch( PITCH_NORM ),
		m_nFlags( 0 )
	{
	}

	const char *m_pSoundName;
	Vector m_vecOrigin;
	float m_flVolume;
	float m_flSoundTime;
	CEntityIndex m_nSpeakerEntity;
	SoundEventGuid_t m_nForceGuid;
	CEntityIndex m_nSourceSoundscape;
	uint16 m_nPitch;
	uint8 m_nFlags;
};

struct GameTick_t
{
public:
	DECLARE_SCHEMA_CLASS_INLINE(GameTick_t)

	SCHEMA_FIELD(int32_t, m_Value);
};

struct AmmoIndex_t
{
public:
	DECLARE_SCHEMA_CLASS_INLINE(AmmoIndex_t)

	SCHEMA_FIELD(int8_t, m_Value);
};

class CNetworkVelocityVector
{
public:
	DECLARE_SCHEMA_CLASS_INLINE(CNetworkVelocityVector)

	SCHEMA_FIELD(float, m_vecX)
	SCHEMA_FIELD(float, m_vecY)
	SCHEMA_FIELD(float, m_vecZ)
};

class CNetworkOriginCellCoordQuantizedVector
{
public:
	DECLARE_SCHEMA_CLASS_INLINE(CNetworkOriginCellCoordQuantizedVector)

	SCHEMA_FIELD(uint16, m_cellX)
	SCHEMA_FIELD(uint16, m_cellY)
	SCHEMA_FIELD(uint16, m_cellZ)
	SCHEMA_FIELD(uint16, m_nOutsideWorld)

	SCHEMA_FIELD(float, m_vecX)
	SCHEMA_FIELD(float, m_vecY)
	SCHEMA_FIELD(float, m_vecZ)
};

class CInButtonState
{
public:
	DECLARE_SCHEMA_CLASS_INLINE(CInButtonState)

	SCHEMA_FIELD_POINTER(uint64, m_pButtonStates)
};

class CGlowProperty
{
public:
	DECLARE_SCHEMA_CLASS_INLINE(CGlowProperty)

	SCHEMA_FIELD(Vector, m_fGlowColor)
	SCHEMA_FIELD(int, m_iGlowType)
	SCHEMA_FIELD(int, m_iGlowTeam)
	SCHEMA_FIELD(int, m_nGlowRange)
	SCHEMA_FIELD(int, m_nGlowRangeMin)
	SCHEMA_FIELD(Color, m_glowColorOverride)
	SCHEMA_FIELD(bool, m_bFlashing)
	SCHEMA_FIELD(bool, m_bGlowing)
};

struct TraceHistory
{
	Vector start;
	Vector end;
	Ray_t ray;
	bool didHit;
	Vector m_vStartPos;
	Vector m_vEndPos;
	Vector m_vHitNormal;
	Vector m_vHitPoint;

	float m_flHitOffset;
	float m_flFraction;

	float32 error;
	Vector velocity;
};

class CCheckTransmitInfoHack
{
public:
	CBitVec<16384>* m_pTransmitEntity;

private:
	[[maybe_unused]] int8_t m_pad8[568];

public:
	int32_t m_nPlayerSlot;
	bool m_bFullUpdate;
};

struct trace_info_t {
	CEntityInstance *m_pEnt;
	const CHitBox *m_pHitbox;
	Vector m_vStartPos;
	Vector m_vEndPos;
	Vector m_vHitNormal;
	Vector m_vHitPoint;
	float m_flHitOffset;
	float m_flFraction;
	int32 m_nTriangle;
	int16 m_nHitboxBoneIndex;
	RayType_t m_eRayType;
	bool m_bStartInSolid;
	bool m_bExactHitPoint;

	bool DidHit() const 
	{ 
		return m_flFraction < 1 || m_bStartInSolid; 
	}
};