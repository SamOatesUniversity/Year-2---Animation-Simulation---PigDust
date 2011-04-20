#pragma once
#ifndef __TWM_GRAPHICS_FILE_IMPORT__
#define __TWM_GRAPHICS_FILE_IMPORT__

#include <string>
#include <vector>

namespace twm
{
  class IWorldUpdate;
  class IndexedMeshShape;

  unsigned int ImportMeshes( IWorldUpdate* world, const std::string& filename, std::vector< IndexedMeshShape >& out_meshes );
}

#endif
