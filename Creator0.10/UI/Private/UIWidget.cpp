#include <UIWidget.h>
#include <CrTransform.h>

UIWidget::UIWidget()
	:m_size(100, 100)
	, m_anchorMin(0.5, 0.5)
	, m_anchorMax(0.5, 0.5)
	, m_pivot(0.5, 0.5)
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

void UIWidget::CalculateFinalRect(UIWidget * parent)
{
	if (parent == NULL)
	{
		m_finalPosition.x = m_kTransform->GetLocalPosition().x - m_size.x * m_pivot.x;
		m_finalSize.x = m_size.x;
		m_finalPosition.y = m_kTransform->GetLocalPosition().y - m_size.y * m_pivot.y;
		m_finalSize.y = m_size.y;
	}
	else
	{
		if (m_anchorMin.x == m_anchorMax.x)
		{
			m_finalPosition.x = parent->m_size.x * m_anchorMin.x + m_kTransform->GetLocalPosition().x - m_size.x * m_pivot.x;
			m_finalSize.x = m_size.x;
		}
		else
		{
			m_finalPosition.x = parent->m_finalPosition.x + m_size.x;
			m_finalSize.x = (parent->m_finalSize.x - m_size.x) - m_finalPosition.x;
		}

		if (m_anchorMin.y == m_anchorMax.y)
		{
			m_finalPosition.y = parent->m_size.y * m_anchorMin.y + m_kTransform->GetLocalPosition().y - m_size.y * m_pivot.y;
			m_finalSize.y = m_size.y;
		}
		else
		{
			m_finalPosition.y = parent->m_finalPosition.y + m_size.y;
			m_finalSize.y = (parent->m_finalSize.y - m_size.y) - m_finalPosition.y;
		}
	}
}