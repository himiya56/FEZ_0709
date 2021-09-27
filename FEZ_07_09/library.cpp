//=============================================================================
//
// ����ȈՏ����֐��Q [Library.cpp]
// Author : ��{ ��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "library.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_STRING_LENGTH 256

//*****************************************************************************
// �x���֐�
//*****************************************************************************
void Delay(const int nSecond)
{
	time_t now = nSecond * CLOCKS_PER_SEC + clock();

	while (now > clock());
}

//*****************************************************************************
// �w��͈͓��̗����𐶐�
//*****************************************************************************
int GetRandom(const int min, const int max)
{
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}

//*****************************************************************************
// ���v�l�v�Z�֐�
// �� 1 ����   : �v�Z����l�̌�
// �� 2 ���ȍ~ : ���v�l�v�Z�������l�Q
//*****************************************************************************
int Sum(int nValue, ...)
{
	va_list arg;
	int nSum = 0;	// ���v�l�i�[�p

	va_start(arg, nValue);

	// �����̐������J��Ԃ�
	for (int nCount = 0; nCount < nValue; nCount++)
	{
		// ���v�l�ɉ��Z
		nSum += va_arg(arg, int);
	}

	va_end(arg);

	// ���v�l��Ԃ�
	return nSum;
}

//*****************************************************************************
// int��char�|�C���^�ɕϊ�
//*****************************************************************************
char * NumberToChar(const int nNumber)
{
	// ������ێ��p
	char cString[MAX_STRING_LENGTH];
	// �ϊ�
	snprintf(cString, MAX_STRING_LENGTH, "%d", nNumber);

	return cString;
}

//*****************************************************************************
// float��char�|�C���^�ɕϊ�
//*****************************************************************************
char * NumberToChar(const float fNumber)
{
	// ������ێ��p
	char cString[MAX_STRING_LENGTH];
	// �ϊ�
	snprintf(cString, MAX_STRING_LENGTH, "%.2f", fNumber);

	return cString;
}

//*****************************************************************************
// �x�N�g���̑傫�����v�Z
//*****************************************************************************
float Vec3Length(D3DXVECTOR3 *pVec)
{
	double x, y, z;
	double len;

	if (!pVec) return 0.0f;

	x = (double)(pVec->x);
	y = (double)(pVec->y);
	z = (double)(pVec->z);
	len = sqrt(x * x + y * y + z * z);

	return (float)(len);
}

//*****************************************************************************
// �����蔻����v�Z
//*****************************************************************************
bool CollisionDetectionCalculation(D3DXVECTOR3 PlayerPosOld, D3DXVECTOR3 PlayerPos, D3DXVECTOR3 PlayerSiz, D3DXVECTOR3 ObjectPos, D3DXVECTOR3 ObjectSiz, COLLISION Collision) {
	bool bWidthJudge = false;

	if (PlayerPos.z == ObjectPos.z &&
		PlayerPos.x + (PlayerSiz.x / 2) >= ObjectPos.x - (ObjectSiz.x / 2) &&
		PlayerPos.x - (PlayerSiz.x / 2) <= ObjectPos.x + (ObjectSiz.x / 2) ||
		PlayerPos.x == ObjectPos.x &&
		PlayerPos.z + (PlayerSiz.z / 2) >= ObjectPos.z - (ObjectSiz.z / 2) &&
		PlayerPos.z - (PlayerSiz.z / 2) <= ObjectPos.z + (ObjectSiz.z / 2)) {

		bWidthJudge = true;
	}

	if (Collision == COLLISION_WIDTH) {
		return bWidthJudge;
	}
	else if (bWidthJudge == true &&
		PlayerPos.y - (PlayerSiz.y / 2) <= ObjectPos.y + (ObjectSiz.y / 2) &&
		PlayerPos.y >= ObjectPos.y + (ObjectSiz.y / 2)) {
		return true;
	}

	return false;
}