/*
CreatorEngine
Class UIWidget
Payne
*/

#ifndef _CREATOR_UI_WIDGET_H
#define _CREATOR_UI_WIDGET_H

#include <CrGameObject.h>
#include <rttr/registration.h>
using namespace rttr;

class DLL_ClASS UIWidget : public CrGameObject
{
public:
	UIWidget();
	~UIWidget();

public:
	void AddChild(UIWidget * pNode);
	void CalculateFinalRect(UIWidget * parent);
protected:
	Vector2 m_size;
	Vector2 m_anchorMin;
	Vector2 m_anchorMax;
	Vector2 m_pivot;

	Vector2 m_finalPosition;
	Vector2 m_finalSize;

protected:
	std::vector<UIWidget *> m_pChildrenWidget;
};

RTTR_REGISTRATION
{
	registration::class_<UIWidget>("UIWidget")
	.constructor<>()
	.property("m_objects", &UIWidget::m_objects)
	.method("AddChild", &UIWidget::AddChild);
}

#endif