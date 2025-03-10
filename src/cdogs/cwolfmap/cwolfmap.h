#pragma once
#include <stdbool.h>

#include "audio.h"
#include "common.h"
#include "vswap.h"

#define CW_LEVELS 100
#pragma pack(push, 1)
typedef struct
{
	uint16_t magic;
	int32_t ptr[CW_LEVELS];
} CWMapHead;
typedef struct
{
	uint32_t offPlane0;
	uint32_t offPlane1;
	uint32_t offPlane2;
	uint16_t lenPlane0;
	uint16_t lenPlane1;
	uint16_t lenPlane2;
	uint16_t width;
	uint16_t height;
	char name[16];
	char signature[4];
} CWLevelHead;
#pragma pack(pop)

#define NUM_PLANES 3
typedef struct
{
	int len;
	uint16_t *plane;
} CWPlane;
typedef struct
{
	CWLevelHead header;
	CWPlane planes[NUM_PLANES];
	bool hasPlayerSpawn;
	char *description;
} CWLevel;

typedef struct
{
	CWMapHead mapHead;
	CWLevel *levels;
	int nLevels;
	CWAudio audio;
	CWVSwap vswap;
	CWMapType type;
	CWN3DQuiz *quizzes;
	int nQuizzes;
} CWolfMap;

CWMapType CWGetType(
	const char *path, const char **ext, const char **ext1,
	const int spearMission);
int CWLoad(CWolfMap *map, const char *path, const int spearMission);
void CWCopy(CWolfMap *dst, const CWolfMap *src);
void CWFree(CWolfMap *map);

const char *CWGetDescription(CWolfMap *map, const int spearMission);

void CWN3DLoadQuizzes(CWolfMap *map, const char *languageBuf);

int CWGetAudioSampleRate(const CWolfMap *map);

typedef enum
{
	CWTILE_WALL,
	CWTILE_DOOR_V,
	CWTILE_DOOR_H,
	CWTILE_DOOR_GOLD_V,
	CWTILE_DOOR_GOLD_H,
	CWTILE_DOOR_SILVER_V,
	CWTILE_DOOR_SILVER_H,
	CWTILE_ELEVATOR_V,
	CWTILE_ELEVATOR_H,
	CWTILE_SECRET_EXIT,
	CWTILE_AREA,
	CWTILE_BACKGROUND,
	CWTILE_UNKNOWN,
} CWTile;

typedef enum
{
	CWENT_NONE,
	CWENT_PLAYER_SPAWN_N,
	CWENT_PLAYER_SPAWN_E,
	CWENT_PLAYER_SPAWN_S,
	CWENT_PLAYER_SPAWN_W,
	CWENT_WATER,
	CWENT_OIL_DRUM,
	CWENT_TABLE_WITH_CHAIRS,
	CWENT_FLOOR_LAMP,
	CWENT_CHANDELIER,
	CWENT_HANGING_SKELETON,
	CWENT_DOG_FOOD,
	CWENT_WHITE_COLUMN,
	CWENT_GREEN_PLANT,
	CWENT_SKELETON,
	CWENT_SINK_SKULLS_ON_STICK,
	CWENT_BROWN_PLANT,
	CWENT_VASE,
	CWENT_TABLE,
	CWENT_CEILING_LIGHT_GREEN,
	CWENT_UTENSILS_BROWN_CAGE_BLOODY_BONES,
	CWENT_ARMOR,
	CWENT_CAGE,
	CWENT_CAGE_SKELETON,
	CWENT_BONES1,
	CWENT_KEY_GOLD,
	CWENT_KEY_SILVER,
	CWENT_BED_CAGE_SKULLS,
	CWENT_BASKET,
	CWENT_FOOD,
	CWENT_MEDKIT,
	CWENT_AMMO,
	CWENT_MACHINE_GUN,
	CWENT_CHAIN_GUN,
	CWENT_CROSS,
	CWENT_CHALICE,
	CWENT_CHEST,
	CWENT_CROWN,
	CWENT_LIFE,
	CWENT_BONES_BLOOD,
	CWENT_BARREL,
	CWENT_WELL_WATER,
	CWENT_WELL,
	CWENT_POOL_OF_BLOOD,
	CWENT_FLAG,
	CWENT_CEILING_LIGHT_RED_AARDWOLF,
	CWENT_BONES2,
	CWENT_BONES3,
	CWENT_BONES4,
	CWENT_UTENSILS_BLUE_COW_SKULL,
	CWENT_STOVE_WELL_BLOOD,
	CWENT_RACK_ANGEL_STATUE,
	CWENT_VINES,
	CWENT_BROWN_COLUMN,
	CWENT_AMMO_BOX,
	CWENT_TRUCK_REAR,
	CWENT_SPEAR,
	CWENT_PUSHWALL,
	CWENT_ENDGAME,
	CWENT_NEXT_LEVEL,
	CWENT_SECRET_LEVEL,
	CWENT_GHOST,
	CWENT_ANGEL,
	CWENT_DEAD_GUARD,

	CWENT_GUARD_E,
	CWENT_GUARD_N,
	CWENT_GUARD_W,
	CWENT_GUARD_S,
	CWENT_OFFICER_E,
	CWENT_OFFICER_N,
	CWENT_OFFICER_W,
	CWENT_OFFICER_S,
	CWENT_SS_E,
	CWENT_SS_N,
	CWENT_SS_W,
	CWENT_SS_S,
	CWENT_DOG_E,
	CWENT_DOG_N,
	CWENT_DOG_W,
	CWENT_DOG_S,
	CWENT_MUTANT_E,
	CWENT_MUTANT_N,
	CWENT_MUTANT_W,
	CWENT_MUTANT_S,

	CWENT_GUARD_MOVING_E,
	CWENT_GUARD_MOVING_N,
	CWENT_GUARD_MOVING_W,
	CWENT_GUARD_MOVING_S,
	CWENT_OFFICER_MOVING_E,
	CWENT_OFFICER_MOVING_N,
	CWENT_OFFICER_MOVING_W,
	CWENT_OFFICER_MOVING_S,
	CWENT_SS_MOVING_E,
	CWENT_SS_MOVING_N,
	CWENT_SS_MOVING_W,
	CWENT_SS_MOVING_S,
	// Dogs are always moving
	CWENT_MUTANT_MOVING_E,
	CWENT_MUTANT_MOVING_N,
	CWENT_MUTANT_MOVING_W,
	CWENT_MUTANT_MOVING_S,

	CWENT_TURN_E,
	CWENT_TURN_NE,
	CWENT_TURN_N,
	CWENT_TURN_NW,
	CWENT_TURN_W,
	CWENT_TURN_SW,
	CWENT_TURN_S,
	CWENT_TURN_SE,

	CWENT_TRANS,
	CWENT_UBER_MUTANT,
	CWENT_BARNACLE_WILHELM,
	CWENT_ROBED_HITLER,
	CWENT_DEATH_KNIGHT,
	CWENT_HITLER,
	CWENT_FETTGESICHT,
	CWENT_SCHABBS,
	CWENT_GRETEL,
	CWENT_HANS,
	CWENT_OTTO,

	CWENT_PACMAN_GHOST_RED,
	CWENT_PACMAN_GHOST_YELLOW,
	CWENT_PACMAN_GHOST_ROSE,
	CWENT_PACMAN_GHOST_BLUE,

	CWENT_KERRY_KANGAROO,
	CWENT_ERNIE_ELEPHANT,

	CWENT_UNKNOWN,
} CWEntity;

typedef enum
{
	CWWALL_GREY_BRICK_1,
	CWWALL_GREY_BRICK_2,
	CWWALL_GREY_BRICK_FLAG,
	CWWALL_GREY_BRICK_HITLER,
	CWWALL_CELL,
	CWWALL_GREY_BRICK_EAGLE,
	CWWALL_CELL_SKELETON,
	CWWALL_BLUE_BRICK_1,
	CWWALL_BLUE_BRICK_2,
	CWWALL_WOOD_EAGLE,
	CWWALL_WOOD_HITLER,
	CWWALL_WOOD,
	CWWALL_ENTRANCE,
	CWWALL_STEEL_SIGN,
	CWWALL_STEEL,
	CWWALL_LANDSCAPE,
	CWWALL_RED_BRICK,
	CWWALL_RED_BRICK_SWASTIKA,
	CWWALL_PURPLE,
	CWWALL_RED_BRICK_FLAG,
	CWWALL_ELEVATOR,
	CWWALL_DEAD_ELEVATOR,
	CWWALL_WOOD_IRON_CROSS,
	CWWALL_DIRTY_BRICK_1,
	CWWALL_PURPLE_BLOOD,
	CWWALL_DIRTY_BRICK_2,
	CWWALL_GREY_BRICK_3,
	CWWALL_GREY_BRICK_SIGN,
	CWWALL_BROWN_WEAVE,
	CWWALL_BROWN_WEAVE_BLOOD_2,
	CWWALL_BROWN_WEAVE_BLOOD_3,
	CWWALL_BROWN_WEAVE_BLOOD_1,
	CWWALL_STAINED_GLASS,
	CWWALL_BLUE_WALL_SKULL,
	CWWALL_GREY_WALL_1,
	CWWALL_BLUE_WALL_SWASTIKA,
	CWWALL_GREY_WALL_VENT,
	CWWALL_MULTICOLOR_BRICK,
	CWWALL_GREY_WALL_2,
	CWWALL_BLUE_WALL,
	CWWALL_BLUE_BRICK_SIGN,
	CWWALL_BROWN_MARBLE_1,
	CWWALL_GREY_WALL_MAP,
	CWWALL_BROWN_STONE_1,
	CWWALL_BROWN_STONE_2,
	CWWALL_BROWN_MARBLE_2,
	CWWALL_BROWN_MARBLE_FLAG,
	CWWALL_WOOD_PANEL,
	CWWALL_GREY_WALL_HITLER,
	CWWALL_STONE_WALL_1,
	CWWALL_STONE_WALL_2,
	CWWALL_STONE_WALL_FLAG,
	CWWALL_STONE_WALL_WREATH,
	CWWALL_GREY_CONCRETE_LIGHT,
	CWWALL_GREY_CONCRETE_DARK,
	CWWALL_BLOOD_WALL,
	CWWALL_CONCRETE,
	CWWALL_RAMPART_STONE_1,
	CWWALL_RAMPART_STONE_2,
	CWWALL_ELEVATOR_WALL,
	CWWALL_WHITE_PANEL,
	CWWALL_BROWN_CONCRETE,
	CWWALL_PURPLE_BRICK,
	CWWALL_UNKNOWN
} CWWall;

uint16_t CWLevelGetCh(
	const CWLevel *level, const int planeIndex, const int x, const int y);
CWTile CWChToTile(const uint16_t ch);
CWWall CWChToWall(const uint16_t ch);
CWEntity CWChToEntity(const uint16_t ch);
