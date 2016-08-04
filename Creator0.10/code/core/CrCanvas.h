/*
CreatorEngine
Class CrCanvas
Payne
*/

#ifndef _CREATOR_CANVAS_H
#define _CREATOR_CANVAS_H

#include <CrGameObject.h>
#include <UI\UIWidget.h>

class CrCanvas : public UIWidget
{
public:
	CrCanvas();
	~CrCanvas();

	Vector2 m_pixel;
	Vector2 m_referenceResolution;

	void Render();
	void _Render(CrGameObject * pGameObject);
};

#endif