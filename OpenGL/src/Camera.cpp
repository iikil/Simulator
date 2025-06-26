#include "Camera.h"

namespace LivRender{

Camera::Camera(glm::vec3 CameraPos, glm::vec3 CameraTarget, glm::vec3 CameraUp, float fovy, float aspect, float near, float far)
	:m_CameraPos(CameraPos),m_CameraTarget(CameraTarget),m_CameraLookAt(glm::normalize(CameraTarget-CameraPos)),
	m_CameraUp(glm::vec3(1.0)),m_CameraRight(glm::vec3(1.0)),m_ViewMat4(glm::mat4(1.0)),m_Fovy(fovy),m_Aspect(aspect),m_Near(near),m_Far(far)
{
	m_CameraRight = glm::normalize(glm::cross(m_CameraLookAt, CameraUp));
	m_CameraUp = glm::cross(m_CameraLookAt, m_CameraRight);
	m_ViewMat4 = glm::lookAt(m_CameraPos, m_CameraTarget, m_CameraUp);
	m_Proj = glm::perspective(m_Fovy, m_Aspect, m_Near, m_Far);
}

} // LivRender