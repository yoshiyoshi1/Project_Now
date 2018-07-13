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
		FR,
		FL,
		R1,
		R2
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
	CMatrix tireMat[4],tmpTireMat[4];
	CMesh Body, FTire, RTire, DTire;

	float Speed = 0;

private:
	float reduce = 0.01f;



};

#endif