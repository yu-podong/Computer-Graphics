/****************************************************************************************/
/*                                HW#6. 뷰폿변환 응용                                   */
/*                                               날짜 : 2021년 11월 9일                 */
/*                                                                                      */
/* <문제 정의>                                                                          */
/*  하나의 윈도우를 4개의 뷰폿으로 분할한다.                                            */
/*  뷰폿에 있는 물체들은 각각 keyboard callback이나 mouse callback함수를 사용하여       */
/*  camera의 이동을 제어할 수 있도록 함 (단, 뷰폿별로 따로 시점변환을 적용해야 한다.)   */
/*                                                                                      */
/* <시점변환할 뷰폿 선택 관련 기능>                                                     */
/*   1. 1를 누르면, 좌측 상단 뷰폿을 선택                                               */
/*   2. 2를 누르면, 우측 상단 뷰폿을 선택                                               */
/*   3. 3를 누르면, 좌측 하단 뷰폿을 선택                                               */
/*   4. 4를 누르면, 우측 하단 뷰폿을 선택                                               */
/*                                                                                      */
/*                                                                                      */
/* <시점 관련 기능>                                                                     */
/*   1. ↑ 키를 누르면 Camera의 Y축 좌표가 0.1씩 연속적으로 증가                         */
/*   2. ↓ 키를 누르면 Camera의 Y축 좌표가 0.1씩 연속적으로 감소                         */
/*   3. ← 키를 누르면 Camera가 반지름이 radius인 원 궤도를 왼쪽으로 이동하여 움직임     */
/*   4. → 키를 누르면 Camera의 반지름이 radius인 원 궤도를 오른쪽으로 이동하여 움직임   */
/*   5. i 키를 누르면 Camera의 Z축 좌표가 0.1씩 연속적으로 증가 (Zoom in)               */
/*   6. o 키를 누르면 Camera의 Z축 좌표가 0.1씩 연속적으로 증가 (Zoom out)              */
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

// 그림을 그릴 때 필요한 초기값 설정 진행
void MyInit() {
	// window의 배경색을 횐색으로 설정
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// 투영행렬 스택 선택
	glMatrixMode(GL_PROJECTION);
	// CTM을 항등행렬로 초기화
	glLoadIdentity();

	// 가시부피를 2*2*1 크기로 설정
	glOrtho(-2.0, 2.0, -2.0, 2.0, -0.5, 5.0);
	// 모델뷰 행렬 스택 선택
	glMatrixMode(GL_MODELVIEW);
	// CTM을 항등행렬로 초기화
	glLoadIdentity();
}

// torus, 구, 원뿔을 각각의 위치에 배치하여 그리는 함수
void DrawScene() {
	// 선으로 이루어진 torus 그리기(90도 회전)
	glPushMatrix();
		glColor3f(0.5, 0.8, 0.9);
		glutWireTeapot(0.5);
	glPopMatrix();

	// 선으로 이루어진 구 그리기
	glPushMatrix();
		glColor3f(0.1, 0.7, 0.7);
		glTranslatef(0.5, -0.5, -0.5);
		glutWireSphere(0.5, 15, 15);
	glPopMatrix();

	// 선으로 이루어진 원뿔 그리기 (90도 회전)
	glPushMatrix();
		glColor3f(1.0, 0.7, 0.8);
		glTranslatef(-0.5, 0.5, 0.5);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glutWireCone(0.5, 0.5, 15, 15);
	glPopMatrix();
}

// display event가 발생할 때 호출되는 함수
void MyDisplay() {
	// 이전에 그려진 그림을 삭제 (색 버퍼 초기화)
	glClear(GL_COLOR_BUFFER_BIT);

	// window의 4분할 영역 중, 왼쪽 상단에 w/2 * h/2 크기로 viewport 배치
	glViewport(0, Height / 2, Width / 2, Height / 2);
	glPushMatrix();
		// 아래의 인자값으로 카메라 위치, 초점으로 시점 변경
		gluLookAt(0.0 + c_eyes[0][0], 1.0 + c_eyes[0][1], c_eyes[0][2], 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
		// 각 모델을 해당하는 위치에 그리는 함수 호출
		DrawScene();
	glPopMatrix();

	// window의 4분할 영역 중, 오른쪽 상단에 w/2 * h/2 크기로 viewport 배치
	glViewport(Width / 2, Height / 2, Width / 2, Height / 2);
	// 원근투영을 위한 투영행렬 스택 선택
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		// CTM을 항등행렬로 초기화
		glLoadIdentity();
		// 원근투영 진행
		gluPerspective(30, (GLdouble)Width / (GLdouble)Height, 3.0, 50.0);
		// 시점변환 및 모델변환을 위해 모델뷰 행렬스택 선택
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			// 아래의 인자값으로 카메라 위치, 초점으로 시점 변경
			gluLookAt(5.0 + c_eyes[1][0], 5.0 + c_eyes[1][1], c_eyes[1][2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			// 각 모델을 해당하는 위치에 그리는 함수 호출
			DrawScene();
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// window의 4분할 영역 중, 왼쪽 하단에 w/2 * h/2 크기로 viewport 배치
	glViewport(0, 0, Width / 2, Height / 2);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		// CTM을 항등행렬로 초기화
		glLoadIdentity();
		// 직교투영 진행
		glOrtho(-3.0*Widthfactor, 3.0*Widthfactor, -3.0*Heightfactor, 3.0*Heightfactor, -2.0, 2.0);
		// 시점변환 및 모델변환을 위해 모델뷰 행렬스택 선택
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			// 아래의 인자값으로 카메라 위치, 초점으로 시점 변경
			gluLookAt(1.0 + c_eyes[2][0], 1.0 + c_eyes[2][1], c_eyes[2][2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			// 각 모델을 해당하는 위치에 그리는 함수 호출
			DrawScene();
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// window의 4분할 영역 중, 오른쪽 하단에 w/2 * h/2 크기로 viewport 배치
	glViewport(Width / 2, 0, Width / 2, Height / 2);
	glPushMatrix();
		// 아래의 인자값으로 카메라 위치, 초점으로 시점 변경
		gluLookAt(1.0 + c_eyes[3][0], 0.0 + c_eyes[3][1], c_eyes[3][2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		// 각 모델을 해당하는 위치에 그리는 함수 호출
		DrawScene();
	glPopMatrix();

	glFlush();
}
// window 사이즈가 변경될 때, 가시부피의 종횡비를 뷰폿과 일치시켜줄 reshape callback 함수
void MyReshape(int newWidth, int newHeight) {
	// window의 사이즈 변경으로 인해 발생한 늘어난 비율을 계산
	Widthfactor = (GLfloat)newWidth / (GLfloat)500;
	Heightfactor = (GLfloat)newHeight / (GLfloat)500;

	// 현재 window size로 변경
	Width = newWidth;
	Height = newHeight;

	// 투영변환을 위한 행렬을 선택
	glMatrixMode(GL_PROJECTION);
	// CTM을 항등행렬로 초기화
	glLoadIdentity();

	// 가시부피 크기를 뷰폿의 종횡비에 맞도록 설정
	glOrtho(-2.0*Widthfactor, 2.0*Widthfactor, -2.0*Heightfactor, 2.0*Heightfactor, -0.5, 5.0);
}

// 화살표를 이용하여 각 뷰폿의 시점을 변경해줄 special keyboard callback 함수
void specialKeyboardCallback(int key, int x, int y) {
	switch (key) {
		// 위쪽 방향키를 누르면, 카메라의 y좌표가 0.1 증가
		case GLUT_KEY_UP:
			c_eyes[select_viewport][1] += 0.1;
			break;
		// 아래쪽 방향키를 누르면, 카메라의 y좌표가 0.1 감소
		case GLUT_KEY_DOWN:
			c_eyes[select_viewport][1] -= 0.1;
			break;
		// 왼쪽 방향키를 누르면, 카메라의 좌표가 원점을 기준으로 원 궤도를 그리며 왼쪽으로 이동
		case GLUT_KEY_LEFT:
			angle[select_viewport] -= 0.1;
			c_eyes[select_viewport][0] = radius[select_viewport] * sin(angle[select_viewport]);
			c_eyes[select_viewport][2] = radius[select_viewport] * cos(angle[select_viewport]);
			break;
		// 오른쪽 방향키를 누르면, 카메라의 좌표가 원점을 기준으로 원 궤도를 그리며 오른쪽으로 이동
		case GLUT_KEY_RIGHT:
			angle[select_viewport] += 0.1;
			c_eyes[select_viewport][0] = radius[select_viewport] * sin(angle[select_viewport]);
			c_eyes[select_viewport][2] = radius[select_viewport] * cos(angle[select_viewport]);
			break;
	}
	// 강제로 display event 발생
	glutPostRedisplay();
}

// 시점변환할 뷰폿 설정 및 zoom-in/zoom-out을 수행해줄 keyboard callback함수
void keyboardCallback(unsigned char key, int x, int y) {
	switch (key) {
		// 시점변환할 viewport으로 왼쪽 상단 뷰폿을 선택
		case '1':
			select_viewport = 0;
			break;
		// 시점변환할 viewport으로 오른쪽 상단 뷰폿을 선택
		case '2':
			select_viewport = 1;
			break;
		// 시점변환할 viewport으로 왼쪽 하단 뷰폿을 선택
		case '3':
			select_viewport = 2;
			break;
		// 시점변환할 viewport으로 오른쪽 하단 뷰폿을 선택
		case '4':
			select_viewport = 3;
			break;
		// i를 입력한 경우, 카메라 z좌표를 0.1 감소
		case 'i':
			c_eyes[select_viewport][2] -= 0.05;
			radius[select_viewport] = c_eyes[select_viewport][2];
			glutPostRedisplay();
			break;
		// o를 입력한 경우, 카메라 z좌표를 0.1 증가
		case 'o':
			c_eyes[select_viewport][2] += 0.05;
			radius[select_viewport] = c_eyes[select_viewport][2];
			glutPostRedisplay();
			break;
	}
}

int main(int argc, char** argv) {
	// window의 시작 사이즈를 500*500으로 설정
	Width = 500;
	Height = 500;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// window 사이즈를 width*height로 설정
	glutInitWindowSize(Width, Height);
	// window의 위치를 디스플레이 화면의 왼쪽 상단에 배치
	glutInitWindowPosition(0, 0);
	// window의 제목을 '뷰폿변환 응용'으로 설정
	glutCreateWindow("뷰폿변환 응용");

	// 그림을 그릴 때 필요한 값을 설정하는 함수 호출
	MyInit();
	// display callback 함수 등록
	glutDisplayFunc(MyDisplay);
	// reshape callback 함수 등록
	glutReshapeFunc(MyReshape);
	// special keyboard callback 함수 등록
	glutSpecialFunc(specialKeyboardCallback);
	// keyboard callback 함수 등록
	glutKeyboardFunc(keyboardCallback);

	// window에서 발생한 event를 감지할 main loop
	glutMainLoop();
	return 0;
}