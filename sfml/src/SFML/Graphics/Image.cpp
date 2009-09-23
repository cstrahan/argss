////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/ImageLoader.hpp>
#include <SFML/Graphics/RenderImage.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/GraphicsContext.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string.h>

//#include "../../../../src/tools/HSLRGB.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H



#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

struct ColorHSL {
    float h;
    float s;
    float l;
};

ColorHSL RGB2HSL(sf::Color col) {
    ColorHSL ncol;
    float vmin, vmax, delta;
    float dr, dg, db;
    float r, g, b;
    r = col.r / 255.0;
    g = col.g / 255.0;
    b = col.b / 255.0;
    vmin = min(min(r, g), b);
    vmax = max(max(r, g), b);
    delta = vmax - vmin;
    ncol.l = (vmax + vmin) / 2;
    if (delta == 0) {
        ncol.h = 0;
        ncol.s = 0;
    }
    else {
        if(ncol.l < 0.5) {
            ncol.s = delta / (vmax + vmin);
        }
        else {
            ncol.s = delta / (2 - vmax - vmin);
        }
        dr = (((vmax - r) / 6) + (delta / 2)) / delta;
        dg = (((vmax - g) / 6) + (delta / 2)) / delta;
        db = (((vmax - b) / 6) + (delta / 2)) / delta;
        if(r == vmax) {
            ncol.h = db - dg;
        }
        else if(g == vmax) {
            ncol.h = (1.0 / 3) + dr - db;
        }
        else if(b == vmax) {
            ncol.h = (2.0 / 3) + dg - dr;
        }
    }
    return ncol;
}

float Hue_2_RGB(float v1, float v2, float vH) {
   if (vH < 0) vH += 1;
   if (vH > 1) vH -= 1;
   if ((6 * vH) < 1) return (v1 + (v2 - v1) * 6 * vH);
   if ((2 * vH) < 1) return (v2);
   if ((3 * vH) < 2) return (v1 + (v2 - v1) * ((2.0 / 3) - vH ) * 6);
   return v1;
}

sf::Color HSL2RGB(ColorHSL col) {
    sf::Color ncol;
    float v1, v2;
    if(col.s == 0) {
        ncol.r = (sf::Uint8)(col.l * 255);
        ncol.g = (sf::Uint8)(col.l * 255);
        ncol.b = (sf::Uint8)(col.l * 255);
    }
    else {
        if(col.l < 0.5) {
            v2 = col.l * (1 + col.s);
        }
        else {
            v2 = (col.l + col.s) - (col.s * col.l);
        }
        v1 = 2 * col.l - v2;
        ncol.r = (sf::Uint8)(255 * Hue_2_RGB(v1, v2, col.h + (1.0 / 3)));
        ncol.g = (sf::Uint8)(255 * Hue_2_RGB(v1, v2, col.h));
        ncol.b = (sf::Uint8)(255 * Hue_2_RGB(v1, v2, col.h - (1.0 / 3)));
    }
    return ncol;
}

sf::Color RGBAdjustHSL(sf::Color col, int h, float s, float l) {
    ColorHSL hsl;
    sf::Color rgb = col;
    hsl = RGB2HSL(rgb);
    hsl.h = hsl.h + h / 360.0;
    while(hsl.h > 1) {hsl.h -= 1;}
    while(hsl.h < 0) {hsl.h += 1;}
    hsl.s = hsl.s + s;
    if (hsl.s > 1) {hsl.s = 1;}
    if (hsl.s < 0) {hsl.s = 0;}
    hsl.l = hsl.l * l;
    if (hsl.l > 1) {hsl.l = 1;}
    if (hsl.l < 0) {hsl.l = 0;}
    rgb = HSL2RGB(hsl);
    rgb.a = col.a;
    return rgb;
}



namespace sf
{
////////////////////////////////////////////////////////////
/// Default constructor
////////////////////////////////////////////////////////////
Image::Image() :
myWidth            (0),
myHeight           (0),
myTextureWidth     (0),
myTextureHeight    (0),
myTexture          (0),
myIsSmooth         (true),
myNeedTextureUpdate(false),
myNeedArrayUpdate  (false)
{

}


////////////////////////////////////////////////////////////
/// Copy constructor
////////////////////////////////////////////////////////////
Image::Image(const Image& Copy) :
Resource<Image>    (Copy),
myWidth            (Copy.myWidth),
myHeight           (Copy.myHeight),
myTextureWidth     (Copy.myTextureWidth),
myTextureHeight    (Copy.myTextureHeight),
myTexture          (0),
myIsSmooth         (Copy.myIsSmooth),
myPixels           (Copy.myPixels),
myNeedTextureUpdate(false),
myNeedArrayUpdate  (false)
{
    CreateTexture();
}


////////////////////////////////////////////////////////////
/// Construct an empty image
////////////////////////////////////////////////////////////
Image::Image(unsigned int Width, unsigned int Height, const Color& Col) :
myWidth            (0),
myHeight           (0),
myTextureWidth     (0),
myTextureHeight    (0),
myTexture          (0),
myIsSmooth         (true),
myNeedTextureUpdate(false),
myNeedArrayUpdate  (false)
{
    Create(Width, Height, Col);
}


////////////////////////////////////////////////////////////
/// Construct the image from pixels in memory
////////////////////////////////////////////////////////////
Image::Image(unsigned int Width, unsigned int Height, const Uint8* Data) :
myWidth            (0),
myHeight           (0),
myTextureWidth     (0),
myTextureHeight    (0),
myTexture          (0),
myIsSmooth         (true),
myNeedTextureUpdate(false),
myNeedArrayUpdate  (false)
{
    LoadFromPixels(Width, Height, Data);
}


////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
Image::~Image()
{
    // Destroy the OpenGL texture
    DestroyTexture();
}


////////////////////////////////////////////////////////////
/// Load the image from a file
////////////////////////////////////////////////////////////
bool Image::LoadFromFile(const std::string& Filename)
{
    // Let the image loader load the image into our pixel array
    bool Success = priv::ImageLoader::GetInstance().LoadImageFromFile(Filename, myPixels, myWidth, myHeight);

    if (Success)
    {
        // Loading succeeded : we can create the texture
        if (CreateTexture())
            return true;
    }

    // Oops... something failed
    Reset();

    return false;
}


////////////////////////////////////////////////////////////
/// Load the image from a file in memory
////////////////////////////////////////////////////////////
bool Image::LoadFromMemory(const char* Data, std::size_t SizeInBytes)
{
    // Check parameters
    if (!Data || (SizeInBytes == 0))
    {
        std::cerr << "Failed to image font from memory, no data provided" << std::endl;
        return false;
    }

    // Let the image loader load the image into our pixel array
    bool Success = priv::ImageLoader::GetInstance().LoadImageFromMemory(Data, SizeInBytes, myPixels, myWidth, myHeight);

    if (Success)
    {
        // Loading succeeded : we can create the texture
        if (CreateTexture())
            return true;
    }

    // Oops... something failed
    Reset();

    return false;
}


////////////////////////////////////////////////////////////
/// Load the image directly from an array of pixels
////////////////////////////////////////////////////////////
bool Image::LoadFromPixels(unsigned int Width, unsigned int Height, const Uint8* Data)
{
    if (Data)
    {
        // Store the texture dimensions
        myWidth  = Width;
        myHeight = Height;

        // Fill the pixel buffer with the specified raw data
        const Color* Ptr = reinterpret_cast<const Color*>(Data);
        myPixels.assign(Ptr, Ptr + Width * Height);

        // We can create the texture
        if (CreateTexture())
        {
            return true;
        }
        else
        {
            // Oops... something failed
            Reset();
            return false;
        }
    }
    else
    {
        // No data provided : create a white image
        return Create(Width, Height, Color(255, 255, 255, 255));
    }
}


////////////////////////////////////////////////////////////
/// Save the content of the image to a file
////////////////////////////////////////////////////////////
bool Image::SaveToFile(const std::string& Filename) const
{
    // Check if the array of pixels needs to be updated
    EnsureArrayUpdate();

    // Let the image loader save our pixel array into the image
    return priv::ImageLoader::GetInstance().SaveImageToFile(Filename, myPixels, myWidth, myHeight);
}


////////////////////////////////////////////////////////////
/// Create an empty image
////////////////////////////////////////////////////////////
bool Image::Create(unsigned int Width, unsigned int Height, Color Col)
{
    // Store the texture dimensions
    myWidth  = Width;
    myHeight = Height;

    // Recreate the pixel buffer and fill it with the specified color
    myPixels.clear();
    myPixels.resize(Width * Height, Col);

    // We can create the texture
    if (CreateTexture())
    {
        return true;
    }
    else
    {
        // Oops... something failed
        Reset();
        return false;
    }
}


////////////////////////////////////////////////////////////
/// Create transparency mask from a specified colorkey
////////////////////////////////////////////////////////////
void Image::CreateMaskFromColor(Color ColorKey, Uint8 Alpha)
{
    // Check if the array of pixels needs to be updated
    EnsureArrayUpdate();

    // Calculate the new color (old color with no alpha)
    Color NewColor(ColorKey.r, ColorKey.g, ColorKey.b, Alpha);

    // Replace the old color by the new one
    std::replace(myPixels.begin(), myPixels.end(), ColorKey, NewColor);

    // The texture will need to be updated
    myNeedTextureUpdate = true;
}


////////////////////////////////////////////////////////////
/// Copy pixels from another image onto this one.
/// This function does a slow pixel copy and should only
/// be used at initialization time
////////////////////////////////////////////////////////////
void Image::Copy(const Image& Source, unsigned int DestX, unsigned int DestY, const IntRect& SourceRect, bool ApplyAlpha)
{
    // Make sure both images are valid
    if ((Source.myWidth == 0) || (Source.myHeight == 0) || (myWidth == 0) || (myHeight == 0))
        return;

    // Make sure both images have up-to-date arrays
    EnsureArrayUpdate();
    Source.EnsureArrayUpdate();

    // Adjust the source rectangle
    IntRect SrcRect = SourceRect;
    if (SrcRect.GetWidth() == 0 || (SrcRect.GetHeight() == 0))
    {
        SrcRect.Left   = 0;
        SrcRect.Top    = 0;
        SrcRect.Right  = Source.myWidth;
        SrcRect.Bottom = Source.myHeight;
    }
    else
    {
        if (SrcRect.Left   < 0) SrcRect.Left = 0;
        if (SrcRect.Top    < 0) SrcRect.Top  = 0;
        if (SrcRect.Right  > static_cast<int>(Source.myWidth))  SrcRect.Right  = Source.myWidth;
        if (SrcRect.Bottom > static_cast<int>(Source.myHeight)) SrcRect.Bottom = Source.myHeight;
    }

    // Then find the valid bounds of the destination rectangle
    int Width  = SrcRect.GetWidth();
    int Height = SrcRect.GetHeight();
    if (DestX + Width  > myWidth)  Width  = myWidth  - DestX;
    if (DestY + Height > myHeight) Height = myHeight - DestY;

    // Make sure the destination area is valid
    if ((Width <= 0) || (Height <= 0))
        return;

    // Precompute as much as possible
    int          Pitch     = Width * 4;
    int          Rows      = Height;
    int          SrcStride = Source.myWidth * 4;
    int          DstStride = myWidth * 4;
    const Uint8* SrcPixels = Source.GetPixelsPtr() + (SrcRect.Left + SrcRect.Top * Source.myWidth) * 4;
    Uint8*       DstPixels = reinterpret_cast<Uint8*>(&myPixels[0]) + (DestX + DestY * myWidth) * 4;

    // Copy the pixels
    if (ApplyAlpha)
    {
        // Interpolation using alpha values, pixel by pixel (slower)
        for (int i = 0; i < Rows; ++i)
        {
            for (int j = 0; j < Width; ++j)
            {
                // Get a direct pointer to the components of the current pixel
                const Uint8* Src   = SrcPixels + j * 4;
                Uint8*       Dst   = DstPixels + j * 4;

                // Interpolate RGB components using the alpha value of the source pixel
                Uint8 Alpha = Src[3];
                Dst[0] = (Src[0] * Alpha + Dst[0] * (255 - Alpha)) / 255;
                Dst[1] = (Src[1] * Alpha + Dst[1] * (255 - Alpha)) / 255;
                Dst[2] = (Src[2] * Alpha + Dst[2] * (255 - Alpha)) / 255;
            }

            SrcPixels += SrcStride;
            DstPixels += DstStride;
        }
    }
    else
    {
        // Optimized copy ignoring alpha values, row by row (faster)
        for (int i = 0; i < Rows; ++i)
        {
            memcpy(DstPixels, SrcPixels, Pitch);
            SrcPixels += SrcStride;
            DstPixels += DstStride;
        }
    }

    // The texture will need an update
    myNeedTextureUpdate = true;
}


////////////////////////////////////////////////////////////
/// Create the image from the current contents of the
/// given window
////////////////////////////////////////////////////////////
bool Image::CopyScreen(RenderWindow& Window, const IntRect& SourceRect)
{
    // Adjust the source rectangle
    IntRect SrcRect = SourceRect;
    if (SrcRect.GetWidth() == 0 || (SrcRect.GetHeight() == 0))
    {
        SrcRect.Left   = 0;
        SrcRect.Top    = 0;
        SrcRect.Right  = Window.GetWidth();
        SrcRect.Bottom = Window.GetHeight();
    }
    else
    {
        if (SrcRect.Left   < 0) SrcRect.Left = 0;
        if (SrcRect.Top    < 0) SrcRect.Top  = 0;
        if (SrcRect.Right  > static_cast<int>(Window.GetWidth()))  SrcRect.Right  = Window.GetWidth();
        if (SrcRect.Bottom > static_cast<int>(Window.GetHeight())) SrcRect.Bottom = Window.GetHeight();
    }

    // Store the texture dimensions
    myWidth  = SrcRect.GetWidth();
    myHeight = SrcRect.GetHeight();

    // We can then create the texture
    if (Window.SetActive() && CreateTexture())
    {
        GLint PreviousTexture;
        GLCheck(glGetIntegerv(GL_TEXTURE_BINDING_2D, &PreviousTexture));

        GLCheck(glBindTexture(GL_TEXTURE_2D, myTexture));
        GLCheck(glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, SrcRect.Left, SrcRect.Top, myWidth, myHeight));

        GLCheck(glBindTexture(GL_TEXTURE_2D, PreviousTexture));

        myNeedTextureUpdate = false;
        myNeedArrayUpdate = true;

        return true;
    }
    else
    {
        Reset();
        return false;
    }
}


////////////////////////////////////////////////////////////
/// Change the color of a pixel
////////////////////////////////////////////////////////////
void Image::SetPixel(unsigned int X, unsigned int Y, const Color& Col)
{
    // First check if the array of pixels needs to be updated
    EnsureArrayUpdate();

    // Check if pixel is whithin the image bounds
    if ((X >= myWidth) || (Y >= myHeight))
    {
        std::cerr << "Cannot set pixel (" << X << "," << Y << ") for image "
                  << "(width = " << myWidth << ", height = " << myHeight << ")" << std::endl;
        return;
    }

    myPixels[X + Y * myWidth] = Col;

    // The texture will need to be updated
    myNeedTextureUpdate = true;
}


////////////////////////////////////////////////////////////
/// Get a pixel from the image
////////////////////////////////////////////////////////////
const Color& Image::GetPixel(unsigned int X, unsigned int Y) const
{
    // First check if the array of pixels needs to be updated
    EnsureArrayUpdate();

    // Check if pixel is whithin the image bounds
    if ((X >= myWidth) || (Y >= myHeight))
    {
        std::cerr << "Cannot get pixel (" << X << "," << Y << ") for image "
                  << "(width = " << myWidth << ", height = " << myHeight << ")" << std::endl;
        return Color::Black;
    }

    return myPixels[X + Y * myWidth];
}


////////////////////////////////////////////////////////////
/// Get a read-only pointer to the array of pixels (RGBA 8 bits integers components)
/// Array size is GetWidth() x GetHeight() x 4
/// This pointer becomes invalid if you reload or resize the image
////////////////////////////////////////////////////////////
const Uint8* Image::GetPixelsPtr() const
{
    // First check if the array of pixels needs to be updated
    EnsureArrayUpdate();

    if (!myPixels.empty())
    {
        return reinterpret_cast<const Uint8*>(&myPixels[0]);
    }
    else
    {
        std::cerr << "Trying to access the pixels of an empty image" << std::endl;
        return NULL;
    }
}


////////////////////////////////////////////////////////////
/// Bind the image for rendering
////////////////////////////////////////////////////////////
void Image::Bind() const
{
    // First check if the texture needs to be updated
    EnsureTextureUpdate();

    // Bind it
    if (myTexture)
    {
        GLCheck(glEnable(GL_TEXTURE_2D));
        GLCheck(glBindTexture(GL_TEXTURE_2D, myTexture));
    }
}


////////////////////////////////////////////////////////////
/// Enable or disable image smoothing filter
////////////////////////////////////////////////////////////
void Image::SetSmooth(bool Smooth)
{
    if (Smooth != myIsSmooth)
    {
        myIsSmooth = Smooth;

        if (myTexture)
        {
            // Make sure we have a valid context
            priv::GraphicsContext Ctx;

            GLint PreviousTexture;
            GLCheck(glGetIntegerv(GL_TEXTURE_BINDING_2D, &PreviousTexture));

            GLCheck(glBindTexture(GL_TEXTURE_2D, myTexture));
            GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, myIsSmooth ? GL_LINEAR : GL_NEAREST));
            GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, myIsSmooth ? GL_LINEAR : GL_NEAREST));

            GLCheck(glBindTexture(GL_TEXTURE_2D, PreviousTexture));
        }
    }
}


////////////////////////////////////////////////////////////
/// Return the width of the image
////////////////////////////////////////////////////////////
unsigned int Image::GetWidth() const
{
    return myWidth;
}


////////////////////////////////////////////////////////////
/// Return the height of the image
////////////////////////////////////////////////////////////
unsigned int Image::GetHeight() const
{
    return myHeight;
}


////////////////////////////////////////////////////////////
/// Tells whether the smooth filtering is enabled or not
////////////////////////////////////////////////////////////
bool Image::IsSmooth() const
{
    return myIsSmooth;
}


////////////////////////////////////////////////////////////
/// Convert a subrect expressed in pixels, into float
/// texture coordinates
////////////////////////////////////////////////////////////
FloatRect Image::GetTexCoords(const IntRect& Rect, bool Adjust) const
{
    float Width  = static_cast<float>(myTextureWidth);
    float Height = static_cast<float>(myTextureHeight);

    if (Adjust && myIsSmooth)
    {
        return FloatRect((Rect.Left   + 0.5f) / Width,
                         (Rect.Top    + 0.5f) / Height,
                         (Rect.Right  - 0.5f) / Width,
                         (Rect.Bottom - 0.5f) / Height);
    }
    else
    {
        return FloatRect(Rect.Left   / Width,
                         Rect.Top    / Height,
                         Rect.Right  / Width,
                         Rect.Bottom / Height);
    }
}


////////////////////////////////////////////////////////////
/// Get a valid texture size according to hardware support
////////////////////////////////////////////////////////////
unsigned int Image::GetValidTextureSize(unsigned int Size)
{
    // Make sure we have a valid context
    priv::GraphicsContext Ctx;

    if (glewIsSupported("GL_ARB_texture_non_power_of_two") != 0)
    {
        // If hardware supports NPOT textures, then just return the unmodified size
        return Size;
    }
    else
    {
        // If hardware doesn't support NPOT textures, we calculate the nearest power of two
        unsigned int PowerOfTwo = 1;
        while (PowerOfTwo < Size)
            PowerOfTwo *= 2;

        return PowerOfTwo;
    }
}


////////////////////////////////////////////////////////////
/// Assignment operator
////////////////////////////////////////////////////////////
Image& Image::operator =(const Image& Other)
{
    Image Temp(Other);

    std::swap(myWidth,             Temp.myWidth);
    std::swap(myHeight,            Temp.myHeight);
    std::swap(myTextureWidth,      Temp.myTextureWidth);
    std::swap(myTextureHeight,     Temp.myTextureHeight);
    std::swap(myTexture,           Temp.myTexture);
    std::swap(myIsSmooth,          Temp.myIsSmooth);
    std::swap(myNeedArrayUpdate,   Temp.myNeedArrayUpdate);
    std::swap(myNeedTextureUpdate, Temp.myNeedTextureUpdate);
    myPixels.swap(Temp.myPixels);

    return *this;
}


////////////////////////////////////////////////////////////
/// Create the OpenGL texture
////////////////////////////////////////////////////////////
bool Image::CreateTexture()
{
    // Check if texture parameters are valid before creating it
    if (!myWidth || !myHeight)
        return false;

    // Make sure we have a valid context
    priv::GraphicsContext Ctx;

    // Adjust internal texture dimensions depending on NPOT textures support
    unsigned int TextureWidth  = GetValidTextureSize(myWidth);
    unsigned int TextureHeight = GetValidTextureSize(myHeight);

    // Check the maximum texture size
    GLint MaxSize;
    GLCheck(glGetIntegerv(GL_MAX_TEXTURE_SIZE, &MaxSize));
    if ((TextureWidth > static_cast<unsigned int>(MaxSize)) || (TextureHeight > static_cast<unsigned int>(MaxSize)))
    {
        std::cerr << "Failed to create image, its internal size is too high (" << TextureWidth << "x" << TextureHeight << ")" << std::endl;
        return false;
    }

    // Destroy the previous OpenGL texture if it already exists with another size
    if ((TextureWidth != myTextureWidth) || (TextureHeight != myTextureHeight))
    {
        DestroyTexture();
        myTextureWidth  = TextureWidth;
        myTextureHeight = TextureHeight;
    }

    // Create the OpenGL texture
    if (!myTexture)
    {
        GLint PreviousTexture;
        GLCheck(glGetIntegerv(GL_TEXTURE_BINDING_2D, &PreviousTexture));

        GLuint Texture = 0;
        GLCheck(glGenTextures(1, &Texture));
        GLCheck(glBindTexture(GL_TEXTURE_2D, Texture));
        GLCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, myTextureWidth, myTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
        GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
        GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));
        GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, myIsSmooth ? GL_LINEAR : GL_NEAREST));
        GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, myIsSmooth ? GL_LINEAR : GL_NEAREST));
        myTexture = static_cast<unsigned int>(Texture);

        GLCheck(glBindTexture(GL_TEXTURE_2D, PreviousTexture));
    }

    myNeedTextureUpdate = true;

    return true;
}


////////////////////////////////////////////////////////////
/// Make sure the texture in video memory is updated with the
/// array of pixels
////////////////////////////////////////////////////////////
void Image::EnsureTextureUpdate() const
{
    if (myNeedTextureUpdate)
    {
        // Copy the pixels
        if (myTexture && !myPixels.empty())
        {
            GLint PreviousTexture;
            GLCheck(glGetIntegerv(GL_TEXTURE_BINDING_2D, &PreviousTexture));

            // Update the texture with the pixels array in RAM
            GLCheck(glBindTexture(GL_TEXTURE_2D, myTexture));
            GLCheck(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, myWidth, myHeight, GL_RGBA, GL_UNSIGNED_BYTE, &myPixels[0]));

            GLCheck(glBindTexture(GL_TEXTURE_2D, PreviousTexture));
        }

        myNeedTextureUpdate = false;
    }
}


////////////////////////////////////////////////////////////
/// Make sure the array of pixels is updated with the
/// texture in video memory
////////////////////////////////////////////////////////////
void Image::EnsureArrayUpdate() const
{
    if (myNeedArrayUpdate)
    {
        // Save the previous texture
        GLint PreviousTexture;
        GLCheck(glGetIntegerv(GL_TEXTURE_BINDING_2D, &PreviousTexture));

        // Resize the destination array of pixels
        myPixels.resize(myWidth * myHeight);

        if ((myWidth == myTextureWidth) && (myHeight == myTextureHeight))
        {
            // Texture and array have the same size, we can use a direct copy

            // Copy pixels from texture to array
            GLCheck(glBindTexture(GL_TEXTURE_2D, myTexture));
            GLCheck(glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &myPixels[0]));
        }
        else
        {
            // Texture and array don't have the same size, we have to use a slower algorithm

            // All the pixels will first be copied to a temporary array
            std::vector<Color> AllPixels(myTextureWidth * myTextureHeight);
            GLCheck(glBindTexture(GL_TEXTURE_2D, myTexture));
            GLCheck(glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &AllPixels[0]));

            // The we copy the useful pixels from the temporary array to the final one
            const Color* Src = &AllPixels[0];
            Color* Dst = &myPixels[0];
            for (unsigned int i = 0; i < myHeight; ++i)
            {
                std::copy(Src, Src + myWidth, Dst);
                Src += myTextureWidth;
                Dst += myWidth;
            }
        }

        // Restore the previous texture
        GLCheck(glBindTexture(GL_TEXTURE_2D, PreviousTexture));

        myNeedArrayUpdate = false;
    }
}


////////////////////////////////////////////////////////////
/// Reset the image attributes
////////////////////////////////////////////////////////////
void Image::Reset()
{
    DestroyTexture();

    myWidth             = 0;
    myHeight            = 0;
    myTextureWidth      = 0;
    myTextureHeight     = 0;
    myTexture           = 0;
    myIsSmooth          = true;
    myNeedTextureUpdate = false;
    myNeedArrayUpdate   = false;
    myPixels.clear();
}


////////////////////////////////////////////////////////////
/// Destroy the OpenGL texture
////////////////////////////////////////////////////////////
void Image::DestroyTexture()
{
    // Destroy the internal texture
    if (myTexture)
    {
        // Make sure we have a valid context
        priv::GraphicsContext Ctx;

        GLuint Texture = static_cast<GLuint>(myTexture);
        GLCheck(glDeleteTextures(1, &Texture));
        myTexture           = 0;
        myNeedTextureUpdate = false;
        myNeedArrayUpdate   = false;
    }
}

////////////////////////////////////////////////////////////
/// Blits one image to this one.
////////////////////////////////////////////////////////////
void Image::CopyA(const Image& Source, unsigned int DestX, unsigned int DestY, const IntRect& SourceRect, bool ApplyAlpha, int opacity)
{
    // Make sure both images are valid
    if ((Source.myWidth == 0) || (Source.myHeight == 0) || (myWidth == 0) || (myHeight == 0))
        return;

    // Make sure both images have up-to-date arrays
    EnsureArrayUpdate();
    Source.EnsureArrayUpdate();

    // Adjust the source rectangle
    IntRect SrcRect = SourceRect;
    if (SrcRect.GetWidth() == 0 || (SrcRect.GetHeight() == 0))
    {
        SrcRect.Left   = 0;
        SrcRect.Top    = 0;
        SrcRect.Right  = Source.myWidth;
        SrcRect.Bottom = Source.myHeight;
    }
    else
    {
        if (SrcRect.Left   < 0) SrcRect.Left = 0;
        if (SrcRect.Top    < 0) SrcRect.Top  = 0;
        if (SrcRect.Right  > static_cast<int>(Source.myWidth))  SrcRect.Right  = Source.myWidth;
        if (SrcRect.Bottom > static_cast<int>(Source.myHeight)) SrcRect.Bottom = Source.myHeight;
    }

    // Then find the valid bounds of the destination rectangle
    int Width  = SrcRect.GetWidth();
    int Height = SrcRect.GetHeight();
    if (DestX + Width  > myWidth)  Width  = myWidth  - DestX;
    if (DestY + Height > myHeight) Height = myHeight - DestY;

    // Make sure the destination area is valid
    if ((Width <= 0) || (Height <= 0))
        return;

    // Precompute as much as possible
    int          Pitch     = Width * 4;
    int          Rows      = Height;
    int          SrcStride = Source.myWidth * 4;
    int          DstStride = myWidth * 4;
    const Uint8* SrcPixels = Source.GetPixelsPtr() + (SrcRect.Left + SrcRect.Top * Source.myWidth) * 4;
    Uint8*       DstPixels = reinterpret_cast<Uint8*>(&myPixels[0]) + (DestX + DestY * myWidth) * 4;

    // Copy the pixels
    if (ApplyAlpha)
    {
        if (opacity > 255) {opacity = 255;}
        if (opacity > 0) {
            // Interpolation using alpha values, pixel by pixel (slower)
            for (int i = 0; i < Rows; ++i)
            {
                for (int j = 0; j < Width; ++j)
                {
                    // Get a direct pointer to the components of the current pixel
                    const Uint8* Src   = SrcPixels + j * 4;
                    Uint8*       Dst   = DstPixels + j * 4;

                    // Interpolate RGB components using the alpha value of the source pixel
                    Uint8 SrcA = Src[3] * opacity / 255;
                    Dst[0] = (Dst[0] * (255 - SrcA) + Src[0] * SrcA) / 255;
                    Dst[1] = (Dst[1] * (255 - SrcA) + Src[1] * SrcA) / 255;
                    Dst[2] = (Dst[2] * (255 - SrcA) + Src[2] * SrcA) / 255;
                    Dst[3] = Dst[3] * (255 - SrcA) / 255 + SrcA;
                }
                SrcPixels += SrcStride;
                DstPixels += DstStride;
            }
        }
    }
    else
    {
        // Optimized copy ignoring alpha values, row by row (faster)
        for (int i = 0; i < Rows; ++i)
        {
            memcpy(DstPixels, SrcPixels, Pitch);
            SrcPixels += SrcStride;
            DstPixels += DstStride;
        }
    }

    // The texture will need an update
    myNeedTextureUpdate = true;
}

////////////////////////////////////////////////////////////
/// Adjust HSL values of the image.
////////////////////////////////////////////////////////////
void Image::HSL_Adjust(int h, double s, double l, const IntRect& DestRect)
{
    if (((myWidth == 0) || (myHeight == 0)))
        return;
    EnsureArrayUpdate();

    // Adjust the source rectangle
    IntRect Rect = DestRect;
    if (Rect.GetWidth() == 0 || (Rect.GetHeight() == 0)) {
        Rect.Left   = 0;
        Rect.Top    = 0;
        Rect.Right  = myWidth;
        Rect.Bottom = myHeight;
    }
    else {
        if (Rect.Left   < 0) Rect.Left = 0;
        if (Rect.Top    < 0) Rect.Top  = 0;
        if (Rect.Right  > static_cast<int>(myWidth))  Rect.Right  = myWidth;
        if (Rect.Bottom > static_cast<int>(myHeight)) Rect.Bottom = myHeight;
    }

    // Then find the valid bounds of the destination rectangle
    unsigned int Width  = Rect.GetWidth();
    unsigned int Height = Rect.GetHeight();
    if (Rect.Left + Width  > myWidth)  Width  = myWidth  - Rect.Left;
    if (Rect.Bottom + Height > myHeight) Height = myHeight - Rect.Bottom;

    // Make sure the destination area is valid
    if ((Width <= 0) || (Height <= 0))
        return;

    sf::Color col;
    for(unsigned int y = 0; y < Height; y++) {
        for(unsigned int x = 0; x < Width; x++) {
            col = myPixels[Rect.Right + x + (Rect.Top + y) * myWidth];
            myPixels[Rect.Left + x + (Rect.Top + y) * myWidth] = RGBAdjustHSL(col, h, s, l);
        }
    }
}

////////////////////////////////////////////////////////////
/// Fills a rect with the given color.
////////////////////////////////////////////////////////////
void Image::FillRect(const IntRect& DestRect, const Color& Col)
{
    if (((myWidth == 0) || (myHeight == 0)))
        return;
    EnsureArrayUpdate();

    // Adjust the source rectangle
    IntRect Rect = DestRect;
    if (Rect.GetWidth() == 0 || (Rect.GetHeight() == 0))
    {
        Rect.Left   = 0;
        Rect.Top    = 0;
        Rect.Right  = myWidth;
        Rect.Bottom = myHeight;
    }
    else
    {
        if (Rect.Left   < 0) Rect.Left = 0;
        if (Rect.Top    < 0) Rect.Top  = 0;
        if (Rect.Right  > static_cast<int>(myWidth))  Rect.Right  = myWidth;
        if (Rect.Bottom > static_cast<int>(myHeight)) Rect.Bottom = myHeight;
    }

    // Then find the valid bounds of the destination rectangle
    unsigned int Width  = Rect.GetWidth();
    unsigned int Height = Rect.GetHeight();
    if (Rect.Left + Width  > myWidth)  Width  = myWidth  - Rect.Left;
    if (Rect.Bottom + Height > myHeight) Height = myHeight - Rect.Bottom;

    // Make sure the destination area is valid
    if ((Width <= 0) || (Height <= 0))
        return;

    for(unsigned int y = 0; y < Height; y++)
    {
        for(unsigned int x = 0; x < Width; x++)
        {
            myPixels[Rect.Left + x + (Rect.Top + y) * myWidth] = Col;
        }
    }
    // The texture will need an update
    myNeedTextureUpdate = true;
}

////////////////////////////////////////////////////////////
/// Resamples the image.
////////////////////////////////////////////////////////////
Image Image::Resample(unsigned int Width, unsigned int Height, const IntRect& SourceRect) {
    Image newimg = Image(Width, Height, Color(0, 0, 0, 0));

    Uint8* SrcPixels = reinterpret_cast<Uint8*>(&myPixels[0]);

    IntRect Rect = SourceRect;
    if (Rect.GetWidth() == 0 || (Rect.GetHeight() == 0))
    {
        Rect.Left   = 0;
        Rect.Top    = 0;
        Rect.Right  = myWidth;
        Rect.Bottom = myHeight;
    }
    else
    {
        if (Rect.Left   < 0) Rect.Left = 0;
        if (Rect.Top    < 0) Rect.Top  = 0;
        if (Rect.Right  > static_cast<int>(myWidth))  Rect.Right  = myWidth;
        if (Rect.Bottom > static_cast<int>(myHeight)) Rect.Bottom = myHeight;
    }

    double scaleWidth =  (double)Width / (double)Rect.GetWidth();
    double scaleHeight = (double)Height / (double)Rect.GetHeight();

    int row = myWidth * 4;

    for(unsigned int cy = 0; cy < Height; cy++)
    {
        int nearestMatchY = (int)(cy / scaleHeight) * row;
        for(unsigned int cx = 0; cx < Width; cx++)
        {
            int nearestMatch = nearestMatchY + (int)(cx / scaleWidth) * 4;
            newimg.SetPixel(cx, cy, Color(SrcPixels[nearestMatch],
                                        SrcPixels[nearestMatch + 1],
                                        SrcPixels[nearestMatch + 2],
                                        SrcPixels[nearestMatch + 3]));
        }
    }
    return newimg;
}

////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////
void Image::DDrawText(int x, int y, int width, int height, const Unicode::Text& myText, const Color& Col)
{
    const Unicode::UTF32String& text = myText;
    if (text.empty())
        return;

    FT_Library library;
    if( FT_Init_FreeType(&library) ) {
        // Error
    }

    FT_Face face;

    FT_Error error = FT_New_Face(library, "C:\\WINDOWS\\Fonts\\arial.ttf", 0, &face);

    if( error == FT_Err_Unknown_File_Format ) {
        // ( "Error: Unknown font file format\n" );
    }
    else if( error ) {
        // ( "Error: Unknown error loading font\n" );
    }

    if( FT_Set_Pixel_Sizes( face, 80, 80 ) ) {
        // ( "Error: Could not set font pixel size\n" );
    }

    FT_Matrix matrix;


    matrix.xx = 0x10000;
    matrix.xy = 0;
    matrix.yx = 0;
    matrix.yy = 0x10000;

    height = myHeight;

    FT_Vector pen;

    x = 50;
    y = 50;

    pen.x = x << 6;
    pen.y = (height - y) << 6;

    int ix, iy, i, j, p, q, x_max, y_max, pixel;
    char color;

    FT_Bitmap *bitmap;
    FT_GlyphSlot slot = face->glyph;

    for(int n = 0; n < text.size(); n++) {
        FT_Set_Transform(face, &matrix, &pen);

        if(FT_Load_Char(face, text[n], FT_LOAD_RENDER)) {
            continue;
        }

        bitmap = &slot->bitmap;
        ix = slot->bitmap_left;
        iy = height - slot->bitmap_top;
        x_max = ix + bitmap->width;
        y_max = iy + bitmap->rows;

        Uint8* DstPixels = reinterpret_cast<Uint8*>(&myPixels[0]);

        for(i = ix, p = 0; i < x_max; i++, p++)  {
            for(j = iy, q = 0; j < y_max; j++, q++) {
                if(i < 0 || j < 0 || i >= width || j >= height) {
                    continue;
                }

                color = bitmap->buffer[q * bitmap->width + p];
                pixel = (j * height + i) * 4;
                DstPixels[pixel++] = Col.r;   // R
                DstPixels[pixel++] = Col.g;   // G
                DstPixels[pixel++] = Col.b;   // B
                DstPixels[pixel] |= color;   // A
            }
        }
        pen.x += slot->advance.x;
        pen.y += slot->advance.y;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(library);
}

////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////
/*void Image::DDrawText(int x, int y, int width, int height, const Unicode::Text& myText, const Color& Col)
{
    const Unicode::UTF32String& Text = myText;
    if (Text.empty())
        return;

    FT_Library library;
    FT_Init_FreeType(&library);

    FT_Face face;
    FT_New_Face(library, "C:\\WINDOWS\\Fonts\\arial.ttf", 0, &face);

    FT_GlyphSlot slot = face->glyph;
    //FT_UInt glyph_index;
    int pen_x, pen_y, n;

    FT_Set_Char_Size(face, 0, 20 * 64, 250, 250);
    //FT_Set_Pixel_Sizes(face, 0, 18);

    pen_x = 0;
    pen_y = 0;

    for(n = 0; n < 1; n++ ) {
        //glyph_index = FT_Get_Char_Index(face, text[n]);
        //FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER);

        FT_Load_Char(face, Text[n], FT_LOAD_RENDER);

        int a = slot->bitmap_top;
        int b = slot->bitmap_left;
        int c = slot->bitmap.rows;
        int d = slot->bitmap.width;


        //Uint8* DstPixels = reinterpret_cast<Uint8*>(&myPixels[0]) +
        //    (pen_x + slot->bitmap_left + (pen_y - slot->bitmap_top) * myWidth) * 4;

        Uint8* DstPixels = reinterpret_cast<Uint8*>(&myPixels[0]) + (pen_x + pen_y * myWidth) * 4;

        const Uint8* SrcPixels = reinterpret_cast<Uint8*>(&slot->bitmap.buffer[0]);

        for (int i = 0; i < slot->bitmap.rows; ++i)
        {
            for (int j = 0; j < slot->bitmap.width; ++j) {
                const Uint8* Src   = SrcPixels + j;
                Uint8*       Dst   = DstPixels + j * 4;

                Dst[0] = (Col.r * Col.a + Dst[0] * (255 - Col.a)) / 255;
                Dst[1] = (Col.g * Col.a + Dst[1] * (255 - Col.a)) / 255;
                Dst[2] = (Col.b * Col.a + Dst[2] * (255 - Col.a)) / 255;
                Dst[3] = (Dst[3] + Col.a) > 255 ? 255 : Dst[3] + Col.a;
            }
            DstPixels += myWidth * 4;
            SrcPixels += slot->bitmap.width;
        }

        pen_x += slot->advance.x >> 6;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(library);
}*/

} // namespace sf

