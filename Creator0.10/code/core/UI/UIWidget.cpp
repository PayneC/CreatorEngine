#include <UI\UIWidget.h>

UIWidget::UIWidget()
	:m_size()
{
}

UIWidget::~UIWidget()
{
	
}


void UIWidget::AddChild(UIWidget * pNode)
{
	CrGameObject::AddChild(pNode);
	m_pChildrenWidget.push_back(pNode);
}
