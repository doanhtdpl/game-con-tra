#ifndef __CMANAGE__AUDIO__
#define __CMANAGE__AUDIO__

#include <hash_map>
#include "CSoundUtil.h"
#include "CSingleton.h"

enum TypeAudio;

class ManageAudio : public CSingleton<ManageAudio>
{
	friend class CSingleton<ManageAudio>;
protected:
	CSoundManager* soundManage;
	std::hash_map<int, CSound*> listAudio;

public:
	bool _Music_Background;
	bool _Sound;

	ManageAudio(void);
	int init_DirectSound(HWND);
	void addSound(int key, bool loop, std::string fileName);
	CSound* loadSound(bool loop, std::string fileName);
	void playSound(TypeAudio _type);
	void loopSound(CSound *);
	void stopSound(TypeAudio _type);
	void readFileAudio();
	~ManageAudio(void);
};

#endif // !__CMANAGE__AUDIO__

#ifndef __TYPE__AUDIO__
#define __TYPE__AUDIO__

enum TypeAudio
{
	AUDIO_BACKGROUND_STATE_1 = 1001,
	AUDIO_BACKGROUND_GAMEOVER = 1002,
	AUDIO_BACKGROUND_MENU = 1003,
	VBOOM_SFX = 1004,
	BOSS_DEAD_SFX = 1005,
	BRIDGE_BURN_SFX = 1006,
	BRIDGE_EXPLOISION_SFX = 1007,
	BULLET_L_SFX = 1008,
	BULLET_M_SFX = 1009,
	BULLET_N = 1010,
	BULLET_S = 1011,
	E_BROKEN = 1012,
	ENEMY_ATTACKED_SFX = 1013,
	ENEMY_DEAD_SFX = 1014,
	RAMBO_1UP_SFX = 1015,
	RAMBO_DEAD_SFX = 1016,
	RAMBO_STEP_SFX = 1017
};

#endif // !__TYPE__AUDIO__
