/*
	C-Dogs SDL
	A port of the legendary (and fun) action/arcade cdogs.
	Copyright (c) 2022 Cong Xu
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	Redistributions of source code must retain the above copyright notice, this
	list of conditions and the following disclaimer.
	Redistributions in binary form must reproduce the above copyright notice,
	this list of conditions and the following disclaimer in the documentation
	and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/
#include "loading_screens.h"

#include <cdogs/draw/draw.h>
#include <cdogs/files.h>
#include <cdogs/font.h>
#include <cdogs/map_build.h>
#include <cdogs/pic_manager.h>
#include <cdogs/pics.h>
#include <cdogs/tile_class.h>

LoadingScreen gLoadingScreen;

void LoadingScreenInit(LoadingScreen *l, GraphicsDevice *g)
{
	memset(l, 0, sizeof *l);
	l->g = g;
}
void LoadingScreenTerminate(LoadingScreen *l)
{
	MapTerminate(&l->m);
	DrawBufferTerminate(&l->db);
}

static void LazyLoad(LoadingScreen *l)
{
	if (l->logo == NULL)
	{
		l->logo = PicManagerGetPic(&gPicManager, "logo");
	}
	// Create map large enough to cover the entire screen
	const struct vec2i mapSize = svec2i(X_TILES, Y_TILES);
	if (gPicManager.tileStyleNames.size > 0 &&
		(l->m.Size.x < mapSize.x || l->m.Size.y < mapSize.y))
	{
		// Map with floors only
		Mission m;
		MissionInit(&m);
		m.Type = MAPTYPE_CLASSIC;
		m.Size = mapSize;
		TileClassInit(
			&m.u.Classic.TileClasses.Floor, &gPicManager, &gTileFloor,
			IntFloorStyle(rand() % FLOOR_STYLE_COUNT),
			TileClassBaseStyleType(TILE_CLASS_FLOOR),
			RangeToColor(rand() % COLORRANGE_COUNT),
					  RangeToColor(rand() % COLORRANGE_COUNT));
		m.u.Classic.ExitEnabled = false;
		MapBuild(&l->m, &m, false, 0, GAME_MODE_NORMAL, NULL);
		MapMarkAllAsVisited(&l->m);
		DrawBufferInit(&l->db, mapSize, l->g);
	}
}

static int ReloadTileClass(any_t data, any_t item)
{
	PicManager *pm = data;
	TileClass *t = item;
	TileClassReloadPic(t, pm);
	return MAP_OK;
}
void LoadingScreenReload(LoadingScreen *l)
{
	if (hashmap_iterate(l->m.TileClasses, ReloadTileClass, &gPicManager) != MAP_OK)
	{
		CASSERT(false, "failed to reload tile classes");
	}
}

void LoadingScreenDraw(LoadingScreen *l, const char *loadingText)
{
	WindowContextPreRender(&l->g->gameWindow);

	LazyLoad(l);
	
	if (!svec2i_is_zero(l->m.Size))
	{
		DrawBufferSetFromMap(&l->db, &l->m, Vec2CenterOfTile(svec2i_scale_divide(l->m.Size, 2)), X_TILES);
		DrawBufferArgs args;
		memset(&args, 0, sizeof args);
		DrawBufferDraw(&l->db, svec2i_zero(), &args);
	}
	
	if (l->logo)
	{
		const struct vec2i pos = svec2i(
			CENTER_X(svec2i_zero(), l->g->cachedConfig.Res, l->logo->size.x),
			CENTER_Y(
				svec2i_zero(), svec2i_scale_divide(l->g->cachedConfig.Res, 2),
					 l->logo->size.y));
		PicRender(
				  l->logo, l->g->gameWindow.renderer, pos, colorWhite, 0, svec2_one(),
			SDL_FLIP_NONE, Rect2iZero());
	}

	FontOpts opts = FontOptsNew();
	opts.HAlign = ALIGN_CENTER;
	opts.VAlign = ALIGN_CENTER;
	opts.Area = svec2i(l->g->cachedConfig.Res.x, l->g->cachedConfig.Res.y / 2);
	FontStrOpt(loadingText, svec2i(0, l->g->cachedConfig.Res.y / 2), opts);

	WindowContextPostRender(&l->g->gameWindow);
}
