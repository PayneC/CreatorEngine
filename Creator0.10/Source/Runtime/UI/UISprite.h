/*
CreatorEngine
Class UISprite
Payne
*/

#ifndef _CREATOR_UI_SPRITE_H
#define _CREATOR_UI_SPRITE_H

#include <UI\UIWidget.h>

class UISprite : public UIWidget
{
public:
	UISprite();
	~UISprite();

protected:
	Vector2 m_pixel;
};

#endif