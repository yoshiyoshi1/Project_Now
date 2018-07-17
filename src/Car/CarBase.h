#ifndef __CARBASE_h__
#define __CARBASE_h__



class CarBase {

public:
	CarBase();
	~CarBase();

	virtual void Update();
	virtual void Draw();
	void Move(float maxSpeed);

	float GetSpeed() { return Speed; }
	int GetCarType() { return carType; }

	enum TirePos {
		FR,	//�^�]�ȑ�
		FL,	//����ȑ�
		R1,	//���1��
		R2	//���2��
	};

	enum CarType {
		Taxi,
		Sedan,
		Onebox,
		Bus,
		Truck
	};

protected:
	int carType;

	CMatrix bodyMat;
	CMatrix tireMat[4],tireTrans[4],tmpTireMat[4];
	CMatrix beforemat;
	CMesh Body, FTire, RTire, DTire;

	bool isForword = false;
	bool isBack = false;

	float Speed = 0;
	float FTireRot = 0;

private:
	const float reduce = 0.05f;



};

#endif