#include <SDL.h>
#include <SDL_image.h>


#ifndef __SPRITE_SHEET__
#define __SPRITE_SHEET__


// @brief class for spritesheet handling
class SpriteSheet
{
public:
    SpriteSheet();
    SpriteSheet(SDL_Renderer *param_renderer, int param_frame_width, int param_frame_height, int param_sprite_sheet_width, int param_sprite_sheet_height, const char *param_sprite_sheet_path);
    ~SpriteSheet(); 

    SDL_Texture *GetSpriteSheet() const;
    int GetFrameWidth() const;
    int GetFrameHeight() const;

    // @brief setting animation parameters (pass value < 0 to dont change counter speed or total frames)
    void SetAnimationParameters(int param_animation_counter, int param_counter_speed, int param_total_frames);

    void Animate(SDL_Rect *src_rect);

private:
    // renderer for sprite sheet
    SDL_Renderer *sheet_renderer;
    
    // each sprite animation frame dimensions (in px)
    int frame_width;
    int frame_height;

    // entire sprite sheet dimensions (how many frames are in colums and how many rows)
    int sprite_sheet_width;
    int sprite_sheet_height;

    // texture for spritesheet
    SDL_Texture *sprite_sheet_texture;
    
    // counter for changing next frame
    int animation_counter;

    // this value tells if counter should refresh and change frame
    int counter_speed;

    int total_frames;
    
};

#endif // __SPRITE_SHEET__