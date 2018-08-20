#ifndef __TRUCK_h__ 
#define __TRUCK_h__ 


class Truck : public CarBase {
public: 
	Truck(); 
	~Truck(); 

	void Update()override;
	void Draw()override;

private:

	const float MAX_SPEED = 50;
 
}; 
 
#endif 
