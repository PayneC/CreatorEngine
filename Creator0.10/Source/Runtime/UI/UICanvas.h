/*
CreatorEngine
Class CrCanvas
Payne
*/

#ifndef _CREATOR_UI_CANVAS_H
#define _CREATOR_UI_CANVAS_H

#include <CrGameObject.h>
#include <UI\UIWidget.h>

class UICanvas : public UIWidget
{
public:
	UICanvas();
	~UICanvas();

	Vector2 m_referenceResolution;	//�ο��ֱ���
	Vector2 m_devicesResolution;	//�豸�ֱ���

	void Render();
	void _Render(CrGameObject* pGameObject);
private:
	glm::mat4 m_m4Projection;
};

#endif