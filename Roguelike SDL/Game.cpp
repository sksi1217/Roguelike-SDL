// Game.cpp

#include "Game.h"
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Player* _player;
EnemySkelet* _skelet;
Camera camera = { {800, 600}, 5 };

// Designer
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

// Destructor
Game::~Game() {
	for (auto obj : ManagerGame::gameObjects) {
		delete obj; // Remove all objects from the list
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}


// Initialization
void Game::Initialize() {
	std::cout << "Game initialized!" << std::endl;
}

// Resource Loading
void Game::LoadContent() {
	std::cout << "Loading content..." << std::endl;


	// Loading player texture
	SDL_Texture* playerTexture = Help::LoadTexture(renderer, "Textures/Models/player1.bmp");
	_player = new Player(playerTexture, { 0, 10 });
	ManagerGame::gameObjects.push_back(_player); // Adding a player to the object list

	// Loading player texture
	// SDL_Texture* playeTexture = Help::LoadTexture(renderer, "Textures/Models/player1.bmp");
	_skelet = new EnemySkelet(playerTexture, { 60, 0 });
	ManagerGame::gameObjects.push_back(_skelet);
	ManagerGame::enemies.push_back(_skelet);

	// Creating other objects
	SDL_Texture* boxTexture = Help::LoadTexture(renderer, "Textures/Models/box.bmp");
	GameObject* box1 = new GameObject();
	box1->Position = { -16, 20 };
	box1->Scale = 1;
	box1->WidthColliderX = 16;
	box1->HeightColliderY = 16;
	box1->Texture = boxTexture;
	box1->IsStatic = true;
	ManagerGame::gameObjects.push_back(box1);


	GameObject* box2 = new GameObject();
	box2->Position = { 0, 20 };
	box2->Scale = 1;
	box2->WidthColliderX = 16;
	box2->HeightColliderY = 16;
	box2->Texture = boxTexture;
	box2->IsStatic = true;
	ManagerGame::gameObjects.push_back(box2);
}

// Logic Update
void Game::Update(float deltaTime) {

	// Список объектов для удаления
	std::vector<GameObject*> objectsToRemove;
	objectsToRemove.clear();

	_skelet->UpdatePosPlr(_player->Position); // Обновляем позицию игрока для скелета
	for (auto obj : ManagerGame::gameObjects) {
		obj->Update(deltaTime); // Обновляем каждый объект
		if (!obj->IsActive)
		{
			objectsToRemove.push_back(obj); // Отложено добавляем объекты для удаления
		}
	}

	// Удаление объектов после завершения итерации
	for (auto objRemove : objectsToRemove)
	{
		ManagerGame::gameObjects.pop_back();
	}

	camera.UpdateCamera(_player->Position, deltaTime);
}

// Frame rendering
void Game::Draw() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Drawing of all objects
	for (auto obj : ManagerGame::gameObjects) {
		obj->Draw(renderer, camera);
	}

	SDL_RenderPresent(renderer);
}

// Выгрузка ресурсов
void Game::UnloadContent() {
	std::cout << "Unloading content..." << std::endl;
}

// Game.cpp
void Game::HandleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_x:
				camera.ZoomIn();
				break;
			case SDLK_c:
				camera.ZoomOut();
				break;
			}
		}
	}
}

void Game::Run() {
	Initialize();
	LoadContent();

	const int TARGET_FPS = 60;
	const Uint32 TARGET_FRAME_TIME = 1000 / TARGET_FPS; // Time of one frame in milliseconds

	Uint32 lastTime = SDL_GetTicks(); // Time of previous frame

	while (isRunning) {
		Uint32 currentTime = SDL_GetTicks();
		float deltaTime = (currentTime - lastTime) / 1000.0f; // Time difference between frames
		lastTime = currentTime;

		HandleEvents();

		// Logic Update
		Update(deltaTime);

		Draw();

		// Restriction FPS
		Uint32 frameTime = SDL_GetTicks() - currentTime;
		if (frameTime < TARGET_FRAME_TIME) {
			SDL_Delay(TARGET_FRAME_TIME - frameTime);
		}
	}

	UnloadContent();
}