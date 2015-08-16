#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "cocos2d.h"
USING_NS_CC;

static const char* GLOBAL_FONT = "code";

static const int DEFAULT_FONT_SIZE = 72;

static const int MENU_FONT_SIZE = 90;

static const float BACKGROUND_MUSIC_VOLUME = 0.2f;
static const float SOUND_EFFECTS_VOLUME = 0.5f;

static const float TILE_HEIGHT_PADDING = 20.0f;
static const int BOARD_ROWS = 4;
static const int BOARD_COLUMNS = 4;

static const float SCENE_TRANSITION_TIME = 0.5f;
static const float DEFAULT_ANIMATION_TIME = 0.5f;

static const int TIME_ATTACK_ROWS_TO_RUN = 52;

static const float TIMER_UPDATE_INTERVAL = 0.05f;
static const float TIMER_INITIAL_DELAY = 0.4f;

static const Color4B GAME_BACKGROUND_COLOR = Color4B(127, 255, 179, 255);
static const Color4B MENU_BACKGROUND_COLOR = Color4B(33, 212, 179, 255);
static const Color4B PAUSE_BACKGROUND_COLOR = Color4B(0, 0, 0, 160);
static const Color3B SCORE_COLOR = Color3B(255, 255, 36);

static const Color3B ARCADE_TEXT_COLOR = Color3B(148, 31, 242);
static const Color3B TIME_ATTACK_TEXT_COLOR = Color3B(168, 31, 82);
static const Color3B ZEN_TEXT_COLOR = Color3B(33, 112, 179);

static const int ADD_PINK_CHANCE_PERCENT = 5;
static const int ADD_BLUE_CHANCE_PERCENT = 2;

static const int TILE_CHANGE_CHANCE_PERCENT = 4;
static const int ROW_SLIDE_CHANCE_PERCENT = 7;

static const int LOWEST_VISIBLE_ROW_TO_CHANGE = 2;

static const int BLACK_TILE_SCORE = 5;
static const int PINK_TILE_SCORE = BLACK_TILE_SCORE * 2;
static const int BLUE_TILE_SCORE = BLACK_TILE_SCORE * 4;

static const float PINK_TILE_TIME_REDUCE = 0.5f;
static const float BLUE_TILE_TIME_REDUCE = 1.0f;

static const float TILE_ROTATION_DEGREE = 4.0f;

static const float ARCADE_MODE_INITIAL_MOVE_SPEED = 0.6f;
static const float ARCADE_MODE_SPEED_UP_FACTOR = 0.01f;
static const float ARCADE_MODE_MINIMUM_SPEED = 0.1f;

static const char* ARCADE_HIGH_SCORE_KEY = "arcade_high_score";
static const char* TIME_ATTACK_HIGH_SCORE_KEY = "time_attack_high_score";
static const char* ZEN_HIGH_SCORE_KEY = "zen_high_score";

static const char* SCORE_KEY = "score";
static const char* IS_WIN_KEY = "is_win";

enum class Direction {
    UP,DOWN,LEFT,RIGHT
};

enum GameMode {
    ARCADE, TIME_ATTACK, ZEN
};

#endif /* CONSTANTS_H_ */
