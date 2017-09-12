

#include "CreatorEngine.h"

class testCamera : public CrComponent
{
private:
	float a;
	float b;
	float bb;
public:
	testCamera();
	~testCamera();
	void Awake();
	void Update();
	void Destroy();
	void EventCallback(GLint64 msg, GLint64 wParam, GLint64 lParam);
};
