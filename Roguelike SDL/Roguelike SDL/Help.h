#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>


static class Help
{
public:
	// Метод для загрузки текстуры
	static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& filePath);

};