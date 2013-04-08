//================================================
/* @file: Bone.cpp
** ��Ŀ��������������
** �ļ����������������Ƥ�������ʵ��
**
** @author: tup
** mail: worksdata@163.com
** DateCreate:2013/4/5
** DateRewrite:
*///===============================================
#include "Bone.h"
/*�������ʵ��*/
/*���캯��*/
Bone::Bone():m_parent(0),m_length(0)
{
	memset(m_rela,0,16*sizeof(float));
	m_rela[0]=1;
	m_rela[5]=1;
	m_rela[10]=1;
	m_rela[15]=1;
	memset(m_abso,0,16*sizeof(float));
	m_abso[0]=1;
	m_abso[5]=1;
	m_abso[10]=1;
	m_abso[15]=1;
}
/*���ù�������*/
void Bone::SetBone(int parent,float length)
{
	m_parent=parent;
	m_length=length;
}
void Bone::SetBone(int parent,float length,M3DMatrix44f rela,M3DMatrix44f abso)
{
	m_parent=parent;
	m_length=length;
	m3dCopyMatrix44(m_rela,rela);
	m3dCopyMatrix44(m_abso,abso);
}
/*��Ƥ�������ʵ��*/
/*���캯��*/
MeshVertex::MeshVertex():m_red(0.0f),m_green(0.0f),m_blue(0.0f),m_alpha(0.0f),m_nNumBone(0)
{
	//��ʼ���Զ���ĸ���Ա(�˼ҷ�װ�õ�һ��ʵ�����ͳ�ʼ�����˰�)
	memset(m_arrBoneIdx,0,4*sizeof(int));
	memset(m_arrWeight,0,4*sizeof(int));
}
/*������Ƥ��������*/
void MeshVertex::SetMeshVertex(M3DVector3f pos,M3DVector3f normal,int b1,int b2,int b3,int b4,
		float w1,float w2,float w3,float w4,float red,float green,float blue,float alpha,int nNumBone)
{
	m3dCopyVector3(m_pos,pos);
	m3dCopyVector3(m_normal,normal);
	m_arrBoneIdx[0]=b1;
	m_arrBoneIdx[1]=b2;
	m_arrBoneIdx[2]=b3;
	m_arrBoneIdx[3]=b4;
	m_arrWeight[0]=w1;
	m_arrWeight[1]=w2;
	m_arrWeight[2]=w3;
	m_arrWeight[3]=w4;
	m_red=red;
	m_green=green;
	m_blue=blue;
	m_alpha=alpha;
	m_nNumBone=nNumBone;
}
