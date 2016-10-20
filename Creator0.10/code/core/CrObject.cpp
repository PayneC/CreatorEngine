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
	
	CrMemoryPool::Instance()->AddChunkToReleasePool(this);

}

void CrObject::AddEventListen(EventFunc func)
{
	CrEvent::Instance()->AddListen(this, func);
}

void CrObject::RemoveEventListen(EventFunc func)
{
	CrEvent::Instance()->RemoveListen(this, func);
}