#include "SpriteCache.h"
#include "SOIL.h"

SpriteCache* SpriteCache::instance = NULL;

SpriteCache::SpriteCache()
{
}


SpriteCache::~SpriteCache()
{
}

int SpriteCache::Load(std::string name)
{
	int textureID = -1;

	// If it exists already
	if (spriteMap.find(name) != spriteMap.end())
	{
		textureID = spriteMap[name];
	}
	else // Otherwise, add it
	{
		textureID = SOIL_load_OGL_texture(name.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

		spriteMap.insert(std::pair<std::string, int>(name, textureID));
	}

	return textureID;
}

int SpriteCache::GetTextureID(std::string name)
{
	int textureId = -1;

	textureId = spriteMap[name];

	return textureId;
}

SpriteCache* SpriteCache::GetInstance()
{
	if (!instance)
	{
		instance = new SpriteCache();
	}

	return instance;
}

void SpriteCache::Destroy()
{
	if (instance)
	{
		delete instance;
		instance = NULL;
	}
}