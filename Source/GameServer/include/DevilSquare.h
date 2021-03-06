#ifndef DEVILSQUARE_H
#define DEVILSQUARE_H

#include "DevilSquareGround.h"
#include "user.h"
#include "../Test/CharacterInfo.h"

// Original

enum eDevilSquareState
{
	DevilSquare_CLOSE = 0,
	DevilSquare_OPEN = 1,
	DevilSquare_PLAYING = 2,
};

#define MAX_DEVILSQUARE_USER	15

#define DS_LEVEL_RANGE(level) ( ( ((level)) < 0  )?FALSE:( ((level)) > MAX_DEVILSQUARE_GROUND-1  )?FALSE:TRUE)

class CDevilSquare
{

public:

	CDevilSquare(void);
	~CDevilSquare(void);
	void Init();
	void SetState(enum eDevilSquareState eState);
	enum eDevilSquareState GetState(){return this->m_eState;};	// line : 93
	int Run();
	int GetRemainTime(){return this->m_iRemainTime;}
	void SetMonster();
	void ClearMonstr();
	void gDevilSquareMonsterRegen(LPOBJ lpObj);
	void DieProcDevilSquare(LPOBJ lpObj);
	int gObjMonsterExpSingle(LPOBJ lpObj, LPOBJ lpTargetObj, int dmg, int tot_dmg);
	void gObjExpParty(LPOBJ lpObj, LPOBJ lpTargetObj, int AttackDamage, int MSBFlag);
	void gObjMonsterScoreDivision(LPOBJ lpMonObj, LPOBJ lpObj, int AttackDamage, int MSBFlag);
	void Load(const char* filename);
	void CalcScore();
	void SetClose();
	int GetDevilSquareIndex(int iGateNumber);
	int GetUserLevelToEnter(int iUserIndex, WORD& btMoveGate);

private:

	void SetOpen();
	void SetPlaying();
	void ProcClose();
	void ProcOpen();
	void ProcPlaying();
	void SendEventStartMsg();
	void ItemClear();
	void CheckSync();
	void SendLiveCall();
	void gObjScoreClear();
	void CheckInvalidUser();

public:


	enum eDevilSquareState m_eState;	// 4
	DWORD m_iTime;	// 8
	int m_iRemainTime;	// C
	int m_iremainTimeSec;	// 10
	BOOL m_bSendTimeCount;	// 14
	BOOL m_bQuit;	// 18
	BOOL m_bFlag;	// 1C
	UINT m_hThread;	// 20
	int m_iCloseTime;	// 24
	int m_iOpenTime;	// 28
	int m_iPlaytime;	// 2C
	CDevilSquareGround m_DevilSquareGround[MAX_DEVILSQUARE_GROUND];	// 30
	int m_BonusScoreTable[MAX_CLASS_TYPE][MAX_DEVILSQUARE_GROUND];	// 1BA8

	// ---- NEW ADDED
	char Enabled;
	char DS1ChaosSuccessRate;
	char DS2ChaosSuccessRate;
	char DS3ChaosSuccessRate;
	char DS4ChaosSuccessRate;
	char DS5ChaosSuccessRate;
	char DS6ChaosSuccessRate;
	char DS7ChaosSuccessRate;
};

extern CDevilSquare g_DevilSquare;


struct EVENT_LEVEL_LIMITATION_EX
{
	int NormalCharacterMinLevel; // Dark Knight, Dark Wizard, Elf
	int NormalCharacterMaxLevel; // Dark Knight, Dark Wizard, Elf
	int SpecialCharacterMinLevel; // Magic Gladiator, Dark Lord
	int SpecialCharacterMaxLevel; // Magic Gladitor, Dark Lord
	int MoveGate;	// Dest Gate
};

static EVENT_LEVEL_LIMITATION_EX g_sttDEVILSQUARE_LEVEL[MAX_DEVILSQUARE_GROUND] =
{
	// Devil Square 1
	15, 130, // DK, DW, Elf
	10, 110, // MG, DL
	58,	// Gate

	// Devil Square 2
	131, 180, // DK, DW, Elf
	111, 160, // MG, DL
	59,	// Gate

	// Devil Square 3
	181, 230, // DK, DW, Elf
	161, 210, // MG, DL
	60,	// Gate

	// Devil Square 4
	231, 280, // DK, DW, Elf
	211, 260, // MG, DL
	61,	// Gate

	// Devil Square 5
	281, 330, // DK, DW, Elf
	261, 310, // MG, DL
	111,	// Gate

	// Devil Square 6
	331, 400, // DK, DW, Elf
	311, 400, // MG, DL
	112	// Gate
};


unsigned __stdcall DevilSquareThreadFunc(void * p);
void DevilSquareProtocolCore(BYTE protoNum, LPBYTE aRecv, int  aLen);
void DataSendRank(char* pMsg, int size);

#endif