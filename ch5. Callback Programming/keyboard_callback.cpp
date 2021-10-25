/***************************************************************************/
/*                   HW#3-1 : Keyboard Callback 응용I                      */
/*                                               날짜 : 2021년 10월 1일    */
/*                                                                         */
/* 문제 정의 : 코드 5-3을 수정하여 특정 키(특수 키 제외)가 눌렸을 경우,    */
/*             해당하는 기능을 수행하도록 진행			                   */
/* 기능                                                                    */
/*   1. a 또는 A : 4개의 vertex 좌표가 동일하게 왼쪽으로 0.1씩 이동        */
/*   2. f 또는 F : 4개의 vertex 좌표가 동일하게 오른쪽으로 0.1씩 이동      */
/*   3. r 또는 R : 4개의 vertex 좌표가 동일하게 아래쪽으로 0.1씩 이동하고, */
/*                 빨간색으로 Polygon 칠함                                 */
/*   4. v 또는 V : 4개의 vertex 좌표가 동일하게 위쪽으로 0.1씩 이동        */
/*   5. b 또는 B : 파란색으로 Polygon 칠함                                 */
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

// 누른 키에 따라 그림을 움직이게 하는 keyboard callback function
void keyCallback(unsigned char key, int x, int y) {
	switch (key) {
		// a 또는 A가 입력되면, 사각형을 왼쪽으로 이동
		case 'a':
		case 'A':
			vertexs[0][0] -= 0.1;
			vertexs[1][0] -= 0.1;
			vertexs[2][0] -= 0.1;
			vertexs[3][0] -= 0.1;
			break;
		// f 또는 F가 입력되면, 사각형을 오른쪽으로 이동
		case 'f':
		case 'F':
			vertexs[0][0] += 0.1;
			vertexs[1][0] += 0.1;
			vertexs[2][0] += 0.1;
			vertexs[3][0] += 0.1;
			break;
		// r 또는 R이 입력되면, 사각형을 아래쪽으로 이동하고 사각형 색을 red로 변경
		case 'r':
		case 'R':
			vertexs[0][1] -= 0.1;
			vertexs[1][1] -= 0.1;
			vertexs[2][1] -= 0.1;
			vertexs[3][1] -= 0.1;
			glColor3f(1.0, 0.0, 0.0);
			break;
		// v 또는 V가 입력되면, 사각형을 위쪽으로 이동
		case 'v':
		case 'V':
			vertexs[0][1] += 0.1;
			vertexs[1][1] += 0.1;
			vertexs[2][1] += 0.1;
			vertexs[3][1] += 0.1;
			break;
		// b 또는 B가 입력되면, 사각형 색을 blue로 변경
		case 'b':
		case 'B':
			glColor3f(0.0, 0.0, 1.0);
			break;
	}

	// 강제적으로 display event를 발생시켜, 좌표 & 색상 변경사항 반영
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
	// window의 타이틀을 'Keyboard Callback 응용I'으로 설정
	glutCreateWindow("Keyboard Callback 응용I");

	// 색상과 변환과 관련된 함수 호출
	myInit();
	// display callback function 등록
	glutDisplayFunc(displayCallback);
	// keyboard callback function 등록
	glutKeyboardFunc(keyCallback);
	
	// callback 함수로 등록한 event가 발생하는지 지속적으로 감지
	glutMainLoop();

	return 0;
}
