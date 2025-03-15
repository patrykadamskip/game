#include "SpriteSheet.hpp"
#include "MacroConst.hpp"
#include <SDL.h>

#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

class Player
{
public:
    enum class MovementDirection
    {
        Up,
        Down,
        Left,
        Right,
        UpLeft,
        UpRight,
        DownLeft,
        DownRight,
        Idle
    };

    Player(SDL_Renderer *renderer, const char *sprite_sheet_path);

    //@brief drawing player on screen
    void Render();
    //@brief updating player HP position etc.
    void Update();

    //@brief setter for movement_direction member
    void SetDirection(MovementDirection direction);

private:
    // renderer for drawing player sprite
    SDL_Renderer *player_renderer;

    // direction of player movement
    MovementDirection movement_direction;

    int player_speed;

    // position x and y of the player according to left top corner of the screen
    int posX;
    int posY;

    // player health
    int health;

    // row in spritesheet of current animation of player
    int current_animation;

    // rectangle for copying frame from spritesheet
    SDL_Rect src_rect;

    // player spritesheet
    SpriteSheet player_sprite_sheet;
};

#endif //__PLAYER_HPP__