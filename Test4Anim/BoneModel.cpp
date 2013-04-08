//=============================================================
/* @file: BoneModel.cpp
** ��Ŀ������������Ƥ����
** �ļ�����������ģ�����ʵ���ļ�
** ˵��������ģ����������������Ƥ������
**
** @author: tup
** mail: worksdata@163.com
** DateCreate: 2012/4/5
** DateRewrite:
*///============================================================
#include "BoneModel.h"

BoneModel::BoneModel()
{
}

void BoneModel::InitData()
{
	/*�������*/
	m_bones[0].SetBone(-1,4.5f);
	m_bones[1].SetBone(0,4.5f);
	/*����ÿ����Ƥ����*/
	M3DVector3f tmpVec;
	M3DVector3f tmpNml;

	m3dLoadVector3(tmpVec,-1.0f,0.0f,0.0f);
	m3dLoadVector3(tmpNml,0.0f,0.0f,1.0f);
	m_ModelPoints[0].SetMeshVertex(tmpVec,tmpNml,0,0,0,0,1.0f,0.0f,0.0f,0.0f,
		0.5f,0.5f,0.5f,1.0f,1);
	m3dLoadVector3(tmpVec,1.0f,0.0f,0.0f);
	m_ModelPoints[1].SetMeshVertex(tmpVec,tmpNml,0,0,0,0,1.0f,0.0f,0.0f,0.0f,
		0.5f,0.5f,0.5f,1.0f,1);
	m3dLoadVector3(tmpVec,1.0f,3.0f,0.0f);
	m_ModelPoints[2].SetMeshVertex(tmpVec,tmpNml,0,1,0,0,0.5f,0.5f,0.0f,0.0f,
		0.5f,0.5f,0.5f,1.0f,2);
	m3dLoadVector3(tmpVec,-1.0f,3.0f,0.0f);
	m_ModelPoints[3].SetMeshVertex(tmpVec,tmpNml,0,1,0,0,0.5f,0.5f,0.0f,0.0f,
		0.5f,0.5f,0.5f,1.0f,2);
	m3dLoadVector3(tmpVec,-1.0f,3.0f,0.0f);
	m_ModelPoints[4].SetMeshVertex(tmpVec,tmpNml,0,1,0,0,0.5f,0.5f,0.0f,0.0f,
		0.0f,0.5f,0.5f,1.0f,2);
	m3dLoadVector3(tmpVec,1.0f,3.0f,0.0f);
	m_ModelPoints[5].SetMeshVertex(tmpVec,tmpNml,0,1,0,0,0.5f,0.5f,0.0f,0.0f,
		0.0f,0.5f,0.5f,1.0f,2);
	m3dLoadVector3(tmpVec,1.0f,6.0f,0.0f);
	m_ModelPoints[6].SetMeshVertex(tmpVec,tmpNml,0,1,0,0,0.35f,0.65f,0.0f,0.0f,
		0.0f,0.5f,0.5f,1.0f,2);
	m3dLoadVector3(tmpVec,-1.0f,6.0f,0.0f);
	m_ModelPoints[7].SetMeshVertex(tmpVec,tmpNml,0,1,0,0,0.35f,0.65f,0.0f,0.0f,
		0.0f,0.5f,0.5f,1.0f,2);
	m3dLoadVector3(tmpVec,-1.0f,6.0f,0.0f);
	m_ModelPoints[8].SetMeshVertex(tmpVec,tmpNml,0,1,0,0,0.35f,0.65f,0.0f,0.0f,
		0.5f,0.5f,0.5f,1.0f,2);
	m3dLoadVector3(tmpVec,1.0f,6.0f,0.0f);
	m_ModelPoints[9].SetMeshVertex(tmpVec,tmpNml,0,1,0,0,0.35f,0.65f,0.0f,0.0f,
		0.5f,0.5f,0.5f,1.0f,2);
	m3dLoadVector3(tmpVec,1.0f,9.0f,0.0f);
	m_ModelPoints[10].SetMeshVertex(tmpVec,tmpNml,1,0,0,0,1.0f,0.0f,0.0f,0.0f,
		0.5f,0.5f,0.5f,1.0f,1);
	m3dLoadVector3(tmpVec,-1.0f,9.0f,0.0f);
	m_ModelPoints[11].SetMeshVertex(tmpVec,tmpNml,1,0,0,0,1.0f,0.0f,0.0f,0.0f,
		0.5f,0.5f,0.5f,1.0f,1);
}
