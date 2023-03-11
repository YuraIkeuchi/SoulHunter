#include "Helper.h"

//max min‚ğbool•ª‚Å•Ô‚·
bool Helper::CheckMax(float& Num, const float Max,const float Add) {
	Num += Add;

	Num = max(Num, Max);


	if (Num <= Max) {
		return true;
	}
	else {
		return false;
	}

	return false;
}

bool Helper::CheckMin(float& Num, const float Min, const float Add) {
	Num += Add;
	Num = min(Num, Min);

	if (Num >= Min) {
		return true;
	}
	else {
		return false;
	}

	return false;
}
//Clamp‚ğ•Ô‚·ŠÖ”
void Helper::IntClamp(int& Num,const int Min,const int Max) {
	Num = min(max(Num, Min), Max);
}

void Helper::FloatClamp(float& Num,const float Min,const float Max) {
	Num = min(max(Num, Min), Max);
}

//XMFLOAT3‚Æfloat‚ğ‰ÁZ‚·‚éŠÖ”
void Helper::Float3AddFloat(XMFLOAT3& Num, float Add) {
	Num.x += Add;
	Num.y += Add;
	Num.z += Add;
}

//XMFLOAT3‚ÆXMFLOAT3‚ğ‰ÁZ‚·‚éŠÖ”
void Helper::Float3AddFloat3(XMFLOAT3& Num, XMFLOAT3 Add) {
	Num.x += Add.x;
	Num.y += Add.y;
	Num.z += Add.z;
}

//XMFLOAT3‚Æfloat‚ğŒ¸Z‚·‚éŠÖ”
void Helper::Float3SubFloat(XMFLOAT3& Num, float Sub) {
	Num.x -= Sub;
	Num.y -= Sub;
	Num.z -= Sub;
}

//XMFLOAT3‚ÆXMFLOAT3‚ğŒ¸Z‚·‚éŠÖ”
void Helper::Float3SubFloat3(XMFLOAT3& Num, XMFLOAT3 Sub) {
	Num.x -= Sub.x;
	Num.y -= Sub.y;
	Num.z -= Sub.z;
}