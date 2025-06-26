#ifndef LIVRENDER_CAMERA_H
#define LIVRENDER_CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace LivRender{

class Camera
{
private:
	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraTarget;
	glm::vec3 m_CameraLookAt;
	glm::vec3 m_CameraUp;
	glm::vec3 m_CameraRight;
	glm::mat4 m_ViewMat4;
	glm::mat4 m_Proj;
	float m_Fovy;
	float m_Aspect;
	float m_Near;
	float m_Far;
public:
	Camera(glm::vec3 CameraPos = glm::vec3(0.0f,0.0f,0.0f), 
		glm::vec3 CameraTarget = glm::vec3(0.0f,0.0f,-1.0f),
		glm::vec3 CameraUp = glm::vec3(0.0f,1.0f,0.0f),
		float fovy = glm::radians(45.0f), float aspect = 800.0f/600.0f,
		float near = 0.1f, float far = 1000.0f);
	~Camera() {}
	inline glm::vec3 GetCameraPos() { return m_CameraPos; }
	inline glm::vec3 GetCameraTarget() { return m_CameraTarget; }
	inline glm::vec3 GetCameraUp() { return m_CameraUp; }
	inline glm::vec3 GetCameraRight() { return m_CameraRight; }
	inline glm::mat4 GetCameraMatrix() { return m_ViewMat4; }
	inline glm::mat4 GetCameraProjM() { return m_Proj; }

	inline void SetCameraPos(glm::vec3 Pos) {
		m_CameraPos = Pos;
		m_CameraLookAt = glm::normalize(m_CameraTarget - m_CameraPos);
		m_CameraRight = glm::normalize(glm::cross(m_CameraLookAt, m_CameraUp));
		m_CameraUp = glm::cross(m_CameraLookAt, m_CameraRight);
		m_ViewMat4 = glm::lookAt(m_CameraPos, m_CameraTarget, m_CameraUp);
	}
	inline void SetCameraTarget(glm::vec3 Target) { 
		m_CameraTarget = Target; 
		m_CameraLookAt = glm::normalize(m_CameraTarget - m_CameraPos);
		m_CameraRight = glm::normalize(glm::cross(m_CameraLookAt, m_CameraUp));
		m_CameraUp = glm::cross(m_CameraLookAt, m_CameraRight);
		m_ViewMat4 = glm::lookAt(m_CameraPos, m_CameraTarget, m_CameraUp);
	}
	inline void SetCameraUp(glm::vec3 Up) { 
		m_CameraUp = Up;
		m_CameraRight = glm::normalize(glm::cross(m_CameraLookAt, m_CameraUp));
		m_CameraUp = glm::cross(m_CameraLookAt, m_CameraRight);
		m_ViewMat4 = glm::lookAt(m_CameraPos, m_CameraTarget, m_CameraUp);
	}
	inline void SetCameraProjM(float fovy, float aspect, float near, float far)
	{
		m_Fovy = fovy;
		m_Aspect = aspect;
		m_Near = near;
		m_Far = far;
		m_Proj = glm::perspective(fovy, aspect, near, far);
	}
};

}      // LivRender
#endif // LIVRENDER_CAMERA_H