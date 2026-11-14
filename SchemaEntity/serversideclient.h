#pragma once

#include "playerslot.h"
#include "steam/steamclientpublic.h"
#include "utlstring.h"
#include "inetchannel.h"
#include "networkbasetypes.pb.h"

class CServerSideClient : public INetworkMessageProcessingPreFilter
{
public:
	virtual ~CServerSideClient() = 0;

	INetChannel* GetNetChannel() const { return m_NetChannel; };
    CPlayerSlot GetPlayerSlot() const { return m_nClientSlot; };
    CEntityIndex GetEntityIndex() const { return m_nEntityIndex; };
    CPlayerUserId GetUserID() const { return m_UserID; };
    int GetSignonState() const { return m_nSignonState; }
    CSteamID GetClientSteamID() const { return m_SteamID; }
    const char* GetClientName() const { return m_Name; };
    bool IsConnected() const { return m_nSignonState >= SIGNONSTATE_CONNECTED; };
    bool IsSpawned() const { return m_nSignonState >= SIGNONSTATE_NEW; };
    bool IsActive() const { return m_nSignonState == SIGNONSTATE_FULL; };
    bool IsFakeClient() const { return m_bFakePlayer; };
    bool IsHLTV() const { return m_bIsHLTV; }
    bool IsFullyAuthenticated() { return m_bFullyAuthenticated; }
    const netadr_t* GetRemoteAddress() const { return &m_NetAdr0; }

	void ForceFullUpdate() { m_nDeltaTick = -1; }
	
	virtual void Connect(int a2, const char* szName, int a4, void* a5, bool bFakePlayer, int a7, int a8) = 0;

private:
	[[maybe_unused]] void *m_pVT1;
	[[maybe_unused]] char pad1[0x30];
#ifdef __linux__
	[[maybe_unused]] char pad2[0x10];
#endif
	CUtlString m_Name;
	CPlayerSlot m_nClientSlot;
	CEntityIndex m_nEntityIndex;
	[[maybe_unused]] char pad3[0x8];
	INetChannel *m_NetChannel;
	[[maybe_unused]] char pad4[0x4];
	int32 m_nSignonState;
	[[maybe_unused]] char pad5[0x38];
	bool m_bFakePlayer;
	[[maybe_unused]] char pad6[0x7];
	CPlayerUserId m_UserID;
	[[maybe_unused]] char pad7[0x1];
	CSteamID m_SteamID;
	[[maybe_unused]] char pad8[0x19];
	netadr_t m_NetAdr0;
	[[maybe_unused]] char pad9[0x14];
	netadr_t m_NetAdr1;
	[[maybe_unused]] char pad10[0x22];
	bool m_bIsHLTV;
	[[maybe_unused]] char pad11[0x19];
	int m_nDeltaTick;
	[[maybe_unused]] char pad12[0x882];
	bool m_bFullyAuthenticated;
};