#ifndef __TAXI_h__
#define __TAXI_h__

class Taxi :public CarBase {

public:
	Taxi();
	~Taxi();

	void Update()override;
	void Draw()override;


	CMatrix& GetMat() { return bodyMat; }

private:

	const float MAX_SPEED = 50;
	

};

#endif
