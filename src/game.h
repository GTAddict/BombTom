#include <list>

namespace irrklang
{
	class ISoundEngine;
}

class Background;
class Sprite;
class Player;
class Enemy;

class CGame
{
public:
	const char *GetGameTitle() { return mGameTitle; }
	static CGame	*CreateInstance();
	static CGame	*GetInstance() { return sInstance; };
	~CGame();
	void DrawScene();
	void UpdateFrame(float milliseconds);
	void DestroyGame();
	void init();
	void shutdown();
	void RandomTom();
	static const int mScreenWidth = 1920;
	static const int mScreenHeight = 1080;
	static const int mBitsPerPixel = 32;
private:
	static const char mGameTitle[20];
	static CGame *sInstance;
	CGame() {};

	Background* bg;
	Player* player;
	std::list<Enemy*> enemyList;
	float enemyTimerElapsedMs;
	float dialogueTimeElapsedMs;

	irrklang::ISoundEngine* mAudioEngine;
};
