#ifndef __TAXI_h__
#define __TAXI_h__

class Taxi :public CarBase {

public:
	Taxi();
	~Taxi();

	void Update()override;
	void Draw()override;


private:
	CMatrix Tiremat,mat;
	CMatrix tmp;
	CMesh body, FTire, RTire;

};

#endif
