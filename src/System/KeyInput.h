#ifndef __KINPUT_h__
#define __KINPUT_h__

class KeyInput {

public:
	boolean isDoubleInput(const float ms);

private:
	std::vector<DWORD> time;
	bool keyflg = false;


	//*********************************************
	// ƒVƒ“ƒOƒ‹ƒgƒ“ŽÀ‘•
public:
	static void CreateInstance() { new KeyInput(); }
	static void DeleteInstance() { delete m_lpInstance; }
	static KeyInput* GetInstance() { return m_lpInstance; }
private:
	KeyInput();
	~KeyInput();
	KeyInput(KeyInput &);
	KeyInput & operator= (KeyInput &);
	static KeyInput *m_lpInstance;

	//*********************************************
};

#define KINPUT KeyInput::GetInstance()

#endif