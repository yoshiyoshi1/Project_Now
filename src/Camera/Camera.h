#ifndef __Camera_h__
#define __Camera_h__

class Camera
{
public :
	Camera();
	~Camera();

	void Update();

	void SetProj();
	
	void SetView(CMatrix mBase);
	void SetView();

private:
	CMatrix m_mProj;
	CMatrix m_mView;
	CMatrix m_mRot;

	CVector3 m_vPos;
	CVector3 m_vLook;
	CVector3 m_vHead;

};


#endif