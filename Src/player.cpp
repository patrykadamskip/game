#include "player.hpp"

using namespace Constants::PlayerMacro;

Player::Player(SDL_Renderer *renderer, const char *sprite_sheet_path) : player_renderer(renderer), movement_direction(MovementDirection::Idle), 
                                                                        player_speed(5), posX(200), posY(200), health(100),
                                                                        current_animation(SpriteSheetMacro::TEST_PLAYER_WALKING_ANIMATION),
                                                                        src_rect{SpriteSheetMacro::TEST_PLAYER_START_FRAME, current_animation, SpriteSheetMacro::TEST_PLAYER_SPRITE_WIDTH, SpriteSheetMacro::TEST_PLAYER_SPRITE_HEIGHT}, 
                                                                        player_sprite_sheet(renderer, SpriteSheetMacro::TEST_PLAYER_SPRITE_WIDTH, 
                                                                                          SpriteSheetMacro::TEST_PLAYER_SPRITE_HEIGHT, SpriteSheetMacro::TEST_PLAYER_SHEET_WIDTH,
                                                                                          SpriteSheetMacro::TEST_PLAYER_SHEET_HEIGHT,  sprite_sheet_path)
                                                                                          
{
    player_sprite_sheet.SetAnimationParameters(0, 10, 1);
}



void Player::Render()
{
    SDL_Rect dstRect = {posX, posY, SpriteSheetMacro::TEST_PLAYER_SPRITE_WIDTH, SpriteSheetMacro::TEST_PLAYER_SPRITE_HEIGHT};
    
    SDL_RenderCopy(player_renderer, player_sprite_sheet.GetSpriteSheet(), &src_rect, &dstRect);
    return;
}

void Player::Update()
{   

    player_sprite_sheet.Animate(&src_rect);

    switch(movement_direction)
    {
        case MovementDirection::Up:
            if((posY - player_speed) < 0)
                {
                    posY = 0;
                }
            else
                {
                    posY -= player_speed;
                }
            break;

        case MovementDirection::Down:
            if((posY + player_speed + player_sprite_sheet.GetFrameHeight()) > Constants::General::MainWinHeight)
                {
                    posY = Constants::General::MainWinHeight - player_sprite_sheet.GetFrameHeight();
                }
            else
                {
                    posY += player_speed;
                }
            break;

        case MovementDirection::Left:
            if((posX - player_speed) < 0)
                {
                    posX = 0;
                }
            else
                {
                    posX -= player_speed;
                }
            break;

        case MovementDirection::Right:
            if((posX + player_speed + player_sprite_sheet.GetFrameWidth()) > Constants::General::MainWinWidth)
                {
                    posX = Constants::General::MainWinWidth - player_sprite_sheet.GetFrameWidth();
                }
            else
                {
                    posX += player_speed;
                }
            break;
        
        case MovementDirection::UpLeft:
            if((posX - player_speed) < 0)
                {
                    posX = 0;
                }
            else
                {
                    posX -= player_speed;
                }

            if((posY - player_speed) < 0)
                {
                    posY = 0;
                }
            else
                {
                    posY -= player_speed;
                }
            
            break;

        case MovementDirection::UpRight:
            if((posY - player_speed) < 0)
                {
                    posY = 0;
                }
            else
                {
                    posY -= player_speed;
                }

            if((posX + player_speed + player_sprite_sheet.GetFrameWidth()) > Constants::General::MainWinWidth)
                {
                    posX = Constants::General::MainWinWidth - player_sprite_sheet.GetFrameWidth();
                }
            else
                {
                    posX += player_speed;
                }

            break;
        
        case MovementDirection::DownLeft:
            if((posY + player_speed + player_sprite_sheet.GetFrameHeight()) > Constants::General::MainWinHeight)
                {
                    posY = Constants::General::MainWinHeight - player_sprite_sheet.GetFrameHeight();
                }
            else
                {
                    posY += player_speed;
                }
            
            if((posX - player_speed) < 0)
                {
                    posX = 0;
                }
            else
                {
                    posX -= player_speed;
                }
            break;
        
        case MovementDirection::DownRight:
            if((posY + player_speed + player_sprite_sheet.GetFrameHeight()) > Constants::General::MainWinHeight)
                {
                    posY = Constants::General::MainWinHeight - player_sprite_sheet.GetFrameHeight();
                }
            else
                {
                    posY += player_speed;
                }
            
            if((posX + player_speed + player_sprite_sheet.GetFrameWidth()) > Constants::General::MainWinWidth)
                {
                    posX = Constants::General::MainWinWidth - player_sprite_sheet.GetFrameWidth();
                }
            else
                {
                    posX += player_speed;
                }
            break;


        
        case MovementDirection::Idle:
            break;
    }
    return;
}

void Player::SetDirection(MovementDirection direction)
{
    movement_direction = direction;
    return;
}