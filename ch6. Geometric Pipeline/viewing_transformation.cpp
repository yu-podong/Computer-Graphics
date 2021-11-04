/***************************************************************************/
/*                  HW#5-1 : gluLookAy()의 실시간 제어                     */
/*                                               날짜 : 2021년 11월 2일    */
/*                                                                         */
/* 문제 정의 : 코드6-8을 수정하여 시점 좌표계를 Keyboard Callback 함수로   */
/*              실시간 제어가 가능하도록 구현                              */
/*                                                                         */
/* 기능                                                                    */
/*   1. ↑ 키를 누르면 Camera의 Y축 좌표가 0.1씩 연속적으로 증가            */
/*   2. ↓ 키를 누르면 Camera의 Y축 좌표가 0.1씩 연속적으로 감소            */
/*   3. ← 키를 누르면 Camera의 X축 좌표가 0.1씩 연속적으로 감소            */
/*   4. → 키를 누르면 Camera의 X축 좌표가 0.1씩 연속적으로 증가            */
/*                                                                         */
/*   5. a 또는 A 키를 누르면 초점의 X축 좌표가 0.1씩 연속적으로 증가       */
/*   6. f 또는 F 키를 누르면 초점의 X축 좌표가 0.1씩 연속적으로 감소       */
/*   7. r 또는 R 키를 누르면 초점의 Y축 좌표가 0.1씩 연속적으로 증가       */
/*   8. v 또는 V 키를 누르면 초점의 Y축 좌표가 0.1씩 연속적으로 감소       */
/*   9. z 또는 Z 키를 누르면 초점의 Z축 좌표가 0.1씩 연속적으로 증가       */
/*   10. t 또는 T 키를 누르면 초점의 Z축 좌표가 0.1씩 연속적으로 감소      */
/***************************************************************************/

#include <GL/glut.h>

// 카메라의 위치를 변경할 때 사용할 배열
GLfloat c_eye[2] = { 0.0, 0.0 };
// 카메라의 초점을 변경할 때 사용할 배열
GLfloat c_at[3] = { 0.0, 0.0, 0.0 };

// 주전자가 놓인 바닥을 그려줄 함수
void DrawGround() {
	// 회색으로 색상 설정
	glColor3f(0.5, 0.5, 0.5);
	// 사각형을 그리기 위한 좌표 설정
	glBegin(GL_POLYGON);
		glVertex3f(-2.0, -0.71, 2.0);
		glVertex3f(2.0, -0.71, 2.0);
		glVertex3f(2.0, -0.71, -2.0);
		glVertex3f(-2.0, -0.71, -2.0);
	glEnd();

	// 해당 인자값이 의미하는 색상으로 설정
	glColor3f(0.3, 0.3, 0.3);
	// 바닥의 선을 그리기 위한 좌표 설정
	glBegin(GL_LINES);
		for (float x = -2.0; x <= 2.2; x += 0.2) {
			glVertex3f(x, -0.7, -2.0);
			glVertex3f(x, -0.7, 2.0);
		}

		for (float z = -2.0; z <= 2.2; z += 0.2) {
			glVertex3f(-2.0, -0.7, z);
			glVertex3f(2.0, -0.7, z);
		}
	glEnd();
}

// display event 발생 시, 주전자 및 카메라 시점을 변경하는 display callback함수
void MyDisplay() {
	// 색 버퍼와 깊이 버퍼를 초기화
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 시점 변환을 위해 모델뷰 행렬스택 선택
	glMatrixMode(GL_MODELVIEW);
	// CTM을 항등행렬로 변경
	glLoadIdentity();

	// 시점을 해당 인자값으로 변경
	gluLookAt(0.0+c_eye[0], 3.5+c_eye[1], 3.5, 0.0+c_at[0], 0.0+c_at[1], 0.0+c_at[2], 0.0, 1.0, 0.0);

	// 바닥을 그리는 함수 호출
	DrawGround();

	// 해당 인자값으로 색상을 변경
	glColor3f(1.0, 1.0, 0.0);
	// 주전자를 그림
	glutWireTeapot(1.0);

	glFlush();
}

// reshape event 발생 시 호출할 reshape callback
void MyReshape(int w, int h) {
	// viewport 크기 설정
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// 투영을 위해 투영행렬 스택 선택
	glMatrixMode(GL_PROJECTION);
	// CTM을 항등행렬로 변경
	glLoadIdentity();
	// 원근 투영 진행
	gluPerspective(45.0, (GLsizei)w / (GLsizei)h, 0.0, 100);
}

// 특정 키를 입력했을 때, 카메라 초점을 변경할 수 있는 keyboard callback
void keyboardCallback(unsigned char key, int x, int y) {
	switch (key) {
		// a,A키를 누르면, 초점의 X좌표값이 0.1 증가
		case 'a':
		case 'A':
			c_at[0] += 0.1;
			break;
		// f,F키를 누르면, 초점의 X좌표값이 0.1 감소
		case 'f':
		case 'F':
			c_at[0] -= 0.1;
			break;
		// r,R키를 누르면, 초점의 Y좌표값이 0.1 증가
		case 'r':
		case 'R':
			c_at[1] += 0.1;
			break;
		// v,V키를 누르면, 초점의 Y좌표값이 0.1 감소
		case 'v':
		case 'V':
			c_at[1] -= 0.1;
			break;
		// z,Z키를 누르면, 초점의 Z좌표값이 0.1 증가
		case 'z':
		case 'Z':
			c_at[2] += 0.1;
			break;
		// t,T키를 누르면, 초점의 Z좌표값이 0.1 감소
		case 't':
		case 'T':
			c_at[2] -= 0.1;
			break;
	}
	// 강제로 display event를 발생
	glutPostRedisplay();
}

// 방향키를 입력했을 때, 카메라 위치을 변경할 수 있는 keyboard callback
void specialCallback(int key, int x, int y) {
	switch (key) {
		// up방향키를 누르면 카메라 위치 Y좌표를 증가 
		case GLUT_KEY_UP:
			c_eye[1] += 0.1;
			break;
		// down방향키를 누르면 카메라 위치 Y좌표를 감소 
		case GLUT_KEY_DOWN:
			c_eye[1] -= 0.1;
			break;
		// left방향키를 누르면 카메라 위치 X좌표를 감소
		case GLUT_KEY_LEFT:
			c_eye[0] -= 0.1;
			break;
		// right방향키를 누르면 카메라 위치 X좌표를 증가
		case GLUT_KEY_RIGHT:
			c_eye[0] += 0.1;
			break;
	}
	// 강제로 display event를 발생
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// window 사이즈를 500*500으로 설정
	glutInitWindowSize(500, 500);
	// window가 생성될 위치를 왼쪽 상단으로 설정
	glutInitWindowPosition(0, 0);
	// window의 title을 'VCS (View Coordinate System)'로 설정
	glutCreateWindow("VCS (View Coordinate System)");
	// background 색을 검정으로 설정
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// display callback 등록
	glutDisplayFunc(MyDisplay);
	// reshape callback 등록
	glutReshapeFunc(MyReshape);
	// keyboard callback 등록
	glutKeyboardFunc(keyboardCallback);
	// special-keyboard callback 등록
	glutSpecialFunc(specialCallback);

	glutMainLoop();

	return 0;
}