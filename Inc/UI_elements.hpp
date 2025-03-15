#include <SDL.h>
#include <SDL_image.h>
#include "MacroConst.hpp"
#include <SDL_ttf.h>
#include <string>

#ifndef __UIELEMENTS_HPP__
#define __UIELEMENTS_HPP__

class Window
{

public:
    //@brief default constructor for main window
    Window();

    //@brief destructor for window
    ~Window();

    void Render();
    SDL_Surface *GetSurface() const;
    SDL_Window *GetWindow() const;

private:
    SDL_Window *SDLWindow;
};

enum class Buttontype
{
    None,
    Start,
    Progress,
    Options,
    Exit,
    Resume,
    Save
};

class PrimeButton
{
public:
    virtual void Render(SDL_Renderer *renderer) = 0;
    virtual void Update() = 0;
    virtual ~PrimeButton();
    PrimeButton(Buttontype type, int x, int y, int w, int h, SDL_Renderer *renderer, bool isActiveScene);
    Buttontype GetType() const { return type; }
    bool GetState() const;
    void SetState();
    void SetActive(bool isActive);

protected:
    SDL_Renderer *renderer;
    Buttontype type;
    int xPos, yPos;
    int width, height;
    bool active_scene;
    bool state;
};

class Button : public PrimeButton
{

public:
    Button(Buttontype type, int x, int y, int w, int h, const char *idlePath, const char *activePath, SDL_Renderer *renderer, bool isActiveScene);

    ~Button();

    void Render(SDL_Renderer *renderer) override;

    void Update() override;

    void EventHandler(SDL_Event *event);

private:
    //@brief idle state button image
    SDL_Texture *ibutton_texture;

    //@brief active state button image
    SDL_Texture *abutton_texture;
};

class TextInput : public PrimeButton
{
public:
    TextInput(Buttontype type, int x, int y, int w, int h, SDL_Renderer *renderer, bool isActiveScene);

    ~TextInput();

    void Render(SDL_Renderer *renderer) override;

    void Update() override;

    void HandleEvent(SDL_Event *event);

    std::string GetText() const;

    void SetText(const std::string &text);

private:
    std::string text;

    SDL_Color text_color;

    TTF_Font *font;

    SDL_Texture *text_texture;

    void UpdateTexture();
};

#endif //__UIELEMENTS_HPP__