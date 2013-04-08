//=====================================================================
/* @file: MainAnim.cpp
** ��Ŀ������������Ƥ�����ļ�ʵ��
** �ļ�����������ģ����ʵ�ֶ������ļ�
** 
** @author: tup
** mail: worksdata@163.com
** FileCreate: 2012/4/7
** FileRewrite:
** ˵����
** ��Ա任���� ���Ա任���� ��ʾ�任���� ����
** 1.ǰ2���ǹ�����ĳ�Ա����ʾ������ģ�͵ĳ�Ա
** 2.��Ƥ���Ź�������������ʾ�õ�����ʾ������Ƥ�����ڹ����ı�������ϵ�л��ƣ�
** �������Ȼ��ƹ�����Ȼ���ڹ������ڵ�����ϵ�л�����Ƥ������Ƥ��mesh����������
** ����ϵ�л��ƣ�ֻ�Ǹ������㶼���Զ�Ӧ�����ľ��Ա任���󣨲�����ƽ�ƣ�
** 3.�����У���������Ƥ�Ƿֿ����Ƶģ����ƹ���ʱ���Թ�������ʾ���󣨰�����ת��ƽ�ƣ���
** ��Ƥ�Ѿ��̶���λ���ˣ�����ƽ�ƣ� ��ˣ�����Ƥ����Ӧ�õ��Ǿ��Ծ���
** ref����OpenGL��̾��⡷
*///=================================================================
#define FREEGLUT_STATIC
#include <GL/glut.h>

#include "BoneModel.h"

BoneModel* pObjModel=NULL;
GLfloat xRot=0.0f;
GLfloat zRot=0.0f;
/*ֻ��תһ�����(�ӹ���������1)���鿴Ч��
* �����У�����Ϊ������������Ϊ0����
* ����Ϊ�ӹ���������Ϊ1��
*/
void SetupRC()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	//glColor3f(0.5f,0.5f,0.5f);
	glEnable(GL_DEPTH_TEST);

	/*��ʼ������ģ������*/
	pObjModel=new BoneModel();
	pObjModel->InitData();
}

/*�������еĹ����任����*/
void UpdateBones()
{
	/*���ڱ���ƽ�ƺ���ת����*/
	M3DMatrix44f XRotMat,zRotMat,InvTransMat;

	/*ѭ�����¹���*/
	for(int i=0;i<MAX_BONES;++i)
	{
		//����Ƿ������
		if(pObjModel->m_bones[i].m_parent == -1)
		{
			/*��ʼ����������� ���� ��ʾ����*/
			m3dTranslationMatrix44(pObjModel->m_bones[i].m_rela,0.0f,0.0f,1.0f);//��������λ����DrawModel()��ָ��
			m3dCopyMatrix44(pObjModel->m_bones[i].m_abso,pObjModel->m_bones[i].m_rela);
			m3dCopyMatrix44(pObjModel->m_DispMat[i],pObjModel->m_bones[i].m_rela);
		}
		else
		{
			//�ڸ������Ļ�����ƽ�ƣ���Ҫ������ʾ��ʱ���ӹ���֮�䲻�ܵ���ջ
			//�ƶ�����������λ��
			m3dTranslationMatrix44(pObjModel->m_bones[i].m_rela,0.0f,pObjModel->m_bones[pObjModel->m_bones[i].m_parent].m_length,0.0f);
			/*������ת����*/
			m3dRotationMatrix44(XRotMat,m3dDegToRad(xRot),1.0f,0.0f,0.0f);
			m3dRotationMatrix44(zRotMat,m3dDegToRad(zRot),0.0f,0.0f,1.0f);
			/*������Ծ��������󣨴�ʱ����Ծ���ƽ�ƾ���ֻ����ƽ�Ʋ���������ת������*/
			m3dInvertMatrix44(InvTransMat,pObjModel->m_bones[i].m_rela);
			/*�ӹ�����ʾ����=���������Ծ���*�ӹ���ƽ�ƾ���*�ӹ�����ת����*/
			m3dMatrixMultiply44(pObjModel->m_DispMat[i],pObjModel->m_bones[pObjModel->m_bones[i].m_parent].m_abso,pObjModel->m_bones[i].m_rela);
			m3dMatrixMultiply44(pObjModel->m_DispMat[i],pObjModel->m_DispMat[i],XRotMat);
			m3dMatrixMultiply44(pObjModel->m_DispMat[i],pObjModel->m_DispMat[i],zRotMat);
			/*������������Ա任����(����ƽ��)*/
			m3dMatrixMultiply44(pObjModel->m_bones[i].m_rela,pObjModel->m_bones[i].m_rela,XRotMat);
			m3dMatrixMultiply44(pObjModel->m_bones[i].m_rela,pObjModel->m_bones[i].m_rela,zRotMat);
			m3dMatrixMultiply44(pObjModel->m_bones[i].m_rela,pObjModel->m_bones[i].m_rela,InvTransMat);
			/*������Ա任����(����ƽ��--�����ԭ��)*/
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
	/*��Ⱦ�����еĶ���*/
	for(int j=0;j<MAX_MESHES;++j)
	{
		glBegin(GL_QUADS);
		
		for(int i=0;i<MAX_VERTICES_PER_MESH;++i)
		{
			float vx=0.0f,vy=0.0f,vz=0.0f;       /*mesh��������*/
			float vnx=0.0f,vny=0.0f,vnz=0.0f;    /*mesh���㷨������*/
			float tmp1=0.0f,tmp2=0.0f,tmp3=0.0f;/*������vnx,vny,vnzҪ��ʼ��Ϊ0����Ϊ���²�ѭ����vnx vny vnzҪ����Ȩ���ۼ�*/

			/*����Ȩֵ���㶥���pos normal����*/
			nIdx=i+j*MAX_VERTICES_PER_MESH;
			for(int k=0;k < pObjModel->m_ModelPoints[nIdx].m_nNumBone;++k)
			{
				m3dCopyMatrix44(mat,pObjModel->m_bones[pObjModel->m_ModelPoints[nIdx].m_arrBoneIdx[k]].m_abso);//�����õ��Ǿ��Ծ���
				/*��Ȩ��������Զ���λ�õ�Ӱ��*/
				
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
				
				/*�������ҷ���һ���޴��Ĵ��󣨾���ôһ���򵥵Ĳ��Գ���ͻ���2��ʱ�������ԣ�:��vx������tmp1,vy--tmp2,vz--tmp3,huh,FOOLISH.*/
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
			/*��Ⱦ���񶥵�*/
			glColor4f(pObjModel->m_ModelPoints[nIdx].m_red,pObjModel->m_ModelPoints[nIdx].m_green,
				pObjModel->m_ModelPoints[nIdx].m_blue,pObjModel->m_ModelPoints[nIdx].m_alpha);
			glNormal3f(vnx,vny,vnz);
			glVertex3f(vx,vy,vz);
		}
		glEnd();
	}
}

/*���ݹ�����λ�ñ仯�����ƹ�������Ƥ*/
void DrawModel()
{
	glLoadIdentity();//????
	glTranslatef(0.0f,-4.0f,-15.0f);

	DrawMesh();
	
	/*���ƹ���*/
	for(int i=0;i<MAX_BONES;++i)
	{
		glPushMatrix();

		glMultMatrixf(pObjModel->m_DispMat[i]);
		glColor3f(1.0f,0.0f,0.0f);

		glBegin(GL_LINES);
		/*�����߶���ɵ�ģ�����*/
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
