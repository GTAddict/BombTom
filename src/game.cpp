#define GAME_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collInfo.h"
#include "random.h"
#include "openGLStuff.h"
#include "game.h"
#include "InputManager.h"
#include "Sprite.h"
#include "ShapeDraw.h"
#include "SpriteRenderer.h"
#include "SpriteCache.h"
#include "Player.h"
#include "Enemy.h"
#include "Background.h"

#define ENEMY_SPAWN_INTERVAL 1000
#define DIALOGUE_INTERVAL 2000

// Declarations
const char8_t CGame::mGameTitle[] = "BombTom";
CGame* CGame::sInstance = NULL;

BOOL Initialize(GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window, keys, 0.0f, 0.0f, 0.0f);
	CGame::CreateInstance();
	CGame::GetInstance()->init();
	return TRUE;
}

void CGame::init()
{
	bg = new Background(1920, 1080);
	player = new Player();
	enemyTimerElapsedMs = 0;
	dialogueTimeElapsedMs = 0;
	InputManagerC::GetInstance()->init();

}

void CGame::RandomTom()
{
	int randomDialogue = rand() % 5;
	switch (randomDialogue)
	{
	case 0:
		PlaySound("sound\\Assignments.wav", NULL, SND_ASYNC);
		break;
	case 1:
		PlaySound("sound\\Exams.wav", NULL, SND_ASYNC);
		break;
	case 2:
		PlaySound("sound\\Finals.wav", NULL, SND_ASYNC);
		break;
	case 3:
		PlaySound("sound\\Homework.wav", NULL, SND_ASYNC);
		break;
	case 4:
		PlaySound("sound\\Projects.wav", NULL, SND_ASYNC);
		break;
	}
}

void CGame::UpdateFrame(float milliseconds)
{
	enemyTimerElapsedMs += milliseconds;
	dialogueTimeElapsedMs += milliseconds;

	keyProcess();
	player->UpdateFrame(milliseconds);

	std::list<Enemy*> pendingKill;

	for each (Enemy* enemy in enemyList)
	{
		if (enemy->IsAlive())
		{
 			enemy->UpdateFrame(milliseconds);
		}
		else
		{
			RandomTom();
			pendingKill.push_back(enemy);
		}
	}

	for each (Enemy* enemy in pendingKill)
	{
		enemyList.remove(enemy);
		delete enemy;
	}

	pendingKill.clear();

	if (enemyTimerElapsedMs >= ENEMY_SPAWN_INTERVAL)
	{
		enemyTimerElapsedMs -= ENEMY_SPAWN_INTERVAL;

		Enemy* enemy = new Enemy(*player);
		int randomX = (rand() % (1920 - player->GetWidth())) + player->GetWidth() / 2;

		enemy->SetPosition(randomX, 1080 - player->GetHeight() / 2);

		enemyList.push_back(enemy);
	}

	if (!player->GetAlive())
	{
		RandomTom();
		DestroyGame();
		init();
	}
}

void CGame::DrawScene(void)											
{
	startOpenGLDrawing();
	SpriteRenderer::GetInstance()->Render();
}


CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}
void CGame::shutdown()
{
}
void CGame::DestroyGame(void)
{
	SpriteCache::GetInstance()->Destroy();
	SpriteRenderer::GetInstance()->Destroy();

	delete player;
	for each (Enemy* enemy in enemyList)
	{
		delete enemy;
	}
	enemyList.clear();
	delete bg;
}