//=============================================================================
// 
//  �v���R���p�C���w�b�_�[ [precompile.h]
//  Author : ���n�Ή끕���搶
// 
//=============================================================================
#ifndef _PRECOMPIRE_H_
#define _PRECOMPIRE_H_	// ��d�C���N���[�h�h�~

#include <Windows.h>
#define WIN32_LEAN_AND_MEAN		// Windows �w�b�_�[����قƂ�ǎg�p����Ă��Ȃ����������O����

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <DirectXMath.h>	// �x�N�g����FLOAT3�ȂǕ֗��ȎZ�p���C�u����
using namespace DirectX;

#include <d2d1.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

// C++��std�p
#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iterator>
#include <codecvt>
#include <fstream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <stack>


// ���C�u�����̃����N
#pragma comment(lib, "d3d11.lib")		// �`�揈���ɕK�v
#ifndef _DEBUG
#pragma comment(lib, "d3dx11.lib")		// [d3d11.lib]�̊g�����C�u����
#else
#pragma comment(lib, "d3dx11d.lib")		// [d3d11.lib]�̊g�����C�u����
#endif
#pragma comment(lib, "dxguid.lib")		// DirectX�R���|�l�[�g(���i)�g�p�ɕK�v
#pragma comment(lib, "winmm.lib")		// �V�X�e�������擾�ɕK�v
#pragma comment(lib, "dinput8.lib")		// ���͏����ɕK�v
#pragma comment(lib, "dsound.lib")

#define DIRECTINPUT_VERSION	(0x0800)	// �r���h���̌x���p�}�N��
#include <dinput.h>						// ���͏����ɕK�v
#include <xaudio2.h>					// �T�E���h�����ɕK�v
#include <dsound.h>						// �T�E���h���������ɕK�v
#include <Xinput.h>


// DirectXAPI�֌W�̃����N
#pragma comment(lib, "dxgi.lib")

// �V�F�[�_�R���p�C������̋@�\���C���N���[�h
#include <d3dcompiler.h>

// �V�F�[�_�R���p�C���p�̐ÓI���C�u�����������N
#pragma comment(lib, "d3dcompiler.lib")

#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

#include <d3d11.h>			// �`�揈���ɕK�v
#include <wrl/client.h>		// �f�o�C�X�̊Ǘ������₷�����邽�߂�DirectX�ł̃X�}�[�g�|�C���^�̂悤�Ȃ���
using Microsoft::WRL::ComPtr;

// �}�C���C�u����
#include "mylib.h"

// �G�t�F�N�V�A
#ifndef _DEBUG
#pragma comment(lib, "Effekseer.lib")
#else
#pragma comment(lib, "Effekseerd.lib")
#endif
#include <Effekseer.h>

#ifndef _DEBUG
#pragma comment(lib, "EffekseerRendererDX9.lib")
#else
#pragma comment(lib, "EffekseerRendererDX9d.lib")
#endif
#include <EffekseerRendererDX9.h>

// json
#include <json.hpp>
using json = nlohmann::json;
//
//// Imgui
//#define IMGUI_DEFINE_MATH_OPERATORS
//#include "imgui.h"
//#include "imgui_impl_dx9.h"
//#include "imgui_impl_win32.h"
//#include <implot.h>
//#include <implot_internal.h>

// ���������[�N�o�͗p�}�N��
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>		// ���������[�N���o�ɕK�v

// crtdbg.h�̃o�O�΍��p�}�N��
#if _DEBUG
#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else

#define DEBUG_NEW new
#endif

#endif	// _PRECOMPIRE_H_