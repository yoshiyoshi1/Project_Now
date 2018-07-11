#include "../main.h"

#include "Camera.h"

Camera::Camera()
{
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	m_vLook.Set(0.0f, 0.0f, 0.0f);
	m_vHead.Set(0.0f, 1.0f, 0.0f);
	
	m_vOffset.Set(0.0f, 1.0f, 0.0f);

	m_mRot.CreateRotateY(180);
	m_mRot.RotateX_Local(-45);
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

void Camera::SetView(CMatrix& mBase)
{
	m_vLook.TransformCoord(&m_vOffset, &mBase);
	m_vPos.TransformNormal(&CVector3(0, 0, m_DisToBase), &m_mRot);
	m_vPos.Add(&m_vLook);

	m_mView.SetLookAtLH(m_vPos, m_vLook, m_vHead);

	cdg.GetDev()->SetTransform(D3DTS_VIEW, &m_mView);
}
void Camera::SetView() 
{
	CMatrix mIden;
	mIden.CreateIdentity();

	SetView(mIden);
}
