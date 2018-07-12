#ifndef __CARBASE_h__
#define __CARBASE_h__



class CarBase {

public:
	CarBase();
	~CarBase();

	virtual void Update();
	virtual void Draw();
	void Move(float maxSpeed);

	boolean isDoubleInput();

	float GetSpeed() { return Speed; }

	enum TirePos {
		FR,
		FL,
		R1,
		R2
	};

protected:
	CMatrix bodyMat;
	CMatrix tireMat[4],tmpTireMat[4];
	CMesh Body, FTire, RTire, DTire;

	float Speed = 0;

private:
	float reduce = 0.01f;


	//‚Q‰ñ“ü—Í”»’è—p‚Ì•Ï”
private:
	std::vector<DWORD> time;
	bool keyflg= false;



};

#endif