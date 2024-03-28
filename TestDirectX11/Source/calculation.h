//=============================================================================
// 
// �֗��֐� [calculation.h]
// Author : ���n�Ή�
// 
//=============================================================================

#ifndef _CALCULATION_H_
#define _CALCULATION_H_		// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "constans.h"

/**
@brief	�ȒP�Ȑ���
@details �ڍׂȐ���
@param	hoge	[in][out][inout]	�����̐���
@return	piyo	�߂�l�̐���
*/

//==========================================================================
// �}�N����`
//==========================================================================
#define MAX_COMMENT	(512)	// �R�����g�̍ő吔

/**
@brief	�֗��֐�
*/
namespace UtilFunc
{
	namespace Transformation
	{
		template<class T> void ValueNormalize(T& Value, T MaxValue, T MinValue);	// �l�̐��K������
		MyLib::Vector3 RotationChangeToForwardVector(float rot);
		void RotNormalize(float& fRot);
		void RotNormalize(MyLib::Vector3& rot);
		int Random(int nMinNum, int nMaxNum);
		float GetRandomPi();
	}

	namespace Collision
	{
		bool CollisionTriangle(const MyLib::Vector3& posCenter, const MyLib::Vector3& posLeft, const MyLib::Vector3& posRight, const MyLib::Vector3& MainPos, const MyLib::Vector3& MainPosOld);	// �O�p�`�̓����ɂ��邩����

	}
}

//==========================================================================
// �l�[���X�y�[�X��`
//==========================================================================
namespace UtilFunc	// �֗��֐�
{

	/**
	@brief	�␳�֐�
	*/
	namespace Correction
	{
		/**
		@brief	�����␳
		@details �␳�W����1.0f�ɂ����1F�ŕ␳���������܂�
		@param	fMain	[inout]	�␳����l
		@param	fTarget	[in]	�ڕW�̒l
		@param	fFactor	[in]	�␳�W��(0.0f �` 1.0f)
		@return	void
		*/
		inline void InertiaCorrection(float& fMain, float fTarget, float fFactor)
		{
			// �͈͊O�␳
			UtilFunc::Transformation::ValueNormalize(fFactor, 1.0f, 0.0f);

			fMain += (fTarget - fMain) * fFactor;
		}

		/**
		@brief	�����␳
		@details �␳�W����1.0f�ɂ����1F�ŕ␳���������܂�
		@param	main	[inout]	�␳����l
		@param	target	[in]	�ڕW�̒l
		@param	fFactor	[in]	�␳�W��(0.0f �` 1.0f)
		@return	void
		*/
		inline void InertiaCorrection(MyLib::Vector3& main, const MyLib::Vector3& target, float fFactor)
		{
			// �͈͊O�␳
			UtilFunc::Transformation::ValueNormalize(fFactor, 1.0f, 0.0f);

			main.x += (target.x - main.x) * fFactor;
			main.y += (target.y - main.y) * fFactor;
			main.z += (target.z - main.z) * fFactor;
		}

		/**
		@brief	���`�␳(����, ���j�A)
		@details https://mo-no.design/blog/wp-content/uploads/2023/02/linear.mp4
		@param	start	[in]	�����l
		@param	end		[in]	�ڕW�l
		@param	time	[in]	�␳����(0.0f �` 1.0f)
		@return	�␳���ꂽfloat�l
		*/
		inline float EasingLinear(float start, float end, float time)
		{
			// �͈͊O�␳
			UtilFunc::Transformation::ValueNormalize(time, 1.0f, 0.0f);
			return start + (end - start) * time;
		}

		/**
		@brief	���`�␳(����, ���j�A)
		@details https://mo-no.design/blog/wp-content/uploads/2023/02/linear.mp4
		@param	start		[in]	�����l
		@param	end			[in]	�ڕW�l
		@param	startTime	[in]	�J�n����
		@param	endTime		[in]	�I������
		@param	currentTime	[in]	���݂̎���
		@return	�␳���ꂽfloat�l
		*/
		inline float EasingLinear(float start, float end, float startTime, float endTime, float currentTime)
		{
			// ����
			float ratio = (currentTime - startTime) / (endTime - startTime);
			UtilFunc::Transformation::ValueNormalize(ratio, 1.0f, 0.0f);

			return EasingLinear(start, end, ratio);
		}

		/**
		@brief	���`�␳(���X�ɉ���, �C�[�Y�C��)
		@details https://mo-no.design/blog/wp-content/uploads/2023/02/easein_1.mp4
		@param	start	[in]	�����l
		@param	end		[in]	�ڕW�l
		@param	time	[in]	�␳����(0.0f �` 1.0f)
		@return	�␳���ꂽfloat�l
		*/
		inline float EasingEaseIn(float start, float end, float time)
		{
			// �͈͊O�␳
			UtilFunc::Transformation::ValueNormalize(time, 1.0f, 0.0f);
			return start + (end - start) * time * time;
		}

		/**
		@brief	���`�␳(���X�ɉ���, �C�[�Y�C��)
		@details https://mo-no.design/blog/wp-content/uploads/2023/02/easein_1.mp4
		@param	start		[in]	�����l
		@param	end			[in]	�ڕW�l
		@param	startTime	[in]	�J�n����
		@param	endTime		[in]	�I������
		@param	currentTime	[in]	���݂̎���
		@return	�␳���ꂽfloat�l
		*/
		inline float EasingEaseIn(float start, float end, float startTime, float endTime, float currentTime)
		{
			// ����
			float ratio = (currentTime - startTime) / (endTime - startTime);
			UtilFunc::Transformation::ValueNormalize(ratio, 1.0f, 0.0f);

			return EasingEaseIn(start, end, ratio);
		}

		/**
		@brief	���`�␳(���X�Ɍ���, �C�[�Y�A�E�g)
		@details https://mo-no.design/blog/wp-content/uploads/2023/02/easeout_1.mp4
		@param	start	[in]	�����l
		@param	end		[in]	�ڕW�l
		@param	time	[in]	�␳����(0.0f �` 1.0f)
		@return	�␳���ꂽfloat�l
		*/
		inline float EasingEaseOut(float start, float end, float time)
		{
			// �͈͊O�␳
			UtilFunc::Transformation::ValueNormalize(time, 1.0f, 0.0f);
			float fSquaredTime = time * time;

			return start + (end - start) * (1.0f - (1.0f - fSquaredTime) * (1.0f - fSquaredTime));
		}

		/**
		@brief	���`�␳(���X�Ɍ���, �C�[�Y�A�E�g)
		@details https://mo-no.design/blog/wp-content/uploads/2023/02/easeout_1.mp4
		@param	start		[in]	�����l
		@param	end			[in]	�ڕW�l
		@param	startTime	[in]	�J�n����
		@param	endTime		[in]	�I������
		@param	currentTime	[in]	���݂̎���
		@return	�␳���ꂽfloat�l
		*/
		inline float EasingEaseOut(float start, float end, float startTime, float endTime, float currentTime)
		{
			// ����
			float ratio = (currentTime - startTime) / (endTime - startTime);
			UtilFunc::Transformation::ValueNormalize(ratio, 1.0f, 0.0f);

			return EasingEaseOut(start, end, ratio);
		}

		/**
		@brief	���`�␳(�������Ă��猸��, �C�[�Y�C���A�E�g)
		@details https://mo-no.design/blog/wp-content/uploads/2023/02/easeinout_1.mp4
		@param	start	[in]	�����l
		@param	end		[in]	�ڕW�l
		@param	time	[in]	�␳����(0.0f �` 1.0f)
		@return	�␳���ꂽfloat�l
		*/
		inline float EasingEaseInOut(float start, float end, float time)
		{
			// �͈͊O�␳
			UtilFunc::Transformation::ValueNormalize(time, 1.0f, 0.0f);

			float fValue = 0.0f;
			if (time < 0.5f)
			{
				time = 2.0f * time;
				fValue = start + (end - start) * 0.5f * time * time;
			}
			else 
			{
				time = 2.0f * time - 1.0f;
				float fSquaredTime = time * time;
				fValue = start + (end - start) * (0.5f * (1.0f - (1.0f - fSquaredTime) * (1.0f - fSquaredTime)) + 0.5f);
			}
			return fValue;
		}

		/**
		@brief	���`�␳(�������Ă��猸��, �C�[�Y�C���A�E�g)
		@details https://mo-no.design/blog/wp-content/uploads/2023/02/easeinout_1.mp4
		@param	start		[in]	�����l
		@param	end			[in]	�ڕW�l
		@param	startTime	[in]	�J�n����
		@param	endTime		[in]	�I������
		@param	currentTime	[in]	���݂̎���
		@return	�␳���ꂽfloat�l
		*/
		inline float EasingEaseInOut(float start, float end, float startTime, float endTime, float currentTime)
		{
			// ����
			float ratio = (currentTime - startTime) / (endTime - startTime);
			UtilFunc::Transformation::ValueNormalize(ratio, 1.0f, 0.0f);

			return EasingEaseInOut(start, end, ratio);
		}

#if 0
		/**
		@brief	Catmull-Rom Spline���(�S�Ă̓_��ʂ���`���)
		@details https://storage.googleapis.com/zenn-user-upload/cu4a6qn5njn0pskn6pfx6lypic0h
		@param	PointMili1	[in]	��̑O�̐���_(f-1)
		@param	Point0		[in]	��̍ŏ��̐���_(f0)
		@param	Point1		[in]	���2�Ԗڂ̐���_(f1)
		@param	Point2		[in]	��̎��̐���_ (f2)
		@param	time		[in]	�␳����(0.0f �` 1.0f)
		@return	��Ԃ��ꂽ�l
		*/
		inline MyLib::Vector3 CatmullRomSplineInterp(MyLib::Vector3 PointMili1, MyLib::Vector3 Point0, MyLib::Vector3 Point1, MyLib::Vector3 Point2, float time)
		{
			// 4�_�ŕ␳
			MyLib::Vector3 a4 = Point0;
			MyLib::Vector3 a3 = (Point1 - PointMili1) / 2.0f;
			MyLib::Vector3 a1 = (Point2 - Point0) / 2.0f - 2.0f * Point1 + a3 + 2.0f * a4;
			MyLib::Vector3 a2 = 3.0f * Point1 - (Point2 - Point0) / 2.0f - 2.0f * a3 - 3.0f * a4;

			return (a1 * time * time * time + a2 * time * time + a3 * time + a4);
		}
#endif

		/**
		@brief	�񎟋Ȑ��␳
		@param	Value		[inout]	�⊮�����l
		@param	nRange		[in]	�⊮�͈̔�
		@param	RangeOrigin	[in]	�⊮�͈͂̋N�_�ƂȂ�l
		@param	Max			[in]	�⊮�̍ő�l
		@param	nAlphaCnt	[in]	�񎟋Ȑ��␳�p�̃J�E���^�[�ϐ��ւ̎Q��
		@return	void
		*/
		template<class T> inline void CuadricCurveComp(T& Value, const int nRange, T RangeOrigin, T Max, int& nAlphaCnt)
		{
			// �⊮�̒l����o��
			T Comp = (static_cast<T>(Max) / static_cast<T>((nRange * nRange)));

			if (nAlphaCnt > nRange)
			{// �͈͒�������߂�
				nAlphaCnt = -nRange;
			}
			else if (nAlphaCnt < -nRange)
			{// �͈͒�������߂�
				nAlphaCnt = nRange;
			}

			// �s�����̃J�E���g���Z
			nAlphaCnt++;

			// �Ȑ��␳
			Value = static_cast<T>(((Comp * (nAlphaCnt * nAlphaCnt)) - (2 * (Comp * nAlphaCnt * RangeOrigin)) + (Comp * (RangeOrigin * RangeOrigin))));
			Value += RangeOrigin;
		}

	}

	/**
	@brief	�v�Z�֐�
	*/
	namespace Calculation
	{
		/**
		@brief	�����擾
		@param	nNum	[in]	���������߂����l
		@return	����
		*/
		inline int GetDigit(int nNum)
		{
			if (nNum <= 0)
			{
				nNum = 0;
			}

			// �����𕶎���ɕϊ�
			std::string number;
			sprintf((char*)number.c_str(), "%d", nNum);

			// ������̒����i�����j���擾
			int nDigit = strlen(number.c_str());
			if (nDigit <= 0)
			{
				nDigit = 1;
			}

			return nDigit;
		}

		/**
		@brief	�w�肳�ꂽ���e�덷�͈͓��ɂ��邩����
		@param	value	[in]	���肵�����l
		@param	target	[in]	��ɂ���l
		@param	range	[in]	���e�͈�
		@return	���茋��
		*/
		inline bool IsNearlyTarget(float value, float target, float range)
		{
			if (abs(value) <= range + target)
			{
				return true;
			}
			return false;
		}

		/**
		@brief	��_�Ԃ̒����擾(2D)
		@param	pos1	[in]	�n�_
		@param	pos2	[in]	�I�_
		@return	����
		*/
		inline float GetPosLength2D(MyLib::Vector3 pos1, MyLib::Vector3 pos2)
		{
			return sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
				+ (pos1.y - pos2.y) * (pos1.y - pos2.y));
		}

		/**
		@brief	��_�Ԃ̒����̐�Βl�擾(2D)
		@param	pos1	[in]	�n�_
		@param	pos2	[in]	�I�_
		@return	�����̐�Βl
		*/
		inline float GetFabsPosLength2D(MyLib::Vector3 pos1, MyLib::Vector3 pos2)
		{
			return fabsf(GetPosLength2D(pos1, pos2));
		}

		/**
		@brief	��_�Ԃ̒����擾(3D)
		@param	pos1	[in]	�n�_
		@param	pos2	[in]	�I�_
		@return	����
		*/
		inline float GetPosLength3D(MyLib::Vector3 pos1, MyLib::Vector3 pos2)
		{
			return sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
				+ (pos1.z - pos2.z) * (pos1.z - pos2.z));
		}

		/**
		@brief	��_�Ԃ̒����̐�Βl�擾(3D)
		@param	pos1	[in]	�n�_
		@param	pos2	[in]	�I�_
		@return	�����̐�Βl
		*/
		inline float GetFabsPosLength3D(MyLib::Vector3 pos1, MyLib::Vector3 pos2)
		{
			return fabsf(GetPosLength3D(pos1, pos2));
		}

		/**
		@brief	��_�̒��S�_�擾(3D)
		@param	pos1	[in]	�n�_
		@param	pos2	[in]	�I�_
		@return	���S�_
		*/
		inline MyLib::Vector3 GetCenterPosition3D(MyLib::Vector3 pos1, MyLib::Vector3 pos2)
		{
			return MyLib::Vector3(
				(pos1.x + pos2.x),
				(pos1.y + pos2.y),
				(pos1.z + pos2.z)) * 0.5f;
		}

		/**
		@brief	�ӏ�̈ʒu�擾(2D)
		@param	point1	[in]	�n�_�̒��_���W
		@param	point2	[in]	�I�_�̒��_���W
		@param	fRate	[in]	����
		@return	�ʒu
		*/
		inline MyLib::Vector3 GetPointOnEdge2D(MyLib::Vector3 point1, MyLib::Vector3 point2, float fRate)
		{
			return MyLib::Vector3(
				point1.x + fRate * (point2.x - point1.x),
				point1.y + fRate * (point2.y - point1.y),
				0.0f);
		}

		/**
		@brief	�������̈ʒu�擾
		@param	start		[in]	�n�_
		@param	end			[in]	�I�_
		@param	fMaxHeight	[in]	�����̍ő�l
		@param	time		[in]	�␳����(0.0f �` 1.0f)
		@return	��������̈ʒu�擾
		*/
		inline MyLib::Vector3 GetParabola3D(MyLib::Vector3 start, MyLib::Vector3 end, float fMaxHeight, float time)
		{
			// �ʒu
			MyLib::Vector3 pos = mylib_const::DEFAULT_VECTOR3;

			// XZ�ړ�
			pos.x = start.x + (end.x - start.x) * time;
			pos.z = start.z + (end.z - start.z) * time;

			// ����
			pos.y = start.y + (end.y - start.y) * time + sinf(XM_PI * time) * fMaxHeight;

			return pos;
		}

		// �䗦���v�Z����֐�
		/**
		@brief	�䗦���v�Z
		@param	size		[in]	�񎟌��T�C�Y
		@return	�䗦
		*/
		inline float AspectRatio(const MyLib::Vector2& size) 
		{
			return size.x / size.y;
		}
#if 0

		/**
		@brief	���f���̒��_���v�Z
		@param	RotY		[in]	���f����Y������
		@param	pVtxMax		[inout]	���_���W�̍ő�l
		@param	pVtxMin		[inout]	���_���W�̍ŏ��l
		@param	pMesh		[in]	���f���̃��b�V���I�u�W�F�N�g
		@param	pVtxBuff	[in]	���_�o�b�t�@
		@return	void
		*/
		inline void CalModelVtx(float RotY, MyLib::Vector3* pVtxMax, MyLib::Vector3* pVtxMin, LPD3DXMESH pMesh, BYTE* pVtxBuff)
		{
			// ���Z�b�g
			*pVtxMin = MyLib::Vector3(10000.0f, 10000.0f, 10000.0f);
			*pVtxMax = MyLib::Vector3(-10000.0f, -10000.0f, -10000.0f);

			// ���f���̒��_�����擾
			int nNumVtx = pMesh->GetNumVertices();

			// ���_�t�H�[�}�b�g�̃T�C�Y���擾
			DWORD dwSizeFVF = D3DXGetFVFVertexSize(pMesh->GetFVF());

			// ���_�o�b�t�@�����b�N
			pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			// �S�Ă̒��_���`�F�b�N����
			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				// ����̃f�[�^
				MyLib::Vector3 vtx = *(MyLib::Vector3*)pVtxBuff;

				// X
				if (pVtxMin->x > vtx.x)
				{// ���̍ŏ��l��������̒l����������������

					pVtxMin->x = vtx.x;
				}
				if (pVtxMax->x < vtx.x)
				{// ���̍ő�l��������̒l���傫��������

					pVtxMax->x = vtx.x;
				}

				// Y
				if (pVtxMin->y > vtx.y)
				{// ���̍ŏ��l��������̒l����������������

					pVtxMin->y = vtx.y;
				}
				if (pVtxMax->y < vtx.y)
				{// ���̍ő�l��������̒l���傫��������

					pVtxMax->y = vtx.y;
				}

				// Z
				if (pVtxMin->z > vtx.z)
				{// ���̍ŏ��l��������̒l����������������

					pVtxMin->z = vtx.z;
				}
				if (pVtxMax->z < vtx.z)
				{// ���̍ő�l��������̒l���傫��������

					pVtxMax->z = vtx.z;
				}

				pVtxBuff += dwSizeFVF;	// �T�C�Y���|�C���^�ړ�
			}

			// ���_�o�b�t�@���A�����b�N
			pMesh->UnlockVertexBuffer();

			MyLib::Vector3 VtxMax = *pVtxMax, VtxMin = *pVtxMin;

			if (RotY <= XM_PI * 0.5f + 0.05f && RotY >= XM_PI * 0.5f - 0.05f)
			{// 1.57f�̂Ƃ�

				pVtxMax->x = VtxMax.z;
				pVtxMin->x = VtxMin.z;

				pVtxMax->z = -VtxMin.x;
				pVtxMin->z = -VtxMax.x;
			}
			else if (RotY <= -XM_PI * 0.5f + 0.05f && RotY >= -XM_PI * 0.5f - 0.05f)
			{// -1.57f�̂Ƃ�

				pVtxMax->x = -VtxMin.z;
				pVtxMin->x = -VtxMax.z;

				pVtxMax->z = VtxMax.x;
				pVtxMin->z = VtxMin.x;
			}
			else if (RotY <= XM_PI + 0.05f && RotY >= XM_PI - 0.05f)
			{// XM_PI�̂Ƃ�

				pVtxMax->x = -VtxMin.x;
				pVtxMin->x = -VtxMax.x;

				pVtxMax->z = -VtxMin.z;
				pVtxMin->z = -VtxMax.z;
			}
			else if (RotY <= -XM_PI + 0.05f && RotY >= -XM_PI - 0.05f)
			{// -XM_PI�̂Ƃ�

				pVtxMax->x = -VtxMin.x;
				pVtxMin->x = -VtxMax.x;

				pVtxMax->z = -VtxMin.z;
				pVtxMin->z = -VtxMax.z;
			}
		}
#endif

		/**
		@brief	3���_����Ȃ鍂���擾
		@param	pos			[in]	���肷��I�u�W�F�N�g�̈ʒu
		@param	posCenter	[in]	���肷��O�p�`�̎�O�̒��_���W
		@param	posLeft		[in]	���肷��O�p�`�̍��̒��_���W
		@param	posRight	[in]	���肷��O�p�`�̉E�̒��_���W
		@param	posRight	[out]	���n����
		@return	3���_����Ȃ鍂��
		*/
		inline float GetVtxHeight(const MyLib::Vector3& pos, const MyLib::Vector3& posCenter, const MyLib::Vector3& posRight, const MyLib::Vector3& posLeft, bool* pLand)
		{
			// ����
			float fHeight = 0.0f;

			// ���p�����ƈʒu�̃x�N�g��
			MyLib::Vector3 calvec = pos - posCenter;

			// �x�N�g���Ɩ@��
			MyLib::Vector3
				vec1 = posRight - posCenter,
				vec2 = posLeft - posRight,
				nor = MyLib::Vector3(0.0f, 0.0f, 0.0f);

			if (UtilFunc::Collision::CollisionTriangle(posCenter, posRight, posLeft, pos, pos) == true)
			{// �O�p�ɓ����Ă�����

				// �O�ς����߂�
				nor = vec1.Cross(vec2);

				// �O�ς̐��K�������Ė@���ɂ���
				nor = nor.Normal();

				if (nor.y != 0.0f)
				{// �@����0.0f����Ȃ�������

					// ���������߂�
					fHeight = -((calvec.x * nor.x) + (-posCenter.y * nor.y) + (calvec.z * nor.z)) / nor.y;
					*pLand = true;
				}
				else
				{
					// ���������߂�
					fHeight = -((calvec.x * nor.x) + (-posCenter.y * nor.y) + (calvec.z * nor.z)) / nor.y;
					*pLand = true;
				}
			}

			return fHeight;
		}

		/**
		@brief	����ւ�����
		@param	pValue		[out]	�\�[�g����l
		@param	nStart		[in]	�\�[�g����l�̏����l
		@param	nMax		[in]	�\�[�g�̍ő�l
		@return	void
		*/
		template<class T> inline void CalSort(T* pValue, int nStart, int nMax)
		{
			for (int nCntData = nStart; nCntData < nMax - 1; nCntData++)
			{
				for (int nCntSort = nCntData + 1; nCntSort < nMax; nCntSort++)
				{
					T nTemp = pValue[nCntData];
					pValue[nCntData] = pValue[nCntSort];
					pValue[nCntSort] = nTemp;
				}
			}
		}
	}

	/**
	@brief	�����蔻��֐�
	*/
	namespace Collision
	{
		/**
		@brief	1��2�̓����蔻��(�~)(2D)
		@param	pos1		[in]	�Ώ�1�̈ʒu
		@param	pos2		[in]	�Ώ�2�̈ʒu
		@param	fRadius1	[in]	�Ώ�1�̔��a
		@param	fRadius2	[in]	�Ώ�2�̔��a
		@return	������������bool�l
		*/
		inline bool CircleRange2D(const MyLib::Vector3& pos1, const MyLib::Vector3& pos2, float fRadius1, float fRadius2)
		{
			float fLength =
				(pos1.x - pos2.x) * (pos1.x - pos2.x) +
				(pos1.y - pos2.y) * (pos1.y - pos2.y);

			if (fLength <= (fRadius1 + fRadius2) * (fRadius1 + fRadius2))
			{// �~�̒��ɓ�������
				return true;
			}

			return false;
		}

		/**
		@brief	1��2�̓����蔻��(�~)(3D)
		@param	pos1		[in]	�Ώ�1�̈ʒu
		@param	pos2		[in]	�Ώ�2�̈ʒu
		@param	fRadius1	[in]	�Ώ�1�̔��a
		@param	fRadius2	[in]	�Ώ�2�̔��a
		@return	������������bool�l
		*/
		inline bool CircleRange3D(const MyLib::Vector3& pos1, const MyLib::Vector3& pos2, float fRadius1, float fRadius2)
		{
			float fLength =
				(pos1.x - pos2.x) * (pos1.x - pos2.x) +
				(pos1.z - pos2.z) * (pos1.z - pos2.z);

			if (fLength <= (fRadius1 + fRadius2) * (fRadius1 + fRadius2))
			{// �~�̒��ɓ�������

				MyLib::Vector3 collisionPoint = pos1 + (pos2 - pos1).Normal() * fRadius1;

				return true;
			}

			return false;
		}

		/**
		@brief	1��2�̓����蔻��(��)
		@param	pos1		[in]	�Ώ�1�̈ʒu
		@param	pos2		[in]	�Ώ�2�̈ʒu
		@param	fRadius1	[in]	�Ώ�1�̔��a
		@param	fRadius2	[in]	�Ώ�2�̔��a
		@return	������������bool�l
		*/
		inline MyLib::HitResult SphereRange(const MyLib::Vector3& pos1, const MyLib::Vector3& pos2, float fRadius1, float fRadius2)
		{
			float fLength =
				(pos1.x - pos2.x) * (pos1.x - pos2.x) +
				(pos1.y - pos2.y) * (pos1.y - pos2.y) +
				(pos1.z - pos2.z) * (pos1.z - pos2.z);

			if (fLength <= (fRadius1 + fRadius2) * (fRadius1 + fRadius2))
			{// ���̒��ɓ�������

				MyLib::Vector3 collisionVector = (pos2 - pos1).Normal() * fRadius1;
				MyLib::Vector3 collisionPoint = pos1 + collisionVector;
				return MyLib::HitResult(true, collisionPoint);
			}

			return MyLib::HitResult(false, MyLib::Vector3());
		}

		/**
		@brief	1��2�̓����蔻��(��)
		@param	pos1		[in]	�Ώ�1�̈ʒu
		@param	pos2		[in]	�Ώ�2�̈ʒu
		@param	fRadius1	[in]	�Ώ�1�̔��a
		@param	fRadius2	[in]	�Ώ�2�̔��a
		@param	fHeight1	[in]	�Ώ�1�̍���
		@param	fHeight2	[in]	�Ώ�2�̍���
		@return	������������bool�l
		*/
		inline bool CylinderRange(MyLib::Vector3 pos1, MyLib::Vector3 pos2, float fRadius1, float fRadius2, float fHeight1, float fHeight2)
		{
			if (CircleRange3D(pos1, pos2, fHeight1, fHeight2) &&
				pos1.y + fHeight1 >= pos2.y &&
				pos1.y <= pos2.y + fHeight2)
			{// �~�̒��ɓ��� && �������Ԃ���
				return true;
			}

			return false;
		}

		/**
		@brief	�L�����N�^�[���m�̓����蔻�� & �␳
		@param	MainPos			[inout]	�����̈ʒu
		@param	MainPosOld		[inout]	�����̑O��̈ʒu
		@param	MainVtxMax		[in]	�����̒��_�ő�l
		@param	MainVtxMin		[in]	�����̒��_�ŏ��l
		@param	TargetPos		[inout]	�Ώۂ̈ʒu
		@param	TargetVtxMax	[in]	�Ώۂ̒��_�ő�l
		@param	TargetVtxMin	[in]	�Ώۂ̒��_�ŏ��l
		@return	void
		*/
		inline void CollisionCharacter(MyLib::Vector3& MainPos, MyLib::Vector3& MainPosOld, MyLib::Vector3 MainVtxMax, MyLib::Vector3 MainVtxMin, MyLib::Vector3& TargetPos, MyLib::Vector3 TargetVtxMax, MyLib::Vector3 TargetVtxMin)
		{
			// ���̔���
			if (MainPos.z + MainVtxMax.z > TargetPos.z + TargetVtxMin.z &&	// �G�̍ŏ��l�ɓ����Ă�
				MainPos.z + MainVtxMin.z < TargetPos.z + TargetVtxMax.z)	// �G�̍ő�l�ɓ����Ă�
			{// �G��Z���̒��ɂ���Ƃ�

				if (MainPos.x + MainVtxMin.x <= TargetPos.x + TargetVtxMax.x &&		// ���݂̍ŏ��l���G�̍ő�l����������
					MainPosOld.x + MainVtxMin.x >= TargetPos.x + TargetVtxMax.x)	// �O��̍ŏ��l���G�̍ő�l�����傫��
				{// �E����

					MainPos.x = (TargetPos.x + TargetVtxMax.x) - MainVtxMin.x + 0.1f;
				}
				if (MainPos.x + MainVtxMax.x >= TargetPos.x + TargetVtxMin.x &&		// ���݂̍ő�l���G�̍ŏ��l�����傫��
					MainPosOld.x + MainVtxMax.x <= TargetPos.x + TargetVtxMin.x)	// �O��̍ő�l���G�̍ŏ��l����������
				{// ������

					MainPos.x = (TargetPos.x + TargetVtxMin.x) - MainVtxMax.x - 0.1f;
				}
			}

			// �c�̔���
			if (MainPos.x + MainVtxMax.x > TargetPos.x + TargetVtxMin.x &&	// �G�̍ŏ��l�ɓ����Ă�
				MainPos.x + MainVtxMin.x < TargetPos.x + TargetVtxMax.x)	// �G�̍ő�l�ɓ����Ă�
			{// �G��X���̒��ɂ���Ƃ�

				if (MainPos.z + MainVtxMin.z <= TargetPos.z + TargetVtxMax.z &&		// ���݂̍ŏ��l���G�̍ő�l����������
					MainPosOld.z + MainVtxMin.z >= TargetPos.z + TargetVtxMax.z)	// �O��̍ŏ��l���G�̍ő�l�����傫��
				{// ������

					MainPos.z = (TargetPos.z + TargetVtxMax.z) - MainVtxMin.z + 0.1f;
				}
				if (MainPos.z + MainVtxMax.z >= TargetPos.z + TargetVtxMin.z &&		// ���݂̍ő�l���G�̍ŏ��l�����傫��
					MainPosOld.z + MainVtxMax.z <= TargetPos.z + TargetVtxMin.z)	// �O��̍ő�l���G�̍ŏ��l����������
				{// ��O����

					MainPos.z = (TargetPos.z + TargetVtxMin.z) - MainVtxMax.z - 0.1f;
				}
			}
		}

		/**
		@brief	�L�����N�^�[���m�̓����蔻��
		@param	MainPos			[in]	�����̈ʒu
		@param	MainPosOld		[in]	�����̑O��̈ʒu
		@param	MainVtxMax		[in]	�����̒��_�ő�l
		@param	MainVtxMin		[in]	�����̒��_�ŏ��l
		@param	TargetPos		[in]	�Ώۂ̈ʒu
		@param	TargetVtxMax	[in]	�Ώۂ̒��_�ő�l
		@param	TargetVtxMin	[in]	�Ώۂ̒��_�ŏ��l
		@return	������������bool�l
		*/
		inline bool bHitCharacter(MyLib::Vector3 MainPos, MyLib::Vector3 MainPosOld, MyLib::Vector3 MainVtxMax, MyLib::Vector3 MainVtxMin, MyLib::Vector3 TargetPos, MyLib::Vector3 TargetVtxMax, MyLib::Vector3 TargetVtxMin)
		{
			// ���̔���
			if (MainPos.z + MainVtxMax.z > TargetPos.z + TargetVtxMin.z &&	// �G�̍ŏ��l�ɓ����Ă�
				MainPos.z + MainVtxMin.z < TargetPos.z + TargetVtxMax.z)	// �G�̍ő�l�ɓ����Ă�
			{// �G��Z���̒��ɂ���Ƃ�

				if (MainPos.x + MainVtxMin.x <= TargetPos.x + TargetVtxMax.x &&	// ���݂̍ŏ��l���G�̍ő�l����������
					MainPosOld.x + MainVtxMin.x >= TargetPos.x + TargetVtxMax.x)// �O��̍ŏ��l���G�̍ő�l�����傫��
				{// �E����
					return true;
				}
				if (MainPos.x + MainVtxMax.x >= TargetPos.x + TargetVtxMin.x &&	// ���݂̍ő�l���G�̍ŏ��l�����傫��
					MainPosOld.x + MainVtxMax.x <= TargetPos.x + TargetVtxMin.x)// �O��̍ő�l���G�̍ŏ��l����������
				{// ������
					return true;
				}
			}

			// �c�̔���
			if (MainPos.x + MainVtxMax.x > TargetPos.x + TargetVtxMin.x &&	// �G�̍ŏ��l�ɓ����Ă�
				MainPos.x + MainVtxMin.x < TargetPos.x + TargetVtxMax.x)	// �G�̍ő�l�ɓ����Ă�
			{// �G��X���̒��ɂ���Ƃ�

				if (MainPos.z + MainVtxMin.z <= TargetPos.z + TargetVtxMax.z &&	// ���݂̍ŏ��l���G�̍ő�l����������
					MainPosOld.z + MainVtxMin.z >= TargetPos.z + TargetVtxMax.z)// �O��̍ŏ��l���G�̍ő�l�����傫��
				{// ������
					return true;
				}
				if (MainPos.z + MainVtxMax.z >= TargetPos.z + TargetVtxMin.z &&	// ���݂̍ő�l���G�̍ŏ��l�����傫��
					MainPosOld.z + MainVtxMax.z <= TargetPos.z + TargetVtxMin.z)// �O��̍ő�l���G�̍ŏ��l����������
				{// ��O����
					return true;
				}
			}

			return false;
		}

		/**
		@brief	�����̓����蔻��
		@param	pos0		[in]	�������[�̈ʒu
		@param	pos1		[in]	�����E�[�̈ʒu
		@param	pPos		[inout]	�����̈ʒu
		@param	posOld		[in]	�����̑O��ʒu
		@return	void
		*/
		inline void CollisionLimitLine(const MyLib::Vector3& pos0, const MyLib::Vector3& pos1, MyLib::Vector3& pPos, MyLib::Vector3 posOld)
		{
			// ���E���̃x�N�g��
			MyLib::Vector3 vecLine;
			vecLine.x = pos1.x - pos0.x;
			vecLine.z = pos1.z - pos0.z;

			// �v���C���[�̋��E���̃x�N�g��
			MyLib::Vector3 vecLinePlayer;
			vecLinePlayer.x = pPos.x - posOld.x;
			vecLinePlayer.z = pPos.z - posOld.z;

			// �v���C���[�ƕǂ̃x�N�g��
			MyLib::Vector3 vecToPosPlayer;
			vecToPosPlayer.x = pos1.x - posOld.x;
			vecToPosPlayer.z = pos1.z - posOld.z;

			// �ʐς̍ő�l
			float fMaxAreaPlayer = (vecLinePlayer.z * vecLine.x) - (vecLinePlayer.x * vecLine.z);

			// ����̖ʐ�
			float fNowAreaPlayer = (vecToPosPlayer.z * vecLine.x) - (vecToPosPlayer.x * vecLine.z);

			// ����
			float fRatePlayer = fNowAreaPlayer / fMaxAreaPlayer;

			if (fRatePlayer >= 0.0f && fRatePlayer <= 1.0f)
			{// �ʐς͈͓̔��ɂ����画��

				if ((vecLinePlayer.z * vecToPosPlayer.x) - (vecLinePlayer.x * vecToPosPlayer.z) > 0)
				{// �ǂɓ���������

					// �@���x�N�g��(���E���x�N�g����X��Z���])
					MyLib::Vector3 vecNor = MyLib::Vector3(vecLine.z, 0.0f, -vecLine.x);

					// �x�N�g���̐��K��
					vecNor = vecNor.Normal();

					// �v���C���[�̋t�ړ���
					MyLib::Vector3 PlayerInverceMove;
					PlayerInverceMove.x = vecLinePlayer.x * (fRatePlayer - 1.0f);
					PlayerInverceMove.z = vecLinePlayer.z * (fRatePlayer - 1.0f);

					// ����(�ǂ̖@���ƃv���C���[�̋t�ړ���)
					float fDot = (PlayerInverceMove.x * vecNor.x) + (PlayerInverceMove.z * vecNor.z);

					// �ǂ���ړ���
					MyLib::Vector3 MoveWall = vecNor * fDot;

					// �Ԃ������_�ɕ␳
					pPos += MoveWall + (vecNor * 0.1f);

				}
			}
		}

		/**
		@brief	�����̉E�ɂ��邩�ǂ���(2D)
		@details �����ɑ΂��ĉE�ɂ��邩�̔���Ȃ̂ŁA���ɋ��ė~�����ꍇ��pos0��pos1�����ւ��Ďg�p
		@param	pos0		[in]	�������[�̈ʒu
		@param	pos1		[in]	�����E�[�̈ʒu
		@param	MainPos		[in]	���肷��Ώۂ̈ʒu
		@param	MainPos		[in]	���肷��Ώۂ̑O��̈ʒu
		@return	�����̉E���ɂ��邩��bool�l
		*/
		inline bool CollisionLine2D(const MyLib::Vector3& pos0, const MyLib::Vector3& pos1, const MyLib::Vector3& MainPos, const MyLib::Vector3& MainPosOld)
		{
			// ���E���̃x�N�g��
			MyLib::Vector3 vecLine;
			vecLine.x = pos1.x - pos0.x;
			vecLine.y = pos0.y - pos1.y;

			// �e�ƕǂ̃x�N�g��
			MyLib::Vector3 vecToPos;
			vecToPos.x = MainPos.x - pos0.x;
			vecToPos.y = pos0.y - MainPos.y;

			if ((vecLine.y * vecToPos.x) - (vecLine.x * vecToPos.y) <= 0)
			{// ���𒴂���
				return true;
			}

			return false;
		}

		/**
		@brief	�����̉E�ɂ��邩�ǂ���(3D)
		@details �����ɑ΂��ĉE�ɂ��邩�̔���Ȃ̂ŁA���ɋ��ė~�����ꍇ��pos0��pos1�����ւ��Ďg�p
		@param	pos0		[in]	�������[�̈ʒu
		@param	pos1		[in]	�����E�[�̈ʒu
		@param	MainPos		[in]	���肷��Ώۂ̈ʒu
		@param	MainPos		[in]	���肷��Ώۂ̑O��̈ʒu
		@return	�����̉E���ɂ��邩��bool�l
		*/
		inline bool CollisionLine3D(const MyLib::Vector3& pos0, const MyLib::Vector3& pos1, const MyLib::Vector3& MainPos, const MyLib::Vector3& MainPosOld)
		{
			// ���E���̃x�N�g��
			MyLib::Vector3 vecLine;
			vecLine.x = pos1.x - pos0.x;
			vecLine.z = pos1.z - pos0.z;

			// �e�ƕǂ̃x�N�g��
			MyLib::Vector3 vecToPos;
			vecToPos.x = MainPos.x - pos0.x;
			vecToPos.z = MainPos.z - pos0.z;

			if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) <= 0)
			{// ���𒴂���
				return true;
			}

			return false;
		}

		/**
		@brief	�O�p�̓����ɂ��邩����
		@param	posCenter	[in]	���肷��O�p�`�̎�O�̒��_���W
		@param	posLeft		[in]	���肷��O�p�`�̍��̒��_���W
		@param	posRight	[in]	���肷��O�p�`�̉E�̒��_���W
		@param	MainPos		[in]	�����̈ʒu
		@param	MainPosOld	[in]	�����̑O��ʒu
		@return	���ɂ��邩��bool�l
		*/
		inline bool CollisionTriangle(const MyLib::Vector3& posCenter, const MyLib::Vector3& posLeft, const MyLib::Vector3& posRight, const MyLib::Vector3& MainPos, const MyLib::Vector3& MainPosOld)
		{
			// �����������̔���
			bool bHit = false;
			bool bLine1 = false, bLine2 = false, bLine3 = false;

			// �^�񒆂ƍ��̐�
			bLine1 = UtilFunc::Collision::CollisionLine3D(posCenter, posLeft, MainPos, MainPosOld);

			// ���ƉE�̐�
			bLine2 = UtilFunc::Collision::CollisionLine3D(posLeft, posRight, MainPos, MainPosOld);

			// �E�Ɛ^�񒆂̐�
			bLine3 = UtilFunc::Collision::CollisionLine3D(posRight, posCenter, MainPos, MainPosOld);

			// �S�Ă͈̔͂ɓ����Ă�����
			if (bLine1 == true && bLine2 == true && bLine3 == true)
			{
				bHit = true;
			}

			return bHit;
		}

		/**
		@brief	�l�p�̓����ɂ��邩����
		@details 4�̒��_���S�Č��܂��Ă���ꍇ�Ɏg��
		@param	posLeftUP	[in]	���肷��l�p�`����̒��_���W
		@param	posRightUP	[in]	���肷��l�p�`�E��̒��_���W
		@param	posLeftDW	[in]	���肷��l�p�`�����̒��_���W
		@param	posRightDW	[in]	���肷��l�p�`�E���̒��_���W
		@param	MainPos		[in]	�����̈ʒu
		@return	���ɂ��邩��bool�l
		*/
		inline bool CollisionSquare(const MyLib::Vector3& posLeftUP, const MyLib::Vector3& posRightUP, const MyLib::Vector3& posLeftDW, const MyLib::Vector3& posRightDW, const MyLib::Vector3& MainPos)
		{
			// �����������̔���
			bool bHit = false;
			bool bLine1 = false, bLine2 = false, bLine3 = false, bLine4 = false;

			// ����ƉE��
			bLine1 = UtilFunc::Collision::CollisionLine3D(posRightUP, posLeftUP, MainPos, MainPos);

			// �E��ƉE��
			bLine2 = UtilFunc::Collision::CollisionLine3D(posRightDW, posRightUP, MainPos, MainPos);

			// �E���ƍ���
			bLine3 = UtilFunc::Collision::CollisionLine3D(posLeftDW, posRightDW, MainPos, MainPos);

			// �����ƍ���
			bLine4 = UtilFunc::Collision::CollisionLine3D(posLeftUP, posLeftDW, MainPos, MainPos);

			// �S�Ă͈̔͂ɓ����Ă�����
			if (bLine1 == true && bLine2 == true && bLine3 == true && bLine4 == true)
			{
				// ��������
				bHit = true;
			}

			return bHit;
		}

		/**
		@brief	�l�p�̓����ɂ��邩����
		@details 4�̒��_���܂����߂��Ă��Ȃ��ꍇ�Ɏg��
		@param	posSquare	[in]	���肷��l�p�`�̒��S���W
		@param	SquareSize	[in]	���肷��l�p�`�̃T�C�Y
		@param	fSquareRot	[in]	���肷��l�p�`�̃T�C�Y
		@param	MainPos		[in]	�����̈ʒu
		@return	���ɂ��邩��bool�l
		*/
		inline bool CollisionSquare(MyLib::Vector3 posSquare, MyLib::Vector2 SquareSize, float fSquareRot, MyLib::Vector3 MainPos)
		{
			// �����������̔���
			bool bHit = false;
			bool bLine1 = false, bLine2 = false, bLine3 = false, bLine4 = false;

			float fLength = sqrtf(SquareSize.x * SquareSize.x + SquareSize.y * SquareSize.y);	// �Ίp���̒���
			float fAngle = atan2f(SquareSize.x, SquareSize.y);									// �Ίp���̌���

			// ���肷��l�p��4���_
			MyLib::Vector3 LeftUp = MyLib::Vector3(posSquare.x + sinf(fSquareRot - fAngle) * fLength, posSquare.y, posSquare.z + cosf(fSquareRot - fAngle) * fLength);
			MyLib::Vector3 RightUp = MyLib::Vector3(posSquare.x + sinf(fSquareRot + fAngle) * fLength, posSquare.y, posSquare.z + cosf(fSquareRot + fAngle) * fLength);
			MyLib::Vector3 LeftDown = MyLib::Vector3(posSquare.x + sinf(fSquareRot - XM_PI + fAngle) * fLength, posSquare.y, posSquare.z + cosf(fSquareRot - XM_PI + fAngle) * fLength);
			MyLib::Vector3 RightDown = MyLib::Vector3(posSquare.x + sinf(fSquareRot + XM_PI - fAngle) * fLength, posSquare.y, posSquare.z + cosf(fSquareRot + XM_PI - fAngle) * fLength);

			// ����ƉE��
			bLine1 = UtilFunc::Collision::CollisionLine3D(RightUp, LeftUp, MainPos, MainPos);

			// �E��ƉE��
			bLine2 = UtilFunc::Collision::CollisionLine3D(RightDown, RightUp, MainPos, MainPos);

			// �E���ƍ���
			bLine3 = UtilFunc::Collision::CollisionLine3D(LeftDown, RightDown, MainPos, MainPos);

			// �����ƍ���
			bLine4 = UtilFunc::Collision::CollisionLine3D(LeftUp, LeftDown, MainPos, MainPos);

			// �S�Ă͈̔͂ɓ����Ă�����
			if (bLine1 == true && bLine2 == true && bLine3 == true && bLine4 == true)
			{
				// ��������
				bHit = true;
			}

			return bHit;
		}

		/**
		@brief	�l�p�̓����ɂ��邩����(2D)
		@details 4�̒��_���S�Č��܂��Ă���ꍇ�Ɏg��
		@param	posLeftUP	[in]	���肷��l�p�`����̒��_���W
		@param	posRightUP	[in]	���肷��l�p�`�E��̒��_���W
		@param	posLeftDW	[in]	���肷��l�p�`�����̒��_���W
		@param	posRightDW	[in]	���肷��l�p�`�E���̒��_���W
		@param	MainPos		[in]	�����̈ʒu
		@return	���ɂ��邩��bool�l
		*/
		inline bool CollisionSquare2D(MyLib::Vector3 posLeftUP, MyLib::Vector3 posRightUP, MyLib::Vector3 posLeftDW, MyLib::Vector3 posRightDW, MyLib::Vector3 MainPos)
		{
			// �����������̔���
			bool bHit = false;
			bool bLine1 = false, bLine2 = false, bLine3 = false, bLine4 = false;

			// ����ƉE��
			bLine1 = UtilFunc::Collision::CollisionLine2D(posRightUP, posLeftUP, MainPos, MainPos);

			// �E��ƉE��
			bLine2 = UtilFunc::Collision::CollisionLine2D(posRightDW, posRightUP, MainPos, MainPos);

			// �E���ƍ���
			bLine3 = UtilFunc::Collision::CollisionLine2D(posLeftDW, posRightDW, MainPos, MainPos);

			// �����ƍ���
			bLine4 = UtilFunc::Collision::CollisionLine2D(posLeftUP, posLeftDW, MainPos, MainPos);

			// �S�Ă͈̔͂ɓ����Ă�����
			if (bLine1 == true && bLine2 == true && bLine3 == true && bLine4 == true)
			{
				bHit = true;
			}

			return bHit;
		}

		/**
		@brief	�l�p�Ǝl�p�̓����蔻��(2D)
		@details 4�̒��_���܂����߂��Ă��Ȃ��ꍇ�Ɏg��
		@param	MainPos		[inout]	�����̈ʒu
		@param	TargetPos	[inout]	�Ώۂ̈ʒu
		@param	MainSize	[in]	�����̃T�C�Y
		@param	TargetSize	[in]	�Ώۂ̃T�C�Y
		@param	fMainRot	[in]	������Y���̌���
		@param	fTargetRot	[in]	�Ώۂ�Y���̌���
		@return	�Փ˂�������bool�l
		*/
		inline bool CollisionSquareSquare2D(MyLib::Vector3& MainPos, MyLib::Vector3& TargetPos, MyLib::Vector2 MainSize, MyLib::Vector2 TargetSize, float fMainRot, float fTargetRot)
		{
			float fTargetLength = sqrtf(
				TargetSize.x * TargetSize.x +
				TargetSize.y * TargetSize.y);							// �Ίp���̒���
			float fTargetAngle = atan2f(TargetSize.x, TargetSize.y);	// �Ίp���̌���

			// ���肷��l�p��4���_
			MyLib::Vector3 LeftUp = MyLib::Vector3(
				TargetPos.x + sinf(fTargetRot - fTargetAngle) * fTargetLength,
				TargetPos.y,
				TargetPos.z + cosf(fTargetRot - fTargetAngle) * fTargetLength);

			MyLib::Vector3 RightUp = MyLib::Vector3(
				TargetPos.x + sinf(fTargetRot + fTargetAngle) * fTargetLength,
				TargetPos.y,
				TargetPos.z + cosf(fTargetRot + fTargetAngle) * fTargetLength);

			MyLib::Vector3 LeftDown = MyLib::Vector3(
				TargetPos.x + sinf(fTargetRot - XM_PI + fTargetAngle) * fTargetLength,
				TargetPos.y,
				TargetPos.z + cosf(fTargetRot - XM_PI + fTargetAngle) * fTargetLength);

			MyLib::Vector3 RightDown = MyLib::Vector3(
				TargetPos.x + sinf(fTargetRot + XM_PI - fTargetAngle) * fTargetLength,
				TargetPos.y,
				TargetPos.z + cosf(fTargetRot + XM_PI - fTargetAngle) * fTargetLength);

			//***********************
			// ��`�̔���
			//***********************
			if (UtilFunc::Collision::CollisionSquare(MainPos, MainSize, fMainRot, LeftUp) == true)
			{// ����
				return true;
			}
			if (UtilFunc::Collision::CollisionSquare(MainPos, MainSize, fMainRot, RightUp) == true)
			{// �E��
				return true;
			}
			if (UtilFunc::Collision::CollisionSquare(MainPos, MainSize, fMainRot, LeftDown) == true)
			{// ����
				return true;
			}
			if (UtilFunc::Collision::CollisionSquare(MainPos, MainSize, fMainRot, RightDown) == true)
			{// �E��
				return true;
			}

			return false;
		}

		/**
		@brief	�~�Ƌ�`�̓����蔻��(2D)
		@param	posCircle		[inout]	�~�̒��S���W
		@param	posSquare		[inout]	��`�̒��S���W
		@param	rotSquare		[in]	��`�̌���
		@param	fCircleRadius	[in]	�~�̔��a
		@param	SquareSize		[in]	��`�̃T�C�Y
		@return	�Փ˂�������bool�l
		*/
		inline bool CollisionCircleSquare2D(MyLib::Vector3& posCircle, MyLib::Vector3& posSquare, MyLib::Vector3 rotSquare, float fCircleRadius, MyLib::Vector2 SquareSize)
		{
			float fSquareSizeX = SquareSize.x;	// ��`�̃T�C�YX
			float fSquareSizeY = SquareSize.y;	// ��`�̃T�C�YY

			float fLength = 0.0f;	// �Ίp���̒���
			float fAngle = 0.0f;	// �Ίp���̌���

			MyLib::Vector3 LeftUp, RightUp, LeftDown, RightDown;

			//****************************************************
			// X�̃T�C�Y�ɉ~�̔��a�𑫂�����`�̔���
			//****************************************************
			fSquareSizeX += fCircleRadius;	// ��`�̃T�C�YX
			fSquareSizeY = SquareSize.y;	// ��`�̃T�C�YY

			fLength = sqrtf(fSquareSizeX * fSquareSizeX + fSquareSizeY * fSquareSizeY);	// �Ίp���̒���
			fAngle = atan2f(fSquareSizeX, fSquareSizeY);								// �Ίp���̌���

			// ���肷��l�p��4���_
			LeftUp.x = posSquare.x + sinf(rotSquare.z - XM_PI + fAngle) * fLength;
			LeftUp.y = posSquare.y + cosf(rotSquare.z - XM_PI + fAngle) * fLength;
			LeftUp.z = 0.0f;

			RightUp.x = posSquare.x + sinf(rotSquare.z + XM_PI - fAngle) * fLength;
			RightUp.y = posSquare.y + cosf(rotSquare.z + XM_PI - fAngle) * fLength;
			RightUp.z = 0.0f;

			LeftDown.x = posSquare.x + sinf(rotSquare.z - fAngle) * fLength;
			LeftDown.y = posSquare.y + cosf(rotSquare.z - fAngle) * fLength;
			LeftDown.z = 0.0f;

			RightDown.x = posSquare.x + sinf(rotSquare.z + fAngle) * fLength;
			RightDown.y = posSquare.y + cosf(rotSquare.z + fAngle) * fLength;
			RightDown.z = 0.0f;

			// ��`�̔���
			if (UtilFunc::Collision::CollisionSquare2D(LeftUp, RightUp, LeftDown, RightDown, posCircle) == true)
			{// ��`�ɓ��������ꍇ
				return true;
			}

			//****************************************************
			// Y�̃T�C�Y�ɉ~�̔��a�𑫂�����`�̔���
			//****************************************************
			fSquareSizeX = SquareSize.x;	// ��`�̃T�C�YX
			fSquareSizeY += fCircleRadius;	// ��`�̃T�C�YY

			fLength = sqrtf(fSquareSizeX * fSquareSizeX + fSquareSizeY * fSquareSizeY);	// �Ίp���̒���
			fAngle = atan2f(fSquareSizeX, fSquareSizeY);								// �Ίp���̌���

			// ���肷��l�p��4���_
			LeftUp.x = posSquare.x + sinf(rotSquare.z - XM_PI + fAngle) * fLength;
			LeftUp.y = posSquare.y + cosf(rotSquare.z - XM_PI + fAngle) * fLength;
			LeftUp.z = 0.0f;

			RightUp.x = posSquare.x + sinf(rotSquare.z + XM_PI - fAngle) * fLength;
			RightUp.y = posSquare.y + cosf(rotSquare.z + XM_PI - fAngle) * fLength;
			RightUp.z = 0.0f;

			LeftDown.x = posSquare.x + sinf(rotSquare.z - fAngle) * fLength;
			LeftDown.y = posSquare.y + cosf(rotSquare.z - fAngle) * fLength;
			LeftDown.z = 0.0f;

			RightDown.x = posSquare.x + sinf(rotSquare.z + fAngle) * fLength;
			RightDown.y = posSquare.y + cosf(rotSquare.z + fAngle) * fLength;
			RightDown.z = 0.0f;

			// ��`�̔���
			if (UtilFunc::Collision::CollisionSquare2D(LeftUp, RightUp, LeftDown, RightDown, posCircle) == true)
			{// ��`�ɓ��������ꍇ
				return true;
			}

			//***********************
			// �e���_���̉~�̔���
			//***********************
			//****************************************************
			// ���̃T�C�Y
			//****************************************************
			fSquareSizeX = SquareSize.x;	// ��`�̃T�C�YX
			fSquareSizeY = SquareSize.y;	// ��`�̃T�C�YY

			fLength = sqrtf(fSquareSizeX * fSquareSizeX + fSquareSizeY * fSquareSizeY);	// �Ίp���̒���
			fAngle = atan2f(fSquareSizeX, fSquareSizeY);								// �Ίp���̌���

			// ���肷��l�p��4���_
			LeftUp.x = posSquare.x + sinf(rotSquare.z - XM_PI + fAngle) * fLength;
			LeftUp.y = posSquare.y + cosf(rotSquare.z - XM_PI + fAngle) * fLength;
			LeftUp.z = 0.0f;

			RightUp.x = posSquare.x + sinf(rotSquare.z + XM_PI - fAngle) * fLength;
			RightUp.y = posSquare.y + cosf(rotSquare.z + XM_PI - fAngle) * fLength;
			RightUp.z = 0.0f;

			LeftDown.x = posSquare.x + sinf(rotSquare.z - fAngle) * fLength;
			LeftDown.y = posSquare.y + cosf(rotSquare.z - fAngle) * fLength;
			LeftDown.z = 0.0f;

			RightDown.x = posSquare.x + sinf(rotSquare.z + fAngle) * fLength;
			RightDown.y = posSquare.y + cosf(rotSquare.z + fAngle) * fLength;
			RightDown.z = 0.0f;

			if (UtilFunc::Collision::CircleRange2D(posCircle, LeftUp, fCircleRadius, 0.0f) == true)
			{// ����
				return true;
			}
			if (UtilFunc::Collision::CircleRange2D(posCircle, RightUp, fCircleRadius, 0.0f) == true)
			{// �E��
				return true;
			}
			if (UtilFunc::Collision::CircleRange2D(posCircle, LeftDown, fCircleRadius, 0.0f) == true)
			{// ����
				return true;
			}
			if (UtilFunc::Collision::CircleRange2D(posCircle, RightDown, fCircleRadius, 0.0f) == true)
			{// �E��
				return true;
			}

			// �������ĂȂ������Ԃ�
			return false;
		}

		/**
		@brief	�~�Ƌ�`�̓����蔻��(3D)
		@param	posCircle		[inout]	�~�̒��S���W
		@param	posSquare		[inout]	��`�̒��S���W
		@param	rotSquare		[in]	��`�̌���
		@param	fCircleRadius	[in]	�~�̔��a
		@param	SquareSize		[in]	��`�̃T�C�Y
		@return	�Փ˂�������bool�l
		*/
		inline bool CollisionCircleSquare3D(MyLib::Vector3& posCircle, MyLib::Vector3& posSquare, MyLib::Vector3 rotSquare, float fCircleRadius, MyLib::Vector2 SquareSize)
		{
			float fSquareSizeX = SquareSize.x;	// ��`�̃T�C�YX
			float fSquareSizeY = SquareSize.y;	// ��`�̃T�C�YY

			float fLength = 0.0f;	// �Ίp���̒���
			float fAngle = 0.0f;	// �Ίp���̌���

			MyLib::Vector3 LeftUp, RightUp, LeftDown, RightDown;

			//****************************************************
			// X�̃T�C�Y�ɉ~�̔��a�𑫂�����`�̔���
			//****************************************************
			fSquareSizeX += fCircleRadius;	// ��`�̃T�C�YX
			fSquareSizeY = SquareSize.y;	// ��`�̃T�C�YY

			fLength = sqrtf(fSquareSizeX * fSquareSizeX + fSquareSizeY * fSquareSizeY);	// �Ίp���̒���
			fAngle = atan2f(fSquareSizeX, fSquareSizeY);								// �Ίp���̌���

			// ���肷��l�p��4���_
			LeftUp = MyLib::Vector3(posSquare.x + cosf(rotSquare.x) * sinf(rotSquare.y - fAngle) * fLength, posSquare.y, posSquare.z + cosf(rotSquare.x) * cosf(rotSquare.y - fAngle) * fLength);
			RightUp = MyLib::Vector3(posSquare.x + cosf(rotSquare.x) * sinf(rotSquare.y + fAngle) * fLength, posSquare.y, posSquare.z + cosf(rotSquare.x) * cosf(rotSquare.y + fAngle) * fLength);
			LeftDown = MyLib::Vector3(posSquare.x + cosf(rotSquare.x) * sinf(rotSquare.y - XM_PI + fAngle) * fLength, posSquare.y, posSquare.z + cosf(rotSquare.x) * cosf(rotSquare.y - XM_PI + fAngle) * fLength);
			RightDown = MyLib::Vector3(posSquare.x + cosf(rotSquare.x) * sinf(rotSquare.y + XM_PI - fAngle) * fLength, posSquare.y, posSquare.z + cosf(rotSquare.x) * cosf(rotSquare.y + XM_PI - fAngle) * fLength);

			// ��`�̔���
			if (UtilFunc::Collision::CollisionSquare(LeftUp, RightUp, LeftDown, RightDown, posCircle) == true)
			{// ��`�ɓ��������ꍇ
				return true;
			}

			//****************************************************
			// Y�̃T�C�Y�ɉ~�̔��a�𑫂�����`�̔���
			//****************************************************
			fSquareSizeX = SquareSize.x;	// ��`�̃T�C�YX
			fSquareSizeY += fCircleRadius;	// ��`�̃T�C�YY

			fLength = sqrtf(fSquareSizeX * fSquareSizeX + fSquareSizeY * fSquareSizeY);	// �Ίp���̒���
			fAngle = atan2f(fSquareSizeX, fSquareSizeY);								// �Ίp���̌���

			// ���肷��l�p��4���_
			LeftUp = MyLib::Vector3(posSquare.x + cosf(rotSquare.x) * sinf(rotSquare.y - fAngle) * fLength, posSquare.y, posSquare.z + cosf(rotSquare.x) * cosf(rotSquare.y - fAngle) * fLength);
			RightUp = MyLib::Vector3(posSquare.x + cosf(rotSquare.x) * sinf(rotSquare.y + fAngle) * fLength, posSquare.y, posSquare.z + cosf(rotSquare.x) * cosf(rotSquare.y + fAngle) * fLength);
			LeftDown = MyLib::Vector3(posSquare.x + cosf(rotSquare.x) * sinf(rotSquare.y - XM_PI + fAngle) * fLength, posSquare.y, posSquare.z + cosf(rotSquare.x) * cosf(rotSquare.y - XM_PI + fAngle) * fLength);
			RightDown = MyLib::Vector3(posSquare.x + cosf(rotSquare.x) * sinf(rotSquare.y + XM_PI - fAngle) * fLength, posSquare.y, posSquare.z + cosf(rotSquare.x) * cosf(rotSquare.y + XM_PI - fAngle) * fLength);

			// ��`�̔���
			if (UtilFunc::Collision::CollisionSquare(LeftUp, RightUp, LeftDown, RightDown, posCircle) == true)
			{// ��`�ɓ��������ꍇ
				return true;
			}

			//***********************
			// �e���_���̉~�̔���
			//***********************
			if (UtilFunc::Collision::CircleRange3D(posCircle, LeftUp, fCircleRadius, fCircleRadius) == true)
			{// ����
				return true;
			}
			if (UtilFunc::Collision::CircleRange3D(posCircle, RightUp, fCircleRadius, fCircleRadius) == true)
			{// �E��
				return true;
			}
			if (UtilFunc::Collision::CircleRange3D(posCircle, LeftDown, fCircleRadius, fCircleRadius) == true)
			{// ����
				return true;
			}
			if (UtilFunc::Collision::CircleRange3D(posCircle, RightDown, fCircleRadius, fCircleRadius) == true)
			{// �E��
				return true;
			}

			// �������ĂȂ������Ԃ�
			return false;
		}

		/**
		@brief	��̓����蔻��(3D)
		@param	posCenter		[in]	��̎n�_���_���W
		@param	posLeft			[in]	��̍������_���W
		@param	posRight		[in]	��̉E�����_���W
		@param	TargetPos		[in]	���肷��Ώۂ̈ʒu
		@param	fTargetRadius	[in]	���肷��Ώۂ̔��a
		@return	�Փ˂�������bool�l
		*/
		inline bool CollisionFan3D(MyLib::Vector3 posCenter, MyLib::Vector3 posLeft, MyLib::Vector3 posRight, MyLib::Vector3 TargetPos, float fTargetRadius)
		{
			// �����������̔���
			bool bHit = false;
			bool bLine1 = false, bLine2 = false, bCircle = false;

			// ���̓_�Ƃ̐���
			bLine1 = UtilFunc::Collision::CollisionLine3D(posLeft, posCenter, TargetPos, TargetPos);

			// �E�̓_�Ƃ̐���
			bLine2 = UtilFunc::Collision::CollisionLine3D(posCenter, posRight, TargetPos, TargetPos);

			// ��̔��a
			float fLen =
				sqrtf((posLeft.x - posCenter.x) * (posLeft.x - posCenter.x)
					+ (posLeft.z - posCenter.z) * (posLeft.z - posCenter.z));

			// �~�̓����蔻��
			if (UtilFunc::Collision::CircleRange3D(posCenter, TargetPos, fLen, fTargetRadius) == true)
			{// �������Ă�����
				bCircle = true;
			}

			// �S�Ă͈̔͂ɓ����Ă�����
			if (bLine1 == true && bLine2 == true && bCircle == true)
			{
				bHit = true;
			}

			return bHit;
		}

#if 0
		/**
		@brief	���E���̔���(3D)
		@param	posMain			[in]	���S�ƂȂ�l�̈ʒu
		@param	posTarget		[in]	�Ώۂ̈ʒu
		@param	mainRotY		[in]	����
		@param	fieldofview		[in]	����p
		@return	�Փ˂�������bool�l
		*/
		inline bool CollisionViewRange3D(const MyLib::Vector3& posMain, MyLib::Vector3& posTarget, float mainRotY, float fieldofview)
		{

			// 2�L�����̃x�N�g��
			MyLib::Vector3 toPlayer = posTarget - posMain;

			// �O���x�N�g��
			MyLib::Vector3 forward = UtilFunc::Transformation::RotationChangeToForwardVector(mainRotY);

			// �x�N�g���ƑO���x�N�g���̊p�x�v�Z
			float angle = (toPlayer.Dot(forward) / (toPlayer.Length() * forward.Length()));
			angle = acos(angle);

			// ���E�̒��ɂ��邩����
			fieldofview = XMConvertToRadians(fieldofview);
			if (angle <= fieldofview / 2.0f)
			{
				return true;
			}

			return false;
		}
#endif
	}

	/**
	@brief	�ϊ��֐�
	*/
	namespace Transformation
	{
		/**
		@brief	�p�x�̐��K��(�P��)
		@details -�� or �΂𒴂����p�x��␳����B�͈͓��Ɏ��܂�܂Ŗ������[�v
		@param	fRot	[inout]	�␳����p�x
		@return	void
		*/
		inline void RotNormalize(float& fRot)
		{
			while (1)
			{
				// 1�����z������␳����
				if (fRot < -XM_PI)
				{
					fRot += XM_PI * 2.0f;
				}
				else if (fRot > XM_PI)
				{
					fRot -= XM_PI * 2.0f;
				}

				if (fRot >= -XM_PI && fRot <= XM_PI)
				{// �S�Đ��K���ς݂ŏI��
					break;
				}
			}
		}

		/**
		@brief	�p�x�̐��K��(VECTOR3)
		@details -�� or �΂𒴂����p�x��␳����B�͈͓��Ɏ��܂�܂Ŗ������[�v
		@param	fRot	[inout]	�␳����p�x
		@return	void
		*/
		inline void RotNormalize(MyLib::Vector3& rot)
		{
			// ���ꂼ��̐��K��
			UtilFunc::Transformation::RotNormalize(rot.x);
			UtilFunc::Transformation::RotNormalize(rot.y);
			UtilFunc::Transformation::RotNormalize(rot.z);
		}

		/**
		@brief	�x���@�����W�A���ɕϊ�
		@param	degree	[in]	�x���@�̊p�x
		@return	���W�A���p�x
		*/
		inline float DegreeChangeToRadian(float degree)
		{
			return degree * (XM_PI / 180.0f);
		}

		/**
		@brief	���W�A���p�x��x���@�ɕϊ�
		@param	radian	[in]	���W�A���p�x
		@return	�x���@
		*/
		inline float RadianChangeToDegree(float radian)
		{
			return radian * (180.0f / XM_PI);
		}

		/**
		@brief	�l�̐��K������
		@param	Value		[inout]	�␳�������l
		@param	MaxValue	[in]	�ő�l
		@param	MinValue	[in]	�ŏ��l
		@return	void
		*/
		template<class T>inline void ValueNormalize(T& Value, T MaxValue, T MinValue)
		{
			if (Value >= MaxValue)
			{
				// �ő�l�ɕ␳
				Value = MaxValue;
			}
			else if (Value <= MinValue)
			{
				// �ŏ��l�ɕ␳
				Value = MinValue;
			}
		}

		/**
		@brief	���[���h�}�g���b�N�X��pos�ɕϊ�
		@param	worldmtx	[in]	���[���h�}�g���b�N�X
		@return	�ʒu
		*/
		inline MyLib::Vector3 WorldMtxChangeToPosition(XMMATRIX worldmtx)
		{
			return MyLib::Vector3(worldmtx.r[3].m128_f32[0], worldmtx.r[3].m128_f32[1], worldmtx.r[3].m128_f32[2]);
		}

		/**
		@brief	���[���h�}�g���b�N�X��rot�ɕϊ�
		@param	worldmtx	[in]	���[���h�}�g���b�N�X
		@return	����(��Βl)
		*/
		inline MyLib::Vector3 WorldMtxChangeToRotation(XMMATRIX worldmtx)
		{
			MyLib::Vector3 rot = mylib_const::DEFAULT_VECTOR3;

			/*rot.x = atan2f(worldmtx._32, worldmtx._33);
			rot.y = atan2f(-worldmtx._31, sqrtf(worldmtx._32 * worldmtx._32 + worldmtx._33 * worldmtx._33));
			rot.z = atan2f(worldmtx._21, worldmtx._11);*/

			// XYZ ���� (���[�� �� �s�b�` �� ���[)
			/*rot.x = atan2f(-worldmtx._23, worldmtx._22);
			rot.y = asinf(worldmtx._21);
			rot.z = atan2f(-worldmtx._12, worldmtx._11);*/

			// ZYX ���� (���[ �� �s�b�` �� ���[��)
			// rot.z = atan2f(worldmtx._21, worldmtx._11);
			// rot.y = asinf(-worldmtx._31);
			// rot.x = atan2f(worldmtx._32, worldmtx._33);

			// ZYZ ���� (���[ �� �s�b�` �� ���[)
			// rot.z = atan2f(worldmtx._32, worldmtx._31);
			// rot.y = acosf(worldmtx._33);
			// rot.z = atan2f(worldmtx._23, -worldmtx._13);
			return rot;
		}

		/**
		@brief	������O���x�N�g���ɕϊ�
		@param	rot	[in]	����
		@return	�O���x�N�g��
		*/
		inline MyLib::Vector3 RotationChangeToForwardVector(float rot)
		{
			return MyLib::Vector3(sinf(XM_PI + rot), 0.0f, cosf(XM_PI + rot));
		}

		/**
		@brief	�����_���l�擾
		@param	nMinNum	[in]	�͈͂̍ŏ��l
		@param	nMaxNum	[in]	�͈͂̍ő�l
		@return	���I���ꂽ�����_���l
		*/
		inline int Random(int nMinNum, int nMaxNum)
		{
			// �͈�
			int nRange = nMaxNum - nMinNum;

			if (nMinNum == 0)
			{
				// �͈͂�1���Z
				nRange += 1;
			}

			if (nMinNum + 1 == nMaxNum || nMaxNum - 1 == nMinNum)
			{
				nRange += 1;
			}

			// �����_������
			return (rand() % nRange + nMinNum);
		}

		/**
		@brief	�����_���ȉ~�����擾
		@return	���I���ꂽ�����_���l
		*/
		inline float GetRandomPi()
		{
			return static_cast<float>(UtilFunc::Transformation::Random(-314, 314) * 0.01f);
		}

		/**
		@brief	���͈͂̃����_���x�N�g���擾
		@return	���̃����_���ȃx�N�g���l
		*/
		inline MyLib::Vector3 GetRandomVecSphere()
		{
			// ���x�N�g��
			MyLib::Vector3 vecSphere = mylib_const::DEFAULT_VECTOR3;

			// ���͈͓̔��Ń����_������
			float fRot = UtilFunc::Transformation::GetRandomPi(), fRotPhi = UtilFunc::Transformation::GetRandomPi();

			vecSphere.x = cosf(fRot) * sinf(fRotPhi);
			vecSphere.y = sinf(fRot);
			vecSphere.z = cosf(fRot) * cosf(fRotPhi);

			return vecSphere;
		}

		/**
		@brief	���͈͂̃����_���Ȉʒu�擾
		@param	pos		[in]	���̒��S���W
		@param	fRadius	[in]	�擾���鋅�̔��a
		@return	���I���ꂽ�����_���Ȉʒu
		*/
		inline MyLib::Vector3 GetRandomPositionSphere(MyLib::Vector3 pos, float fRadius)
		{
			MyLib::Vector3 spherepos = mylib_const::DEFAULT_VECTOR3;
			MyLib::Vector3 vec = GetRandomVecSphere();

			// �������v�Z
			spherepos = vec * fRadius;
			spherepos += pos;

			return spherepos;
		}

		/**
		@brief	��������ɕ��������ϊ�
		@param	size		[in]	���̃T�C�Y
		@param	height		[in]	�ύX��̍���
		@return	�񎟌��T�C�Y
		*/
		inline MyLib::Vector2 AdjustSizeByHeight(MyLib::Vector2 size, float height)
		{
			MyLib::Vector2 result = size;
			result.y = height;

			// �����Ɣ䗦���畝���v�Z
			result.x = height * UtilFunc::Calculation::AspectRatio(size);
			return result;
		}

		/**
		@brief	������ɍ����������v�Z
		@param	size		[in]	���̃T�C�Y
		@param	width		[in]	�ύX��̕�
		@return	�񎟌��T�C�Y
		*/
		inline MyLib::Vector2 AdjustSizeByWidth(MyLib::Vector2 size, float width)
		{
			MyLib::Vector2 result = size;
			result.x = width;

			// ���Ɣ䗦���獂�����v�Z
			result.y = width / UtilFunc::Calculation::AspectRatio(size);
			return result;
		}

		/**
		@brief	HSV�l��RGB�l�ɕϊ�
		@details https://ja.wikipedia.org/wiki/HSV%E8%89%B2%E7%A9%BA%E9%96%93
		@param	H	[in]	�F��
		@param	S	[in]	�ʓx
		@param	V	[in]	���x
		@return	RGB�l
		*/
		inline MyLib::Color HSVtoRGB(float H, float S, float V)
		{
			if (H > 360.0f)
			{
				H -= 360.0f;
			}
			else if (H < 0.0f)
			{
				H += 360.0f;
			}
			float C = V * S;
			float X = C * (1 - (float)abs(fmod(H / 60.0f, 2) - 1));
			float m = V - C;

			// RGB�ʂ̐��l
			float R = 0.0f, G = 0.0f, B = 0.0f;
			if (H >= 0.0f && H < 60.0f)
			{
				R = C;
				G = X;
				B = 0.0f;
			}
			else if (H >= 60.0f && H < 120.0f)
			{
				R = X;
				G = C;
				B = 0.0f;
			}
			else if (H >= 120.0f && H < 180.0f)
			{
				R = 0.0f;
				G = C;
				B = X;
			}
			else if (H >= 180.0f && H < 240.0f)
			{
				R = 0.0f;
				G = X;
				B = C;
			}
			else if (H >= 240.0f && H < 300.0f)
			{
				R = X;
				G = 0.0f;
				B = C;
			}
			else 
			{
				R = C;
				G = 0.0f;
				B = X;
			}

			return MyLib::Color(R + m, G + m, B + m, 1.0f);
		}

		/**
		@brief	���C�h�����񂩂�}���`�o�C�g������ɕϊ�����֐�
		@param	wideStr		[in]	���C�h������
		@return	�}���`�o�C�g������
		*/
		inline std::string WideToMultiByte(const wchar_t* wideStr)
		{
			if (wideStr == nullptr)
				return std::string();

			// ���C�h������̒������擾
			int wideLength = wcslen(wideStr);

			// �}���`�o�C�g������̒������v�Z
			int multiLength = WideCharToMultiByte(CP_UTF8, 0, wideStr, wideLength, nullptr, 0, nullptr, nullptr);

			if (multiLength == 0)
				return std::string();

			// �}���`�o�C�g��������i�[���邽�߂̃o�b�t�@���m��
			std::string multiString(multiLength, 0);

			// ���C�h��������}���`�o�C�g������ɕϊ�
			WideCharToMultiByte(CP_UTF8, 0, wideStr, wideLength, &multiString[0], multiLength, nullptr, nullptr);

			return multiString;
		}


		/**
		@brief	\\\\��\\�ɒu������
		@param	str		[in]	������
		@return	�ϊ����ꂽstring����
		*/
		inline std::string ReplaceBackslash(std::string str)
		{
			size_t pos = 0;

			while ((pos = str.find("\\\\", pos)) != std::string::npos)
			{
				// \\\\��\\�ɒu��
				str.replace(pos, 2, "\\");

				// \\�̎����猟�����ĊJ
				pos += 1;
			}
			return str;
		}

		/**
		@brief	/��\\�ɒu������
		@param	str		[in]	������
		@return	�ϊ����ꂽstring����
		*/
		inline std::string ReplaceForwardSlashes(std::string str)
		{
			for (size_t i = 0; i < str.size(); i++) 
			{
				if (str[i] == '/') 
				{
					str.replace(i, 1, "\\");
				}
			}
			return str;
		}
	}

}



#endif