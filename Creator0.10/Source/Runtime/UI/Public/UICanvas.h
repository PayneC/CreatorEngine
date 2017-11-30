/*
CreatorEngine
Class CrCanvas
Payne
*/

#ifndef _CREATOR_UI_CANVAS_H
#define _CREATOR_UI_CANVAS_H

#include <UIWidget.h>

class DLL_ClASS UICanvas : public UIWidget
{
private:
	static std::list<UICanvas*> m_pCanvasList;
public:
	static std::list<UICanvas*> AllCanvas();
public:
	UICanvas();
	~UICanvas();

	Vector2 m_referenceResolution;	//参考分辨率
	Vector2 m_devicesResolution;	//设备分辨率

	void Render();
	void _Render(CrGameObject* pGameObject);
private:
	glm::mat4 m_m4Projection;
};

#endif