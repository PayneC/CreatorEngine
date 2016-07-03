/*
CreatorEngine
Class CrMeshChunk : CrMemoryChunk
Payne
*/

#ifndef _CREATOR_MESHCHUNK_H
#define _CREATOR_MESHCHUNK_H

#include "CrDefine.h"
#include "CrObject.h"

class CrMeshChunk : public CrObject
{
	friend class CrMeshPool;
	friend class CrModel;
public:
	CrMeshChunk();
	~CrMeshChunk();

	EasyGet(GLuint, m_dVertexId, VertexId);

	EasyGet(GLuint, m_dVertexBufferId, VertexBufferId);
	EasyGet(GLuint, m_dNormalBufferId, NormalBufferId);
	EasyGet(GLuint, m_dElementBufferId, ElementBufferId);
	EasyGet(GLuint, m_dColorBufferId, ColorBufferId);
	EasyGet(GLuint, m_dUVBufferId, UVBufferId);
	
	EasyGet(size_t, m_dVertexSize, VertexSize);
	EasyGet(size_t, m_dNormalSize, NormalSize);
	EasyGet(size_t, m_dElementSize, ElementSize);
	EasyGet(size_t, m_dColorSize, ColorSize);
	EasyGet(size_t, m_dUVSize, UVSize);
	

private:

};


#endif