#ifndef __BUS_h__ 
#define __BUS_h__ 


class Bus : public CarBase { 
public: 
	Bus(); 
	~Bus(); 

	void Update()override;
	void Draw()override;

private:

	const float MAX_SPEED = 50;
 
}; 
 
#endif 
