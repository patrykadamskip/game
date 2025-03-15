#include "scene.hpp"

using namespace Constants;
// START of MenuScene inicialization

// menuscene inicialization list
MenuScene::MenuScene(SDL_Renderer *renderer, bool isActive)
    : Scene(SceneType::MainMenu, nullptr),

      renderer(renderer),

      start_button(Buttontype::Start, MenuMacro::UI::BUTTON_X_POSITION, MenuMacro::UI::START_BUTTON_Y_POSITION, MenuMacro::UI::BUTTON_WIDTH, MenuMacro::UI::BUTTON_HEIGHT, MenuMacro::Paths::START_BUTTON_IDLE_PATH, MenuMacro::Paths::START_BUTTON_ACTIVE_PATH, renderer, active),

      progress_button(Buttontype::Progress, MenuMacro::UI::BUTTON_X_POSITION, MenuMacro::UI::PROGRESS_BUTTON_Y_POSITION, MenuMacro::UI::BUTTON_WIDTH, MenuMacro::UI::BUTTON_HEIGHT, MenuMacro::Paths::PROGRESS_BUTTON_ACTIVE_PATH, MenuMacro::Paths::PROGRESS_BUTTON_ACTIVE_PATH, renderer, active),

      options_button(Buttontype::Options, MenuMacro::UI::BUTTON_X_POSITION, MenuMacro::UI::OPTIONS_BUTTON_Y_POSITION, MenuMacro::UI::BUTTON_WIDTH, MenuMacro::UI::BUTTON_HEIGHT, MenuMacro::Paths::OPTIONS_BUTTON_IDLE_PATH, MenuMacro::Paths::OPTIONS_BUTTON_ACTIVE_PATH, renderer, active),

      exit_button(Buttontype::Exit, MenuMacro::UI::BUTTON_X_POSITION, MenuMacro::UI::EXIT_BUTTON_Y_POSITION, MenuMacro::UI::BUTTON_WIDTH, MenuMacro::UI::BUTTON_HEIGHT, MenuMacro::Paths::EXIT_BUTTON_IDLE_PATH, MenuMacro::Paths::EXIT_BUTTON_ACTIVE_PATH, renderer, active)

{
    SetActive(isActive);
    // Add buttons to the array
    buttons.push_back(&start_button);
    buttons.push_back(&progress_button);
    buttons.push_back(&options_button);
    buttons.push_back(&exit_button);
}

// menu activation and disactivation sequence
void Scene::SetActive(bool isActive)
{
    active = isActive;
    for (auto button : buttons)
    {
        button->SetActive(isActive);
    }
}

void Scene::RenderBlur(SDL_Renderer *renderer, SDL_Texture *actual_background)
{
    // Render the translucent background
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128); // 50% opacity
    SDL_RenderFillRect(renderer, NULL);

    // Render the actual background with transparency
    SDL_SetTextureBlendMode(actual_background, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(actual_background, 128); // 50% opacity
    SDL_RenderCopy(renderer, actual_background, NULL, NULL);
    return;
}

void Scene::RenderButtons(std::vector<PrimeButton *> buttons, SDL_Renderer *renderer)
{
    for (auto button : buttons)
    {
        button->Render(renderer);
    }
}

MenuScene::~MenuScene() {}

void MenuScene::Update()
{
    // PLACEHOLDER FUNCTION FOR UPDATING SCENE
    return;
}

// menu rendering function
void MenuScene::Render()
{
    RenderButtons(buttons, renderer);
    return;
}

Buttontype Scene::GetActiveButton() const
{
    for (auto button : buttons)
    {
        if (button->GetState())
        {
            return button->GetType();
        }
    }
    return Buttontype::None;
}

// END of MenuScene inicialization

// START of ArenaScene inicialization

ArenaScene::ArenaScene(SDL_Renderer *renderer, const char *background_texture)
    : Scene(SceneType::Arena, nullptr),
      renderer(renderer),
      actual_background(nullptr),
      player(renderer, PlayerMacro::Paths::TEST_PLAYER_SPRITE_PATH)
{
    SDL_Surface *tempSurface = IMG_Load(background_texture);
    if (!tempSurface)
    {
        SDL_GetError();
        return;
    }

    actual_background = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    if (!actual_background)
    {
        SDL_GetError();
        return;
    }
}

ArenaScene::~ArenaScene()
{
    SDL_DestroyTexture(actual_background);
}

void ArenaScene::Update()
{
    // PLACEHOLDER FUNCTION FOR UPDATING SCENE
    return;
}

void ArenaScene::Render()
{
    SDL_RenderCopy(renderer, actual_background, NULL, NULL);
    player.Render();
    return;
}

Player *ArenaScene::GetPlayer()
{
    return &player;
}

// END of ArenaScene inicialization
// 23

OptionsSceneMenu::OptionsSceneMenu(SDL_Renderer *renderer, const char *background_texture, Scene *parm_prev_scene, Config *Config)
    : Scene(SceneType::Options, parm_prev_scene),
      renderer(renderer),
      actual_background(nullptr),
      volume_input(Buttontype::None, 100, 200, MenuMacro::UI::BUTTON_WIDTH, MenuMacro::UI::BUTTON_HEIGHT, renderer, true)

{
    SetActive(true);

    buttons.push_back(&volume_input); // ogarnac czy da sie miec to

    config = Config;

    SDL_Surface *tempSurface = IMG_Load(background_texture);
    if (!tempSurface)
    {
        SDL_GetError();
        return;
    }

    actual_background = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    if (!actual_background)
    {
        SDL_GetError();
        return;
    }
}

OptionsSceneMenu::~OptionsSceneMenu()
{
    SDL_DestroyTexture(actual_background);
}

void OptionsSceneMenu::Update()
{
    // PLACEHOLDER FUNCTION FOR UPDATING SCENE
    return;
}

void OptionsSceneMenu::Render()
{
    // Render the previous scene first
    if (prev_scene)
    {
        if (prev_scene->GetType() == SceneType::Arena)
            dynamic_cast<ArenaScene *>(prev_scene)->Render();
        else if (prev_scene->GetType() == SceneType::MainMenu)
            dynamic_cast<MenuScene *>(prev_scene)->Render();
    }

    // For now this is useless

    // // Render the translucent background
    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128); // 50% opacity
    // SDL_RenderFillRect(renderer, NULL);

    // // Render the actual background with transparency
    // SDL_SetTextureBlendMode(actual_background, SDL_BLENDMODE_BLEND);
    // SDL_SetTextureAlphaMod(actual_background, 128); // 50% opacity
    // SDL_RenderCopy(renderer, actual_background, NULL, NULL);

    // End of useless content

    RenderBlur(renderer, actual_background);

    if (prev_scene->GetType() == SceneType::Arena)
    {
    }

    // Render the text inputs
    volume_input.Render(renderer);

    return;
}

void OptionsSceneMenu::HandleEvent(SDL_Event *event)
{
    if ((event->type == SDL_MOUSEBUTTONDOWN) || (event->type == SDL_TEXTINPUT) || (event->type == SDL_KEYDOWN))
    {
        volume_input.HandleEvent(event); // Pass event to TextInput object
    }
}

void OptionsSceneMenu::SetConfig(Config *Config)
{
    config = Config;
}

ArenaOptionsScene::ArenaOptionsScene(SDL_Renderer *renderer, const char *background_texture, Scene *prev_scene)
    : Scene(SceneType::ArenaOptions, prev_scene),
      renderer(renderer),
      actual_background(nullptr),
      options_button(Buttontype::Options, 100, 100, 200, 50, MenuMacro::Paths::OPTIONS_BUTTON_IDLE_PATH, MenuMacro::Paths::OPTIONS_BUTTON_ACTIVE_PATH, renderer, true),
      resume_button(Buttontype::Resume, 100, 200, 200, 50, MenuMacro::Paths::OPTIONS_BUTTON_IDLE_PATH, MenuMacro::Paths::OPTIONS_BUTTON_ACTIVE_PATH, renderer, true),
      save_button(Buttontype::Save, 100, 300, 200, 50, "path_to_idle_texture", "path_to_active_texture", renderer, true),
      exit_to_menu_button(Buttontype::Exit, 100, 400, 200, 50, MenuMacro::Paths::OPTIONS_BUTTON_IDLE_PATH, MenuMacro::Paths::OPTIONS_BUTTON_ACTIVE_PATH, renderer, true)
{
    SetActive(true);

    buttons.push_back(&options_button);
    buttons.push_back(&resume_button);
    buttons.push_back(&save_button);
    buttons.push_back(&exit_to_menu_button);

    SDL_Surface *tempSurface = IMG_Load(background_texture);
    if (!tempSurface)
    {
        std::cerr << "IMG_Load Error: " << SDL_GetError() << std::endl; // Log the error
        return;
    }

    actual_background = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    if (!actual_background)
    {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl; // Log the error
        return;
    }
}

ArenaOptionsScene::~ArenaOptionsScene()
{
    SDL_DestroyTexture(actual_background);
}

void ::ArenaOptionsScene::Render()
{
    // Render the previous scene first
    if (prev_scene)
    {
        if (prev_scene->GetType() == SceneType::Arena)
            dynamic_cast<ArenaScene *>(prev_scene)->Render();
        else if (prev_scene->GetType() == SceneType::MainMenu)
            dynamic_cast<MenuScene *>(prev_scene)->Render();
    }

    RenderBlur(renderer, actual_background);

    RenderButtons(buttons, renderer);

    return;
}

void ArenaOptionsScene::Update()
{
    // PLACEHOLDER FUNCTION FOR UPDATING SCENE
    return;
}

void ArenaOptionsScene::HandleEvent(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE)
    {
        if (prev_scene->GetType() == SceneType::Arena)
            dynamic_cast<ArenaScene *>(prev_scene)->SetActive(true);
    }
}

Scene *Scene::GetPrevScene() const
{
    return prev_scene;
}

void Scene::SetPrevScene(Scene *scene)
{
    prev_scene = scene;
}