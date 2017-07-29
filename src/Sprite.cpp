#include "Sprite.h"
#include "SOIL.h"
#include "SpriteCache.h"
#include "glut.h"
#include "SpriteRenderer.h"
#include <cmath>

Sprite::Sprite()
	: mTextureId(-1)
	, mPosX(-1)
	, mPosY(-1)
	, mWidth(-1)
	, mHeight(-1)
	, mLayerID((int)Layers::invalid)
	, mVisible(true)
{
}


Sprite::~Sprite()
{
}

void Sprite::Init(std::string fileName, int x, int y, int width, int height, int layer)
{
	mTextureId = SpriteCache::GetInstance()->Load(fileName);
	mWidth = width;
	mHeight = height;

	SetPositionX(x);
	SetPositionY(y);

	mLayerID = layer;

	SpriteRenderer::GetInstance()->Register(this, mLayerID);
}

void Sprite::Destroy()
{
	SpriteRenderer::GetInstance()->UnRegister(this, mLayerID);
}

void Sprite::Render()
{
	if (!mVisible)	return;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(mPosX - mWidth / 2, mPosY - mHeight / 2, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(mPosX + mWidth / 2, mPosY - mHeight / 2, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(mPosX + mWidth / 2, mPosY + mHeight / 2, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(mPosX - mWidth / 2, mPosY + mHeight / 2, 0.0f);
	glEnd();
}

void Sprite::SetPosition(int x, int y)
{
	SetPositionX(x);
	SetPositionY(y);
}

void Sprite::SetPositionX(int x)
{
	mPosX = x;
}

void Sprite::SetPositionY(int y)
{
	mPosY = y;
}

bool Sprite::Intersects(Sprite* other)
{
	if (mPosX < other->mPosX + other->mWidth
		&& mPosX + mWidth > other->mPosX
		&& mPosY < other->mPosY + other->mHeight
		&& mHeight + mPosY > other->mHeight)
	{
		return true;
	}

	return false;
}