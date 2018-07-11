#ifndef __CARBASE_h__
#define __CARBASE_h__



class CarBase {

public:
	CarBase();
	~CarBase();

	virtual void Update();
	virtual void Draw();
	void Move();

	enum TirePos {
		FR,
		FL,
		R1,
		R2
	};

protected:


	CMatrix bodyMat;
	CMatrix tireMat[4],tmpTireMat[4];
	CMesh body, FTire, RTire;

	float Speed = 0;
};

#endif