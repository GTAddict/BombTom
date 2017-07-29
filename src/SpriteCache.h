#pragma once
#include <map>
#include <string>


class SpriteCache
{
public:
	static SpriteCache* GetInstance();
	void Destroy();

	int Load(std::string name);
	int GetTextureID(std::string name);

private:
	SpriteCache();
	~SpriteCache();

	static SpriteCache* instance;
	std::map<std::string, int> spriteMap;
};

