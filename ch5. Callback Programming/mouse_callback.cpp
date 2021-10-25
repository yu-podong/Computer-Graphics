/***************************************************************************/
/*                  HW#3-3 : Mouse Callback 응용                           */
/*                                               날짜 : 2021년 10월 1일    */
/*                                                                         */
/* 문제 정의 : 코드 5-3을 수정하여 특수 키가 눌렸을 경우, 해당하는 기능을  */
/*             수행하도록 진행			                                   */
/* 기능                                                                    */
/*   1. 마우스 왼쪽 버튼을 click										   */
/*      : 4개의 vertex 좌표가 동일하게 오른쪽으로 0.1씩 연속적으로 이동    */
/*   2. 마우스 오른쪽 버튼을 click										   */
/*      : 이동하고 있는 Polygon이 멈춤									   */
/***************************************************************************/

#include <GL/glut.h>

// 4개의 정점의 좌표 저장
float vertexs[4][3] = {
	{0.0, 0.4, 0.0},
	{0.2, 0.4, 0.0},
	{0.2, 0.6, 0.0},
	{0.0, 0.6, 0.0}
};

// Timer를 핸들링하기 위해 설정한 변수
int controlTimer;

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

	// 1*1*2 크기를 가지는 가시부피 설정
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

// 사각형을 그리는 display callback function
void displayCallback() {
	glViewport(0, 0, 500, 500);
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

// 일정시간마다 사각형의 이동을 담당할 timer callback 함수
void timer(int value) {
	// 사각형이 window의 끝에 도달했거나, 오른쪽 마우스가 클릭된 경우
	if (vertexs[1][0] >= 1.0 || controlTimer == 2) {
		// 더이상 timer함수를 진행 X
	}
	// 아직 window의 끝에 도달하지 않았거나 stop하는 버튼이 클릭되지 않았다면
	else {
		// 사각형의 각 꼭짓점을 오른쪽으로 0.1 이동
		vertexs[0][0] += 0.1;
		vertexs[1][0] += 0.1;
		vertexs[2][0] += 0.1;
		vertexs[3][0] += 0.1;

		// 강제로 display event를 발생시켜 변경된 좌표 사각형 이동
		glutPostRedisplay();

		// 500msec뒤에 timer함수를 실행
		glutTimerFunc(500, timer, value);
	}
}

// mouse event를 처리해줄 mouse callback 함수
void mouseCallback(int button, int state, int x, int y) {
	// 왼쪽 마우스가 클릭되었다면
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// control값을 1로 설정
		controlTimer = 1;
		// timer 함수를 호출하여 일정주기마다 사각형 이동
		glutTimerFunc(0, timer, controlTimer);
	}
	// 오른쪽 마우스가 클릭되었다면
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		// control값을 2로 바뀌 timer함수를 더이상 호출하지 않도록 설정
		controlTimer = 2;
	}
}

int main(int argc, char** argv) {
	// OS와 Session 연결 / GLUT library 초기화
	glutInit(&argc, argv);
	// display mode를 RGB로 설정 & 더블 버퍼링을 위한 mode 설정
	glutInitDisplayMode(GLUT_RGB);
	// 새로 생성된 window의 크기를 800 * 600로 설정
	glutInitWindowSize(500, 500);
	// window의 위치를 왼쪽 상단으로 설정
	glutInitWindowPosition(0, 0);
	// window의 타이틀을 'Mouse Callback 응용'으로 설정
	glutCreateWindow("Mouse Callback 응용");

	// 색상과 변환과 관련된 함수 호출
	myInit();
	// display callback function 등록
	glutDisplayFunc(displayCallback);
	// special keyboard callback function 등록
	glutMouseFunc(mouseCallback);

	// callback 함수로 등록한 event가 발생하는지 지속적으로 감지
	glutMainLoop();

	return 0;
}
