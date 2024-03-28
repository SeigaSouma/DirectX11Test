//==========================================================================
//
// ���X�g�}�l�[�W���w�b�_�[[listmanager.h]
// Author�F���n�Ή�
//
//==========================================================================
#ifndef _LISTMANAGER_H_
#define _LISTMANAGER_H_	// ��d�C���N���[�h�h�~

//==========================================================================
// ���X�g�}�l�[�W���N���X�̒�`
//==========================================================================
template<class T> class CListManager
{
public:

	using Iterator = typename std::list<T*>::iterator;

	CListManager();			// �R���X�g���N�^
	~CListManager();		// �f�X�g���N�^

	HRESULT Init();
	void Uninit();

	void Regist(T* pList);				// ���蓖��
	void Delete(T* pList);				// �폜
	bool ListLoop(T** ppList);			// ���X�g���[�v����
	T* GetData(int nIdx);				// �f�[�^�擾
	int FindIdx(T* pList);				// ���X�g����C���f�b�N�X����
	void KillAll();					// �S�č폜
	int GetNumAll();				// �A�C�e���̑����擾
	std::list<T*> GetList() const;	// �A�C�e���̃��X�g�擾

private:

	int m_nNumAll;				// ����
	std::list<T*> m_ListObj;	// ���X�g
};



//==========================================================================
// �R���X�g���N�^
//==========================================================================
template<class T> CListManager<T>::CListManager()
{
	// �l�̃N���A
	m_nNumAll = 0;	// �������Z�b�g
	m_ListObj.clear();	// �A�C�e���̃��X�g
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
template<class T> CListManager<T>::~CListManager()
{
	m_ListObj.clear();
}

//==========================================================================
// ����������
//==========================================================================
template<class T> HRESULT CListManager<T>::Init()
{
	// �������Z�b�g
	m_nNumAll = 0;

	return S_OK;
}

//==========================================================================
// ���蓖��
//==========================================================================
template<class T> void CListManager<T>::Regist(T* pList)
{
	// �A�C�e���̃��X�g�ɒǉ�
	m_ListObj.push_back(pList);

	// �������Z
	m_nNumAll++;
}

//==========================================================================
// �폜
//==========================================================================
template<class T> void CListManager<T>::Delete(T* pList)
{
	// �������g�����X�g����T��
	Iterator itr = std::find(m_ListObj.begin(), m_ListObj.end(), pList);

	// �v�f�����������ꍇ�̂ݍ폜
	if (itr != m_ListObj.end()) 
	{
		m_ListObj.erase(itr);

		// �������Z
		m_nNumAll--;
	}
}


//==========================================================================
// ���X�g���[�v����
//==========================================================================
template<class T> bool CListManager<T>::ListLoop(T** ppList)
{
	if (m_ListObj.empty())
	{// ��̏ꍇ���I��
		return false;
	}

	// �擪�̃C�e���[�^�[���擾
	Iterator it = m_ListObj.begin();
	std::advance(it, 0);

	Iterator itr = it;

	if (*ppList == nullptr)
	{
		*ppList = (*itr);
	}
	else
	{
		// �������g�����X�g����T��
		itr = std::find(m_ListObj.begin(), m_ListObj.end(), *ppList);

		// �I�[�̃C�e���[�^�[���擾
		Iterator enditr = m_ListObj.end();
		enditr = std::prev(enditr);

		if (itr == enditr)
		{// �I�[��������I��
			return false;
		}

		// ���̗v�f��n��
		itr = std::next(itr, 1);
		*ppList = (*itr);
	}

	return (*ppList != nullptr);	// nullptr�ŏI��
}

//==========================================================================
// �f�[�^�擾
//==========================================================================
template<class T> T* CListManager<T>::GetData(int nIdx)
{
	if (m_ListObj.empty())
	{// ��O�͑��I��
		return nullptr;
	}

	if (nIdx >= static_cast<int>(m_ListObj.size()))
	{// ��O�͑��I��
		return nullptr;
	}

	// �C���f�b�N�X���i�񂾗v�f��n��
	Iterator it = m_ListObj.begin();
	std::advance(it, nIdx);
	return (*it);
}

//==========================================================================
// ���X�g����C���f�b�N�X����
//==========================================================================
template<class T> int CListManager<T>::FindIdx(T* pList)
{
	if (m_ListObj.empty())
	{// ��̏ꍇ���I��
		return -1;
	}

	// �������g�����X�g����T��
	Iterator itr = std::find(m_ListObj.begin(), m_ListObj.end(), pList);

	return static_cast<int>(std::distance(m_ListObj.begin(), itr));
}

//==========================================================================
// �I������
//==========================================================================
template<class T> void CListManager<T>::Uninit()
{
	// �N���A
	m_ListObj.clear();

	// ����
	m_nNumAll = 0;
}

//==========================================================================
// �S�č폜
//==========================================================================
template<class T> void CListManager<T>::KillAll()
{
	Iterator it = m_ListObj.begin();

	// �v�f���J��Ԃ�
	while (it != m_ListObj.end())
	{
		// �I������
		(*it)->Uninit();

		// �擪�̗v�f��n��
		it = m_ListObj.begin();
		m_nNumAll--;
	}

	// �N���A
	m_ListObj.clear();

	// ����
	m_nNumAll = 0;

}

//==========================================================================
// �����擾
//==========================================================================
template<class T> int CListManager<T>::GetNumAll()
{
	return m_nNumAll;
}

//==========================================================================
// ���X�g�擾
//==========================================================================
template<class T> std::list<T*> CListManager<T>::GetList() const
{
	return m_ListObj;
}


#endif