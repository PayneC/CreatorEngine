#include "CrObject.h"
#include "CrEngine.h"

CrObject::CrObject()
:m_sUserNumber(0)
{
	AutoRelease();
}

CrObject::~CrObject()
{
}

void CrObject::Release()
{
	--m_sUserNumber;
	if (m_sUserNumber == 0)
		AutoRelease();
}
void CrObject::Retain()
{
	++m_sUserNumber;
}
void CrObject::AutoRelease()
{
	
	CrEngine::MemoryPool()->AddChunkToReleasePool(this);

}