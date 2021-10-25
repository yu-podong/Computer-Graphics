/***************************************************************************/
/*               HW#2-1 : GL Modeling - 2D Primitives 구현                 */
/*                                               날짜 : 2021년 9월 28일    */
/*                                                                         */
/* 문제 정의 : Points, Lines, LineStrip, LineLoop, TrangleFan, Triangles,  */
/*             TriangleStrip, Polygons, Quads, QuadStrip를 강의자료에      */
/*             첨부된 모양과 동일하게 구현                                 */
/* 기능                                                                    */
/*	1. GL_POINTS를 사용하여 정점 표현	                                   */
/*	2. GL_LINES를 사용하여 실선 표현	                                   */ 
/*	3. GL_LINE_STRIP을 사용하여 실선들을 이어줌	                           */
/*	4. GL_LINE_LOOP를 사용하여 모든 정점들을 실선으로 이어줌	           */
/*	5. GL_POLYGON을 사용하여 채워진 육각형 표현	                           */
/*	6. GL_TRIANGLES를 사용하여 채워진 삼각형 표현	                       */
/*	7. GL_TRIANGLE_STRIP을 사용하여 삼각형들을 이어줌	                   */
/*	8. GL_TRIANGLE_FAN을 사용하여 부채 모양으로 삼각형을 이어줌	           */
/*	9. GL_QUADS를 사용하여 채워진 사각형 표현	                           */
/*	10. GL_QUAD_STRIP을 사용하여 사각형들을 이어줌						   */	
/***************************************************************************/

#include <GL/glut.h>

// GL Library를 이용해 문제정의에 작성한 10개의 2D Primitive들을 구현
void MyDisplay() {
	// COLOR BUFFER에 저장된 그림을 삭제 (초기화)
	glClear(GL_COLOR_BUFFER_BIT);

	// 앞으로 그려질 그림의 색상을 파랑색으로 지정
	glColor3f(0.1, 0.1, 1.0);

	// 정점의 size를 설정
	glPointSize(5);

	// 각 Vertex들을 하나의 점으로 표현하여, 육각형 모양으로 배치
	glBegin(GL_POINTS);
		glVertex3f(-1.0, 0.0, 0.0);		// v5
		glVertex3f(-0.5, 1.0, 0.0);		// v4
		glVertex3f(0.5, 1.0, 0.0);		// v3
		glVertex3f(1.0, 0.0, 0.0);		// v2
		glVertex3f(0.5, -1.0, 0.0);		// v1
		glVertex3f(-0.5, -1.0, 0.0);	// v0
	glEnd();

	// 차례대로 2개의 vertex를 선택하여 line 생성 (v5-v4, v3-v2, v1-v0)
	glBegin(GL_LINES);
		glVertex3f(-1.0 +3.0, 0.0, 0.0);	// v5
		glVertex3f(-0.5 + 3.0, 1.0, 0.0);	// v4
		glVertex3f(0.5 + 3.0, 1.0, 0.0);	// v3
		glVertex3f(1.0 + 3.0, 0.0, 0.0);	// v2
		glVertex3f(0.5 + 3.0, -1.0, 0.0);	// v1
		glVertex3f(-0.5 + 3.0, -1.0, 0.0);	// v0
	glEnd();

	// line들을 하나의 줄로 연결하되, 첫번째와 마지막 vertex의 연결 없음
	glBegin(GL_LINE_STRIP);
		glVertex3f(-1.0 + 3.0 + 3.0, 0.0, 0.0);		// v5
		glVertex3f(-0.5 + 3.0 + 3.0, 1.0, 0.0);		// v4
		glVertex3f(0.5 + 3.0 + 3.0, 1.0, 0.0);		// v3
		glVertex3f(1.0 + 3.0 + 3.0, 0.0, 0.0);		// v2
		glVertex3f(0.5 + 3.0 + 3.0, -1.0, 0.0);		// v1
		glVertex3f(-0.5 + 3.0 + 3.0, -1.0, 0.0);	// v0
	glEnd();

	// line들을 하나의 줄로 연결하되, 첫번째와 마지막 vertex을 연결한 line도 포함
	glBegin(GL_LINE_LOOP);
		glVertex3f(-1.0 + 3.0 + 3.0 + 3.0, 0.0, 0.0);	// v5
		glVertex3f(-0.5 + 3.0 + 3.0 + 3.0, 1.0, 0.0);	// v4
		glVertex3f(0.5 + 3.0 + 3.0 + 3.0, 1.0, 0.0);	// v3
		glVertex3f(1.0 + 3.0 + 3.0 + 3.0, 0.0, 0.0);	// v2
		glVertex3f(0.5 + 3.0 + 3.0 + 3.0, -1.0, 0.0);	// v1
		glVertex3f(-0.5 + 3.0 + 3.0 + 3.0, -1.0, 0.0);	// v0
	glEnd();

	// 각 vertex들을 이용하여 채워진 육각형 생성
	glBegin(GL_POLYGON);
		glVertex3f(-1.0, 0.0 - 3.0, 0.0);	// v5
		glVertex3f(-0.5, 1.0 - 3.0, 0.0);	// v4
		glVertex3f(0.5, 1.0 - 3.0, 0.0);	// v3
		glVertex3f(1.0, 0.0 - 3.0, 0.0);	// v2
		glVertex3f(0.5, -1.0 - 3.0, 0.0);	// v1
		glVertex3f(-0.5, -1.0 - 3.0, 0.0);	// v0
	glEnd();

	// 차례대로 3개의 vertex씩 선택하여 채워진 삼각형 2개를 생성
	glBegin(GL_TRIANGLES);
		glVertex3f(-1.0 + 3.0, 0.0 - 3.0, 0.0);		// v5
		glVertex3f(-0.5 + 3.0, 1.0 - 3.0, 0.0);		// v4
		glVertex3f(0.5 + 3.0, 1.0 - 3.0, 0.0);		// v3
		glVertex3f(1.0 + 3.0, 0.0 - 3.0, 0.0);		// v2
		glVertex3f(0.5 + 3.0, -1.0 - 3.0, 0.0);		// v1
		glVertex3f(-0.5 + 3.0, -1.0 - 3.0, 0.0);	// v0
	glEnd();

	// 이웃된 3개의 vertex씩 선택하여 채워진 삼각형으로 이어서 그림 
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-0.5 + 3.0 + 3.0, -0.5 - 3.0, 0.0);	// v6
		glVertex3f(0.2 + 3.0 + 3.0, 0.5 - 3.0, 0.0);	// v5
		glVertex3f(1.0 + 3.0 + 3.0, -0.4 - 3.0, 0.0);	// v4
		glVertex3f(1.5 + 3.0 + 3.0, 0.8 - 3.0, 0.0);	// v3
		glVertex3f(2.0 + 3.0 + 3.0, -0.2 - 3.0, 0.0);	// v2
		glVertex3f(2.5 + 3.0 + 3.0, 0.7 - 3.0, 0.0);	// v1
		glVertex3f(3.0 + 3.0 + 3.0, -0.8 - 3.0, 0.0);	// v0
	glEnd();

	// 이웃한 정점과 마지막 정점을 선택하여 채워진 삼각형으로 그려 부채 모양으로 연결 
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(-0.5, 1.0 - 3.0 - 3.0, 0.0);	 // v5
		glVertex3f(0.2, 1.0 - 3.0 - 3.0, 0.0);	 // v4
		glVertex3f(1.0, 0.5 - 3.0 - 3.0, 0.0);	 // v3
		glVertex3f(1.2, -0.2 - 3.0 - 3.0, 0.0);	 // v2
		glVertex3f(1.6, -0.6 - 3.0 - 3.0, 0.0);	 // v1
		glVertex3f(-1.0, -1.0 - 3.0 - 3.0, 0.0); // v0
	glEnd();

	// 차례대로 4개의 정점을 선택하여 채워진 사각형을 그림
	glBegin(GL_QUADS);
		glVertex3f(-0.9 + 3.0, 0.5 - 3.0 - 3.0, 0.0);	 // v7
		glVertex3f(-0.8 + 3.0, 0.8 - 3.0 - 3.0, 0.0);	 // v6
		glVertex3f(-0.2 + 3.0, 0.9 - 3.0 - 3.0, 0.0);	 // v5
		glVertex3f(-0.3 + 3.0, 0.3 - 3.0 - 3.0, 0.0);	 // v4
		glVertex3f(0.0 + 3.0, -0.5 - 3.0 - 3.0, 0.0);	 // v3
		glVertex3f(0.5 + 3.0, 0.5 - 3.0 - 3.0, 0.0);	 // v2
		glVertex3f(1.1 + 3.0, 0.2 - 3.0 - 3.0, 0.0);	 // v1
		glVertex3f(0.9 + 3.0, -0.5 - 3.0 - 3.0, 0.0);	 // v0
	glEnd();

	// 4개의 정점을 선택하여 생성된 사각형들을 이어서 그림
	glBegin(GL_QUAD_STRIP);
		glVertex3f(-0.8 + 3.0 + 3.0, 0.8 - 3.0 - 3.0, 0.0);	 // v6
		glVertex3f(-0.9 + 3.0 + 3.0, 0.5 - 3.0 - 3.0, 0.0);	 // v7
		glVertex3f(-0.2 + 3.0 + 3.0, 0.9 - 3.0 - 3.0, 0.0);	 // v5
		glVertex3f(-0.3 + 3.0 + 3.0, 0.3 - 3.0 - 3.0, 0.0);	 // v4
		glVertex3f(0.5 + 3.0 + 3.0, 0.5 - 3.0 - 3.0, 0.0);	 // v2
		glVertex3f(0.0 + 3.0 + 3.0, -0.5 - 3.0 - 3.0, 0.0);	 // v3
		glVertex3f(1.1 + 3.0 + 3.0, 0.2 - 3.0 - 3.0, 0.0);	 // v1
		glVertex3f(0.9 + 3.0 + 3.0, -0.5 - 3.0 - 3.0, 0.0);  // v0
	glEnd();

	// 지금까지 쌓인 명령들을 실행할 수 있도록 process로 전달
	glFlush();
}

int main(int argc, char** argv) {
	// OS와 Session 연결 / GLUT library 초기화
	glutInit(&argc, argv);
	// display mode를 RGB로 설정
	glutInitDisplayMode(GLUT_RGB);
	// window 크기의 초기값을 500,500으로 설정
	glutInitWindowSize(500, 500);
	// window의 위치를 모니터의 왼쪽 상단에 띄우도록 설정
	glutInitWindowPosition(0, 0);
	// 새로 생길 window의 타이틀을 '2D Primitives 구현'로 설정
	glutCreateWindow("2D Primitives 구현");

	// window의 배경색을 흰색으로 설정
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// 직교투영 변환 함수를 통해 13 * 13 * 4의 크기를 갖는 가시부피 결정
	glOrtho(-2.0, 11.0, -11.0, 2.0, -2.0, 2.0);

	// display callback 함수 등록
	glutDisplayFunc(MyDisplay);

	// callback 함수로 등록한 event가 발생하는지 지속적으로 감지
	glutMainLoop();

	return 0;
}