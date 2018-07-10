#ifndef __CARBASE_h__
#define __CARBASE_h__



class CarBase {

public:
	CarBase();
	~CarBase();

	void Update();
	void Draw();

private:
	CMatrix mat;
	CMesh mesh;

};

#endif