/*
 * _main.cpp
 *
 *  Created on: 2013/03/28
 *      Author: scientific
 */


#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>


GLuint TexId;
const char *filename="box.png";

GLuint vShaderId;
GLuint fShaderId;
GLuint programId;

//�e�N�X�`���̓ǂݍ���
void LoadTexture()
{
//        cv::Ptr<IplImage> imgA = cvLoadImage(filename);
//        if(imgA.empty())
//        {
//                std::cerr << "Can't Load Image\n";
//                exit(0);
//        }

        glGenTextures(1,&TexId);
        glBindTexture(GL_TEXTURE_2D,TexId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        int width = 8;
        int height = 8;
        unsigned char data[width * height];
        for(int i=0; i< width * height; ++i){
        	data[i] = 255;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                width, height, 0,
                GL_RED, GL_UNSIGNED_BYTE, data);
}

//GLSL�̃Z�b�g�A�b�v
void setUpGLSL()
{
//        //---- ���_�V�F�[�_�I�u�W�F�N�g�̍쐬 ----//
//        vShaderId = glCreateShader(GL_VERTEX_SHADER);
//
//        //.vert�t�@�C���̒��g��S�ēǂݍ���
//        std::ifstream inputFile1("glsl.vert");
//        std::istreambuf_iterator<char> vdataBegin(inputFile1);
//        std::istreambuf_iterator<char> vdataEnd;
//        std::string fileData1(vdataBegin,vdataEnd);
//        const char *vfile = fileData1.c_str();
//
//        //�\�[�X�R�[�h���V�F�[�_�I�u�W�F�N�g�ɕϊ�
//        glShaderSource(vShaderId, 1, &vfile,NULL);
//        glCompileShader(vShaderId);//�R���p�C��
//
//
//        //---- �t���O�����g�V�F�[�_�I�u�W�F�N�g�̍쐬 ----//
//        fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
//
//        //.frag�t�@�C���̒��g��S�ēǂݍ���
//        std::ifstream inputFile2("glsl.frag");
//        std::istreambuf_iterator<char> fdataBegin(inputFile2);
//        std::istreambuf_iterator<char> fdataEnd;
//        std::string fileData2(fdataBegin,fdataEnd);
//        const char *ffile = fileData2.c_str();
//        //�\�[�X�R�[�h���V�F�[�_�I�u�W�F�N�g�ɕϊ�
//        glShaderSource(fShaderId, 1, &ffile,NULL);
//        glCompileShader(fShaderId);//�R���p�C��
//
//        //�v���O�����I�u�W�F�N�g�̍쐬
//        programId = glCreateProgram();
//        glAttachShader(programId,vShaderId);
//        glAttachShader(programId,fShaderId);
//
//        GLint linked;
//        glLinkProgram(programId);
//        glGetProgramiv(programId, GL_LINK_STATUS, &linked);
//        if(linked == GL_FALSE)
//        {
//                std::cerr << "Link Err.\n";
//        }
//
//        glUseProgram(programId);
//
//        //�ϐ���texture0�ɂ́u0�v�������Ă���
//        glUniform1i(glGetUniformLocation(programId, "texture0"), 0);//�e�N�X�`�����j�b�g0�Ƃ���
}

void display()
{
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(3,4,5,0,0,0,0,1,0);
        glColor3f(1,0,1);

        glEnable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TexId);
        glutSolidTeapot(1);
        glBindTexture(GL_TEXTURE_2D, 0);

        glDisable(GL_TEXTURE_2D);
        glutSwapBuffers();
}

void reshape(int w, int h)
{
        glViewport(0,0,w,h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(30,double(w)/h,0.1,200);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
        if(key == 'q')
        {
                glDeleteTextures(1,&TexId);
                glDeleteShader(vShaderId);
                glDeleteShader(fShaderId);
                glDeleteProgram(programId);
                exit(0);
        }
}

void init()
{
        glClearColor(1,1,1,1);
        glEnable(GL_DEPTH_TEST);
}


int main(int argc, char* argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
    glutInitWindowSize(640,480);
    glutCreateWindow("Basic Texture Mapping");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    init();

    glewInit();
    if (!glewIsSupported("GL_VERSION_2_0"))
    {
            std::cerr << "Can't Use GLSL\n";
            return -1;
    }

    LoadTexture();//�e�N�X�`���̓ǂݍ���

    setUpGLSL();

    glutMainLoop();
    return 0;


}

