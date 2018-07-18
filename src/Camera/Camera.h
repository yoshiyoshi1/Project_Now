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
	// 注視点にしたいものの行列を引数で
	//=======================================
	void SetView(CMatrix& mBase);
	//=======================================
	// 注視点にしたいものの行列を引数で
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

	CVector3 m_vOffset;	// 注視対象からどれぐらいずらすか

	float m_DisToBase = 3;	// Base までの距離
};


#endif