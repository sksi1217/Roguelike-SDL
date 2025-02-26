// Game.cpp

#include "Game.h"
#include <iostream>
#include "Player.h"
#include "Help.h"
#include "ManagerGame.h"


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Player* _player;
Camera camera = { {800, 600}, 5 };

// �����������
Game::Game(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        isRunning = false;
        return;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        isRunning = false;
        return;
    }


    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        isRunning = false;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        isRunning = false;
        return;
    }
}

// ����������
Game::~Game() {
    for (auto obj : ManagerGame::gameObjects) {
        delete obj; // ������� ��� ������� �� ������
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}


// �������������
void Game::Initialize() {
    std::cout << "Game initialized!" << std::endl;
}

// �������� ��������
void Game::LoadContent() {
    std::cout << "Loading content..." << std::endl;


    // �������� �������� ������
    SDL_Texture* playerTexture = Help::LoadTexture(renderer, "player.bmp");
    _player = new Player(playerTexture, { 0, 0 });
    ManagerGame::gameObjects.push_back(_player); // ��������� ������ � ������ ��������


    // �������� ������ ��������
    SDL_Texture* boxTexture = Help::LoadTexture(renderer, "box.bmp");
    GameObject* box1 = new GameObject();
    box1->Position = { -50, -50 };
    box1->WidthColliderX = 100;
    box1->HeightColliderY = 100;
    box1->OffsetColliderX = 0;
    box1->OffsetColliderY = 0;
    box1->Texture = boxTexture;
    ManagerGame::gameObjects.push_back(box1);
}

// ���������� ������
void Game::Update(float deltaTime) {
    for (auto obj : ManagerGame::gameObjects) {
        obj->Update(deltaTime); // ��������� ������ ������
    }

    camera.UpdateCamera(_player->Position, deltaTime);

}

// ��������� �����
void Game::Draw() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // ������ ���
    SDL_RenderClear(renderer);

    // ��������� ���� ��������
    for (auto obj : ManagerGame::gameObjects) {
        obj->Draw(renderer, camera);
    }

    SDL_RenderPresent(renderer);
}

// �������� ��������
void Game::UnloadContent() {
    std::cout << "Unloading content..." << std::endl;
}

void Game::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }
}

// ������� ������� ����
void Game::Run() {
    Initialize();
    LoadContent();

    const int TARGET_FPS = 60; // ������� ���������� ������ � �������
    const Uint32 TARGET_FRAME_TIME = 1000 / TARGET_FPS; // ����� ������ ����� � �������������

    Uint32 lastTime = SDL_GetTicks(); // ����� ����������� �����

    while (isRunning) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f; // ������� �� ������� ����� �������
        lastTime = currentTime;

        HandleEvents();

        // ���������� ������
        Update(deltaTime);

        // ��������� �����
        Draw();

        // ����������� FPS
        Uint32 frameTime = SDL_GetTicks() - currentTime;
        if (frameTime < TARGET_FRAME_TIME) {
            SDL_Delay(TARGET_FRAME_TIME - frameTime);
        }
    }

    UnloadContent();
}











// ��������� ������������
//CheckCollisions();
/*
// �������� ������������ ����� ���������
void Game::CheckCollisions() {
    for (size_t i = 0; i < ManagerGame::gameObjects.size(); ++i) {
        for (size_t j = i + 1; j < ManagerGame::gameObjects.size(); ++j) {
            if (ManagerGame::gameObjects[i]->CheckCollision(*ManagerGame::gameObjects[j])) {
                std::cout << "Collision detected between objects!" << std::endl;
                ManagerGame::gameObjects[i]->OnTriggerEnter(ManagerGame::gameObjects[j]);
                ManagerGame::gameObjects[j]->OnTriggerEnter(ManagerGame::gameObjects[i]);
            }
        }
    }
}
*/