#include "sdl_sprite.h"
#include "argss_sdl.h"

#define max(a, b)  (((a) > (b)) ? (a) : (b))
#define min(a, b)  (((a) < (b)) ? (a) : (b))

SDL_Sprite::SDL_Sprite()
{
	viewport = NULL;
	
	sprite = SDL_CreateRGBSurface(SDL_SWSURFACE, 1, 1, 32, rmask, gmask, bmask, amask);
	if(sprite == NULL) {
		rb_raise(ARGSS_Error, "SDL could not create sprite surface.\n%s\n", SDL_GetError());
	}
	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = 0;
	src_rect.h = 0;
    visible = true;
    x = 0;
    y = 0;
    z = 0;
    ox = 0;
    oy = 0;
    zoom_x = 1.0;
    zoom_y = 1.0;
    angle = 0;
    flipx = false;
    flipy = false;
    bush_depth = 0;
    opacity = 255;
    blend_type = 0;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.unused = 0;
	tone.r = 0;
	tone.g = 0;
	tone.b = 0;
	tone.gray = 0;
}

SDL_Sprite::SDL_Sprite(SDL_Viewport* viewport)
{
	viewport = viewport;
}

SDL_Sprite::~SDL_Sprite()
{
}

void SDL_Sprite::draw(SDL_Surface* surface) {
	if(needs_refresh) {
		refresh();
	}
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(sprite, NULL, surface, &offset);
}

void SDL_Sprite::refresh() {
    SDL_FreeSurface(sprite);
	
	SDL_Rect rect;
	
	if(src_rect.w == 0 && src_rect.h == 0) {
		sprite = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, bitmap->w, bitmap->h, 32, rmask, gmask, bmask, amask);
		if(sprite == NULL) {
			rb_raise(ARGSS_Error, "SDL could not create sprite surface.\n%s\n", SDL_GetError());
		}
		surface_disablealpha(bitmap);
		SDL_BlitSurface(bitmap, NULL, sprite, NULL);
	}
	else {
		sprite = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, src_rect.w, src_rect.h, 32, rmask, gmask, bmask, amask);
		if(sprite == NULL) {
			rb_raise(ARGSS_Error, "SDL could not create sprite surface.\n%s\n", SDL_GetError());
		}
		surface_disablealpha(bitmap);
		SDL_BlitSurface(bitmap, &src_rect, sprite, NULL);
	}
	surface_enablealpha(bitmap);
		
	if(tone.r != 0 || tone.b != 0 || tone.g != 0 || tone.gray != 0) {
		SDL_Sprite::apply_tone();
	}
	
	//bush_depth
	//flipx
    //flipy
	//zoom_x
    //zoom_y
    //angle
	
	needs_refresh = false;
}

void SDL_Sprite::apply_tone() {
	SDL_LockSurface(sprite);

	SDL_Color* srccolor;
	SDL_Color* dstcolor;
	srccolor = new SDL_Color;
	dstcolor = new SDL_Color;
	if(tone.gray == 0) {
		for (int yy = 0; yy < sprite->h; yy++) {
			for (int xx = 0; xx < sprite->w; xx++) {
				surface_getpixelcolor(sprite, xx, yy, srccolor);
				dstcolor->r = max(min(srccolor->r + tone.r, 255), 0);
				dstcolor->g = max(min(srccolor->g + tone.g, 255), 0);
				dstcolor->b = max(min(srccolor->b + tone.b, 255), 0);
				dstcolor->unused = srccolor->unused;
				surface_putpixelcolor(sprite, xx, yy, dstcolor);
			}
		}
	}
	else {
		double factor = (255 - tone.gray) / 255.0;
		int gray;
		for (int yy = 0; yy < sprite->h; yy++) {
			for (int xx = 0; xx < sprite->w; xx++) {
				surface_getpixelcolor(sprite, xx, yy, srccolor);
				gray = srccolor->r * 0.299 + srccolor->g * 0.587 + srccolor->b * 0.114;
				dstcolor->r = (Uint8)max(min((srccolor->r - gray) * factor + gray + tone.r + 0.5, 255), 0);
				dstcolor->g = (Uint8)max(min((srccolor->g - gray) * factor + gray + tone.g + 0.5, 255), 0);
				dstcolor->b = (Uint8)max(min((srccolor->b - gray) * factor + gray + tone.b + 0.5, 255), 0);
				dstcolor->unused = srccolor->unused;
				surface_putpixelcolor(sprite, xx, yy, dstcolor);				
			}
		}
	}
	SDL_UnlockSurface(sprite);
}

int SDL_Sprite::get_width() {
	if(src_rect.w == 0) {
		return bitmap->w;
	}
	else {
		return src_rect.w;
	}
}
int SDL_Sprite::get_height() {
	if(src_rect.h == 0) {
		return bitmap->h;
	}
	else {
		return src_rect.h;
	}
}

void SDL_Sprite::update() {
	
}
void SDL_Sprite::flash(SDL_Color color, int duration){
	
}

unsigned long SDL_Sprite::get_id() {
	return id;
}
void SDL_Sprite::set_id(unsigned long nid) {
	id = nid;
}
SDL_Viewport* SDL_Sprite::get_viewport() {
	return viewport;
}
void SDL_Sprite::set_viewport(SDL_Viewport* nviewport) {
	viewport = nviewport;
}
SDL_Surface* SDL_Sprite::get_sprite() {
	return sprite;
}
SDL_Surface* SDL_Sprite::get_bitmap() {
	return bitmap;
}
void SDL_Sprite::set_bitmap(SDL_Surface* nbitmap) {
	bitmap = nbitmap;
	needs_refresh = true;
}
SDL_Rect SDL_Sprite::get_src_rect() {
	return src_rect;
}
void SDL_Sprite::set_src_rect(SDL_Rect nsrc_rect) {
	src_rect = nsrc_rect;
	needs_refresh = true;
}
bool SDL_Sprite::get_visible() {
	return visible;
}
void SDL_Sprite::set_visible(bool nvisible) {
	visible = nvisible;
}
int SDL_Sprite::get_x() {
	return x;
}
void SDL_Sprite::set_x(int nx) {
	x = nx;
}
int SDL_Sprite::get_y() {
	return y;
}
void SDL_Sprite::set_y(int ny) {
	y = ny;
}
int SDL_Sprite::get_z() {
	return z;
}
void SDL_Sprite::set_z(int nz) {
	z = nz;
}
int SDL_Sprite::get_ox() {
	return ox;
}
void SDL_Sprite::set_ox(int nox) {
	ox = nox;
	needs_refresh = true;
}
int SDL_Sprite::get_oy() {
	return oy;
}
void SDL_Sprite::set_oy(int noy) {
	oy = noy;
	needs_refresh = true;
}
float SDL_Sprite::get_zoom_x() {
	return zoom_x;
}
void SDL_Sprite::set_zoom_x(float nzoom_x) {
	zoom_x = nzoom_x;
	needs_refresh = true;
}
float SDL_Sprite::get_zoom_y() {
	return zoom_y;
}
void SDL_Sprite::set_zoom_y(float nzoom_y) {
	zoom_y = nzoom_y;
	needs_refresh = true;
}
float SDL_Sprite::get_angle() {
	return angle;
}
void SDL_Sprite::set_angle(float nangle) {
	angle = nangle;
	needs_refresh = true;
}
bool SDL_Sprite::get_flipx() {
	return flipx;
}
void SDL_Sprite::set_flipx(bool nflipx) {
	flipx = nflipx;
	needs_refresh = true;
}
bool SDL_Sprite::get_flipy() {
	return flipy;
}
void SDL_Sprite::set_flipy(bool nflipy) {
	flipy = nflipy;
	needs_refresh = true;
}
int SDL_Sprite::get_bush_depth() {
	return bush_depth;
}
void SDL_Sprite::set_bush_depth(int nbush_depth) {
	bush_depth = nbush_depth;
	needs_refresh = true;
}
int SDL_Sprite::get_opacity() {
	return opacity;
}
void SDL_Sprite::set_opacity(int nopacity) {
	opacity = nopacity;
}
int SDL_Sprite::get_blend_type() {
	return blend_type;
}
void SDL_Sprite::set_blend_type(int nblend_type) {
	blend_type = nblend_type;
}
SDL_Color SDL_Sprite::get_color() {
	return color;
}
void SDL_Sprite::set_color(SDL_Color ncolor) {
	color = ncolor;
}
SDL_Tone SDL_Sprite::get_tone() {
	return tone;
}
void SDL_Sprite::set_tone(SDL_Tone ntone) {
	tone = ntone;
	needs_refresh = true;
}
