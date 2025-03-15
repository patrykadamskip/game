#include "SpriteSheet.hpp"

SpriteSheet::SpriteSheet()
    : sheet_renderer(nullptr),
      frame_width(0),
      frame_height(0),
      sprite_sheet_width(0),
      sprite_sheet_height(0),
      sprite_sheet_texture(nullptr),
      animation_counter(0), counter_speed(0), total_frames(0)
{
}

SpriteSheet::SpriteSheet(SDL_Renderer *param_renderer, int param_frame_width, int param_frame_height, int param_sprite_sheet_width, int param_sprite_sheet_height, const char *param_sprite_sheet_path)
    : sheet_renderer(param_renderer),
      frame_width(param_frame_width),
      frame_height(param_frame_height),
      sprite_sheet_width(param_sprite_sheet_width),
      sprite_sheet_height(param_sprite_sheet_height),
      sprite_sheet_texture(nullptr),
      animation_counter(0), counter_speed(0), total_frames(0)
{
    SDL_Surface *sprite_sheet_surface = IMG_Load(param_sprite_sheet_path);

    if (!sprite_sheet_surface)
    {
        SDL_GetError();
        return;
    }

    sprite_sheet_texture = SDL_CreateTextureFromSurface(param_renderer, sprite_sheet_surface);
    SDL_FreeSurface(sprite_sheet_surface);

    if (!sprite_sheet_texture)
    {
        SDL_GetError();
        return;
    }
}

SpriteSheet::~SpriteSheet()
{
    SDL_DestroyTexture(sprite_sheet_texture);
}

SDL_Texture *SpriteSheet::GetSpriteSheet() const
{
    return sprite_sheet_texture;
}

int SpriteSheet::GetFrameWidth() const
{
    return frame_width;
}

int SpriteSheet::GetFrameHeight() const
{
    return frame_height;
}

void SpriteSheet::SetAnimationParameters(int param_animation_counter, int param_counter_speed, int param_total_frames)
{
    animation_counter = param_animation_counter;
    if (!(counter_speed < 0))
        counter_speed = param_counter_speed;
    if (!(total_frames < 0))
        total_frames = param_total_frames;
    return;
}

void SpriteSheet::Animate(SDL_Rect *srcRect)
{
    if (animation_counter < counter_speed)
    {
        animation_counter++;
    }
    else
    {

        if (srcRect->x < total_frames * frame_width)
        {
            srcRect->x += frame_width;
        }
        else
        {
            srcRect->x = 0;
        }

        animation_counter = 0;
    }
}