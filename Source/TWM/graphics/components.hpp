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
#ifndef __TWM_GRAPHICS_COMPONENTS__
#define __TWM_GRAPHICS_COMPONENTS__

#include "twm/core/component.hpp"
#include "twm/core/world.hpp"

namespace twm
{
  enum {
    kShape = 10100,
    kBoxShape,
    kSphereShape,
    kConeShape,
    kCylinderShape,
    kIndexedMeshShape,
    kNurbsSurfaceShape,
    kMaterial = 10200,
    kPlasticMaterial,
    kMetalMaterial,
    kStoneMaterial,
    kGlowMaterial,
    kLight = 10300,
    kPointLight,
    kSpotLight,
    kDirectionalLight,
    kCamera = 10400,
    kPerspectiveCamera,
    kViewSpecific = 10500,
    kSkybox,
    kPointSprites,
    kBillboards
  };

  /* TODO
      get accessors
  */

  void RegisterGraphicsComponentTypes( World* world );

  class BoxShape : public ComponentBase< struct BoxShapeData, kBoxShape >
  {
  public:
    BoxShape() {}
    BoxShape( const Component& c ) : ComponentBase(c) {}
  public:
    void SetSize( float x, float y, float z );
  };

  class SphereShape : public ComponentBase< struct SphereShapeData, kSphereShape >
  {
  public:
    SphereShape() {}
    SphereShape( const Component& c ) : ComponentBase(c) {}
  public:
    void SetRadius( float size );
  };

  class ConeShape : public ComponentBase< struct ConeShapeData, kConeShape >
  {
  public:
    ConeShape() {}
    ConeShape( const Component& c ) : ComponentBase(c) {}
  public:
    void SetHeight( float size );
    void SetRadius( float size );
  };

  class CylinderShape : public ComponentBase< struct CylinderShapeData, kCylinderShape >
  {
  public:
    CylinderShape() {}
    CylinderShape( const Component& c ) : ComponentBase(c) {}
  public:
    void SetHeight( float size );
    void SetRadius( float size );
  };

  class IndexedMeshShape : public ComponentBase< struct IndexedMeshShapeData, kIndexedMeshShape >
  {
  public:
    IndexedMeshShape() {}
    IndexedMeshShape( const Component& c ) : ComponentBase(c) {}
  };

  class NurbsSurfaceShape : public ComponentBase< struct NurbsSurfaceShapeData, kNurbsSurfaceShape >
  {
  public:
    NurbsSurfaceShape() {}
    NurbsSurfaceShape( const Component& c ) : ComponentBase(c) {}
  };

  class PlasticMaterial : public ComponentBase< struct PlasticMaterialData, kPlasticMaterial >
  {
  public:
    PlasticMaterial() {}
    PlasticMaterial( const Component& c ) : ComponentBase(c) {}
  public:
    void SetColour( float r, float g, float b );
    void SetColour( const Colour& c ) { SetColour(c.r,c.g,c.b); };
    void SetShininess( float s );
    void SetTexture( const std::string& );
  };

  class MetalMaterial : public ComponentBase< struct MetalMaterialData, kMetalMaterial >
  {
  public:
    MetalMaterial() {}
    MetalMaterial( const Component& c ) : ComponentBase(c) {}
  public:
    void SetColour( float r, float g, float b );
    void SetColour( const Colour& c ) { SetColour(c.r,c.g,c.b); };
    void SetShininess( float s );
    void SetTexture( const std::string& );
  };

  class StoneMaterial : public ComponentBase< struct StoneMaterialData, kStoneMaterial >
  {
  public:
    StoneMaterial() {}
    StoneMaterial( const Component& c ) : ComponentBase(c) {}
  public:
    void SetColour( float r, float g, float b );
    void SetColour( const Colour& c ) { SetColour(c.r,c.g,c.b); };
    void SetTexture( const std::string& );
  };

  class GlowMaterial : public ComponentBase< struct GlowMaterialData, kGlowMaterial >
  {
  public:
    GlowMaterial() {}
    GlowMaterial( const Component& c ) : ComponentBase(c) {}
  public:
    void SetColour( float r, float g, float b );
    void SetColour( const Colour& c ) { SetColour(c.r,c.g,c.b); };
    void SetTexture( const std::string& );
  };

  class PointLight : public ComponentBase< struct PointLightData, kPointLight >
  {
  public:
    PointLight() {}
    PointLight( const Component& c ) : ComponentBase(c) {}
  public:
    void SetColour( float r, float g, float b );
    void SetColour( const Colour& c ) { SetColour(c.r,c.g,c.b); };
    void SetIntensity( float i );
    void SetAttenuation( float linear, float quadratic );
  };

  class SpotLight : public ComponentBase< struct SpotLightData, kSpotLight >
  {
  public:
    SpotLight() {}
    SpotLight( const Component& c ) : ComponentBase(c) {}
  public:
    void SetColour( float r, float g, float b );
    void SetColour( const Colour& c ) { SetColour(c.r,c.g,c.b); };
    void SetIntensity( float i );
    void SetAttenuation( float linear, float quadratic );
    void SetConeAngle( float a );
  };

  class DirectionalLight : public ComponentBase< struct DirectionalLightData, kDirectionalLight >
  {
  public:
    DirectionalLight() {}
    DirectionalLight( const Component& c ) : ComponentBase(c) {}
  public:
    void SetColour( float r, float g, float b );
    void SetColour( const Colour& c ) { SetColour(c.r,c.g,c.b); };
    void SetIntensity( float i );
  };

  class PerspectiveCamera : public ComponentBase< struct PerspectiveCameraData, kPerspectiveCamera >
  {
  public:
    PerspectiveCamera() {}
    PerspectiveCamera( const Component& c ) : ComponentBase(c) {}
  public:
    void SetFieldOfView( float a );
    void SetClippingPlanes( float n, float f );
  };

  class Skybox : public ComponentBase< struct SkyboxData, kSkybox >
  {
  public:
    Skybox() {}
    Skybox( const Component& c ) : ComponentBase(c) {}
  public:
    void SetTexturePosX( const std::string& );
    void SetTextureNegX( const std::string& );
    void SetTexturePosY( const std::string& );
    void SetTextureNegY( const std::string& );
    void SetTexturePosZ( const std::string& );
    void SetTextureNegZ( const std::string& );
  };

  class PointSprites : public ComponentBase< struct PointSpritesData, kPointSprites >
  {
  public:
    enum BlendMode { kBlendAdd, kBlendLerp };
  public:
    PointSprites() {}
    PointSprites( const Component& c ) : ComponentBase(c) {}
  public:
    void SetPositions( const Vector* ptr, unsigned int stride, unsigned int count );
    void SetColours( const ColourAlpha* ptr, unsigned int stride, unsigned int count );
    void SetColours( float r, float g, float b, float a );
    void SetColours( const ColourAlpha& c ) { SetColours( c.r, c.g, c.b, c.a ); }
    void SetSizes( const float* ptr, unsigned int stride, unsigned int count );
    void SetSizes( float size );
    void SetTexture( const std::string& );
    void SetBlendMode( BlendMode );
  };

  // This component should be attached to the Entity with the Camera attached to it.
  class Billboards : public ComponentBase< struct BillboardsData, kBillboards >
  {
  public:
    enum BlendMode { kBlendAdd, kBlendLerp };
  public:
    Billboards() {}
    Billboards( const Component& c ) : ComponentBase(c) {}
  public:
    // Assigns the vertex data for the billboards.
    // Each vertex attribute (position, colour, and texture coordinate) has a pointer
    // and stride associated with it.  The pointer is to the first attribute value (i.e.
    // the first vertex position), stride provides the number of bytes between the first
    // attribute value and the second value in your array.
    // The vertex data will be interpretted as a list of quads (i.e. four sequential vertices
    // in the data will become one quad).  You must provide all the vertex attribute data.
    // The position data will be interpretted to be in camera space.
    // The texture coordinate data will be interpretted as Float2 data.
    // The count argument indicates how many vertices are in the data arrays provided.
    void SetVertices( const Vector* position_ptr, unsigned int position_stride,
                      const ColourAlpha* colour_ptr, unsigned int colour_stride,
                      const float* texcoord_ptr, unsigned int texcoord_stride,
                      unsigned int count );
    void SetTexture( const std::string& );
    void SetBlendMode( BlendMode );
  };
}

#endif
