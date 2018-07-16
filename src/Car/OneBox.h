#ifndef __ONEBOX_h__ 
#define __ONEBOX_h__ 


class OneBox : public CarBase{ 
public: 
	OneBox(); 
	~OneBox(); 

	void Update()override;
	void Draw()override;
 
private:

	const float MAX_SPEED = 50;
}; 
 
#endif 
