#include "entities.hpp"

void Entity::Render(const int sprite_width, const int sprite_height)
{
    SDL_Rect dst_rect = {posX, posY, sprite_width, sprite_height};
    
    SDL_RenderCopy(entity_renderer, entity_sprite_sheet.GetSpriteSheet(), &src_rect, &dst_rect);
    return;
}

void Entity::SetDirection(MovementDirection direction)
{
    entity_movement_direction = direction;
    return;
}