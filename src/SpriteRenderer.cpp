#include "SpriteRenderer.h"
#include "Sprite.h"
#include <algorithm>

SpriteRenderer* SpriteRenderer::s_mInstance = NULL;

SpriteRenderer::SpriteRenderer()
{
}


SpriteRenderer::~SpriteRenderer()
{
}

SpriteRenderer* SpriteRenderer::GetInstance()
{
	if (s_mInstance == NULL)
	{
		s_mInstance = new SpriteRenderer();
	}

	return s_mInstance;
}

void SpriteRenderer::Destroy()
{
	if (s_mInstance)
	{
		delete s_mInstance;
		s_mInstance = NULL;
	}
}

void SpriteRenderer::Render()
{
	for (int i = 0; i <= (int)Layers::count; ++i)
	{
		std::list<Sprite*> sprites = renderMap[(Layers)i];
		for each (Sprite* sprite in sprites)
		{
			sprite->Render();
		}
	}
}

void SpriteRenderer::Register(Sprite* sprite, int layer)
{
	// Assuming that each sprite calls only once. Not
	// checking for multiple registrations
	renderMap[(Layers) layer].push_back(sprite);
}

void SpriteRenderer::UnRegister(Sprite* sprite, int layer)
{
	// Assuming that each sprite calls only once. Not
	// checking for multiple registrations
	renderMap[(Layers)layer].remove(sprite);
}