//=============================================================================
// 
// ���g�̃��C�u���� [mylib.h]
// Author : ���n�Ή�
// 
//=============================================================================

#ifndef _MYLIB_H_
#define _MYLIB_H_		// ��d�C���N���[�h�h�~

#include <json.hpp>

/**
	@brief	�}�C���C�u����
*/
namespace MyLib
{

	/**
	@brief	Vector3 �y3�������z
	*/
	struct Vector3 : public XMFLOAT3
	{
		// �R���X�g���N�^
		Vector3(float x, float y, float z) : XMFLOAT3(x, y, z) {}
		Vector3(float xyz) : XMFLOAT3(xyz, xyz, xyz) {}

		// �f�t�H���g�R���X�g���N�^
		Vector3() : XMFLOAT3(0.0f, 0.0f, 0.0f) {}

		// JSON����̓ǂݍ���
		void from_json(const nlohmann::json& j)
		{
			j.at("x").get_to(x);
			j.at("y").get_to(y);
			j.at("z").get_to(z);
		}

		// JSON�ւ̏�������
		void to_json(nlohmann::json& j) const
		{
			j["x"] = x;
			j["y"] = y;
			j["z"] = z;
		}

		//--------------------------
		// ���Z
		//--------------------------
		inline Vector3 operator + (const float& o) const
		{
			return Vector3(x + o, y + o, z + o);
		}

		inline Vector3 operator + (const Vector3& o) const
		{
			return Vector3(x + o.x, y + o.y, z + o.z);
		}

		//--------------------------
		// ���Z
		//--------------------------
		inline Vector3 operator - (const float& o) const
		{
			return Vector3(x - o, y - o, z - o);
		}

		inline Vector3 operator - () const
		{
			return Vector3(-x, -y, -z);
		}

		inline Vector3 operator - (const Vector3& o) const
		{
			return Vector3(x - o.x, y - o.y, z - o.z);
		}

		//--------------------------
		// ��Z
		//--------------------------
		inline Vector3 operator * (const float& o) const
		{
			return Vector3(x * o, y * o, z * o);
		}

		//--------------------------
		// ���Z
		//--------------------------
		inline Vector3 operator / (const float& o) const
		{
			return Vector3(x / o, y / o, z / o);
		}


		//--------------------------
		// ���Z���
		//--------------------------
		inline Vector3& operator += (const float& o)
		{
			x += o;
			y += o;
			z += o;
			return *this;
		}

		inline Vector3& operator += (const Vector3& o)
		{
			x += o.x;
			y += o.y;
			z += o.z;
			return *this;
		}

		//--------------------------
		// ���Z���
		//--------------------------
		inline Vector3& operator -= (const float& o)
		{
			x -= o;
			y -= o;
			z -= o;
			return *this;
		}

		inline Vector3& operator -= (const Vector3& o)
		{
			x -= o.x;
			y -= o.y;
			z -= o.z;
			return *this;
		}

		//--------------------------
		// ��Z���
		//--------------------------
		inline Vector3& operator *= (const float& o)
		{
			x *= o;
			y *= o;
			z *= o;
			return *this;
		}

		//--------------------------
		// ���Z���
		//--------------------------
		inline Vector3& operator /= (const float& o)
		{
			x /= o;
			y /= o;
			z /= o;
			return *this;
		}


		/**
		@brief	�x�N�g���̒���
		@return	���߂�ꂽ����
		*/
		inline float Length()
		{
			return sqrtf(x * x + y * y + z * z);
		}

		/**
		@brief	XZ�x�N�g���̒���
		@return	���߂�ꂽ����
		*/
		inline float LengthXZ()
		{
			return sqrtf(x * x + z * z);
		}

		/**
		@brief	XY�x�N�g���̒���
		@return	���߂�ꂽ����
		*/
		inline float LengthXY()
		{
			return sqrtf(x * x + y * y);
		}

		/**
		@brief	�x�N�g���̒�����2��
		@return	���߂�ꂽ����
		*/
		inline float LengthSquared() const
		{
			return x * x + y * y + z * z;
		}

		/**
		@brief	XZ�̌���
		@return	����
		*/
		inline float AngleXZ(const Vector3& v)
		{
			return atan2f(x - v.x, z - v.z);
		}

		/**
		@brief	XY�̌���
		@return	����
		*/
		inline float AngleXY(const Vector3& v)
		{
			return atan2f(x - v.x, y - v.y);
		}

		/**
		@brief	�x�N�g���̋���
		@return	2�̃x�N�g���̋���
		*/
		float Distance(const Vector3& v) const
		{
			return sqrtf((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y) + (v.z - z) * (v.z - z));
		}

		/**
		@brief	XZ���ʂ̃x�N�g���̋���
		@return	2�̃x�N�g���̋���(XZ����)
		*/
		float DistanceXZ(const Vector3& v) const
		{
			return sqrtf((v.x - x) * (v.x - x) + (v.z - z) * (v.z - z));
		}

		/**
		@brief	�x�N�g���̋�����2��
		@return	2�̃x�N�g���̋�����2��
		*/
		float DistSquared(const Vector3& v) const
		{
			return (v.x - x) * (v.x - x) + (v.y - y) * (v.y - y) + (v.z - z) * (v.z - z);
		}

		/**
		@brief	�P�ʃx�N�g��
		@return	���K�����ꂽ�x�N�g��
		*/
		inline Vector3 Normal()
		{
			// XMFLOAT3����XMVECTOR�ɕϊ�
			XMVECTOR vec = XMLoadFloat3(this);

			// �x�N�g���𐳋K��
			XMVECTOR vecNor = XMVector3Normalize(vec);

			// ���ʂ�XMFLOAT3�ɖ߂�
			Vector3 result;
			XMStoreFloat3(&result, vecNor);

			return result;
		}

		/**
		@brief	�O��
		@return	2�̃x�N�g���̊O��
		*/
		Vector3 Cross(const Vector3& v) const
		{
			return Vector3(
				y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x);
		}

		/**
		@brief	����
		@return	2�̃x�N�g���̓���
		*/
		Vector3 Dot(const Vector3& v) const
		{
			return Vector3(x * v.x + y * v.y + z * v.z);
		}

		/**
		@brief	�x�N�g���𔽓]
		@return	���]���ꂽ�x�N�g��
		*/
		inline Vector3 Invert()
		{
			return Vector3(-x, -y, -z);
		}

		/**
		@brief	�w�肳�ꂽ���e�덷�͈͓��ɂ��邩����
		@param	range	[in]	���e�͈�
		@return	���茋��
		*/
		inline bool IsNearlyZero(float range) const
		{
			if (abs(x) <= range &&
				abs(y) <= range &&
				abs(z) <= range)
			{
				return true;
			}
			return false;
		}

		/**
		@brief	�v�f���[����
		@return	���茋��
		*/
		inline bool IsZero() const
		{
			if (x == 0.0f &&
				y == 0.0f &&
				z == 0.0f)
			{
				return true;
			}
			return false;
		}

		/**
		@brief	������ϊ�
		@return	(x, y, z)�̌`���ŕϊ����ꂽ������
		*/
		inline std::string ToString() const
		{
			std::stringstream text;
			text << "(" << x << ", " << y << ", " << z << ")";
			return text.str();
		}
	};

	struct Vector2 : public XMFLOAT2
	{
		// �R���X�g���N�^
		Vector2(float x, float y) : XMFLOAT2(x, y) {}
		Vector2(float xy) : XMFLOAT2(xy, xy) {}

		// �f�t�H���g�R���X�g���N�^
		Vector2() : XMFLOAT2(0.0f, 0.0f) {}

		// JSON����̓ǂݍ���
		void from_json(const nlohmann::json& j)
		{
			j.at("x").get_to(x);
			j.at("y").get_to(y);
		}

		// JSON�ւ̏�������
		void to_json(nlohmann::json& j) const
		{
			j["x"] = x;
			j["y"] = y;
		}

		//--------------------------
		// ���Z
		//--------------------------
		inline Vector2 operator + (const float& o) const
		{
			return Vector2(x + o, y + o);
		}

		inline Vector2 operator + (const Vector2& o) const
		{
			return Vector2(x + o.x, y + o.y);
		}

		//--------------------------
		// ���Z
		//--------------------------
		inline Vector2 operator - (const float& o) const
		{
			return Vector2(x - o, y - o);
		}

		inline Vector2 operator - () const
		{
			return Vector2(-x, -y);
		}

		inline Vector2 operator - (const Vector2& o) const
		{
			return Vector2(x - o.x, y - o.y);
		}

		//--------------------------
		// ���Z���
		//--------------------------
		inline Vector2& operator += (const float& o)
		{
			x += o;
			y += o;
			return *this;
		}

		inline Vector2& operator += (const Vector2& o)
		{
			x += o.x;
			y += o.y;
			return *this;
		}

		//--------------------------
		// ���Z���
		//--------------------------
		inline Vector2& operator -= (const float& o)
		{
			x -= o;
			y -= o;
			return *this;
		}

		inline Vector2& operator -= (const Vector2& o)
		{
			x -= o.x;
			y -= o.y;
			return *this;
		}

		/**
		@brief	�x�N�g���̒���
		@return	���߂�ꂽ����
		*/
		inline float Length()
		{
			return sqrtf(x * x + y * y);
		}

		/**
		@brief	�x�N�g���̒�����2��
		@return	���߂�ꂽ����
		*/
		inline float LengthSquared() const
		{
			return x * x + y * y;
		}

		/**
		@brief	����
		@return	����
		*/
		inline float Angle(const Vector2& v)
		{
			return atan2f(x - v.x, y - v.y);
		}

		/**
		@brief	�x�N�g���̋���
		@return	2�̃x�N�g���̋���
		*/
		float Distance(const Vector2& v) const
		{
			return sqrtf((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y));
		}

		/**
		@brief	�x�N�g���̋�����2��
		@return	2�̃x�N�g���̋�����2��
		*/
		float DistSquared(const Vector2& v) const
		{
			return (v.x - x) * (v.x - x) + (v.y - y) * (v.y - y);
		}

		/**
		@brief	�P�ʃx�N�g��
		@return	���K�����ꂽ�x�N�g��
		*/
		inline Vector2 Normal()
		{
			// XMFLOAT3����XMVECTOR�ɕϊ�
			XMVECTOR vec = XMLoadFloat2(this);

			// �x�N�g���𐳋K��
			XMVECTOR vecNor = XMVector2Normalize(vec);

			// ���ʂ�XMFLOAT3�ɖ߂�
			Vector2 result;
			XMStoreFloat2(&result, vecNor);

			return result;
		}

		/**
		@brief	�x�N�g���𔽓]
		@return	���]���ꂽ�x�N�g��
		*/
		inline Vector2 Invert()
		{
			return Vector2(-x, -y);
		}

		/**
		@brief	�w�肳�ꂽ���e�덷�͈͓��ɂ��邩����
		@param	range	[in]	���e�͈�
		@return	���茋��
		*/
		inline bool IsNearlyZero(float range) const
		{
			if (abs(x) <= range &&
				abs(y) <= range)
			{
				return true;
			}
			return false;
		}

		/**
		@brief	�v�f���[����
		@return	���茋��
		*/
		inline bool IsZero() const
		{
			if (x == 0.0f &&
				y == 0.0f)
			{
				return true;
			}
			return false;
		}

		/**
		@brief	������ϊ�
		@return	(x, y, z)�̌`���ŕϊ����ꂽ������
		*/
		inline std::string ToString() const
		{
			std::stringstream text;
			text << "(" << x << ", " << y << ")";
			return text.str();
		}
	};

	struct Color
	{
		float r, g, b, a;	// RGBA

		// �R���X�g���N�^
		Color(float red, float green, float blue, float alpha = 1.0f) : r(red), g(green), b(blue), a(alpha) {}

		// �f�t�H���g�R���X�g���N�^
		Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
	};


	/**
	@brief	HitResult�y�Փˏ��z
	*/
	struct HitResult
	{
		bool ishit;				// �Փˌ���
		MyLib::Vector3 hitpos;	// �Փ˒n�_

		// �f�t�H���g�R���X�g���N�^
		HitResult() : ishit(false), hitpos() {}

		// �p�����[�^�t���R���X�g���N�^
		HitResult(bool bHit, MyLib::Vector3 pos) : ishit(bHit), hitpos(pos) {}
	};

	/**
	@brief	HitResult_Character�y�L�����N�^�[�̏Փˏ��z
	*/
	struct HitResult_Character
	{
		bool ishit;				// �Փˌ���
		bool isdamage;			// �_���[�W����������
		bool isdeath;			// ���S������
		MyLib::Vector3 hitpos;	// �Փ˒n�_

		// �f�t�H���g�R���X�g���N�^
		HitResult_Character() : ishit(false), isdamage(false), isdeath(false), hitpos() {}

		// �p�����[�^�t���R���X�g���N�^
		HitResult_Character(bool bHit, bool bDamage, bool bDeath, MyLib::Vector3 pos) : 
			ishit(bHit), isdamage(bDamage), isdeath(bDeath), hitpos(pos) {}
	};
}


// nlohmann::json�̓��ꉻ
namespace nlohmann 
{
	template <> struct adl_serializer<MyLib::Vector3>
	{
		static void to_json(json& j, const MyLib::Vector3& v)
		{
			v.to_json(j);
		}

		static void from_json(const json& j, MyLib::Vector3& v)
		{
			v.from_json(j);
		}
	};
}

#endif