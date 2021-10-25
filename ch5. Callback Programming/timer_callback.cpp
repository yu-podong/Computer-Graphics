/***************************************************************************/
/*                  HW#3-6 : Timer Callback 응용                           */
/*                                               날짜 : 2021년 10월 4일    */
/*                                                                         */
/* 문제 정의 : 프로그램이 실행되면 코드5-8에 있는 도형이 오른쪽으로 0.1씩  */
/*             연속적으로 움직이게 하고, 오른쪽 경계에 부딪히면 도형의     */
/*             색깔이 변하게 한 후, 다시 도형이 왼쪽으로 0.1씩 연속적으로  */
/*             움직이는 과정을 반복										   */
/* 기능                                                                    */
/*   1. 마우스 왼쪽 키를 누르면 움직이는 도형이 멈춤                       */
/***************************************************************************/

#include <GL/glut.h>

// 사각형의 이동을 위한 변수
float deltaX = 0.0;
// Timer를 핸들링하기 위해 설정한 변수
int moveWay = 'r';

// 배경 및 그림 색 지정 & 투영변환 진행
void myInit() {
	// 배경색을 흰색으로 지정
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// window 위에 그려지는 그림을 회색으로 지정
	glColor3f(0.5, 0.5, 0.5);

	// 투영변환을 위한 행렬 선택
	glMatrixMode(GL_PROJECTION);
	// 해당 행렬에 적용되었던 setting 초기화
	glLoadIdentity();

	// 2*2*2 크기를 가지는 가시부피 설정
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
}

// 사각형을 그리는 display callback function
void displayCallback() {
	// 색 버퍼 초기화
	glClear(GL_COLOR_BUFFER_BIT);

	// 4개의 좌표로 사각형 생성
	glBegin(GL_POLYGON);
	glVertex3f(-1.0 + deltaX, -0.5, 0.0);
	glVertex3f(0.0 + deltaX, -0.5, 0.0);
	glVertex3f(0.0 + deltaX, 0.5, 0.0);
	glVertex3f(-1.0 + deltaX, 0.5, 0.0);
	glEnd();

	// 현재 buffer를 front buffer로 변경
	glutSwapBuffers();
}

// 일정시간마다 사각형의 이동을 담당할 timer callback 함수
void timer(int value) {
	// 왼쪽 마우스가 클릭된 경우
	if (moveWay == 'n') {
		// 더이상 timer함수를 진행 X
	}
	// 왼쪽 마우스가 클릭되지 않은 경우
	else {
		// 사각형이 window의 오른쪽 끝에 도달했으면
		if (moveWay == 'r' && (0.0 + deltaX) >= 1.0) {
			// 사각형이 움직이는 방향을 왼쪽으로 설정
			moveWay = 'l';
			// 사각형 color change
			glColor3f(0.0, 8.0, 0.5);
		}
		// 사각형이 window의 왼쪽 끝에 도달했으면
		else if (moveWay == 'l' && (-1.0 + deltaX) <= -0.9) {
			// 사각형이 움직이는 방향을 오른쪽으로 설정
			moveWay = 'r';
			// 사각형 color change
			glColor3f(0.8, 0.5, 0.0);
		}
		// 아직 window의 어느 한쪽 끝에 도달하지 않았거나 stop하는 버튼이 클릭되지 않았다면
		else if (moveWay == 'r') {
			// 사각형의 각 꼭짓점을 이동방향(오른쪽)을 따라 0.1 이동
			deltaX += 0.1;
		}
		else {
			// 사각형의 각 꼭짓점을 이동방향(왼쪽)을 따라 0.1 이동
			deltaX -= 0.1;
		}

		// 강제로 display event를 발생시켜 변경된 좌표 사각형 이동
		glutPostRedisplay();
		// 250msec뒤에 timer함수를 실행
		glutTimerFunc(250, timer, value);
	}

}

// mouse event를 처리해줄 mouse callback 함수
void mouseCallback(int button, int state, int x, int y) {
	// 왼쪽 마우스가 클릭되었다면
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// 이동방향이 없다고 설정하여, timer함수를 더이상 호출하지 않도록 설정
		moveWay = 'n';
	}
}

int main(int argc, char** argv) {
	// OS와 Session 연결 / GLUT library 초기화
	glutInit(&argc, argv);
	// display mode를 RGB로 설정 & 더블 버퍼링을 위한 mode 설정
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	// 새로 생성된 window의 크기를 800 * 600로 설정
	glutInitWindowSize(500, 500);
	// window의 위치를 왼쪽 상단으로 설정
	glutInitWindowPosition(0, 0);
	// window의 타이틀을 'Timer Callback 응용'으로 설정
	glutCreateWindow("Timer Callback 응용");

	// 색상과 변환과 관련된 함수 호출
	myInit();
	// display callback function 등록
	glutDisplayFunc(displayCallback);
	// special keyboard callback function 등록
	glutMouseFunc(mouseCallback);

	// timer 함수를 호출하여 일정주기마다 사각형 이동
	glutTimerFunc(0, timer, 1);

	// callback 함수로 등록한 event가 발생하는지 지속적으로 감지
	glutMainLoop();

	return 0;
}
