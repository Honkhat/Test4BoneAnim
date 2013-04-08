//========================================================================
/* @file:    Bone.h
** ��Ŀ������������Ƥ����
** �ļ�������������+��Ƥ������
** ʹ�ü�����OpenGL
**
** @author:  Tup
** mail:     worksdata@163.com
** DateCreate:2013/4/5
** DateRewrite:
** ��ע���ѹ��������Ƥ���������һ������Ϊ�����֡�����������Ƥ�������˼��
*///========================================================================
#ifndef __BONE_H__
#define __BONE_H__

#include <math3d.h>
/*������*/
class Bone
{
public:
	Bone();
	/*���ù�������*/
	void SetBone(int parent,float length);
	void SetBone(int parent,float length,M3DMatrix44f rela,M3DMatrix44f abso);

	unsigned int m_parent; /*���ڵ�����*/
	float m_length;        /*��������*/
	/*�任����:���Ա任�������Ա任����*/
	M3DMatrix44f m_abso;
	M3DMatrix44f m_rela;
};

/*��Ƥ������*/
class MeshVertex
{
public:
	MeshVertex();
	/*������Ƥ��������*/
	void SetMeshVertex(M3DVector3f pos,M3DVector3f normal,int b1,int b2,int b3,int b4,
		float w1,float w2,float w3,float w4,float red,float green,float blue,float alpha,int nNumBone);

	M3DVector3f m_pos;           /*����λ��*/
	M3DVector3f m_normal;        /*��������*/
	int         m_arrBoneIdx[4]; /*Ӱ�춥��Ĺ�������������4��*/
	float       m_arrWeight[4];  /*������Ӱ�춥���Ȩ��*/
	int         m_nNumBone;      /*ʵ��Ӱ�춥��Ĺ�����Ŀ*/
	float m_red;
	float m_green;         /*������ɫ*/
	float m_blue;
	float m_alpha;
};
#endif