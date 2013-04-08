//===================================================
/* @file : BoneAnim.h
** ��Ŀ������������Ƥ����
** �ļ���������������ͷ�ļ�
**
** @author: tup
** mail: worksdata@163.com
** DateCreate: 2013/4/5
** DateRewrite:
*///==================================================
#ifndef __BONEMODEL_H__
#define __BONEMODEL_H__

#include "Bone.h"

/*����һЩ��*/
#define MAX_BONES 2
#define MAX_MESHES 3
#define MAX_VERTICES_PER_MESH 4

class BoneModel
{
public:
	BoneModel();

	/*�Զ����ʼ����������Ƥ��������*/
	void InitData();

	Bone         m_bones[MAX_BONES];            /*���еĹ�������*/   
	M3DMatrix44f m_DispMat[MAX_BONES];  /*������������ʾ����*/
	MeshVertex   m_ModelPoints[MAX_MESHES*MAX_VERTICES_PER_MESH];
};
#endif