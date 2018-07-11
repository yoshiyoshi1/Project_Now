#include "../main.h"

#include "Camera.h"

Camera::Camera()
{
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	m_vLook.Set(0.0f, 0.0f, 0.0f);
	m_vHead.Set(0.0f, 1.0f, 0.0f);

	m_mRot.CreateRotateX(0);
	m_mRot.RotateY_Local(0);
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
	CVector3 v;

	m_vLook.TransformCoord(&CVector3(0, 3, 0), &mBase);
	//v[0].TransformCoord(&CVector3(0, 3, 0),&mBase);
	m_vPos.TransformNormal(&CVector3(0, 0, m_DisToBase), &m_mRot);
	//v.TransformNormal(&CVector3(0, 0, m_DisToBase), &m_mRot);
	//D3DXVec3TransformNormal(&v, &CVector3())
	//m_vPos = m_vPos + m_vLook;
	//m_vPos = v + m_vLook;


	m_mView.SetLookAtLH(m_vPos, m_vLook, m_vHead);
	//m_mView.SetLookAtLH(v[1], v[0], m_vHead);

	cdg.GetDev()->SetTransform(D3DTS_VIEW, &m_mView);
}
void Camera::SetView() 
{
	CMatrix mIden;
	mIden.CreateIdentity();

	SetView(mIden);
}
