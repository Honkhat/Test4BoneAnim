//=====================================================================
/* @file: MainAnim.cpp
** 项目描述：骨骼蒙皮动画的简单实例
** 文件描述：调用模型类实现动画的文件
** 
** @author: tup
** mail: worksdata@163.com
** FileCreate: 2012/4/7
** FileRewrite:
** 说明：
** 相对变换矩阵 绝对变换矩阵 显示变换矩阵 解释
** 1.前2个是骨骼类的成员，显示矩阵是模型的成员
** 2.蒙皮跟着骨骼动，骨骼显示用的是显示矩阵，蒙皮不是在骨骼的本地坐标系中绘制（
** 即不是先绘制骨骼，然后在骨骼所在的坐标系中绘制蒙皮），蒙皮（mesh）是在世界
** 坐标系中绘制，只是各个顶点都乘以对应骨骼的绝对变换矩阵（不包含平移）
** 3.本例中，骨骼和蒙皮是分开绘制的，绘制骨骼时乘以骨骼的显示矩阵（包含旋转和平移），
** 蒙皮已经固定好位置了，不用平移， 因此，对蒙皮顶点应用的是绝对矩阵
** ref：《OpenGL编程精粹》
*///=================================================================
#define FREEGLUT_STATIC
#include <GL/glut.h>

#include "BoneModel.h"

BoneModel* pObjModel=NULL;
GLfloat xRot=0.0f;
GLfloat zRot=0.0f;
/*只旋转一块骨骼(子骨骼，索引1)，查看效果
* 此例中，下面为父骨骼（索引为0），
* 上面为子骨骼（索引为1）
*/
void SetupRC()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	//glColor3f(0.5f,0.5f,0.5f);
	glEnable(GL_DEPTH_TEST);

	/*初始化骨骼模型数据*/
	pObjModel=new BoneModel();
	pObjModel->InitData();
}

/*更新所有的骨骼变换矩阵*/
void UpdateBones()
{
	/*用于保存平移和旋转矩阵*/
	M3DMatrix44f XRotMat,zRotMat,InvTransMat;

	/*循环更新骨骼*/
	for(int i=0;i<MAX_BONES;++i)
	{
		//检查是否根骨骼
		if(pObjModel->m_bones[i].m_parent == -1)
		{
			/*初始化根骨骼相对 绝对 显示矩阵*/
			m3dTranslationMatrix44(pObjModel->m_bones[i].m_rela,0.0f,0.0f,1.0f);//根骨骼的位置在DrawModel()中指定
			m3dCopyMatrix44(pObjModel->m_bones[i].m_abso,pObjModel->m_bones[i].m_rela);
			m3dCopyMatrix44(pObjModel->m_DispMat[i],pObjModel->m_bones[i].m_rela);
		}
		else
		{
			//在父骨骼的基础上平移，这要求在显示的时候父子骨骼之间不能弹堆栈
			//移动到父骨骼的位置
			m3dTranslationMatrix44(pObjModel->m_bones[i].m_rela,0.0f,pObjModel->m_bones[pObjModel->m_bones[i].m_parent].m_length,0.0f);
			/*更新旋转矩阵*/
			m3dRotationMatrix44(XRotMat,m3dDegToRad(xRot),1.0f,0.0f,0.0f);
			m3dRotationMatrix44(zRotMat,m3dDegToRad(zRot),0.0f,0.0f,1.0f);
			/*保存相对矩阵的逆矩阵（此时的相对矩阵（平移矩阵）只包含平移操作，无旋转操作）*/
			m3dInvertMatrix44(InvTransMat,pObjModel->m_bones[i].m_rela);
			/*子骨骼显示矩阵=父骨骼绝对矩阵*子骨骼平移矩阵*子骨骼旋转矩阵*/
			m3dMatrixMultiply44(pObjModel->m_DispMat[i],pObjModel->m_bones[pObjModel->m_bones[i].m_parent].m_abso,pObjModel->m_bones[i].m_rela);
			m3dMatrixMultiply44(pObjModel->m_DispMat[i],pObjModel->m_DispMat[i],XRotMat);
			m3dMatrixMultiply44(pObjModel->m_DispMat[i],pObjModel->m_DispMat[i],zRotMat);
			/*计算真正的相对变换矩阵(不含平移)*/
			m3dMatrixMultiply44(pObjModel->m_bones[i].m_rela,pObjModel->m_bones[i].m_rela,XRotMat);
			m3dMatrixMultiply44(pObjModel->m_bones[i].m_rela,pObjModel->m_bones[i].m_rela,zRotMat);
			m3dMatrixMultiply44(pObjModel->m_bones[i].m_rela,pObjModel->m_bones[i].m_rela,InvTransMat);
			/*计算绝对变换矩阵(不含平移--相对于原点)*/
			m3dMatrixMultiply44(pObjModel->m_bones[i].m_abso,pObjModel->m_bones[pObjModel->m_bones[i].m_parent].m_abso,pObjModel->m_bones[i].m_rela);
		}
	}
}

void DrawMesh()
{
	UpdateBones();

	M3DMatrix44f mat;
	int nIdx=0;

	//glPolygonMode(GL_FRONT,GL_LINE);
	/*渲染网格中的顶点*/
	for(int j=0;j<MAX_MESHES;++j)
	{
		glBegin(GL_QUADS);
		
		for(int i=0;i<MAX_VERTICES_PER_MESH;++i)
		{
			float vx=0.0f,vy=0.0f,vz=0.0f;       /*mesh顶点坐标*/
			float vnx=0.0f,vny=0.0f,vnz=0.0f;    /*mesh顶点法线坐标*/
			float tmp1=0.0f,tmp2=0.0f,tmp3=0.0f;/*在这里vnx,vny,vnz要初始化为0，因为在下层循环中vnx vny vnz要不断权重累加*/

			/*根据权值计算顶点的pos normal坐标*/
			nIdx=i+j*MAX_VERTICES_PER_MESH;
			for(int k=0;k < pObjModel->m_ModelPoints[nIdx].m_nNumBone;++k)
			{
				m3dCopyMatrix44(mat,pObjModel->m_bones[pObjModel->m_ModelPoints[nIdx].m_arrBoneIdx[k]].m_abso);//这里用的是绝对矩阵
				/*加权计算骨骼对顶点位置的影响*/
				
				tmp1=(pObjModel->m_ModelPoints[nIdx].m_pos)[0]*mat[0]+
					(pObjModel->m_ModelPoints[nIdx].m_pos)[1]*mat[4]+
					(pObjModel->m_ModelPoints[nIdx].m_pos)[2]*mat[8]+mat[12];
				tmp2=(pObjModel->m_ModelPoints[nIdx].m_pos)[0]*mat[1]+
					(pObjModel->m_ModelPoints[nIdx].m_pos)[1]*mat[5]+
					(pObjModel->m_ModelPoints[nIdx].m_pos)[2]*mat[9]+mat[13];
				tmp3=(pObjModel->m_ModelPoints[nIdx].m_pos)[0]*mat[2]+
					(pObjModel->m_ModelPoints[nIdx].m_pos)[1]*mat[6]+
					(pObjModel->m_ModelPoints[nIdx].m_pos)[2]*mat[10]+mat[14];
				vx+=tmp1*(pObjModel->m_ModelPoints[nIdx].m_arrWeight[k]);
				vy+=tmp2*(pObjModel->m_ModelPoints[nIdx].m_arrWeight[k]);
				vz+=tmp3*(pObjModel->m_ModelPoints[nIdx].m_arrWeight[k]);
				
				/*在这里我犯了一个愚蠢的错误（就这么一个简单的测试程序就花了2天时间来调试）:用vx代替了tmp1,vy--tmp2,vz--tmp3,huh,FOOLISH.*/
				tmp1=(pObjModel->m_ModelPoints[nIdx].m_normal)[0]*mat[0]+
					(pObjModel->m_ModelPoints[nIdx].m_normal)[1]*mat[4]+
					(pObjModel->m_ModelPoints[nIdx].m_normal)[2]*mat[8]+mat[12];
				tmp2=(pObjModel->m_ModelPoints[nIdx].m_normal)[0]*mat[1]+
					(pObjModel->m_ModelPoints[nIdx].m_normal)[1]*mat[5]+
					(pObjModel->m_ModelPoints[nIdx].m_normal)[2]*mat[9]+mat[13];
				tmp3=(pObjModel->m_ModelPoints[nIdx].m_normal)[0]*mat[2]+
					(pObjModel->m_ModelPoints[nIdx].m_normal)[1]*mat[6]+
					(pObjModel->m_ModelPoints[nIdx].m_normal)[2]*mat[10]+mat[14];
				vnx+=tmp1*(pObjModel->m_ModelPoints[nIdx].m_arrWeight[k]);
				vny+=tmp2*(pObjModel->m_ModelPoints[nIdx].m_arrWeight[k]);
				vnz+=tmp3*(pObjModel->m_ModelPoints[nIdx].m_arrWeight[k]);
				
			}
			/*渲染网格顶点*/
			glColor4f(pObjModel->m_ModelPoints[nIdx].m_red,pObjModel->m_ModelPoints[nIdx].m_green,
				pObjModel->m_ModelPoints[nIdx].m_blue,pObjModel->m_ModelPoints[nIdx].m_alpha);
			glNormal3f(vnx,vny,vnz);
			glVertex3f(vx,vy,vz);
		}
		glEnd();
	}
}

/*根据骨骼的位置变化，绘制骨骼和蒙皮*/
void DrawModel()
{
	glLoadIdentity();//????
	glTranslatef(0.0f,-4.0f,-15.0f);

	DrawMesh();
	
	/*绘制骨骼*/
	for(int i=0;i<MAX_BONES;++i)
	{
		glPushMatrix();

		glMultMatrixf(pObjModel->m_DispMat[i]);
		glColor3f(1.0f,0.0f,0.0f);

		glBegin(GL_LINES);
		/*绘制线段组成的模拟骨骼*/
		glVertex3f(-0.4f, 0.0f, -0.4f);
		glVertex3f(0.4f, 0.0f, -0.4f);
		glVertex3f(0.4f, 0.0f, -0.4f);
		glVertex3f(0.4f, 0.0f, 0.4f);
		glVertex3f(0.4f, 0.0f, 0.4f);
		glVertex3f(-0.4f, 0.0f, 0.4f);
		glVertex3f(-0.4f, 0.0f, 0.4f);
		glVertex3f(-0.4f, 0.0f, -0.4f);

		glVertex3f(-0.4f, 0.0f, -0.4f);
		glVertex3f(0.0f, pObjModel->m_bones[i].m_length, 0.0f);
		glVertex3f(0.4f, 0.0f, -0.4f);
		glVertex3f(0.0f, pObjModel->m_bones[i].m_length, 0.0f);
		glVertex3f(0.4f, 0.0f, 0.4f);
		glVertex3f(0.0f, pObjModel->m_bones[i].m_length, 0.0f);
		glVertex3f(-0.4f, 0.0f, 0.4f);
		glVertex3f(0.0f, pObjModel->m_bones[i].m_length, 0.0f);

		glEnd();

		glPopMatrix();
	}
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	DrawModel();

	glPopMatrix();
	glutSwapBuffers();
	//glFlush();
}

void ChangeSize(int w,int h)
{
	GLfloat fAspect=(float)w/(float)h;

	if(h==0)
		h=1;
	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,fAspect,1.0,100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

void SpecialKeys(int key,int x,int y)
{
	if(key==GLUT_KEY_UP)
		xRot-=2.0f;
	if(key==GLUT_KEY_DOWN)
		xRot+=2.0f;
	if(key==GLUT_KEY_LEFT)
		zRot+=2.0f;
	if(key==GLUT_KEY_RIGHT)
		zRot-=2.0f;

	glutPostRedisplay();
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(800,600);
	glutCreateWindow("Bone Animation Eg");

	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);

	SetupRC();

	glutMainLoop();
	return 0;
}
