#include "Help.h"
#include <iostream>
#include <random>

// Method for loading a texture
SDL_Texture* Help::LoadTexture(SDL_Renderer* renderer, const std::string& filePath) {
	// Проверяем, что рендерер и путь к файлу корректны
	if (!renderer || filePath.empty()) {
		std::cerr << "Invalid renderer or file path!" << std::endl;
		return nullptr;
	}

	// Load texture from file
	SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
	if (!texture) {
		std::cerr << "Failed to load texture from '" << filePath << "': " << IMG_GetError() << std::endl;
		return nullptr;
	}

	return texture;
}

// Вычисление длины вектора
float Help::Length(const SDL_FPoint& vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

// Нормализация вектора
SDL_FPoint Help::Normalize(const SDL_FPoint& vector) {
    float length = Length(vector);
    if (length > 0.0f) {
        return { vector.x / length, vector.y / length };
    }
    return { 0.0f, 0.0f }; // Возвращаем нулевой вектор, если длина равна нулю
}

// Скалярное умножение вектора на число
SDL_FPoint Help::Multiply(const SDL_FPoint& vector, float scalar) {
    return { vector.x * scalar, vector.y * scalar };
}

// Скалярное деление вектора на число
SDL_FPoint Help::Divide(const SDL_FPoint& vector, float scalar) {
    if (scalar != 0.0f) {
        return { vector.x / scalar, vector.y / scalar };
    }
    return { 0.0f, 0.0f }; // Избегаем деления на ноль
}

// Разность двух векторов
SDL_FPoint Help::Subtract(const SDL_FPoint& a, const SDL_FPoint& b) {
    return { a.x - b.x, a.y - b.y };
}

// Сумма двух векторов
SDL_FPoint Help::Add(const SDL_FPoint& a, const SDL_FPoint& b) {
    return { a.x + b.x, a.y + b.y };
}

float Help::Distance(const SDL_FPoint& a, const SDL_FPoint& b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float Help::NextFloat() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0f, 1.0f);
    return dis(gen);
}