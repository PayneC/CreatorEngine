#include "test.h"

test::test()
	: a(0.f)
	, b(0.f)
	, bb(1.f)
{

}

test::~test()
{

}

void test::Update()
{
	float t = CrTime::Instance()->GetDelateTime();
	a += t * 1.f;

	if (a > 360.f)
		a = 0.f;

	b += t * bb;
	if (b > 2.f)
	{
		b = 2.f;
		bb = -bb;
	}
	else if (b < 0.1f)
	{
		b = 0.1f;
		bb = -bb;
	}

	m_pGameObject->GetTransform()->SetLocalRotation(glm::vec3(a));
	m_pGameObject->GetTransform()->SetLocalScale(glm::vec3(b));
}