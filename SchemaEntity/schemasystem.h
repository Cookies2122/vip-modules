
#pragma once

#ifdef _WIN32
	#pragma warning(push)
	#pragma warning(disable : 4005)
#endif

#include <type_traits>

#ifdef _WIN32
	#pragma warning(pop)
#endif

#include <tier1/utldelegate.h>
#include <variant.h>
#include <entity2/entityclass.h>
#include <entity2/entityidentity.h>
#include <entity2/entityinstance.h>
#include <entity2/entitynetwork.h>
#include "const.h"
#include "stdint.h"
#include "tier0/dbg.h"
#include "virtual.h"
#undef schema

struct SchemaKey
{
	int32 offset;
	bool networked;
	bool found = false;
};

template <typename T>
inline T* SchemaMissing()
{
	alignas(64) static unsigned char s_spare[4096] = {};
	return reinterpret_cast<T*>(s_spare);
}

class CNetworkVarChainer2
{
public:
	CEntityInstance* m_pEntity;

private:
	uint8 pad_0000[24];

public:
	ChangeAccessorFieldPathIndex_t m_PathIndex;

private:
	uint8 pad_0024[4];
};

void EntityNetworkStateChanged(uintptr_t pEntity, uint nOffset);
void ChainNetworkStateChanged(uintptr_t pNetworkVarChainer, uint nOffset);
void NetworkVarStateChanged(uintptr_t pNetworkVar, uint32_t nOffset, uint32 nNetworkStateChangedOffset);

namespace schema
{
	int16_t FindChainOffset(const char* className, uint32_t classNameHash);
	int16_t FindChainOffset(const char* className);
	SchemaKey GetOffset(const char* className, uint32_t classKey, const char* memberName, uint32_t memberKey);
	int32_t GetServerOffset(const char* pszClassName, const char* pszPropName);
}

constexpr uint32_t val_32_const = 0x811c9dc5;
constexpr uint32_t prime_32_const = 0x1000193;
constexpr uint64_t val_64_const = 0xcbf29ce484222325;
constexpr uint64_t prime_64_const = 0x100000001b3;

inline constexpr uint32_t hash_32_fnv1a_const(const char* const str, const uint32_t value = val_32_const) noexcept
{
	return (str[0] == '\0') ? value : hash_32_fnv1a_const(&str[1], (value ^ uint32_t(str[0])) * prime_32_const);
}

inline constexpr uint64_t hash_64_fnv1a_const(const char* const str, const uint64_t value = val_64_const) noexcept
{
	return (str[0] == '\0') ? value : hash_64_fnv1a_const(&str[1], (value ^ uint64_t(str[0])) * prime_64_const);
}

#define SCHEMA_FIELD_OFFSET(type, varName, extra_offset)                                                                     \
	class varName##_prop                                                                                                     \
	{                                                                                                                        \
	public:                                                                                                                  \
		std::add_lvalue_reference_t<type> Get()                                                                              \
		{                                                                                                                    \
			static const auto m_key = schema::GetOffset(m_className, m_classNameHash, #varName, m_varNameHash);              \
			static const auto m_offset = offsetof(ThisClass, varName);														 \
			if (!m_key.found)                                                                                                \
				return *SchemaMissing<type>();                                                                               \
																															 \
			uintptr_t pThisClass = ((uintptr_t)this - m_offset);                                                             \
                                                                                                                             \
			return *reinterpret_cast<std::add_pointer_t<type>>(pThisClass + m_key.offset + extra_offset);                    \
		}                                                                                                                    \
		void Set(type& val, bool changestate = true)																		 \
		{                                                                                                                    \
			static const auto m_key = schema::GetOffset(m_className, m_classNameHash, #varName, m_varNameHash);              \
			static const auto m_chain = schema::FindChainOffset(m_className, m_classNameHash);                               \
			static const auto m_offset = offsetof(ThisClass, varName);														 \
			if (!m_key.found)                                                                                                \
			{                                                                                                                \
				*SchemaMissing<type>() = val;                                                                                \
				return;                                                                                                      \
			}                                                                                                                \
																															 \
			uintptr_t pThisClass = ((uintptr_t)this - m_offset);                                                             \
                                                                                                                             \
			if(changestate) NetworkStateChanged();                                                                                           \
			*reinterpret_cast<std::add_pointer_t<type>>(pThisClass + m_key.offset + extra_offset) = val;                     \
		}                                                                                                                    \
		void NetworkStateChanged()                                                                                           \
		{                                                                                                                    \
			static const auto m_key = schema::GetOffset(m_className, m_classNameHash, #varName, m_varNameHash);				 \
			static const auto m_chain = schema::FindChainOffset(m_className, m_classNameHash);								 \
			static const auto m_offset = offsetof(ThisClass, varName);														 \
																															 \
			if (!m_key.found)                                                                                                \
				return;                                                                                                      \
			uintptr_t pThisClass = ((uintptr_t)this - m_offset);                                                             \
                                                                                                                             \
			if (m_chain != 0 && m_key.networked)                                                                             \
			{                                                                                                                \
				::ChainNetworkStateChanged(pThisClass + m_chain, m_key.offset + extra_offset);								 \
			}                                                                                                                \
			else if (m_key.networked)                                                                                        \
			{                                                                                                                \
				if (!m_networkStateChangedOffset)                                                                            \
					::EntityNetworkStateChanged(pThisClass, m_key.offset + extra_offset);									 \
				else                                                                                                         \
					::NetworkVarStateChanged(pThisClass, m_key.offset + extra_offset, m_networkStateChangedOffset);			 \
			}                                                                                                                \
		}                                                                                                                    \
		operator std::add_lvalue_reference_t<type>()                                                                         \
		{                                                                                                                    \
			return Get();                                                                                                    \
		}                                                                                                                    \
		std::add_lvalue_reference_t<type> operator()()                                                                       \
		{                                                                                                                    \
			return Get();                                                                                                    \
		}                                                                                                                    \
		std::add_lvalue_reference_t<type> operator->()                                                                       \
		{                                                                                                                    \
			return Get();                                                                                                    \
		}                                                                                                                    \
		void operator()(type val)                                                                                            \
		{                                                                                                                    \
			Set(val);                                                                                                        \
		}                                                                                                                    \
		std::add_lvalue_reference_t<type> operator=(type val)                                                                \
		{                                                                                                                    \
			Set(val);                                                                                                        \
			return Get();                                                                                                    \
		}                                                                                                                    \
		std::add_lvalue_reference_t<type> operator=(varName##_prop& val)                                                     \
		{                                                                                                                    \
			Set(val());                                                                                                      \
			return Get();                                                                                                    \
		}                                                                                                                    \
	private:                                                                                                                 \
		                                   \
		varName##_prop(const varName##_prop&) = delete;                                                                      \
		static constexpr auto m_varNameHash = hash_32_fnv1a_const(#varName);                                                 \
	} varName;

#define SCHEMA_FIELD_POINTER_OFFSET(type, varName, extra_offset)                                                             \
	class varName##_prop                                                                                                     \
	{                                                                                                                        \
	public:                                                                                                                  \
		type* Get()                                                                                                          \
		{                                                                                                                    \
			static const auto m_key = schema::GetOffset(m_className, m_classNameHash, #varName, m_varNameHash);				 \
			static const auto m_offset = offsetof(ThisClass, varName);														 \
			if (!m_key.found)                                                                                                \
				return SchemaMissing<type>();                                                                                \
																															 \
			uintptr_t pThisClass = ((uintptr_t)this - m_offset);                                                             \
                                                                                                                             \
			return reinterpret_cast<std::add_pointer_t<type>>(pThisClass + m_key.offset + extra_offset);                     \
		}                                                                                                                    \
		void NetworkStateChanged()                                                       \
		{                                                                                                                    \
			static const auto m_key = schema::GetOffset(m_className, m_classNameHash, #varName, m_varNameHash);				 \
			static const auto m_chain = schema::FindChainOffset(m_className, m_classNameHash);								 \
			static const auto m_offset = offsetof(ThisClass, varName);														 \
																															 \
			if (!m_key.found)                                                                                                \
				return;                                                                                                      \
			uintptr_t pThisClass = ((uintptr_t)this - m_offset);                                                             \
                                                                                                                             \
			if (m_chain != 0 && m_key.networked)                                                                             \
			{                                                                                                                \
				::ChainNetworkStateChanged(pThisClass + m_chain, m_key.offset + extra_offset);								 \
			}                                                                                                                \
			else if (m_key.networked)                                                                                        \
			{                                                                                                                \
				if (!m_networkStateChangedOffset)                                                                            \
					::EntityNetworkStateChanged(pThisClass, m_key.offset + extra_offset);									 \
				else                                                                                                         \
					::NetworkVarStateChanged(pThisClass, m_key.offset + extra_offset, m_networkStateChangedOffset);			 \
			}                                                                                                                \
		}                                                                                                                    \
		operator type*()                                                                                                     \
		{                                                                                                                    \
			return Get();                                                                                                    \
		}                                                                                                                    \
		type* operator()()                                                                                                   \
		{                                                                                                                    \
			return Get();                                                                                                    \
		}                                                                                                                    \
		type* operator->()                                                                                                   \
		{                                                                                                                    \
			return Get();                                                                                                    \
		}                                                                                                                    \
	private:                                                                                                                 \
		                                   \
		varName##_prop(const varName##_prop&) = delete;                                                                      \
		static constexpr auto m_varNameHash = hash_32_fnv1a_const(#varName);                                                 \
	} varName;

#define SCHEMA_FIELD(type, varName) \
	SCHEMA_FIELD_OFFSET(type, varName, 0)

#define SCHEMA_FIELD_POINTER(type, varName) \
	SCHEMA_FIELD_POINTER_OFFSET(type, varName, 0)

#define DECLARE_SCHEMA_CLASS_BASE(ClassName, offset)								\
	private:																		\
		typedef ClassName ThisClass;												\
		static constexpr const char* m_className = #ClassName;						\
		static constexpr uint32_t m_classNameHash = hash_32_fnv1a_const(#ClassName);\
		static constexpr int m_networkStateChangedOffset = offset;					\
	public:

#define SCHEMA_FIELD_OLD(type, className, propName)                                                    \
    std::add_lvalue_reference_t<type> propName()                                                       \
    {                                                                                                  \
        static const int32_t offset = schema::GetServerOffset(#className, #propName);        \
        if(offset == -1)                                                                               \
            return *SchemaMissing<type>();                                                             \
        return *reinterpret_cast<std::add_pointer_t<type>>(reinterpret_cast<intptr_t>(this) + offset); \
    }

#define DECLARE_SCHEMA_CLASS(className) DECLARE_SCHEMA_CLASS_BASE(className, 0)

#define DECLARE_SCHEMA_CLASS_INLINE(className) DECLARE_SCHEMA_CLASS_BASE(className, 1)