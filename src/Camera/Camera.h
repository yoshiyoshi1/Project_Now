#ifndef __Camera_h__
#define __Camera_h__

class Camera
{
public :
	Camera();
	~Camera();

	void Update();

	void SetProj();
	
	//=======================================
	// �����_�ɂ��������̂̍s���������
	//=======================================
	void SetView(CMatrix& mBase);
	//=======================================
	// �����_�ɂ��������̂̍s���������
	//=======================================
	void SetView();

	void SetDisToBase(float f) 
	{
		m_DisToBase = f;
	}

	CVector3 GetvPos(void) {
		return m_vPos;
	}

private:
	CMatrix m_mProj;
	CMatrix m_mView;
	CMatrix m_mRot;

	CVector3 m_vPos;
	CVector3 m_vLook;
	CVector3 m_vHead;

	CVector3 m_vOffset;	// �����Ώۂ���ǂꂮ�炢���炷��

	float m_DisToBase = 3;	// Base �܂ł̋���
};


#endif