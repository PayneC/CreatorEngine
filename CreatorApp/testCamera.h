

#include <CreatorEngine.h>

class testCamera : public CrComponent
{
private:
	float a;
	float b;
	float bb;

	bool mouseButton3Press;
	bool mouseButton2Press;

public:
	testCamera();
	~testCamera();
	//void Start();
	void Update(double dt);
	//void LateUpdate(double dt);
	//void OnEnable();
	//void OnDisable();
	void OnDestroy();
	void EventCallback(GLint64 msg, GLint64 wParam, GLint64 lParam);
};
