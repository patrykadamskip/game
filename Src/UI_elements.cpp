#include "UI_elements.hpp"
#include <iostream>

// START of Window class initialization

Window::Window()
{
    SDLWindow = nullptr;
    SDLWindow = SDL_CreateWindow(Constants::General::GAMENAME,
                                 0,
                                 20,
                                 Constants::General::MainWinWidth,
                                 Constants::General::MainWinHeight,
                                 SDL_WINDOW_ALLOW_HIGHDPI);
}

Window::~Window()
{
    SDL_DestroyWindow(SDLWindow);
}

void Window::Render()
{

    SDL_SetRenderDrawColor(SDL_GetRenderer(SDLWindow), 50, 50, 50, 255);
    SDL_RenderClear(SDL_GetRenderer(SDLWindow));
}

SDL_Surface *Window::GetSurface() const
{
    return SDL_GetWindowSurface(SDLWindow);
}

SDL_Window *Window::GetWindow() const { return SDLWindow; }

// END of Window class initialization

// START of PrimeButton class initialization

PrimeButton::PrimeButton(Buttontype type, int x, int y, int w, int h, SDL_Renderer *renderer, bool isActiveScene)
    : renderer(renderer), type(type), xPos(x), yPos(y), width(w), height(h), active_scene(isActiveScene), state(false)
{
}

PrimeButton::~PrimeButton()
{
    // Destructor implementation (if needed)
}

bool PrimeButton::GetState() const
{
    return state;
}

void PrimeButton::SetState()
{
    int *mouseX = new int;
    int *mouseY = new int;
    SDL_GetMouseState(mouseX, mouseY);
    if ((*mouseX > xPos) && (*mouseX < xPos + width) && (*mouseY > yPos) && (*mouseY < yPos + height))
    {
        state = true;
        delete mouseX;
        delete mouseY;
        return;
    }
    delete mouseX;
    delete mouseY;
    state = false;
    return;
}

void PrimeButton::SetActive(bool isActive)
{
    active_scene = isActive;
}

// END of PrimeButton class initialization

// START of Button class initialization

Button::Button(Buttontype type, int x, int y, int w, int h, const char *idlePath, const char *activePath, SDL_Renderer *renderer, bool isActiveScene)
    : PrimeButton(type, x, y, w, h, renderer, isActiveScene),
      ibutton_texture(nullptr), abutton_texture(nullptr)
{
    SDL_Surface *idleSurface = IMG_Load(idlePath);
    if (!idleSurface)
    {
        SDL_GetError();
        return;
    }
    ibutton_texture = SDL_CreateTextureFromSurface(renderer, idleSurface);
    SDL_FreeSurface(idleSurface);

    SDL_Surface *activeSurface = IMG_Load(activePath);
    if (!activeSurface)
    {
        SDL_GetError();
        return;
    }
    abutton_texture = SDL_CreateTextureFromSurface(renderer, activeSurface);
    SDL_FreeSurface(activeSurface);
}

Button::~Button()
{
    SDL_DestroyTexture(ibutton_texture);
    SDL_DestroyTexture(abutton_texture);
}

void Button::Render(SDL_Renderer *renderer)
{
    if (!active_scene)
    {
        state = false;
    }
    else
    {
        SetState();
    }

    SDL_Texture *currentTexture = state ? abutton_texture : ibutton_texture;

    SDL_Rect destRect = {xPos, yPos, width, height};

    SDL_RenderCopy(renderer, currentTexture, nullptr, &destRect);
}

void Button::Update()
{
    // Placeholder function for updating button
    return;
}

// END of Button class initialization

// START of TextInput class initialization

TextInput::TextInput(Buttontype type, int x, int y, int w, int h, SDL_Renderer *renderer, bool isActiveScene)
    : PrimeButton(type, x, y, w, h, renderer, isActiveScene),
      text(""), text_color({255, 255, 255, 255}), font(nullptr), text_texture(nullptr)
{
    // Initialize the font (make sure the path to the font file is correct)
    font = TTF_OpenFont(Constants::General::TEST_FONT_PATH, 24);
    if (!font)
    {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }
    UpdateTexture();
}

TextInput::~TextInput()
{
    if (text_texture)
    {
        SDL_DestroyTexture(text_texture);
    }
    TTF_CloseFont(font);
}

void TextInput::Update()
{
    // Implement the update logic here if needed
}

void TextInput::Render(SDL_Renderer *renderer)
{
    SDL_Rect rect = {xPos, yPos, width, height};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    if (text_texture)
    {
        int textWidth, textHeight;
        SDL_QueryTexture(text_texture, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect textRect = {xPos + 5, yPos + 5, textWidth, textHeight};
        SDL_RenderCopy(renderer, text_texture, NULL, &textRect);
    }
}

void TextInput::HandleEvent(SDL_Event *event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x >= xPos && x <= xPos + width && y >= yPos && y <= yPos + height)
        {
            state = true;
            SDL_StartTextInput();
        }
        else
        {
            state = false;
            SDL_StopTextInput();
        }
    }

    if ((event->type == SDL_TEXTINPUT) && state)
    {
        text += event->text.text;
        
        UpdateTexture();
    }
    else if ((event->type == SDL_KEYDOWN) && state)
    {
        if (event->key.keysym.sym == SDLK_BACKSPACE && !text.empty())
        {
            text.pop_back();
            UpdateTexture();
        }
    }

}

std::string TextInput::GetText() const
{
    return text;
}

void TextInput::SetText(const std::string &text)
{
    this->text = text;
    UpdateTexture();
}

void TextInput::UpdateTexture()
{

    if (text_texture)
    {
        SDL_DestroyTexture(text_texture);
        text_texture = nullptr;
    }

    if (!text.empty())
    {
        SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, text.c_str(), text_color);

        SDL_Log("UpdateTexture called with text: %s", text.c_str());
        if (textSurface)
        {
            text_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);
        }
    }
}

// END of TextInput class initialization
