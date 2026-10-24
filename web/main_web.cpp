// Browser entry point: replaces main.cpp (Windows console loop).
// The page calls game_start() once, game_key() on key presses
// and game_tick() every 200 ms, the same pace as Sleep(200) in main.cpp.
#include "../project_02.10.2025.h"
#include "../layout.h"

#define EXPORT(name) extern "C" __attribute__((export_name(name)))

static Game* game = nullptr;
static int dir = -1;

EXPORT("game_start") void game_start() {
    web_console_init();
    dir = -1;
    game = new Game(19, 36, Position(17, 11));
    PlaySoundA("Pac-Man-intro-music.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    game->LoadLayout(layout);
    game->DrawMap();
    game->DrawHero();
    game->ShowCoins();
}

EXPORT("game_key") void game_key(int key) {
    dir = key; // Key::LEFT / RIGHT / UP / DOWN codes
}

EXPORT("game_tick") void game_tick() {
    if (!game) return;
    switch (dir) {
    case (int)Key::LEFT:  game->MoveHero(Key::LEFT); break;
    case (int)Key::RIGHT: game->MoveHero(Key::RIGHT); break;
    case (int)Key::UP:    game->MoveHero(Key::UP); break;
    case (int)Key::DOWN:  game->MoveHero(Key::DOWN); break;
    }
    game->MoveEnemies();
}
