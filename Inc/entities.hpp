#include "SpriteSheet.hpp"
#include "MacroConst.hpp"
#include <SDL.h>

#ifndef __ENTITIES_HPP__
#define __ENTITIES_HPP__

//@brief Entity types in game
enum class EntityType
{
    Reaper,
};

class Entity
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

    //@brief function for determining next entity position
    virtual void CalculateNextPosition(int playerX, int playerY) = 0;

    //@brief updating entity HP position etc.
    virtual void Update() = 0;

    //@brief drawing entity on screen
    void Render(const int sprite_width, const int sprite_height);

    //@brief setter for movement_direction member
    void SetDirection(MovementDirection direction);

protected:
    Entity(EntityType etype) : type(etype) {};

    // renderer for drawing entity sprite
    SDL_Renderer *entity_renderer;

    // type of entity
    EntityType type;

    // direction of entity movement
    MovementDirection entity_movement_direction;

    int entity_speed;

    // position x and y of the entity according to left top corner of the screen
    int posX;
    int posY;

    // entity health
    int entity_health;

    // row in spritesheet of current animation of player
    int current_animation;

    // rectangle for copying frame from spritesheet
    SDL_Rect src_rect;

    // entity spritesheet
    SpriteSheet entity_sprite_sheet;
};

#endif //__ENTITIES_HPP__