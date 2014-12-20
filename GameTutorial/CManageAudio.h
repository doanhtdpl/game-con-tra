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
	AUDIO_BACKGROUND_STATE_1 = 1001
};

#endif // !__TYPE__AUDIO__
