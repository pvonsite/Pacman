#include "Menu.h"
#include <stdio.h>

Menu::Menu(const int baseScrPosX, const int baseScrPosY, const int totalButton, const int buttonWidth, const int buttonHeight) {
    menuTexture  = nullptr;
    for (int i = 0; i < 3; ++i)
        howToPlayTexture[i] = nullptr;
    highScoreTexture = nullptr;
    arrowTexture = nullptr;
    scoreText = nullptr;
    arrowHSPos = 0;
    TOTAL_BUTTON = totalButton;
    MENU_BUTTON_WIDTH  = buttonWidth;
    MENU_BUTTON_HEIGHT = buttonHeight;
    this->baseScrPosX  = baseScrPosX;
    this->baseScrPosY  = baseScrPosY;
}

Menu::~Menu() {
    Mix_FreeChunk(navigationSound);
    Mix_FreeChunk(selectionSound);

    SDL_DestroyTexture(menuTexture);
    menuTexture = nullptr;
    for (int i = 0; i < 3; ++i) {
        SDL_DestroyTexture(howToPlayTexture[i]);
        howToPlayTexture[i] = nullptr;
    }
    SDL_DestroyTexture(highScoreTexture);
    highScoreTexture = nullptr;
    SDL_DestroyTexture(arrowTexture);
    arrowTexture = nullptr;

    for (Button* button : menuButton) {
        delete button; button = nullptr;
    }
    menuButton.clear();
}

SDL_Texture* Menu::loadImage(SDL_Renderer* &renderer, const std::string imgPath) {
    SDL_Surface* Image = IMG_Load(imgPath.c_str());
    SDL_Texture* loadTexture = SDL_CreateTextureFromSurface(renderer, Image);
    SDL_FreeSurface(Image);
    return loadTexture;
}

void Menu::init(SDL_Renderer* &renderer, const std::string imgPath, std::vector<std::string>& buttonText) {
    SDL_Surface* Image = IMG_Load(imgPath.c_str());
    if (Image == nullptr)
        console->Status( IMG_GetError() );
    else {
        menuTexture = SDL_CreateTextureFromSurface(renderer, Image);
        SDL_FreeSurface(Image);
        howToPlayTexture[0] = loadImage(renderer, "Source/Assets/Menu Image/How to Play1.png");
        howToPlayTexture[1] = loadImage(renderer, "Source/Assets/Menu Image/How to Play2.png");
        howToPlayTexture[2] = loadImage(renderer, "Source/Assets/Menu Image/How to Play3.png");
        Image = IMG_Load("Source/Assets/Menu Image/High Scores.png");
        highScoreTexture = loadImage(renderer, "Source/Assets/Menu Image/High Scores.png");
        arrowTexture = loadImage(renderer, "Source/Assets/Menu Image/arrow-upanddown.png");

        scoreText = new TextManager(28);

        for (int i = 0; i < TOTAL_BUTTON; ++i)
            menuButton.push_back(new Button(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, baseScrPosX - MENU_BUTTON_WIDTH / 2, baseScrPosY + (5 + MENU_BUTTON_HEIGHT) * (i - 1)));

        for (int i = 0; i < TOTAL_BUTTON; ++i) {
            if (buttonText[i] == "Sound: ON") {
                if (Mix_Volume(-1, -1) == 0) buttonText[i] = "Sound: OFF";
            }
            menuButton[i]->loadButton(renderer, buttonText[i]);
            menuButton[i]->setStatus(Button::BUTTON_OUT);
        }
        menuButton[0]->setStatus(Button::BUTTON_IN);
        currentButtonID = 0;
        currentMenuStatus = RUNNING;
    }
}


void Menu::render(SDL_Renderer* &renderer, const std::vector<std::string> &scoreData) {
    if (currentMenuStatus == HOW_TO_PLAY) {
        SDL_RenderCopy(renderer, howToPlayTexture[currentHTPid], nullptr, nullptr);
    }
    else if (currentMenuStatus == HIGH_SCORES) {
        SDL_RenderCopy(renderer, highScoreTexture, nullptr, nullptr);
        SDL_Rect srcUP = {0, 0, 431, 400}, srcDOWN = {431, 0, 431, 400};
        SDL_Rect dstUP = {441 - 41, 85, 80, 80}, dstDOWN = {441 - 34, 385, 80, 80};
        static bool alphaUP = true;
        if (alphaUP) alphaMod += 2;
        else alphaMod -= 2;
        if (alphaMod > 255) alphaUP = false, alphaMod = 254;
        else if (alphaMod < 1) alphaUP = true, alphaMod = 0;
        SDL_SetTextureAlphaMod(arrowTexture, alphaMod);
        SDL_RenderCopy(renderer, arrowTexture, &srcUP, &dstUP);
        SDL_RenderCopy(renderer, arrowTexture, &srcDOWN, &dstDOWN);
        for (int i = arrowHSPos; i < arrowHSPos + 7; ++i) {
            scoreText->loadRenderText(renderer, scoreData[i], {0, 0, 0, 255});
            scoreText->renderText(renderer, 441, 160 + 40 * (i - arrowHSPos), TextManager::CENTER);
        }
    }
    else {
        SDL_RenderCopy(renderer, menuTexture, nullptr, nullptr);
        for (int i = 0; i < TOTAL_BUTTON; ++i)
            menuButton[i]->renderButton(renderer);
    }
}

void Menu::handleEvent(SDL_Event &e, SDL_Renderer* &renderer) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s) {
            Mix_PlayChannel(7, navigationSound, 0);
            if (currentMenuStatus == HIGH_SCORES) {
                if (arrowHSPos < 3) ++arrowHSPos;
            }
            else {
                menuButton[currentButtonID]->setStatus(Button::BUTTON_OUT);
                (currentButtonID += 1) %= TOTAL_BUTTON;
                menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
            }
        }
        else if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w) {
            Mix_PlayChannel(7, navigationSound, 0);
            if (currentMenuStatus == HIGH_SCORES) {
                if (arrowHSPos > 0) --arrowHSPos;
            }
            else {
                menuButton[currentButtonID]->setStatus(Button::BUTTON_OUT);
                (currentButtonID += TOTAL_BUTTON - 1) %= TOTAL_BUTTON;
                menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
            }
        }
        else if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a) {
            Mix_PlayChannel(7, navigationSound, 0);
            if (currentMenuStatus == HOW_TO_PLAY) {
                if (currentHTPid > 0) --currentHTPid;
            }
        }
        else if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d) {
            Mix_PlayChannel(7, navigationSound, 0);
            if (currentMenuStatus == HOW_TO_PLAY) {
                if (currentHTPid < 2) ++currentHTPid;
            }
        }
        else if (e.key.keysym.sym == SDLK_RETURN) {
            Mix_PlayChannel(7, navigationSound, 0);
            if (currentMenuStatus == HOW_TO_PLAY) {
                menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
                currentMenuStatus = RUNNING;
            }
            else if (currentMenuStatus == HIGH_SCORES) {
                menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
                currentMenuStatus = RUNNING;
            }
            else {
                menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
                std::string menuText = menuButton[currentButtonID]->getText();
                if (menuText == "New Game") currentMenuStatus = PLAY_BUTTON_PRESSED;
                else if (menuText == "Resume") currentMenuStatus = RESUME;
                else if (menuText == "Exit") currentMenuStatus = EXIT_BUTTON_PRESSED;
                else if (menuText == "Exit to Start Menu") currentMenuStatus = EXIT_BUTTON_PRESSED;
                else if (menuText == "Sound: ON") {
                    menuButton[currentButtonID]->changeSoundButton(renderer);
                    Mix_Volume(-1, 0);
                }
                else if (menuText == "Sound: OFF") {
                    menuButton[currentButtonID]->changeSoundButton(renderer),
                    Mix_Volume(-1, MIX_MAX_VOLUME);
                }
                else if (menuText == "How to Play") {
                    currentMenuStatus = HOW_TO_PLAY;
                    currentHTPid = 0;
                }
                else if (menuText == "High Scores") {
                    currentMenuStatus = HIGH_SCORES;
                    arrowHSPos = 0;
                }
            }
        }
    }
}

bool Menu::isRunning() const {
    return currentMenuStatus == RUNNING;
}

int Menu::getStatus() const {
    return currentMenuStatus;
}

void Menu::reOpen() {
    currentMenuStatus = RUNNING;
    menuButton[currentButtonID]->setStatus(Button::BUTTON_IN);
}

void Menu::changeRunStatus() {
    running = !running;
}
