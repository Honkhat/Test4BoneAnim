//========================================================================
/* @file:    Bone.h
** 项目描述：骨骼蒙皮动画
** 文件描述：骨骼类+蒙皮定点类
** 使用技术：OpenGL
**
** @author:  Tup
** mail:     worksdata@163.com
** DateCreate:2013/4/5
** DateRewrite:
** 备注：把骨骼类和蒙皮顶点类放在一起，正是为了体现“骨骼带动蒙皮”的设计思想
*///========================================================================
#ifndef __BONE_H__
#define __BONE_H__

#include <math3d.h>
/*骨骼类*/
class Bone
{
public:
	Bone();
	/*设置骨骼数据*/
	void SetBone(int parent,float length);
	void SetBone(int parent,float length,M3DMatrix44f rela,M3DMatrix44f abso);

	unsigned int m_parent; /*父节点索引*/
	float m_length;        /*骨骼长度*/
	/*变换矩阵:绝对变换矩阵和相对变换矩阵*/
	M3DMatrix44f m_abso;
	M3DMatrix44f m_rela;
};

/*蒙皮顶点类*/
class MeshVertex
{
public:
	MeshVertex();
	/*设置蒙皮顶点数据*/
	void SetMeshVertex(M3DVector3f pos,M3DVector3f normal,int b1,int b2,int b3,int b4,
		float w1,float w2,float w3,float w4,float red,float green,float blue,float alpha,int nNumBone);

	M3DVector3f m_pos;           /*顶点位置*/
	M3DVector3f m_normal;        /*法线坐标*/
	int         m_arrBoneIdx[4]; /*影响顶点的骨骼索引，做多4个*/
	float       m_arrWeight[4];  /*各骨骼影响顶点的权重*/
	int         m_nNumBone;      /*实际影响顶点的骨骼数目*/
	float m_red;
	float m_green;         /*顶点颜色*/
	float m_blue;
	float m_alpha;
};
#endif