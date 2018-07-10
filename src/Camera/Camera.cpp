#include "../main.h"

#include "Camera.h"

Camera::Camera()
{
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	m_vLook.Set(0.0f, 0.0f, 0.0f);
	m_vHead.Set(0.0f, 1.0f, 0.0f);

	m_mRot.CreateRotateX(30);
	m_mRot.RotateY_Local(90);
}

Camera::~Camera()
{

}

void Camera::Update() 
{
	// ƒJƒƒ‰‚Ì‘€ì‚È‚Ç

}

void Camera::SetProj()
{
	m_mProj.SetPerspectiveFovLH(60, (float)cdg.GetRezoW() / (float)cdg.GetRezoH());
	
	cdg.GetDev()->SetTransform(D3DTS_PROJECTION, &m_mProj);
}

void Camera::SetView(CMatrix mBase)
{
	m_vLook.TransformCoord(&CVector3(0, 0, 0),&mBase);
	m_vPos.TransformNormal(&CVector3(0, 1, 0), &m_mRot);
	m_vPos = m_vPos + m_vLook;

	m_mView.SetLookAtLH(m_vPos, m_vLook, m_vHead);

	cdg.GetDev()->SetTransform(D3DTS_VIEW, &m_mView);
}
void Camera::SetView() 
{
	CMatrix mIden;
	mIden.CreateIdentity();

	SetView(mIden);
}
