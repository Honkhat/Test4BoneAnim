//===================================================
/* @file : BoneAnim.h
** 项目描述：骨骼蒙皮动画
** 文件描述：骨骼动画头文件
**
** @author: tup
** mail: worksdata@163.com
** DateCreate: 2013/4/5
** DateRewrite:
*///==================================================
#ifndef __BONEMODEL_H__
#define __BONEMODEL_H__

#include "Bone.h"

/*定义一些宏*/
#define MAX_BONES 2
#define MAX_MESHES 3
#define MAX_VERTICES_PER_MESH 4

class BoneModel
{
public:
	BoneModel();

	/*自定义初始化骨骼和蒙皮顶点数据*/
	void InitData();

	Bone         m_bones[MAX_BONES];            /*所有的骨骼索引*/   
	M3DMatrix44f m_DispMat[MAX_BONES];  /*各个骨骼的显示矩阵*/
	MeshVertex   m_ModelPoints[MAX_MESHES*MAX_VERTICES_PER_MESH];
};
#endif