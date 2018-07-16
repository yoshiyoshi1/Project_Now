#ifndef __SEDAN_h__ 
#define __SEDAN_h__ 


class Sedan : public CarBase { 
public: 
	Sedan(); 
	~Sedan(); 
 
	void Update()override;
	void Draw()override;

private:

	const float MAX_SPEED = 50;
}; 
 
#endif 
