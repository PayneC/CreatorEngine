/*
CreatorEngine
Class UIWidget
Payne
*/

#ifndef _CREATOR_UI_WIDGET_H
#define _CREATOR_UI_WIDGET_H

#include <CrGameObject.h>

class UIWidget : public CrGameObject
{
public:
	UIWidget();
	~UIWidget();

public:
	void AddChild(UIWidget * pNode);

protected:
	Vector2 m_size;
	
private:
	std::vector<UIWidget *> m_pChildrenWidget;
};

#endif