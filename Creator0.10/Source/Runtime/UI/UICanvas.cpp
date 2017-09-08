#include "UICanvas.h"
#include "CrEngine.h"

UICanvas::UICanvas()
	:m_m4Projection(1.0)
{
	m_sName = "UICanvas";
	CrEngine::Instance()->AddCanvas(this);

	m_size = Vector2(1366, 768);
}

UICanvas::~UICanvas()
{
	CrEngine::Instance()->RemoveCanvas(this);
}

void UICanvas::Render()
{
	_Render(this);
}

void UICanvas::_Render(CrGameObject* pGameObject)
{
	//std::vector<UIWidget *>::iterator iter = m_pChildrenWidget.begin();
	//std::vector<UIWidget *>::iterator iterEnd = m_pChildrenWidget.end();
	//
	//UIWidget * widget = NULL;

	//glMatrixMode(GL_PROJECTION);
	//// 重置当前指定的矩阵为单位矩阵
	//glLoadIdentity;
	//// 指定OpenGL在此区域内绘图
	//glViewport(0, 0, 1366, 768);
	//// 设置世界坐标系的范围
	//glOrtho(0, 1366, 768, 0, 0, 1000);
	//// 将矩阵变换对象切换为模型视图变换
	//glMatrixMode(GL_MODELVIEW);

	//for (; iter != iterEnd; ++iter)
	//{
	//	widget = (*iter);
	//	if (widget)
	//	{
	//		widget->Draw();
	//	}
	//}

	// 重置当前指定的矩阵为单位矩阵
	//glLoadIdentity;

	if (pGameObject == NULL || !pGameObject->GetActive())
		return;
	
	CrMeshRender * meshRender = pGameObject->GetMeshRender();
	CrTransform * transform = pGameObject->GetTransform();
	if (meshRender != NULL && transform != NULL)
	{
		//glm::mat4 m = glm::ortho(0, 16, 0, 9);
		glm::mat4 m = glm::mat4(1.0);
		meshRender->Draw(m, glm::vec3(), m, m);
	}
	
	std::vector<CrGameObject * > gameobjects = pGameObject->GetChildren();
	
	std::vector<CrGameObject * >::iterator iter = gameobjects.begin();
	std::vector<CrGameObject * >::iterator iterEnd = gameobjects.end();
	
	CrGameObject * gameobject = NULL;
	for (; iter != iterEnd; ++iter)
	{
		gameobject = (*iter);
		_Render(gameobject);
	}
}
