#include<iostream>

#include<GL\glew.h>
#include<GL\glut.h>
#include"TextureLoader.h"
#include"glsl.h"
using namespace std;
using namespace cwc;
void keyboard(unsigned char key,int x, int y);
 static void display();


int y=1,x=1,z=3;float rot;
TextureLoader *pTL = new TextureLoader();
TextureLoader *pTL2 = new TextureLoader();
glTexture color,bump;
void idle()
{

	rot+=0.03;
	glutPostRedisplay();
}

static void display()
{
static	int n=0,y2=y;
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
static	 glShaderManager SM;
static	glShader *shader;
	
if(!n)
	shader=SM.loadfromFile("vert.txt","frag.txt");//on load le texte qu'une seule fois
	if (shader==0) 
   std::cout << "Error Loading, compiling or linking shader\n";
	
	if(!n)
	{//on load les textures qu'une seule fois
	pTL->LoadTextureFromDisk("data//e.jpg",&color);
	pTL->SetHighQualityTextures(GL_TRUE);
	pTL->SetMipMapping(GL_TRUE);
	pTL->SetTextureFilter(txBilinear);

	pTL2->LoadTextureFromDisk("data//e2.jpg",&bump);
	pTL2->SetHighQualityTextures(GL_TRUE);
	pTL2->SetMipMapping(GL_TRUE);
    pTL2->SetTextureFilter(txBilinear);
	}
	glBindTexture(GL_TEXTURE_2D,0);
	glActiveTextureARB(GL_TEXTURE0_ARB);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,color.TextureID);



glActiveTextureARB(GL_TEXTURE1_ARB);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,bump.TextureID);

shader->begin();


GLint z=shader->GetUniformLocation("Tex1");
GLint i=shader->GetUniformLocation("LightPosition");
	GLint y=shader->GetUniformLocation("Tex0");
		shader->setUniform1i("Tex0",0,y);
		shader->setUniform1i("Tex1",1,z);
		shader->setUniform1f("invRadius",0.5f,shader->GetUniformLocation("invRadius"));
	shader->setUniform3f("LightPosition",2,1,4,i);
	
	

	
 GLUquadric* params = gluNewQuadric();
gluQuadricNormals(params,GL_SMOOTH);
gluQuadricTexture(params,GL_TRUE);
glRotatef(rot,0,0,1);
 gluSphere(params,2.0,64,64);
 cout<<"y :"<< y2 <<endl;
 shader->end();
 n++;
glutSwapBuffers();
}
static void resize(int w,int h)
{

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(75.,(GLfloat)w/(GLfloat)h,0.2,100.0);
  gluLookAt(4,1,1,0,0,0,0,0,1);


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();


}






void init();
int main(int argc,char **argv)
{

glutInit(&argc,argv);
glutInitWindowSize(800,600);
glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);



glutCreateWindow("bump_mapping");
GLenum err=glewInit();
if(err!=GLEW_OK)
{return 0;}
init();
glutKeyboardFunc(keyboard);
glutDisplayFunc(display);
glutReshapeFunc(resize);
glutIdleFunc(idle);
glutMainLoop();// ne jamais oublier sinon rien
return 0;
}

void init()
{
     glShadeModel(GL_SMOOTH);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0,0.0);
glEnable(GL_DEPTH_TEST);
glEnable(GL_TEXTURE_2D);

glEnable(GL_LIGHT0);

// Create light components
GLfloat ambientLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5, 1.0f };
GLfloat specularLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };


// Assign created components to GL_LIGHT0
glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
float specReflection[] = { 0.8f, 0.8f, 0.8f, 1.0f };
glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
glMateriali(GL_FRONT, GL_SHININESS, 40);


}

void keyboard(unsigned char key,int x, int y)
{

    switch(key) {
    case 27  :
    exit(0);
    break;
	case'r':
		y++;
		break;
	case'f':
		y--;
		break;	
case'd':
		x++;
		break;
case'g':
		x--;
		break;
	case'b':
		rot+=1.5;	
		break;
case'o':
		z++;
		break;
case'l':
		z--;
		break;
default:
break;

break;
    }
    glutPostRedisplay();

}
