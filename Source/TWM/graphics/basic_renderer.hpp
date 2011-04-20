/*
Copyright (c) 2010 Tyrone Davison, Teesside University

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once
#ifndef __TWM_GRAPHICS_BASIC_RENDERER__
#define __TWM_GRAPHICS_BASIC_RENDERER__

#include "twm/windows/renderer.hpp"
#include "twm/core/types.hpp"
#include <boost/unordered_map.hpp>
#include <vector>

struct IDirect3D9;
struct IDirect3DDevice9;
struct IDirect3DTexture9;
struct _D3DPRESENT_PARAMETERS_;

namespace twm
{
  class BasicRenderer : public IRenderer
  {
  public:
    BasicRenderer();
    ~BasicRenderer();
  public: // IRenderer implementation
    bool Init( struct HWND__* );
    void DeInit();
    void Resize( unsigned int width, unsigned int height );
    void Draw( IWorldUpdate*, IMessageIterator* );
  private:
    template< ComponentType T, class FN > void DrawShapes( IWorldUpdate* );
    static Matrix Invert( const Matrix& );
    static Matrix Transpose( const Matrix& );
  private:
    void OnDeviceLost();
    void OnDeviceReset();
    IDirect3DTexture9* GetTexture( const std::string& );
    void DrawSplash();
  private:
    bool _lost;
    IDirect3D9* _d3d;
    IDirect3DDevice9* _dev;
    _D3DPRESENT_PARAMETERS_* _pp;
    class SkyboxMesh *_skybox;
    boost::unordered_map< ComponentId, class Mesh* > _meshes;
    boost::unordered_map< ComponentId, class Sprites* > _sprites;
    boost::unordered_map< ComponentId, class QuadSprites* > _billboards;
    boost::unordered_map< std::string, IDirect3DTexture9* > _textures;
  };
}

#endif
