/***************************************************************************/
/*                   HW#3-2 : Keyboard Callback 응용II                     */
/*                                               날짜 : 2021년 10월 1일    */
/*                                                                         */
/* 문제 정의 : 코드 5-3을 수정하여 특정 키(특수 키 제외)가 눌렸을 경우,    */
/*             해당하는 기능을 수행하도록 진행			                   */
/* 기능                                                                    */
/*   1. ← : 4개의 vertex 좌표가 동일하게 왼쪽으로 0.1씩 이동               */
/*   2. → : 4개의 vertex 좌표가 동일하게 오른쪽으로 0.1씩 이동             */
/*   3. ↓ : 4개의 vertex 좌표가 동일하게 아래쪽으로 0.1씩 이동하고,        */
/*                 빨간색으로 Polygon 칠함                                 */
/*   4. ↑ : 4개의 vertex 좌표가 동일하게 위쪽으로 0.1씩 이동               */
/*   5. PageUp : 4개의 vertex 좌표로 이루어진 Polygon이 각 방향으로 0.1씩  */
/*               연속적으로 확대(Zoom In)                                  */
/*   5. PageDown : 4개의 vertex 좌표로 이루어진 Polygon이 각 방향으로 0.1씩*/
/*                 연속적으로 축소(Zoom Out)                               */
/***************************************************************************/

#include <GL/glut.h>
#include <GL/gl.h>

// 4개의 정점의 좌표 저장
GLfloat vertexs[4][3] = {
	{-0.5, -0.5, 0.0},
	{0.5, -0.5, 0.0},
	{0.5, 0.5, 0.0},
	{-0.5, 0.5, 0.0}
};

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
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

// 사각형을 그리는 display callback function
void displayCallback() {
	// 색 버퍼 초기화
	glClear(GL_COLOR_BUFFER_BIT);

	// 4개의 정점을 이용하여 사각형 생성
	glBegin(GL_POLYGON);
	glVertex3fv(vertexs[0]);
	glVertex3fv(vertexs[1]);
	glVertex3fv(vertexs[2]);
	glVertex3fv(vertexs[3]);
	glEnd();

	// 쌓아놓은 명령들을 바로 실행하도록 process에게 전달
	glFlush();
}

// 방향키를 입력했을 때, 사각형이 더이상 움직일 수 없는 상태인지 판단
int checkVertexs(int key) {
	// 왼쪽 방향키를 입력했을 때, 사각형이 window 좌측에 걸쳐있는 경우
	if (key == GLUT_KEY_LEFT && vertexs[3][0] <= -1.0) {
		return 0;
	}
	// 위쪽 방향키를 입력했을 때, 사각형이 window 상단에 걸쳐있는 경우
	else if (key == GLUT_KEY_UP && vertexs[3][1] >= 1.0) {
		return 0;
	}
	// 오른쪽 방향키를 입력했을 때, 사각형이 window 우측에 걸쳐있는 경우
	else if (key == GLUT_KEY_RIGHT && vertexs[1][0] >= 1.0) {
		return 0;
	}
	// 아래쪽 방향키를 입력했을 때, 사각형이 window 하단에 걸쳐있는 경우
	else if (key == GLUT_KEY_DOWN && vertexs[1][1] <= -1.0) {
		return 0;
	}
}

// 연속적으로 사각형을 확대할 timer 함수
void timerZoomIn(int value) {
	// 확대를 하게 될 시, 사각형의 한 꼭짓점이라도 window를 벗어나는 경우
	if (vertexs[3][0] <= -1.0 || vertexs[3][1] >= 1.0
		|| vertexs[1][0] >= 1.0 || vertexs[1][1] <= -1.0) {
		// 더이상 확대 진행 X
		return;
	}
	// 확대를 해도 사각형의 모든 꼭짓점이 window 안에 있는 경우
	else {
		// 사각형의 각 꼭짓점을 이동하여 확대
		vertexs[0][0] -= 0.1; vertexs[0][1] -= 0.1;
		vertexs[1][0] += 0.1; vertexs[1][1] -= 0.1;
		vertexs[2][0] += 0.1; vertexs[2][1] += 0.1;
		vertexs[3][0] -= 0.1; vertexs[3][1] += 0.1;

		// display event를 강제로 발생시켜, 변경된 좌표를 반영하여 확대된 사각형 가시화
		glutPostRedisplay();
		// 500msec마다 조건을 충족하면 사각형 확대 진행
		glutTimerFunc(500, timerZoomIn, value);
	}
}

// 연속적으로 사각형을 축소할 timer 함수
void timerZoomOut(int value) {
	// 축소를 하게 될 시, 사각형이 가시적으로 보이지 않는 경우
	if (vertexs[1][0] - vertexs[0][0] <= 0.4) {
		// 더이상 축소 진행 X
		return;
	}
	// 축소를 해도 사각형이 가시적으로 보이는 경우
	else {
		// 사각형의 각 꼭짓점을 이동하여 축소
		vertexs[0][0] += 0.1; vertexs[0][1] += 0.1;
		vertexs[1][0] -= 0.1; vertexs[1][1] += 0.1;
		vertexs[2][0] -= 0.1; vertexs[2][1] -= 0.1;
		vertexs[3][0] += 0.1; vertexs[3][1] -= 0.1;

		// display event를 강제로 발생시켜, 변경된 좌표를 반영하여 축소된 사각형 가시화
		glutPostRedisplay();
		// 500msec마다 조건을 충족하면 사각형 축소 진행
		glutTimerFunc(500, timerZoomOut, value);
	}
}

// 누른 키에 따라 그림을 움직이게 하는 keyboard callback function
void specialCallback(int key, int x, int y) {
	// 방향키를 입력하여 사각형을 움직일 수 없는 경우
	if (checkVertexs(key) == 0) {
		// 입력된 방향키에 해당하는 기능 수행 X (무시)
		return;
	}

	switch (key) {
		// 왼쪽 방향키가 입력되면, 사각형을 왼쪽으로 이동
	case GLUT_KEY_LEFT:
		vertexs[0][0] -= 0.1;
		vertexs[1][0] -= 0.1;
		vertexs[2][0] -= 0.1;
		vertexs[3][0] -= 0.1;
		break;
		// 오른쪽 방향키가 입력되면, 사각형을 오른쪽으로 이동
	case GLUT_KEY_RIGHT:
		vertexs[0][0] += 0.1;
		vertexs[1][0] += 0.1;
		vertexs[2][0] += 0.1;
		vertexs[3][0] += 0.1;
		break;
		// 아래쪽 방향키가 입력되면, 사각형을 아래쪽으로 이동하고
	case GLUT_KEY_DOWN:
		vertexs[0][1] -= 0.1;
		vertexs[1][1] -= 0.1;
		vertexs[2][1] -= 0.1;
		vertexs[3][1] -= 0.1;
		break;
		// 위쪽 방향키가 입력되면, 사각형을 위쪽으로 이동
	case GLUT_KEY_UP:
		vertexs[0][1] += 0.1;
		vertexs[1][1] += 0.1;
		vertexs[2][1] += 0.1;
		vertexs[3][1] += 0.1;
		break;
		// Page up키가 입력되면 사각형이 계속 확대
	case GLUT_KEY_PAGE_UP:
		glutTimerFunc(500, timerZoomIn, 1);
		break;
		// Page Dn키가 입력되면 사각형이 계속 축소
	case GLUT_KEY_PAGE_DOWN:
		glutTimerFunc(500, timerZoomOut, 1);
		break;
	}

	// 강제적으로 display event를 발생시켜, 좌표 변경사항 반영
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	// OS와 Session 연결 / GLUT library 초기화
	glutInit(&argc, argv);
	// display mode를 RGB로 설정
	glutInitDisplayMode(GLUT_RGB);
	// 새로 생성된 window의 크기를 800 * 600로 설정
	glutInitWindowSize(300, 300);
	// window의 위치를 왼쪽 상단으로 설정
	glutInitWindowPosition(0, 0);
	// window의 타이틀을 'Keyboard Callback 응용II'으로 설정
	glutCreateWindow("Keyboard Callback 응용II");

	// 색상과 변환과 관련된 함수 호출
	myInit();
	// display callback function 등록
	glutDisplayFunc(displayCallback);
	// keyboard callback function 등록
	glutSpecialFunc(specialCallback);

	// callback 함수로 등록한 event가 발생하는지 지속적으로 감지
	glutMainLoop();

	return 0;
}
