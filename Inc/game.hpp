#include "scene.hpp"
#include <SDL.h>
#include <iostream>
#include <map>

#ifndef __GAME_HPP__
#define __GAME_HPP__

//@brief class of game instance
class Game
{

public:
    //@brief constructor of game instance
    Game();

    //@brief destructor of game instance
    ~Game();

    //@brief initializing game
    void Init();

    //@brief handling new input from user
    //@param event new event
    void EventHandler(SDL_Event *event);

    //@brief additional function for menu event handling
    //@param event current event
    void HandleMenuSceneEvent(SDL_Event *event);

    //@brief help function for HandleMenuSceneEvent to increase readability
    //@param active_button the button which is behind user's cursor
    void HandleMenuButtonClick(Buttontype active_button);

    //@brief additional function for arena event handling
    //@param event current event
    void HandleArenaSceneEvent(SDL_Event *event);

    //@brief updating game in new frame
    void Update();

    //@brief rendering new frame
    void Render();

    //@brief changing actual_scene type
    void ChangeScene(SceneType newSceneType);

    //@brief setter for state of the game
    //@param state new state of the game false if the game is off and true if on
    void SetState(bool state);

    //@brief sets pressed keys to true
    void SetActiveKeys(SDL_Event *event);

    //@brief getter for getting state of the game
    //@retval returns state of the game
    bool GetState() const;

    //@brief additional function for options event handling
    //@param event current event
    void HandleOptionsSceneEvent(SDL_Event *event);

    void ReturnToArena(ArenaScene *prev_scene);

    void HandleArenaOptionsSceneEvent(SDL_Event *event);

    void HandleArenaOptionsButtonClick(Buttontype active_button);

    //@brief getter for event variable declared in private section
    SDL_Event &GetEvent();

private:
    //@brief flag for main game loop
    bool running;

    //@brief application main window
    Window main_window;

    //@brief main renderer for scenes
    SDL_Renderer *scene_renderer;

    //@brief scene that is running at the moment
    Scene *actual_scene;

    Scene *blurred_scene;

    //@brief event in game
    SDL_Event event;

    //@brief variable for saving entry time of a frame
    Uint32 frame_start;

    //@brief variable for checking duration of a frame
    Uint32 frame_end;

    //@brief clock for measuring wave length
    Uint16 timer;

    //@brief map for key states mapping
    std::map<SDL_Keycode, bool> key_states;

    Config config;
};

#endif //__GAME_HPP__