/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/graphics/drawable/MeshDrawable.h>
#include <algorithm>

#include "../../cograconfig.h"

namespace
{
constexpr cogra::uint32 invalidVertexObjectId = static_cast<cogra::uint32>(-1);
}

namespace cogra
{
namespace graphics
{
namespace drawable
{
MeshDrawable::MeshDrawable()
  : m_vertexArrayObjectID(invalidVertexObjectId)
  , m_bufferIDs()
  , m_elementArrayBufferCount(0)
  , m_numVertices(0)
  , m_primitiveType(convertToGLenum(MeshDrawable::Points))
  , m_nPatchVertices(0)
{

}

MeshDrawable::MeshDrawable(const uint32 * const indexBuffer, size_t nIndices, PrimitiveType primtiveType, size_t nVertices, const std::vector<VertexAttributeTypeInfo>& vertexAttributeInfo)
  : m_vertexArrayObjectID(invalidVertexObjectId)
  , m_primitiveType(convertToGLenum(primtiveType))
  , m_nPatchVertices(0)

{
  MeshDrawable_impl(indexBuffer, nIndices, nVertices, vertexAttributeInfo);
}

MeshDrawable::MeshDrawable(MeshDrawable&& other)
{
  m_vertexArrayObjectID = other.m_vertexArrayObjectID;
  m_bufferIDs = std::move(other.m_bufferIDs);
  m_elementArrayBufferCount = other.m_elementArrayBufferCount;
  m_numVertices = other.m_numVertices;
  m_primitiveType = other.m_primitiveType;
  m_nPatchVertices = other.m_nPatchVertices;

  other.m_vertexArrayObjectID = invalidVertexObjectId;
  other.m_bufferIDs.clear();
}

MeshDrawable& MeshDrawable::operator=(MeshDrawable&& other)
{
  m_vertexArrayObjectID = other.m_vertexArrayObjectID;
  m_bufferIDs = std::move(other.m_bufferIDs);
  m_elementArrayBufferCount = other.m_elementArrayBufferCount;
  m_numVertices = other.m_numVertices;
  m_primitiveType = other.m_primitiveType;
  m_nPatchVertices = other.m_nPatchVertices;

  other.m_vertexArrayObjectID = invalidVertexObjectId;
  other.m_bufferIDs.clear();
  return *this;
}

void MeshDrawable::setPrimitiveType(PrimitiveType primitiveType)
{
  m_primitiveType = convertToGLenum(primitiveType);
}

MeshDrawable::PrimitiveType MeshDrawable::getPrimitiveType() const
{
  return convertFromGLenum(m_primitiveType);
}

MeshDrawable::~MeshDrawable()
{
  if(m_vertexArrayObjectID != invalidVertexObjectId)
  {
    GL_SAFE_CALL_NO_THROW(glBindVertexArray(0));
    GL_SAFE_CALL_NO_THROW(glDeleteBuffers(static_cast<GLsizei>(getNumberOfBuffers()),
                                          m_bufferIDs.data()));
    GL_SAFE_CALL_NO_THROW(glDeleteVertexArrays(1, &m_vertexArrayObjectID));
  }
}

size_t MeshDrawable::getNumberOfBuffers() const
{
  return m_bufferIDs.size();
}

void MeshDrawable::draw() const
{
  if(m_elementArrayBufferCount == 0 && m_numVertices == 0)
  {
    return;
  }

  if(m_primitiveType == GL_PATCHES)
  {
    GL_SAFE_CALL(glPatchParameteri(GL_PATCH_VERTICES, m_nPatchVertices));
  }

  GL_SAFE_CALL(glBindVertexArray(m_vertexArrayObjectID));
  if(m_elementArrayBufferCount != 0)
  {
    GL_SAFE_CALL(glDrawElements(m_primitiveType, static_cast<GLsizei>(m_elementArrayBufferCount), GL_UNSIGNED_INT, nullptr));
  }
  else
  {
    GL_SAFE_CALL(glDrawArrays(m_primitiveType, 0, static_cast<GLsizei>(m_numVertices)));
  }

  GL_SAFE_CALL(glBindVertexArray(0));
}

void MeshDrawable::draw(size_t first, size_t count) const
{
  if(count == 0)
  {
    return;
  }

  GL_SAFE_CALL(glBindVertexArray(m_vertexArrayObjectID));
  if(m_elementArrayBufferCount != 0)
  {
    if(first + count > m_elementArrayBufferCount)
    {
      count = m_elementArrayBufferCount - first;
    }
    GL_SAFE_CALL(glDrawElements(m_primitiveType, static_cast<GLsizei>(count), GL_UNSIGNED_INT, reinterpret_cast<const void*>(first * sizeof(uint32))));
  }
  else
  {
    if(first + count > m_numVertices)
    {
      count = m_numVertices - first;
    }

    GL_SAFE_CALL(glDrawArrays(m_primitiveType, static_cast<int32>(first), static_cast<GLsizei>(count)));
  }

  GL_SAFE_CALL(glBindVertexArray(0));
}

size_t MeshDrawable::getNumPrimitives() const
{
  switch(m_primitiveType)
  {
    case MeshDrawable::PrimitiveType::Points:                    return m_elementArrayBufferCount;
    case MeshDrawable::PrimitiveType::LineStrip:                 return m_elementArrayBufferCount - 1;
    case MeshDrawable::PrimitiveType::LineLoop:                  return m_elementArrayBufferCount;
    case MeshDrawable::PrimitiveType::Lines:                     return m_elementArrayBufferCount / 2;
    case MeshDrawable::PrimitiveType::LineStripAdjacency:        return m_elementArrayBufferCount + 3;
    case MeshDrawable::PrimitiveType::LinesAdjacency:            return m_elementArrayBufferCount / 4;
    case MeshDrawable::PrimitiveType::TriangleStrip:             return m_elementArrayBufferCount - 2;
    case MeshDrawable::PrimitiveType::TriangleFan:               return m_elementArrayBufferCount - 2;
    case MeshDrawable::PrimitiveType::Triangles:                 return m_elementArrayBufferCount / 3;
    case MeshDrawable::PrimitiveType::TriangleStripAdjacency:    return (m_elementArrayBufferCount - 4) / 2;
    case MeshDrawable::PrimitiveType::TrianglesAdjacency:        return m_elementArrayBufferCount / 6;
    case MeshDrawable::PrimitiveType::Patches:                   return m_elementArrayBufferCount / m_nPatchVertices;
    default:return m_elementArrayBufferCount;
  }
}

size_t MeshDrawable::getNumVertices() const
{
  return m_numVertices;
}

void MeshDrawable::MeshDrawable_impl(const uint32 * const indexBuffer, size_t nIndices, size_t nVertices, const std::vector<VertexAttributeTypeInfo>& vertexAttributeInfo)
{
  m_elementArrayBufferCount = nIndices;
  m_numVertices = nVertices;
  const bool hasIndexBuffer = (indexBuffer != 0);

  const auto numElementArrayBuffers = hasIndexBuffer == true ? 1 : 0;
  m_bufferIDs.resize(vertexAttributeInfo.size() + numElementArrayBuffers);
#ifdef COGRA_OPENGL_45
  GL_SAFE_CALL(glCreateVertexArrays(1, &m_vertexArrayObjectID));
  GL_SAFE_CALL(glCreateBuffers(static_cast<GLsizei>(getNumberOfBuffers()), m_bufferIDs.data()));
  GL_SAFE_CALL(glBindVertexArray(m_vertexArrayObjectID));
#else
  GL_SAFE_CALL(glGenVertexArrays(1, &m_vertexArrayObjectID));
  GL_SAFE_CALL(glBindVertexArray(m_vertexArrayObjectID));
  GL_SAFE_CALL(glGenBuffers(static_cast<GLsizei>(getNumberOfBuffers()), m_bufferIDs.data()));
#endif
  // Attribute buffers
  for(GLuint aIdx = 0; aIdx < vertexAttributeInfo.size(); aIdx++)
  {
    const GLuint bindingIndex = aIdx;

#ifdef COGRA_OPENGL_45
    GL_SAFE_CALL(glNamedBufferStorage(m_bufferIDs[aIdx],
                                      nVertices * vertexAttributeInfo[aIdx].sizeInBytes,
                                      vertexAttributeInfo[aIdx].data, 0));
    GL_SAFE_CALL(glVertexArrayVertexBuffer(m_vertexArrayObjectID, aIdx,
                                           m_bufferIDs[aIdx], 0,
                                           vertexAttributeInfo[aIdx].sizeInBytes));

    GL_SAFE_CALL(glEnableVertexArrayAttrib(m_vertexArrayObjectID, aIdx));

    if(vertexAttributeInfo[aIdx].numberOfComponents > 1 && vertexAttributeInfo[aIdx].enumType == GL_UNSIGNED_INT)
    {
      GL_SAFE_CALL(glVertexArrayAttribIFormat(m_vertexArrayObjectID, aIdx,
                                              vertexAttributeInfo[aIdx].numberOfComponents,
                                              vertexAttributeInfo[aIdx].enumType, 0));
    }
    else
    {
      GL_SAFE_CALL(glVertexArrayAttribFormat(m_vertexArrayObjectID, aIdx,
                                             vertexAttributeInfo[aIdx].numberOfComponents,
                                             vertexAttributeInfo[aIdx].enumType, GL_FALSE, 0));
    }

    GL_SAFE_CALL(glVertexArrayAttribBinding(m_vertexArrayObjectID, aIdx,
                                            bindingIndex));
#else
    GL_SAFE_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_bufferIDs[aIdx]));
    GL_SAFE_CALL(glBufferData(GL_ARRAY_BUFFER, nVertices * vertexAttributeInfo[aIdx].sizeInBytes, vertexAttributeInfo[aIdx].data, GL_STATIC_DRAW));

    GL_SAFE_CALL(glEnableVertexAttribArray(aIdx));

    if(vertexAttributeInfo[aIdx].enumType == GL_BYTE || vertexAttributeInfo[aIdx].enumType == GL_UNSIGNED_BYTE ||
       vertexAttributeInfo[aIdx].enumType == GL_INT || vertexAttributeInfo[aIdx].enumType == GL_UNSIGNED_INT ||
       vertexAttributeInfo[aIdx].enumType == GL_SHORT || vertexAttributeInfo[aIdx].enumType == GL_UNSIGNED_SHORT)
    {
      if(vertexAttributeInfo[aIdx].normalized)
      {
        GL_SAFE_CALL(glVertexAttribPointer(aIdx, vertexAttributeInfo[aIdx].numberOfComponents, vertexAttributeInfo[aIdx].enumType, GL_TRUE, 0, nullptr));
      }
      else
      {
        GL_SAFE_CALL(glVertexAttribIPointer(aIdx, vertexAttributeInfo[aIdx].numberOfComponents, vertexAttributeInfo[aIdx].enumType, 0, nullptr));
      }
    }
    else
    {
      GL_SAFE_CALL(glVertexAttribPointer(aIdx, vertexAttributeInfo[aIdx].numberOfComponents, vertexAttributeInfo[aIdx].enumType, GL_FALSE, 0, nullptr));
    }

#endif
  }
  // Element array buffer.
  if(hasIndexBuffer)
  {
    const auto elementArrayBufferIdx = vertexAttributeInfo.size();
#ifdef COGRA_OPENGL_45            
    GL_SAFE_CALL(glVertexArrayElementBuffer(m_vertexArrayObjectID, m_bufferIDs[elementArrayBufferIdx]));
    GL_SAFE_CALL(glNamedBufferStorage(m_bufferIDs[elementArrayBufferIdx], nIndices * sizeof(GLint),
                                      indexBuffer, 0));
#else
    GL_SAFE_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferIDs[elementArrayBufferIdx]));
    GL_SAFE_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices * sizeof(GLint), indexBuffer, GL_STATIC_DRAW))
#endif
  }
  else
  {
#ifdef COGRA_OPENGL_45   
    GL_SAFE_CALL(glVertexArrayElementBuffer(m_vertexArrayObjectID, 0));
#else
    GL_SAFE_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
#endif
  }

#ifdef COGRA_OPENGL_45
#else
  GL_SAFE_CALL(glBindVertexArray(0));
#endif
  }

GLenum MeshDrawable::convertToGLenum(PrimitiveType p)
{
  switch(p)
  {
    case MeshDrawable::PrimitiveType::Points:                    return GL_POINTS;
    case MeshDrawable::PrimitiveType::LineStrip:                 return GL_LINE_STRIP;
    case MeshDrawable::PrimitiveType::LineLoop:                  return GL_LINE_LOOP;
    case MeshDrawable::PrimitiveType::Lines:                     return GL_LINES;
    case MeshDrawable::PrimitiveType::LineStripAdjacency:        return GL_LINE_STRIP_ADJACENCY;
    case MeshDrawable::PrimitiveType::LinesAdjacency:            return GL_LINES_ADJACENCY;
    case MeshDrawable::PrimitiveType::TriangleStrip:             return GL_TRIANGLE_STRIP;
    case MeshDrawable::PrimitiveType::TriangleFan:               return GL_TRIANGLE_FAN;
    case MeshDrawable::PrimitiveType::Triangles:                 return GL_TRIANGLES;
    case MeshDrawable::PrimitiveType::TriangleStripAdjacency:    return GL_TRIANGLE_STRIP_ADJACENCY;
    case MeshDrawable::PrimitiveType::TrianglesAdjacency:        return GL_TRIANGLES_ADJACENCY;
    case MeshDrawable::PrimitiveType::Patches:                   return GL_PATCHES;
    default:
      return GL_TRIANGLES;
  }
}

MeshDrawable::PrimitiveType MeshDrawable::convertFromGLenum(GLenum p)
{
  switch(p)
  {
    case GL_POINTS:return MeshDrawable::PrimitiveType::Points;
    case GL_LINE_STRIP:return MeshDrawable::PrimitiveType::LineStrip;
    case GL_LINE_LOOP:return MeshDrawable::PrimitiveType::LineLoop;
    case GL_LINES:return MeshDrawable::PrimitiveType::Lines;
    case GL_LINE_STRIP_ADJACENCY:return MeshDrawable::PrimitiveType::LineStripAdjacency;
    case GL_LINES_ADJACENCY:return MeshDrawable::PrimitiveType::LinesAdjacency;
    case GL_TRIANGLE_STRIP:return MeshDrawable::PrimitiveType::TriangleStrip;
    case GL_TRIANGLE_FAN:return MeshDrawable::PrimitiveType::TriangleFan;
    case GL_TRIANGLES:return MeshDrawable::PrimitiveType::Triangles;
    case GL_TRIANGLE_STRIP_ADJACENCY:return MeshDrawable::PrimitiveType::TriangleStripAdjacency;
    case GL_TRIANGLES_ADJACENCY:return MeshDrawable::PrimitiveType::TrianglesAdjacency;
    case GL_PATCHES:return MeshDrawable::PrimitiveType::Patches;
    default:
      return MeshDrawable::PrimitiveType::Triangles;
  }
}




}
}
}
