#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>


static class Help
{
public:
	static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& filePath);

    // Вычисление длины вектора
    static float Length(const SDL_FPoint& vector);

    // Нормализация вектора
    static SDL_FPoint Normalize(const SDL_FPoint& vector);

    // Скалярное умножение вектора на число
    static SDL_FPoint Multiply(const SDL_FPoint& vector, float scalar);

    // Скалярное деление вектора на число
    static SDL_FPoint Divide(const SDL_FPoint& vector, float scalar);

    // Разность двух векторов
    static SDL_FPoint Subtract(const SDL_FPoint& a, const SDL_FPoint& b);

    // Сумма двух векторов
    static SDL_FPoint Add(const SDL_FPoint& a, const SDL_FPoint& b);

    // Расчет расстояния между двумя точками
    static float Distance(const SDL_FPoint& a, const SDL_FPoint& b);
};