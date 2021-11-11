/****************************************************************************************/
/*                                HW#6. ������ȯ ����                                   */
/*                                               ��¥ : 2021�� 11�� 9��                 */
/*                                                                                      */
/* <���� ����>                                                                          */
/*  �ϳ��� �����츦 4���� �������� �����Ѵ�.                                            */
/*  ������ �ִ� ��ü���� ���� keyboard callback�̳� mouse callback�Լ��� ����Ͽ�       */
/*  camera�� �̵��� ������ �� �ֵ��� �� (��, �������� ���� ������ȯ�� �����ؾ� �Ѵ�.)   */
/*                                                                                      */
/* <������ȯ�� ���� ���� ���� ���>                                                     */
/*   1. 1�� ������, ���� ��� ������ ����                                               */
/*   2. 2�� ������, ���� ��� ������ ����                                               */
/*   3. 3�� ������, ���� �ϴ� ������ ����                                               */
/*   4. 4�� ������, ���� �ϴ� ������ ����                                               */
/*                                                                                      */
/*                                                                                      */
/* <���� ���� ���>                                                                     */
/*   1. �� Ű�� ������ Camera�� Y�� ��ǥ�� 0.1�� ���������� ����                         */
/*   2. �� Ű�� ������ Camera�� Y�� ��ǥ�� 0.1�� ���������� ����                         */
/*   3. �� Ű�� ������ Camera�� �������� radius�� �� �˵��� �������� �̵��Ͽ� ������     */
/*   4. �� Ű�� ������ Camera�� �������� radius�� �� �˵��� ���������� �̵��Ͽ� ������   */
/*   5. i Ű�� ������ Camera�� Z�� ��ǥ�� 0.1�� ���������� ���� (Zoom in)               */
/*   6. o Ű�� ������ Camera�� Z�� ��ǥ�� 0.1�� ���������� ���� (Zoom out)              */
/****************************************************************************************/

#include <GL/glut.h>
#include <math.h>

int Width, Height, select_viewport;
GLfloat Widthfactor, Heightfactor;
GLfloat c_eyes[4][3] = {
	0.0, 0.0, 0.5,
	0.0, 0.0, 0.5,
	0.0, 0.0, 0.5,
	0.0, 0.0, 0.5
};
GLfloat angle[4] = { 0.0 }, radius[4] = { 0.5, 0.5, 0.5, 0.5 };

// �׸��� �׸� �� �ʿ��� �ʱⰪ ���� ����
void MyInit() {
	// window�� ������ Ⱥ������ ����
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// ������� ���� ����
	glMatrixMode(GL_PROJECTION);
	// CTM�� �׵���ķ� �ʱ�ȭ
	glLoadIdentity();

	// ���ú��Ǹ� 2*2*1 ũ��� ����
	glOrtho(-2.0, 2.0, -2.0, 2.0, -0.5, 5.0);
	// �𵨺� ��� ���� ����
	glMatrixMode(GL_MODELVIEW);
	// CTM�� �׵���ķ� �ʱ�ȭ
	glLoadIdentity();
}

// torus, ��, ������ ������ ��ġ�� ��ġ�Ͽ� �׸��� �Լ�
void DrawScene() {
	// ������ �̷���� torus �׸���(90�� ȸ��)
	glPushMatrix();
		glColor3f(0.5, 0.8, 0.9);
		glutWireTeapot(0.5);
	glPopMatrix();

	// ������ �̷���� �� �׸���
	glPushMatrix();
		glColor3f(0.1, 0.7, 0.7);
		glTranslatef(0.5, -0.5, -0.5);
		glutWireSphere(0.5, 15, 15);
	glPopMatrix();

	// ������ �̷���� ���� �׸��� (90�� ȸ��)
	glPushMatrix();
		glColor3f(1.0, 0.7, 0.8);
		glTranslatef(-0.5, 0.5, 0.5);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glutWireCone(0.5, 0.5, 15, 15);
	glPopMatrix();
}

// display event�� �߻��� �� ȣ��Ǵ� �Լ�
void MyDisplay() {
	// ������ �׷��� �׸��� ���� (�� ���� �ʱ�ȭ)
	glClear(GL_COLOR_BUFFER_BIT);

	// window�� 4���� ���� ��, ���� ��ܿ� w/2 * h/2 ũ��� viewport ��ġ
	glViewport(0, Height / 2, Width / 2, Height / 2);
	glPushMatrix();
		// �Ʒ��� ���ڰ����� ī�޶� ��ġ, �������� ���� ����
		gluLookAt(0.0 + c_eyes[0][0], 1.0 + c_eyes[0][1], c_eyes[0][2], 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
		// �� ���� �ش��ϴ� ��ġ�� �׸��� �Լ� ȣ��
		DrawScene();
	glPopMatrix();

	// window�� 4���� ���� ��, ������ ��ܿ� w/2 * h/2 ũ��� viewport ��ġ
	glViewport(Width / 2, Height / 2, Width / 2, Height / 2);
	// ���������� ���� ������� ���� ����
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		// CTM�� �׵���ķ� �ʱ�ȭ
		glLoadIdentity();
		// �������� ����
		gluPerspective(30, (GLdouble)Width / (GLdouble)Height, 3.0, 50.0);
		// ������ȯ �� �𵨺�ȯ�� ���� �𵨺� ��Ľ��� ����
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			// �Ʒ��� ���ڰ����� ī�޶� ��ġ, �������� ���� ����
			gluLookAt(5.0 + c_eyes[1][0], 5.0 + c_eyes[1][1], c_eyes[1][2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			// �� ���� �ش��ϴ� ��ġ�� �׸��� �Լ� ȣ��
			DrawScene();
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// window�� 4���� ���� ��, ���� �ϴܿ� w/2 * h/2 ũ��� viewport ��ġ
	glViewport(0, 0, Width / 2, Height / 2);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		// CTM�� �׵���ķ� �ʱ�ȭ
		glLoadIdentity();
		// �������� ����
		glOrtho(-3.0*Widthfactor, 3.0*Widthfactor, -3.0*Heightfactor, 3.0*Heightfactor, -2.0, 2.0);
		// ������ȯ �� �𵨺�ȯ�� ���� �𵨺� ��Ľ��� ����
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			// �Ʒ��� ���ڰ����� ī�޶� ��ġ, �������� ���� ����
			gluLookAt(1.0 + c_eyes[2][0], 1.0 + c_eyes[2][1], c_eyes[2][2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			// �� ���� �ش��ϴ� ��ġ�� �׸��� �Լ� ȣ��
			DrawScene();
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// window�� 4���� ���� ��, ������ �ϴܿ� w/2 * h/2 ũ��� viewport ��ġ
	glViewport(Width / 2, 0, Width / 2, Height / 2);
	glPushMatrix();
		// �Ʒ��� ���ڰ����� ī�޶� ��ġ, �������� ���� ����
		gluLookAt(1.0 + c_eyes[3][0], 0.0 + c_eyes[3][1], c_eyes[3][2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		// �� ���� �ش��ϴ� ��ġ�� �׸��� �Լ� ȣ��
		DrawScene();
	glPopMatrix();

	glFlush();
}
// window ����� ����� ��, ���ú����� ��Ⱦ�� ������ ��ġ������ reshape callback �Լ�
void MyReshape(int newWidth, int newHeight) {
	// window�� ������ �������� ���� �߻��� �þ ������ ���
	Widthfactor = (GLfloat)newWidth / (GLfloat)500;
	Heightfactor = (GLfloat)newHeight / (GLfloat)500;

	// ���� window size�� ����
	Width = newWidth;
	Height = newHeight;

	// ������ȯ�� ���� ����� ����
	glMatrixMode(GL_PROJECTION);
	// CTM�� �׵���ķ� �ʱ�ȭ
	glLoadIdentity();

	// ���ú��� ũ�⸦ ������ ��Ⱦ�� �µ��� ����
	glOrtho(-2.0*Widthfactor, 2.0*Widthfactor, -2.0*Heightfactor, 2.0*Heightfactor, -0.5, 5.0);
}

// ȭ��ǥ�� �̿��Ͽ� �� ������ ������ �������� special keyboard callback �Լ�
void specialKeyboardCallback(int key, int x, int y) {
	switch (key) {
		// ���� ����Ű�� ������, ī�޶��� y��ǥ�� 0.1 ����
		case GLUT_KEY_UP:
			c_eyes[select_viewport][1] += 0.1;
			break;
		// �Ʒ��� ����Ű�� ������, ī�޶��� y��ǥ�� 0.1 ����
		case GLUT_KEY_DOWN:
			c_eyes[select_viewport][1] -= 0.1;
			break;
		// ���� ����Ű�� ������, ī�޶��� ��ǥ�� ������ �������� �� �˵��� �׸��� �������� �̵�
		case GLUT_KEY_LEFT:
			angle[select_viewport] -= 0.1;
			c_eyes[select_viewport][0] = radius[select_viewport] * sin(angle[select_viewport]);
			c_eyes[select_viewport][2] = radius[select_viewport] * cos(angle[select_viewport]);
			break;
		// ������ ����Ű�� ������, ī�޶��� ��ǥ�� ������ �������� �� �˵��� �׸��� ���������� �̵�
		case GLUT_KEY_RIGHT:
			angle[select_viewport] += 0.1;
			c_eyes[select_viewport][0] = radius[select_viewport] * sin(angle[select_viewport]);
			c_eyes[select_viewport][2] = radius[select_viewport] * cos(angle[select_viewport]);
			break;
	}
	// ������ display event �߻�
	glutPostRedisplay();
}

// ������ȯ�� ���� ���� �� zoom-in/zoom-out�� �������� keyboard callback�Լ�
void keyboardCallback(unsigned char key, int x, int y) {
	switch (key) {
		// ������ȯ�� viewport���� ���� ��� ������ ����
		case '1':
			select_viewport = 0;
			break;
		// ������ȯ�� viewport���� ������ ��� ������ ����
		case '2':
			select_viewport = 1;
			break;
		// ������ȯ�� viewport���� ���� �ϴ� ������ ����
		case '3':
			select_viewport = 2;
			break;
		// ������ȯ�� viewport���� ������ �ϴ� ������ ����
		case '4':
			select_viewport = 3;
			break;
		// i�� �Է��� ���, ī�޶� z��ǥ�� 0.1 ����
		case 'i':
			c_eyes[select_viewport][2] -= 0.05;
			radius[select_viewport] = c_eyes[select_viewport][2];
			glutPostRedisplay();
			break;
		// o�� �Է��� ���, ī�޶� z��ǥ�� 0.1 ����
		case 'o':
			c_eyes[select_viewport][2] += 0.05;
			radius[select_viewport] = c_eyes[select_viewport][2];
			glutPostRedisplay();
			break;
	}
}

int main(int argc, char** argv) {
	// window�� ���� ����� 500*500���� ����
	Width = 500;
	Height = 500;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// window ����� width*height�� ����
	glutInitWindowSize(Width, Height);
	// window�� ��ġ�� ���÷��� ȭ���� ���� ��ܿ� ��ġ
	glutInitWindowPosition(0, 0);
	// window�� ������ '������ȯ ����'���� ����
	glutCreateWindow("������ȯ ����");

	// �׸��� �׸� �� �ʿ��� ���� �����ϴ� �Լ� ȣ��
	MyInit();
	// display callback �Լ� ���
	glutDisplayFunc(MyDisplay);
	// reshape callback �Լ� ���
	glutReshapeFunc(MyReshape);
	// special keyboard callback �Լ� ���
	glutSpecialFunc(specialKeyboardCallback);
	// keyboard callback �Լ� ���
	glutKeyboardFunc(keyboardCallback);

	// window���� �߻��� event�� ������ main loop
	glutMainLoop();
	return 0;
}