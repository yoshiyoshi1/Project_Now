#ifndef __CVector2_h__
#define __CVector2_h__

namespace SimpleLib{

//============================================================================
// ３次元ベクトルクラス
//	D2DXVECTOR2の機能拡張版
//============================================================================
class CVector2 : public D3DXVECTOR2{
public:
	// コンストラクタ
	CVector2(){
		x = 0;
		y = 0;
	}
	CVector2(float fx,float fy,float fz){
		x = fx;
		y = fy;
	}
	CVector2(const D3DXVECTOR2 &In){
		x = In.x;
		y = In.y;
	}

	void Set(float fx,float fy,float fz){
		x = fx;
		y = fy;
	}
	void Set(const D3DXVECTOR2 *v){
		x = v->x;
		y = v->y;
	}

	CVector2& operator=(const D3DXVECTOR2& v){
		x = v.x;
		y = v.y;
		return *this;
	}

	// 各演算子
	CVector2 operator + () const{ return D3DXVECTOR2::operator+(); }
	CVector2 operator - () const{ return D3DXVECTOR2::operator-(); }

	CVector2 operator + ( CONST D3DXVECTOR2& v) const{ return D3DXVECTOR2::operator+(v); }
	CVector2 operator - ( CONST D3DXVECTOR2& v) const{ return D3DXVECTOR2::operator-(v); }
	CVector2 operator * ( FLOAT f) const{ return D3DXVECTOR2::operator*(f); }
	CVector2 operator / ( FLOAT f) const{ return D3DXVECTOR2::operator/(f); }

	//ベクトル加算
	static void Add(D3DXVECTOR2 *vOut,const D3DXVECTOR2 *v1,const D3DXVECTOR2 *v2){	// 静的関数
		D3DXVec2Add(vOut,v1,v2);
	}
	void Add(float fx,float fy){
		Add(this,this,&D3DXVECTOR2(fx,fy));
	}
	void Add(const CVector2 *p){
		Add(this,this,p);
	}
	
	//ベクトル減算
	static void Sub(D3DXVECTOR2 *vOut,const D3DXVECTOR2 *v1,const D3DXVECTOR2 *v2){	// 静的関数
		D3DXVec2Subtract(vOut,v1,v2);
	}
	void Sub(float fx,float fy){
		Sub(this,this,&D3DXVECTOR2(fx,fy));
	}
	void Sub(const D3DXVECTOR2 *p){
		Sub(this,this,p);
	}
	
	// スカラー倍
	static void Scale(D3DXVECTOR2 *vOut,const D3DXVECTOR2 *vSrc,float s){		// 静的関数
		D3DXVec2Scale(vOut,vSrc,s);
	}
	void Scale(float s){
		Scale(this,this,s);
	}

	// 長さ
	static float Length(const D3DXVECTOR2 *vSrc){						// 静的関数
		return D3DXVec2Length(vSrc);
	}
	float Length(){
		return Length(this);
	}

	// 正規化
	static void Normalize(D3DXVECTOR2 *vOut,const D3DXVECTOR2 *vSrc){			// 静的関数
		D3DXVec2Normalize(vOut,vSrc);
	}
	void Normalize(){
		Normalize(this,this);
	}
	void Normalize(D3DXVECTOR2 *vOut) const{
		Normalize(vOut,this);
	}

};

}

#endif
