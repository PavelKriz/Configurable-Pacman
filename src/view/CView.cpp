//
// Created by pavel on 27.04.20.
//

#include "CView.h"


#define SCREEN_WIDTH   800
#define SCREEN_HEIGHT  800


void CView::initSDL() {
    // init sdl
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    // create window
    windowSize_.x_ = mapSize_.x_ * TILE_SIZE;
    windowSize_.y_ = mapSize_.y_ * TILE_SIZE + BOTTOM_BAR_SIZE;
    app_.window_ = SDL_CreateWindow(WINDOW_NAME_, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    windowSize_.x_, windowSize_.y_, windowFlags);

    if (!app_.window_) {
        printf("Failed to open %d x_ %d window: %s\n", mapSize_.x_, mapSize_.y_, SDL_GetError());
        exit(1);
    }

    // rnderer
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    app_.renderer_ = SDL_CreateRenderer(app_.window_, -1, rendererFlags);

    if (!app_.renderer_) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    // image library init
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void CView::prepareScene() {
    SDL_SetRenderDrawColor(app_.renderer_, 128, 128, 255, 255);
    SDL_RenderClear(app_.renderer_);
}

void CView::presentScene() {
    SDL_RenderPresent(app_.renderer_);
}

SDL_Texture *CView::loadTexture(const char *filename, SDL_Renderer *renderer) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if(texture == nullptr){
        throw invalid_argument("Loading texture: "s + filename + " has failed!");
    }
    return texture;
}

void CView::blit(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y) {
    float relativeTileSizeCoeficient = (float)TILE_SIZE / (float)STANDARD_TILE_SIZE;

    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);

    dest.w *= relativeTileSizeCoeficient;
    dest.h *= relativeTileSizeCoeficient;

    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}

void CView::sizedBlit(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h) {
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;

    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}

CView::CView(const SSize &mapSize) {
    mapSize_ = mapSize;
    memset(&app_, 0, sizeof(App));
    initSDL();
    objectDrawer.initialize(loadTexture, app_.renderer_);
}

CView::~CView() {
    SDL_DestroyRenderer(app_.renderer_);

    SDL_DestroyWindow(app_.window_);

    IMG_Quit();

    SDL_Quit();
}

void CView::draw() {
    prepareScene();

    objectDrawer.drawMap(blit, app_.renderer_, map_);
    for (const auto &it : staticBonuses_)
        objectDrawer.drawObject(blit, app_.renderer_, it);
    if(movingBonusEnabled_) {
        objectDrawer.drawObject(blit, app_.renderer_, movingBonus_);
    }
    for (const auto &it : ghosts_)
        objectDrawer.drawObject(blit, app_.renderer_, it);
    objectDrawer.drawObject(blit, app_.renderer_, player_);
    objectDrawer.drawBottomBar(sizedBlit, app_.renderer_, displayInfo_, mapSize_);
    objectDrawer.drawBanner(sizedBlit, app_.renderer_, displayInfo_, windowSize_);
    objectDrawer.drawLifes(sizedBlit, app_.renderer_, displayInfo_, windowSize_);
    objectDrawer.drawScore(sizedBlit, app_.renderer_, displayInfo_, windowSize_);

    presentScene();
}

void CView::drawReadyScreen() {
    prepareScene();

    objectDrawer.drawMap(blit, app_.renderer_, map_);
    for (const auto &it : staticBonuses_)
        objectDrawer.drawObject(blit, app_.renderer_, it);
    objectDrawer.drawObject(blit, app_.renderer_, player_);
    objectDrawer.drawBottomBar(sizedBlit, app_.renderer_, displayInfo_, mapSize_);
    objectDrawer.drawReady(sizedBlit, app_.renderer_, windowSize_);

    presentScene();
}

void CView::updateGameDisplayInfo(const SDisplayInfo &displayInfo) {
    displayInfo_ = displayInfo;
}

void CView::updateMap(const vector<vector<SGameObjectInfo>> &map) {
    map_ = map;
}

void CView::updateGhosts(const vector<SGameObjectInfo> &ghosts) {
    ghosts_ = ghosts;
}

void CView::updateStaticBonuses(const vector<SGameObjectInfo> &staticBonuses) {
    staticBonuses_ = staticBonuses;
}

void CView::updateMovingBonus(const SGameObjectInfo &movingBonus) {
    movingBonus_ = movingBonus;
}

void CView::updatePlayer(const SGameObjectInfo &player) {
    player_ = player;
}

void CView::enableMovingBonus() {
    movingBonusEnabled_ = true;
}

void CView::disableMovingBonus() {
    movingBonusEnabled_ = false;
}




