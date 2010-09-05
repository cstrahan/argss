/////////////////////////////////////////////////////////////////////////////
// ARGSS - Copyright (c) 2009 - 2010, Alejandro Marzini (vgvgf)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//	* Redistributions of source code must retain the above copyright notice,
//	this list of conditions and the following disclaimer.
//	* Redistributions in binary form must reproduce the above copyright
//	notice, this list of conditions and the following disclaimer in the
//	documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/////////////////////////////////////////////////////////////////////////////

#ifndef _TILEMAP_XP_H_
#define _TILEMAP_XP_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <string>
#include <map>
#include <vector>
#include "bitmap.h"
#include "drawable.h"

////////////////////////////////////////////////////////////
/// Tilemap class
////////////////////////////////////////////////////////////
class Tilemap : public Drawable {
public:
	Tilemap(unsigned long iid);
	~Tilemap();

	static void Init();
	static bool IsDisposed(unsigned long id);
	static void New(unsigned long id);
	static Tilemap* Get(unsigned long id);
	static void Dispose(unsigned long id);

	void RefreshBitmaps();
	void Draw(long z);
	void Draw(long z, Bitmap* dst_bitmap);
	void RefreshData();

	void Update();
	unsigned long GetViewport();
	void SetViewport(unsigned long nviewport);
	unsigned long GetTileset();
	void SetTileset(unsigned long ntileset);
	unsigned long GetMapData();
	void SetMapData(unsigned long nmap_data);
	unsigned long GetFlashData();
	void SetFlashData(unsigned long nflash_data);
	unsigned long GetPriorities();
	void SetPriorities(unsigned long npriorities);
	bool GetVisible();
	void SetVisible(bool nvisible);
	int GetOx();
	void SetOx(int nox);
	int GetOy();
	void SetOy(int noy);

private:
	unsigned long id;
	unsigned long viewport;
	unsigned long tileset;
	unsigned long autotiles;
	unsigned long map_data;
	unsigned long flash_data;
	unsigned long priorities;
	bool visible;
	int ox;
	int oy;
	int autotile_frame;
	int autotile_time;

	std::map<unsigned long, std::map<int, std::map<int, Bitmap*> > > autotiles_cache;
	static int autotiles_id[6][8][4];

	struct TileData {
		int id;
		int priority;
	};
	std::vector<std::vector<std::vector<TileData> > > data_cache;
};

#endif
