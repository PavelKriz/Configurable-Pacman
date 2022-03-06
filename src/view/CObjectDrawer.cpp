//
// Created by pavel on 30.04.20.
//

#include "CObjectDrawer.h"

using namespace std;

void CObjectDrawer::generateMapTiles( SDL_Renderer *renderer) {
    for(int i = 0; i < 16; ++i){
        allPossibleMapTiles_[i].texture_ = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, STANDARD_TILE_SIZE, STANDARD_TILE_SIZE);
        SDL_SetRenderTarget(renderer, allPossibleMapTiles_[i].texture_);
        SDL_RenderCopy(renderer, textures_[WALL_index_].texture_, nullptr, nullptr);
        SDL_Rect rect = {0, 0, 0, 0};

        ///Add connections on side where is some neighbour wall
        //right
        if((i & 1) == 1){
            rect = {27, 10, 13, 20};
            SDL_RenderCopy(renderer, textures_[WALL_CONNECTIONS_index_].texture_, &rect, &rect);
        }
        //down
        if((i & 2) == 2){
            rect = {10, 27, 20, 13};
            SDL_RenderCopy(renderer, textures_[WALL_CONNECTIONS_index_].texture_, &rect, &rect);
        }
        //left
        if((i & 4) == 4){
            rect = {0, 10, 13, 20};
            SDL_RenderCopy(renderer, textures_[WALL_CONNECTIONS_index_].texture_, &rect, &rect);
        }
        //up
        if((i & 8) == 8){
            rect = {10, 0, 20, 13};
            SDL_RenderCopy(renderer, textures_[WALL_CONNECTIONS_index_].texture_, &rect, &rect);
        }

        SDL_SetRenderTarget(renderer, NULL);
    }

    // get the sizes of the all map tile textures
    for(int i = 0; i < 16; ++i) {
        SDL_QueryTexture(allPossibleMapTiles_[i].texture_, nullptr, nullptr, &allPossibleMapTiles_[i].textureSize_.x_,
                         &allPossibleMapTiles_[i].textureSize_.y_);
    }
}

void CObjectDrawer::drawMapTile(void (*blit)(SDL_Renderer *, SDL_Texture *, int, int),
                                SDL_Renderer *renderer, vector<vector<SGameObjectInfo>> &map, size_t x, size_t y) {
    if (map[y][x].objectType_ == GAMEOBJECT_EMPTY) {
        blit(renderer, textures_[EMPTY_index_].texture_, x * TILE_SIZE, y * TILE_SIZE);
        return;
    } else if (map[y][x].objectType_ == GAMEOBJECT_GATE) {
        blit(renderer, textures_[GATE_index_].texture_, x * TILE_SIZE, y * TILE_SIZE);
        return;
    }

    //ITS GAMEOBJECT_WALL

    unsigned int index = 0;
    //right
    if (x + 1 != map[y].size()) {
        if (map[y][x + 1].objectType_ == GAMEOBJECT_WALL) {
            index += 1;
        }
    }
    //down
    if (y + 1 != map.size()) {
        if (map[y + 1][x].objectType_ == GAMEOBJECT_WALL) {
            index += 2;
        }
    }
    //left
    if (x != 0) {
        if (map[y][x - 1].objectType_ == GAMEOBJECT_WALL) {
            index += 4;
        }
    }
    //up
    if (y != 0) {
        if (map[y - 1][x].objectType_ == GAMEOBJECT_WALL) {
            index += 8;
        }
    }

    blit(renderer, allPossibleMapTiles_[index].texture_, x * TILE_SIZE, y * TILE_SIZE);
}

void
CObjectDrawer::drawScreenInfo(void (*sizedBlit)(SDL_Renderer *, SDL_Texture *, int, int, int, int), SDL_Renderer *renderer,
                         SGameObjectTexture & toDraw, SSize &windowSize) {
    float xRatio = (float) windowSize.x_ / toDraw.textureSize_.x_;
    float yRatio = (float) windowSize.y_ / toDraw.textureSize_.y_;
    float ratio = min(xRatio, yRatio);
    ratio = ratio > 1 ? 1 : ratio;
    ratio *= BANNER_RATIO;
    int xSize = ratio * toDraw.textureSize_.x_;
    int ySize = ratio * toDraw.textureSize_.y_;
    int xOffset = (windowSize.x_ - xSize) / 2;
    int yOffset = (windowSize.y_ - ySize) / 2;
    sizedBlit(renderer, toDraw.texture_, xOffset, yOffset, xSize, ySize);
}

CObjectDrawer::CObjectDrawer(): valid_(false){

}

CObjectDrawer::~CObjectDrawer() {
    for (unsigned int i = 0; i < NUMBER_OF_TEXTURES_; ++i) {
        SDL_DestroyTexture(textures_[i].texture_);
        textures_[i].texture_ = nullptr;
    }

    for (unsigned int i = 0; i < numberOfAllPossibleMapTilesTextures_; ++i){
        SDL_DestroyTexture(allPossibleMapTiles_[i].texture_);
        allPossibleMapTiles_[i].texture_ = nullptr;
    }
}

void CObjectDrawer::initialize(SDL_Texture *(*loadTexture)(const char *, SDL_Renderer *), SDL_Renderer *renderer) {
    // load all the textures
    textures_[PLAYER_RIGHT_index_].texture_ = loadTexture(GAMEOBJECT_PLAYER_RIGHT_TEXTURE_FILENAME, renderer);
    textures_[PLAYER_DOWN_index_].texture_ = loadTexture(GAMEOBJECT_PLAYER_DOWN_TEXTURE_FILENAME, renderer);
    textures_[PLAYER_LEFT_index_].texture_ = loadTexture(GAMEOBJECT_PLAYER_LEFT_TEXTURE_FILENAME, renderer);
    textures_[PLAYER_UP_index_].texture_ = loadTexture(GAMEOBJECT_PLAYER_UP_TEXTURE_FILENAME, renderer);
    textures_[PLAYER_FRONT_index_].texture_ = loadTexture(GAMEOBJECT_PLAYER_FRONT_TEXTURE_FILENAME, renderer);

    textures_[RED_GHOST_index_].texture_ = loadTexture(GAMEOBJECT_RED_GHOST_TEXTURE_FILENAME, renderer);
    textures_[TURQUOISE_GHOST_index_].texture_ = loadTexture(GAMEOBJECT_TURQUOISE_GHOST_TEXTURE_FILENAME, renderer);
    textures_[SIENA_GHOST_index_].texture_ = loadTexture(GAMEOBJECT_SIENA_GHOST_TEXTURE_FILENAME, renderer);
    textures_[PURPLE_GHOST_index_].texture_ = loadTexture(GAMEOBJECT_PURPLE_GHOST_TEXTURE_FILENAME, renderer);
    textures_[MOVING_BONUS_index_].texture_ = loadTexture(GAMEOBJECT_MOVING_BONUS_TEXTURE_FILENAME, renderer);
    textures_[BASIC_BONUS_index_].texture_ = loadTexture(GAMEOBJECT_BASIC_BONUS_TEXTURE_FILENAME, renderer);
    textures_[KILLER_BONUS_index_].texture_ = loadTexture(GAMEOBJECT_KILLER_BONUS_TEXTURE_FILENAME, renderer);
    textures_[WALL_index_].texture_ = loadTexture(GAMEOBJECT_WALL_TEXTURE_FILENAME, renderer);
    textures_[GATE_index_].texture_ = loadTexture(GAMEOBJECT_GATE_TEXTURE_FILENAME, renderer);
    textures_[EMPTY_index_].texture_ = loadTexture(GAMEOBJECT_EMPTY_TEXTURE_FILENAME, renderer);
    textures_[SCARED_GHOST_index_].texture_ = loadTexture(GAMEOBJECT_SCARED_GHOST_TEXTURE_FILENAME, renderer);
    textures_[KILLED_GHOST_index_].texture_ = loadTexture(GAMEOBJECT_KILLED_GHOST_TEXTURE_FILENAME, renderer);
    textures_[WALL_CONNECTIONS_index_].texture_ = loadTexture(WALL_CONNECTIONS_TEXTURE_FILENAME, renderer);
    textures_[CORONA_index_].texture_ = loadTexture(GAMEOBJECT_CORONA_TEXTURE, renderer);
    textures_[SCARED_CORONA_index_].texture_ = loadTexture(GAMEOBJECT_SCARED_CORONA_TEXTURE, renderer);

    textures_[READY_index_].texture_ = loadTexture(BANNER_READY_TEXTURE, renderer);
    textures_[LEVEL_DONE_index_].texture_ = loadTexture(BANNER_LEVEL_DONE_TEXTURE, renderer);
    textures_[GAME_OVER_index_].texture_ = loadTexture(BANNER_GAME_OVER_TEXTURE, renderer);
    textures_[LOST_LIFE_index_].texture_ = loadTexture(BANNER_LOST_LIFE_TEXTURE, renderer);

    textures_[LIFE_index_].texture_ = loadTexture(LIFE_TEXTURE, renderer);

    textures_[NUMBER_ZERO_index_].texture_ = loadTexture(NUMBER_ZERO_TEXTURE, renderer);
    textures_[NUMBER_ONE_index_].texture_ = loadTexture(NUMBER_ONE_TEXTURE, renderer);
    textures_[NUMBER_TWO_index_].texture_ = loadTexture(NUMBER_TWO_TEXTURE, renderer);
    textures_[NUMBER_THREE_index_].texture_ = loadTexture(NUMBER_THRE_TEXTURE, renderer);
    textures_[NUMBER_FOUR_index_].texture_ = loadTexture(NUMBER_FOUR_TEXTURE, renderer);
    textures_[NUMBER_FIVE_index_].texture_ = loadTexture(NUMBER_FIVE_TEXTURE, renderer);
    textures_[NUMBER_SIX_index_].texture_ = loadTexture(NUMBER_SIX_TEXTURE, renderer);
    textures_[NUMBER_SEVEN_index_].texture_ = loadTexture(NUMBER_SEVEN_TEXTURE, renderer);
    textures_[NUMBER_EIGHT_index_].texture_ = loadTexture(NUMBER_EIGHT_TEXTURE, renderer);
    textures_[NUMBER_NINE_index_].texture_ = loadTexture(NUMBER_NINE_TEXTURE, renderer);

    textures_[BOTTOM_BAR_index_].texture_ = loadTexture(BOTTOM_SCORE_BAR_TEXTURE_FILENAME, renderer);

    //check if all textures were loaded
    for (unsigned int i = 0; i < NUMBER_OF_TEXTURES_; ++i)
        if (textures_[i].texture_ == nullptr)
            throw invalid_argument("Object texture file wasnt loaded. Texture file index that wasnt: "s + to_string(i));

    // get all the textures sizes
    for (unsigned int i = 0; i < NUMBER_OF_TEXTURES_; ++i)
        SDL_QueryTexture(textures_[i].texture_, nullptr, nullptr, &textures_[i].textureSize_.x_,
                         &textures_[i].textureSize_.y_);

    generateMapTiles(renderer);

    valid_ = true;
}


void CObjectDrawer::drawObject(void (*blit)(SDL_Renderer *renderer, SDL_Texture *, int, int), SDL_Renderer *renderer,
                               const SGameObjectInfo &objectInfo) {
    if (!valid_)
        throw invalid_argument("Invalid object cannot be drown.");

    int textureIndex = 0;

    // get the right texture
    switch (objectInfo.objectType_) {

        case GAMEOBJECT_PLAYER:
            switch(objectInfo.additionalInfo_){
                case EGameObjectDirection::DIRECTION_LEFT:
                    textureIndex = PLAYER_LEFT_index_;
                    break;
                case EGameObjectDirection::DIRECTION_UP:
                    textureIndex = PLAYER_UP_index_;
                    break;
                case EGameObjectDirection::DIRECTION_RIGHT:
                    textureIndex = PLAYER_RIGHT_index_;
                    break;
                case EGameObjectDirection::DIRECTION_DOWN:
                    textureIndex = PLAYER_DOWN_index_;
                    break;
                default:
                    textureIndex = PLAYER_FRONT_index_;
            }
            break;
        case GAMEOBJECT_RED_GHOST:
            textureIndex = RED_GHOST_index_;
            break;
        case GAMEOBJECT_TURQUOISE_GHOST:
            textureIndex = TURQUOISE_GHOST_index_;
            break;
        case GAMEOBJECT_SIENA_GHOST:
            textureIndex = SIENA_GHOST_index_;
            break;
        case GAMEOBJECT_PURPLE_GHOST:
            textureIndex = PURPLE_GHOST_index_;
            break;
        case GAMEOBJECT_MOVING_BONUS:
            textureIndex = MOVING_BONUS_index_;
            break;
        case GAMEOBJECT_BASIC_BONUS:
            textureIndex = BASIC_BONUS_index_;
            break;
        case GAMEOBJECT_KILLER_BONUS:
            textureIndex = KILLER_BONUS_index_;
            break;
        case GAMEOBJECT_WALL:
            textureIndex = WALL_index_;
            break;
        case GAMEOBJECT_GATE:
            textureIndex = GATE_index_;
            break;
        case GAMEOBJECT_EMPTY:
            textureIndex = EMPTY_index_;
            break;
        case GAMEOBJECT_KILLED_GHOST:
            textureIndex = KILLED_GHOST_index_;
            break;
        case GAMEOBJECT_SCARED_GHOST:
            textureIndex = SCARED_GHOST_index_;
            break;
        case GAMEOBJECT_CORONA_GHOST:
            textureIndex = CORONA_index_;;
            break;
        case GAMEOBJECT_SCARED_CORONA:
            textureIndex = SCARED_CORONA_index_;
            break;
    }

    // calc the right size
    float relativeTileSizeCoeficient = (float)TILE_SIZE / (float)STANDARD_TILE_SIZE;
    int x = (int) (objectInfo.location_.x_ * TILE_SIZE) - (float) (abs(textures_[textureIndex].textureSize_.x_ - (int) STANDARD_TILE_SIZE) / 2) * relativeTileSizeCoeficient;
    int y = (int) (objectInfo.location_.y_ * TILE_SIZE) - (float) (abs(textures_[textureIndex].textureSize_.y_ - (int) STANDARD_TILE_SIZE) / 2) * relativeTileSizeCoeficient;

    // draw the texture
    blit(renderer, textures_[textureIndex].texture_, x, y);
}

void CObjectDrawer::drawMap(void (*blit)(SDL_Renderer *, SDL_Texture *, int, int), SDL_Renderer *renderer,
                            vector<vector<SGameObjectInfo>> &map) {
    for (size_t j = 0; j < map.size(); ++j) {
        for (size_t i = 0; i < map[0].size(); ++i) {
            drawMapTile(blit, renderer, map, i, j);
        }
    }
}

void CObjectDrawer::drawBottomBar(void (*sizedBlit)(SDL_Renderer *, SDL_Texture *, int, int, int, int), SDL_Renderer *renderer,
                                  SDisplayInfo &displayInfo, SSize &mapSize) {
    int windowWidth = mapSize.x_ * TILE_SIZE;
    int barWidth = ((float) displayInfo.bonusesPicked_ / displayInfo.possibleBonusesToPick_) * windowWidth;
    if(barWidth >= windowWidth)
        barWidth = windowWidth;

    sizedBlit(renderer, textures_[BOTTOM_BAR_index_].texture_, 0, mapSize.y_ * TILE_SIZE,
              barWidth, BOTTOM_BAR_SIZE);
}

void CObjectDrawer::drawBanner(void (*sizedBlit)(SDL_Renderer *, SDL_Texture *, int, int, int, int),
                               SDL_Renderer *renderer, SDisplayInfo &displayInfo, SSize &windowSize) {
    switch (displayInfo.gameState_) {
        case GAMESTATE_VICTORY:
            drawScreenInfo(sizedBlit,renderer, textures_[LEVEL_DONE_index_], windowSize);
            break;
        case GAMESTATE_LOST:
            drawScreenInfo(sizedBlit,renderer, textures_[GAME_OVER_index_], windowSize);
            break;
        case GAMESTATE_LOST_LIFE:
            drawScreenInfo(sizedBlit,renderer, textures_[LOST_LIFE_index_], windowSize);
            break;
        default:
            break;
    }
}

void
CObjectDrawer::drawReady(void (*sizedBlit)(SDL_Renderer *, SDL_Texture *, int, int, int, int), SDL_Renderer *renderer,
                         SSize &windowSize) {
    drawScreenInfo(sizedBlit,renderer, textures_[READY_index_], windowSize);
}

void
CObjectDrawer::drawLifes(void (*sizedBlit)(SDL_Renderer *, SDL_Texture *, int, int, int, int), SDL_Renderer *renderer,
                         SDisplayInfo &displayInfo, SSize &windowSize) {

    int minSize = min(BOTTOM_BAR_SIZE * NUMBER_OF_LIVES, (unsigned int) windowSize.x_) / NUMBER_OF_LIVES;
    int textureSize = min(textures_[LIFE_index_].textureSize_.x_, minSize);
    for(unsigned int i = 0; i < displayInfo.lives_; ++i){
        sizedBlit(renderer, textures_[LIFE_index_].texture_, textureSize * i, windowSize.y_ - BOTTOM_BAR_SIZE,
                  textureSize, textureSize);
    }
}

void
CObjectDrawer::drawScore(void (*sizedBlit)(SDL_Renderer *, SDL_Texture *, int, int, int, int), SDL_Renderer *renderer,
                         SDisplayInfo &displayInfo, SSize &windowSize) {
    string score = to_string(displayInfo.score_);
    float offset = 0.2f;
    float inverseOffset = 1.0f - offset;
    int size = BOTTOM_BAR_SIZE * inverseOffset;

    for(int i = (int) score.size() - 1; i >= 0; --i){
        int inverseI = (score.size() - 1) - i;
        sizedBlit(renderer, textures_[NUMBER_ZERO_index_ + (score[i] - '0')].texture_, windowSize.x_ - (inverseI + 1) * size,
                  windowSize.y_ - BOTTOM_BAR_SIZE * (inverseOffset + offset / 2),
                  size, size);
    }
}

