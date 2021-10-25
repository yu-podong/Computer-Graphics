/***************************************************************************/
/*                       HW#3-5 : Idle Callback 응용                       */
/*                                               날짜 : 2021년 10월 4일    */
/*                                                                         */
/* 문제 정의 : 코드 5-7을 수정하여 특정 방향키를 눌렀을 경우,              */
/*             해당하는 기능을 수행하도록 진행			                   */
/* 기능                                                                    */
/*   1. ↑ : 4개의 vertex 좌표가 동일하게 위쪽으로 연속적으로 0.1씩 이동    */
/*   2. ↓  : 4개의 vertex 좌표가 동일하게 아래쪽으로 연속적으로 0.1씩 이동 */
/*   3. ← : 4개의 vertex 좌표가 동일하게 왼쪽으로 연속적으로 0.1씩 이동    */
/*   4. → : 4개의 vertex 좌표가 동일하게 오른쪽으로 연속적으로 0.1씩 이동  */
/***************************************************************************/

#include <GL/glut.h>

// 사각형을 이동할 때 사용할 변수
GLfloat deltaX = 0.0, deltaY = 0.0;
// 어떤 키를 입력했는지 저장할 변수
GLint whichKey = ' ';

// 배경 및 그림 색 지정 & 투영변환 진행
void myInit() {
	// 배경색을 흰색으로 지정
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// 투영변환을 위한 행렬 선택
	glMatrixMode(GL_PROJECTION);
	// 해당 행렬에 적용되었던 setting 초기화
	glLoadIdentity();

	// 2*2*2 크기를 가지는 가시부피 설정
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

// 방향키를 입력했을 때 실행될 callback function
void specialCallback(int key, int x, int y) {
	switch (key) {
		// 위쪽 방향키를 입력하면, whickKey값이 u로 변경
		case GLUT_KEY_UP:
			whichKey = 'u';
			break;
		// 아래쪽 방향키를 입력하면, whickKey값이 d로 변경
		case GLUT_KEY_DOWN:
			whichKey = 'd';
			break;
		// 왼쪽 방향키를 입력하면, whickKey값이 l로 변경
		case GLUT_KEY_LEFT:
			whichKey = 'l';
			break;
		// 오른쪽 방향키를 입력하면, whickKey값이 r로 변경
		case GLUT_KEY_RIGHT:
			whichKey = 'r';
			break;
	}
}

// 사각형을 그리는 display callback function
void displayCallback() {
	// 색 버퍼를 초기화
	glClear(GL_COLOR_BUFFER_BIT);
	// 아래의 RGB값으로 사각형의 색 결정
	glColor3f(0.0, 0.5, 0.8);

	// 4개의 좌표을 이용하여 사각형을 해당 위치에 생성
	glBegin(GL_POLYGON);
		glVertex3f(-1.0 + deltaX, -0.5 + deltaY, 0.0);
		glVertex3f(0.0 + deltaX, -0.5 + deltaY, 0.0);
		glVertex3f(0.0 + deltaX, 0.5 + deltaY, 0.0);
		glVertex3f(-1.0 + deltaX, 0.5 + deltaY, 0.0);
	glEnd();
	
	// 현재 buffer를 front buffer로 전환
	glutSwapBuffers();
}

// 아무 event가 발생하지 않는 순간마다 실행할 callback function
void idleCallback() {
	// 전에 입력된 방향키가 UP이고, 사각형이 window의 상단에 걸쳐있지 않은 경우
	if (whichKey == 'u' && (0.5 + deltaY) < 1.0) {
		// 사각형을 위쪽으로 이동
		deltaY += 0.1;
	}
	// 전에 입력된 방향키가 DOWN이고, 사각형이 window의 하단에 걸쳐있지 않은 경우
	else if (whichKey == 'd' && (-0.5 + deltaY) > -0.9) {
		// 사각형을 아래쪽으로 이동
		deltaY -= 0.1;
	}
	// 전에 입력된 방향키가 LEFT이고, 사각형이 window의 좌측에 걸쳐있지 않은 경우
	else if (whichKey == 'l' && (-1.0 + deltaX) > -0.9) {
		// 사각형을 왼쪽으로 이동
		deltaX -= 0.1;
	}
	// 전에 입력된 방향키가 RIGHT이고, 사각형이 window의 우측에 걸쳐있지 않은 경우
	else if (whichKey == 'r' && (0.0 + deltaX) < 1.0) {
		// 사각형을 오른쪽으로 이동
		deltaX += 0.1;
	}
	
	// 변경된 좌표값을 가지고 사각형을 움직이기 위해, 강제적으로 display event 발생
	glutPostRedisplay();
	// delay를 걸어서 사각형의 움직임이 빠르지 않도록 설정
	Sleep(250);
}

int main(int argc, char** argv) {
	// OS와 Session 연결 / GLUT library 초기화
	glutInit(&argc, argv);
	// display mode를 RGB로 설정
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	// 새로 생성된 window의 크기를 800 * 600로 설정
	glutInitWindowSize(300, 300);
	// window의 위치를 왼쪽 상단으로 설정
	glutInitWindowPosition(0, 0);
	// window의 타이틀을 'Idle Callback 응용'으로 설정
	glutCreateWindow("Idle Callback 응용");

	// 색상과 변환과 관련된 함수 호출
	myInit();
	// display callback function 등록
	glutDisplayFunc(displayCallback); 
	// special callback function 등록
	glutSpecialFunc(specialCallback);
	// idle callback function 등록
	glutIdleFunc(idleCallback);

	// callback 함수로 등록한 event가 발생하는지 지속적으로 감지
	glutMainLoop();

	return 0;
}
