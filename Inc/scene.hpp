#include "UI_elements.hpp"
#include "player.hpp"
#include "entities.hpp"
#include "config.hpp"
#include <SDL.h>
#include <vector>

#ifndef __SCENE_HPP__
#define __SCENE_HPP__

//@brief Scene types in game
enum class SceneType
{
    MainMenu,
    Arena,
    Options,
    ArenaOptions
};

//@brief Scene abstraction class for making different scenes in game
class Scene
{
public:
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual ~Scene() {}
    SceneType GetType() const { return type; }
    Config *GetConfig() const { return config; }
    bool IsActive() const { return active; }
    void SetActive(bool isActive);
    void RenderButtons(std::vector<PrimeButton *> buttons, SDL_Renderer *renderer);
    void RenderBlur(SDL_Renderer *renderer, SDL_Texture *actual_background);
    Buttontype GetActiveButton() const;
    Scene *GetPrevScene() const;
    void SetPrevScene(Scene *scene);

protected:
    Scene(SceneType scenetype, Scene *prev_scene) : type(scenetype), prev_scene(prev_scene) {};
    SceneType type;
    Config *config;
    bool active;
    Scene *prev_scene;
    std::vector<PrimeButton *> buttons;
};

class MenuScene : public Scene
{
public:
    MenuScene(SDL_Renderer *renderer, bool isThisSceneActive);

    ~MenuScene();

    void Update();

    void Render();

private:
    SDL_Renderer *renderer;

    Button start_button;

    Button progress_button;

    Button options_button;

    Button exit_button;
};

class ArenaScene : public Scene
{
public:
    ArenaScene(SDL_Renderer *renderer, const char *background_texture);

    ~ArenaScene();

    void Update();

    //@brief rendering scene with player
    void Render();

    //@brief getter function for player member
    Player *GetPlayer();

private:
    SDL_Renderer *renderer;

    SDL_Texture *actual_background;

    Player player;
};

class OptionsSceneMenu : public Scene
{
public:
    OptionsSceneMenu(SDL_Renderer *renderer, const char *background_texture, Scene *parm_prev_scene, Config *config);

    ~OptionsSceneMenu();

    void Update();

    void Render();

    void HandleEvent(SDL_Event *event);

    void SetConfig(Config *config);

private:
    SDL_Renderer *renderer;

    SDL_Texture *actual_background;

    TextInput volume_input;
};

class ArenaOptionsScene : public Scene
{
public:
    ArenaOptionsScene(SDL_Renderer *renderer, const char *background_texture, Scene *prev_scene);

    ~ArenaOptionsScene();

    void Update();

    void Render();

    void HandleEvent(SDL_Event *event);

private:
    SDL_Renderer *renderer;

    SDL_Texture *actual_background;

    Button options_button;

    Button resume_button;

    Button save_button;

    Button exit_to_menu_button;
};

#endif //__SCENE_HPP__