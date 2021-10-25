/***************************************************************************/
/*                       HW#3-4 : Menu Callback 응용                       */
/*                                               날짜 : 2021년 10월 3일    */
/*                                                                         */
/* 문제 정의 : 코드 5-6을 수정하여 특정 메뉴를 눌렀을 경우,                */
/*             해당하는 기능을 수행하도록 진행			                   */
/* 기능                                                                    */
/*   1. Draw Sphere 하부 메뉴 : Small Sphere, Large Sphere                 */
/*   2. Draw Torus 하부 메뉴 : Small Torus , Large Torus                   */
/*   3. Draw Teapot 하부 메뉴 : Small Teapot , Large Teapot                */
/*   4. Change Color 하부 메뉴 : Red, Green, Blue                          */
/***************************************************************************/

#include <GL/glut.h>
#include <stdlib.h>
#include <string>

// 도형의 사이즈 및 색상 변경 메뉴를 클릭했는지 구분할 변수
GLboolean isSmall = true, checkColorMenu = false;
// 도형 종류 및 색상을 결정지을 변수 
GLint selectMenu = 's', color = 'r';

// 선택한 mainMenu에 해당하는 기능을 수행하기 위한 작업을 하는 함수
void mainMenuCallback(int entryID) {
	// but 이 프로그램에선 처리할 작업 없음
}

// 선택한 'Draw Sphere'의 서브 메뉴에 해당하는 기능을 수행하기 위한 작업을 하는 함수
void sphereMenuCallback(int entryID) {
	// sphere 메뉴를 선택했음을 표시
	selectMenu = 's';

	// 'small sphere' 서브메뉴를 선택
	if (entryID == 1) {
		isSmall = true;
	}
	// 'big sphere' 서브메뉴를 선택
	else if (entryID == 2) {
		isSmall = false;
	}
	// 변경된 변수의 값을 가지고, 선택한 기능이 수행되도록 display event를 강제 발생
	glutPostRedisplay();
}

// 선택한 'Draw Torus'의 서브 메뉴에 해당하는 기능을 수행하기 위한 작업을 하는 함수
void torusMenuCallback(int entryID) {
	// torus 메뉴를 선택했음을 표시
	selectMenu = 't';

	// 'small torus' 서브메뉴를 선택
	if (entryID == 1) {
		isSmall = true;
	}
	// 'big torus' 서브메뉴를 선택
	else if (entryID == 2) {
		isSmall = false;
	}
	// 변경된 변수의 값을 가지고, 선택한 기능이 수행되도록 display event를 강제 발생
	glutPostRedisplay();
}

// 선택한 'Draw Teapot'의 서브 메뉴에 해당하는 기능을 수행하기 위한 작업을 하는 함수
void teapotMenuCallback(int entryID) {
	// teapot 메뉴를 선택했음을 표시
	selectMenu = 'T';

	// 'small teapot' 서브메뉴를 선택
	if (entryID == 1) {
		isSmall = true;
	}
	// 'big teapot' 서브메뉴를 선택
	else if (entryID == 2) {
		isSmall = false;
	}
	// 변경된 변수의 값을 가지고, 선택한 기능이 수행되도록 display event를 강제 발생
	glutPostRedisplay();
}

void colorMenuCallback(int entryID) {
	// color 메뉴를 선택했음을 표시
	checkColorMenu = true;

	// 'red' 서브메뉴 선택
	if (entryID == 1) {
		color = 'r';
	}
	// 'green' 서브메뉴 선택
	else if (entryID == 2) {
		color = 'g';
	}
	// 'blue' 서브메뉴 선택
	else if (entryID == 3) {
		color = 'b';
	}
	// 변경된 변수의 값을 가지고, 선택한 기능이 수행되도록 display event를 강제 발생
	glutPostRedisplay();
}

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

	// sphereMenu 함수 등록 & 선택된 메뉴 아이디 값이 리턴
	GLint sphereMenuID = glutCreateMenu(sphereMenuCallback);
	// 'Draw Sphere'의 서브메뉴로 'Small Sphere'를 추가하고 메뉴 아이디를 1로 설정
	glutAddMenuEntry("Small Sphere", 1);
	// 'Draw Sphere'의 서브메뉴로 'Big Sphere'를 추가하고 메뉴 아이디를 2로 설정
	glutAddMenuEntry("Large Sphere", 2);

	// torusMenu 함수 등록 & 선택된 메뉴 아이디 값이 리턴
	GLint torusMenuID = glutCreateMenu(torusMenuCallback);
	// 'Draw Torus'의 서브메뉴로 'Small Torus'를 추가하고 메뉴 아이디를 1로 설정
	glutAddMenuEntry("Small Sphere", 1);
	// 'Draw Torus'의 서브메뉴로 'Big Torus'를 추가하고 메뉴 아이디를 2로 설정
	glutAddMenuEntry("Large Sphere", 2);

	// teapotMenu 함수 등록 & 선택된 메뉴 아이디 값이 리턴
	GLint teapotMenuID = glutCreateMenu(teapotMenuCallback);
	// 'Draw Teapot'의 서브메뉴로 'Small Teapot'를 추가하고 메뉴 아이디를 1로 설정
	glutAddMenuEntry("Small Sphere", 1);
	// 'Draw Teapot'의 서브메뉴로 'Big Teapot'를 추가하고 메뉴 아이디를 2로 설정
	glutAddMenuEntry("Large Sphere", 2);

	// colorMenu 함수 등록 & 선택된 메뉴 아이디 값이 리턴
	GLint colorMenuID = glutCreateMenu(colorMenuCallback);
	// 'Change Color'의 서브메뉴로 'Red'를 추가하고 메뉴 아이디를 1로 설정
	glutAddMenuEntry("Red", 1);
	// 'Change Color'의 서브메뉴로 'Green'를 추가하고 메뉴 아이디를 2로 설정
	glutAddMenuEntry("Green", 2);
	// 'Change Color'의 서브메뉴로 'Blue'를 추가하고 메뉴 아이디를 3로 설정
	glutAddMenuEntry("Blue", 3);

	// sphereMenu 함수 등록 & 선택된 메뉴 아이디 값이 리턴
	GLint mainMenuID = glutCreateMenu(mainMenuCallback);
	// 여러 서브메뉴로 이루어진 'Draw Sphere'메뉴를 추가
	glutAddSubMenu("Draw Sphere", sphereMenuID);
	// 여러 서브메뉴로 이루어진 'Draw Torus'메뉴를 추가
	glutAddSubMenu("Draw Torus", torusMenuID);
	// 여러 서브메뉴로 이루어진 'Draw Teapot'메뉴를 추가
	glutAddSubMenu("Draw Teapot", teapotMenuID);
	// 여러 서브메뉴로 이루어진 'Change Color'메뉴를 추가
	glutAddSubMenu("Change Color", colorMenuID);

	// 오늘쪽 마우스 버튼에 main menu 할당
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// 사각형을 그리는 display callback function
void displayCallback() {
	// 색 버퍼 초기화
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 0.0, 0.0);

	// change color의 red를 선택하면
	if (checkColorMenu && color == 'r') {
		// 그려질 도형을 red로 설정
		glColor3f(1.0, 0.0, 0.0);
	}
	// change color의 green을 선택하면
	else if (checkColorMenu && color == 'g') {
		// 그려질 도형을 green로 설정
		glColor3f(0.0, 1.0, 0.0);
	}
	// change color의 blue를 선택하면
	else if (checkColorMenu && color == 'b') {
		// 그려질 도형을 blue로 설정
		glColor3f(0.0, 0.0, 1.0);
	}
	// 처음 프로그램을 실행하여 아무 짓도 안했을 경우
	else {
		// 도형을 설정된 값이 나타내는 색으로 설정
		glColor3f(0.0, 0.5, 0.5);
	}

	//  Small Sphere를 선택한 경우, 작은 Sphere 생성
	if (selectMenu == 's' && isSmall) {
		glutWireSphere(0.5, 30, 30);
	}
	//  Large Sphere를 선택한 경우, 큰 Sphere 생성
	else if (selectMenu == 's' && (!isSmall)) {
		glutWireSphere(0.7, 30, 30);
	}
	//  Small Torus를 선택한 경우, 작은 Torus 생성
	else if (selectMenu == 't' && isSmall) {
		glutWireTorus(0.1, 0.3, 40, 20);
	}
	// Large Torus를 선택한 경우, 큰 Torus 생성
	else if (selectMenu == 't' && (!isSmall)) {
		glutWireTorus(0.2, 0.5, 40, 20);
	}
	// Small Teapot을 선택한 경우, 작은 Teapot 생성
	else if (selectMenu == 'T' && isSmall) {
		glutWireTeapot(0.3);
	}
	// Large Teapot을 선택한 경우, 큰 Teapot 생성
	else if (selectMenu == 'T' && (!isSmall)) {
		glutWireTeapot(0.5);
	}

	// 쌓아놓은 명령들을 바로 실행하도록 process에게 전달
	glFlush();
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
	// window의 타이틀을 'Menu Callback 응용'으로 설정
	glutCreateWindow("Menu Callback 응용");

	// 색상과 변환과 관련된 함수 호출
	myInit();
	// display callback function 등록
	glutDisplayFunc(displayCallback);

	// callback 함수로 등록한 event가 발생하는지 지속적으로 감지
	glutMainLoop();

	return 0;
}
