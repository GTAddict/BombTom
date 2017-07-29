#pragma once
#include <string>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(std::string fileName, int x, int y, int width, int height, int layer);
	void Destroy();
	void Render();

	void SetPosition(int x, int y);
	virtual void SetPositionX(int x);
	virtual void SetPositionY(int y);

	int GetPositionX() { return mPosX; }
	int GetPositionY() { return mPosY; }

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

	void SetVisible(bool visible) { mVisible = visible; }

	virtual void UpdateFrame(long milliseconds) {} ;

	bool Intersects(Sprite* other);

protected:
	int mTextureId;
	int mPosX;
	int mPosY;
	int mWidth;
	int mHeight;
	int mLayerID;
	bool mVisible;
};

