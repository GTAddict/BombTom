#pragma once
#include <list>
#include <map>

enum class Layers
{
	invalid = -1,
	first = 0,
	background = first,
	player,
	enemy,
	bullet,
	count
};

class Sprite;

typedef std::map<Layers, std::list<Sprite*>> RenderMap_t;

class SpriteRenderer
{
public:
	void Render();
	void Register(Sprite* sprite, int layer);
	void UnRegister(Sprite* sprite, int layer);

	static SpriteRenderer* GetInstance();
	void Destroy();

private:
	SpriteRenderer();
	~SpriteRenderer();
	RenderMap_t renderMap;

	static SpriteRenderer* s_mInstance;
};

