#include "Help.h"
#include <iostream>

// ����� ��� �������� ��������
SDL_Texture* Help::LoadTexture(SDL_Renderer* renderer, const std::string& filePath) {
	// ���������, ��� �������� � ���� � ����� ���������
	if (!renderer || filePath.empty()) {
		std::cerr << "Invalid renderer or file path!" << std::endl;
		return nullptr;
	}

	// ��������� �������� �� �����
	SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
	if (!texture) {
		std::cerr << "Failed to load texture from '" << filePath << "': " << IMG_GetError() << std::endl;
		return nullptr;
	}

	return texture; // ���������� ��������� ��������
}