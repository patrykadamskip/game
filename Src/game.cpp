#include "game.hpp"
#include <memory>

Game::Game()
    : running(true),
      scene_renderer(nullptr),
      actual_scene(nullptr),
      config("Config") // Provide necessary arguments for Config constructor
{
}

Game::~Game()
{
    if (scene_renderer)
        SDL_DestroyRenderer(scene_renderer);

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

void Game::Init()
{
    // SDL2 inicialization
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL initialization error: " << SDL_GetError() << std::endl;
        return;
    }

    // SDL2_image inicialization
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        std::cerr << "SDL_image initialization error: " << IMG_GetError() << std::endl;
        return;
    }

    // SDL2_ttf inicialization
    if (TTF_Init() != 0)
    {
        std::cerr << "SDL_ttf initialization error: " << TTF_GetError() << std::endl;
        return;
    }
    scene_renderer = SDL_CreateRenderer(main_window.GetWindow(), -1, SDL_RENDERER_ACCELERATED);
    if (!scene_renderer)
    {
        std::cerr << "Renderer initialization failed: " << SDL_GetError() << std::endl;
        return;
    }
    actual_scene = new MenuScene(scene_renderer, true);
    timer = 0;

    return;
}

void Game::EventHandler(SDL_Event *event)
{
    // START measuring frame duration
    frame_start = SDL_GetTicks();

    while (SDL_PollEvent(event))
    {
        SetActiveKeys(event);
        if (event->type == SDL_QUIT)
        {
            SetState(false);
        }
        // Checking actual_scene type
        switch (actual_scene->GetType())
        {
        // START OF MENU SCENE CASE
        case SceneType::MainMenu:
            HandleMenuSceneEvent(event);
            break;
        // END OF MENU SCENE CASE
        // START OF ARENA SCENE CASE
        case SceneType::Arena:
            HandleArenaSceneEvent(event);
            break;
            // END OF ARENA SCENE CASE
        case SceneType::Options:
            HandleOptionsSceneEvent(event);
            break;
        case SceneType::ArenaOptions:
            HandleArenaOptionsSceneEvent(event);
            break;
        }
    }
    return;
}

void Game::HandleMenuSceneEvent(SDL_Event *event)
{

    MenuScene *menu_scene = dynamic_cast<MenuScene *>(actual_scene);
    if (!menu_scene)
        return;

    auto active_button = menu_scene->GetActiveButton();

    if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        HandleMenuButtonClick(active_button);
    }
}

void Game::HandleArenaSceneEvent(SDL_Event *event)
{

    ArenaScene *arena_scene = dynamic_cast<ArenaScene *>(actual_scene);
    if (!arena_scene)
        return;

    if (event->type == SDL_KEYDOWN && key_states[SDLK_ESCAPE])
    {
        ChangeScene(SceneType::ArenaOptions);
        return;
    }

    Player::MovementDirection direction = Player::MovementDirection::Idle;

    if (key_states[SDLK_w] && key_states[SDLK_a])
        direction = Player::MovementDirection::UpLeft;
    else if (key_states[SDLK_w] && key_states[SDLK_d])
        direction = Player::MovementDirection::UpRight;
    else if (key_states[SDLK_s] && key_states[SDLK_a])
        direction = Player::MovementDirection::DownLeft;
    else if (key_states[SDLK_s] && key_states[SDLK_d])
        direction = Player::MovementDirection::DownRight;
    else if (key_states[SDLK_w])
        direction = Player::MovementDirection::Up;
    else if (key_states[SDLK_s])
        direction = Player::MovementDirection::Down;
    else if (key_states[SDLK_a])
        direction = Player::MovementDirection::Left;
    else if (key_states[SDLK_d])
        direction = Player::MovementDirection::Right;

    arena_scene->GetPlayer()->SetDirection(direction);

    return;
}

void Game::HandleOptionsSceneEvent(SDL_Event *event)
{
    OptionsSceneMenu *options_scene = dynamic_cast<OptionsSceneMenu *>(actual_scene);

    if (!options_scene)
        return;

    // Check if the escape key was pressed
    if (event->type == SDL_KEYDOWN && key_states[SDLK_ESCAPE])
    {
        if (options_scene->GetPrevScene()->GetType() == SceneType::Arena)
            ReturnToArena(dynamic_cast<ArenaScene *>(options_scene->GetPrevScene()));
        else
            ChangeScene(options_scene->GetPrevScene()->GetType());
    }

    options_scene->HandleEvent(event);
}

void Game::HandleArenaOptionsSceneEvent(SDL_Event *event)
{
    ArenaOptionsScene *arena_options_scene = dynamic_cast<ArenaOptionsScene *>(actual_scene);

    if (!arena_options_scene)
        return;

    if (event->type == SDL_KEYDOWN && key_states[SDLK_ESCAPE])
    {
        if (arena_options_scene->GetPrevScene()->GetType() == SceneType::Arena)
            ReturnToArena(dynamic_cast<ArenaScene *>(arena_options_scene->GetPrevScene()));
    }
    if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        HandleArenaOptionsButtonClick(arena_options_scene->GetActiveButton());
    }

    return;
}

void Game::ReturnToArena(ArenaScene *prev_scene)
{
    if (prev_scene)
    {
        delete actual_scene;
        actual_scene = nullptr; // Set to nullptr after deletion
        prev_scene->SetActive(true);
        actual_scene = prev_scene;
    }
    else
    {
        std::cerr << "Error: prev_scene is nullptr!" << std::endl;
    }
    return;
}

void Game::HandleArenaOptionsButtonClick(Buttontype active_button)
{
    switch (active_button)
    {
    case Buttontype::Resume:
        ChangeScene(SceneType::Arena);
        break;
    case Buttontype::Save:
        break;
    case Buttontype::Exit:
        ChangeScene(SceneType::MainMenu);
        break;
    case Buttontype::Options:
        ChangeScene(SceneType::Options);
        break;
    default:
        break;
    }
}

void Game::HandleMenuButtonClick(Buttontype active_button)
{
    switch (active_button)
    {
    case Buttontype::Start:
        ChangeScene(SceneType::Arena);
        break;

    case Buttontype::Progress:

        break;

    case Buttontype::Options:
        ChangeScene(SceneType::Options);
        break;

    case Buttontype::Exit:
        SetState(false);
        break;

    default:
        break;
    }
}

void Game::ChangeScene(SceneType newSceneType)
{
    Scene *newScene = nullptr;
    switch (newSceneType)
    {
    case SceneType::MainMenu:
        newScene = new MenuScene(scene_renderer, true);
        break;
    case SceneType::Arena:
        newScene = new ArenaScene(scene_renderer, Constants::ArenaMacro::Paths::TEST_BACKGROUND_PATH);
        break;
    case SceneType::Options:
        newScene = new OptionsSceneMenu(scene_renderer, Constants::OptionsMenuMacro::Paths::TEST_BACKGROUND_PATH_OPTIONS, actual_scene, &config);
        break;
    case SceneType::ArenaOptions:
        newScene = new ArenaOptionsScene(scene_renderer, Constants::OptionsMenuMacro::Paths::TEST_BACKGROUND_PATH_OPTIONS, actual_scene);
        break;
    }
    if (newScene)
    {
        if (newScene->GetType() == SceneType::Options || newScene->GetType() == SceneType::ArenaOptions)
        {
            blurred_scene = actual_scene;
            if (actual_scene->GetPrevScene())
            {
                newScene->SetPrevScene(actual_scene->GetPrevScene());
                blurred_scene = actual_scene->GetPrevScene();
            }
            actual_scene->SetActive(false);
            actual_scene = newScene;
        }
        else
        {
            delete actual_scene;
            actual_scene = newScene;
        }
        actual_scene->SetActive(true);
    }
    else
    {
        std::cerr << "Failed to create the new scene!" << std::endl;
    }
}

void Game::Update()
{

    // PLACEHOLDER FUNCTION FOR UPDATING GAME OBJECTS VARIABLES etc.

    switch (actual_scene->GetType())
    {
    case SceneType::Arena:

        ArenaScene *arena_scene = dynamic_cast<ArenaScene *>(actual_scene);
        if (!arena_scene)
            return;

        arena_scene->GetPlayer()->Update();

        break;
    }

    return;
}

void Game::Render()
{
    // JUST PLACEHOLDER BACKGROUND FOR MENUSCENE
    // MAKE SOME SENSIBLE BACKGROUND FOR MENU AND DELETE THIS
    SDL_SetRenderDrawColor(scene_renderer, 0, 0, 0, 255);
    SDL_RenderClear(scene_renderer);
    //********************* */

    main_window.Render();
    actual_scene->Render();

    SDL_RenderPresent(scene_renderer);

    // END of measuring frame duration
    //& restricting fps to __FRAME_RATE if necessary
    frame_end = SDL_GetTicks() - frame_start;
    if (frame_end < Constants::General::FRAME_RATE)
    {
        SDL_Delay(Constants::General::FRAME_RATE - frame_end);
    }

    return;
}

void Game::SetState(bool state)
{
    running = state;
    return;
}

void Game::SetActiveKeys(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
        key_states[event->key.keysym.sym] = true;
        break;
    case SDL_KEYUP:
        key_states[event->key.keysym.sym] = false;
        break;
    }
}

bool Game::GetState() const
{
    return running;
}

SDL_Event &Game::GetEvent()
{
    return event;
}
