#include "Helper.h"

//Clampを返す関数
void Helper::IntClamp(int& Num,const int Min,const int Max) {
	Num = min(max(Num, Min), Max);
}

void Helper::FloatClamp(float& Num,const float Min,const float Max) {
	Num = min(max(Num, Min), Max);
}