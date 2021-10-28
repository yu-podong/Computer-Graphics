/***************************************************************************/
/*                   HW#1 : 3D Sierpinski Gasket                           */
/*  작성자 : 유현진                              날짜 : 2021년 9월 17일    */
/*                                                                         */
/* 문제 정의 : 2D Sierpinski Gasket를 기반으로 하여 2D Sierpinski          */
/*             Gasket를 구현하고, reshape callback으로 왜곡문제 해결       */
/* 기능                                                                    */
/*    1. gasket을 구현하기 위해 정사면체를 분할하여 여러 정사면체를 생성   */
/*    2. sub-tetra를 생성하기 위한 정점 & 면 생성                          */
/*    3. gasket을 구현할 callback함수 정의 & 그림에 필요한 요소 설정       */
/*    4. reshape시, 왜곡문제를 해결해 줄 callback함수 생성                 */
/*    5. 배경색 설정 & 투영변환을 위한 투영변환 선택 및 가시부피 설정      */
/*    6. window 초기값 설정 및 callback함수 등록                           */
/***************************************************************************/

#include <GL/glut.h>
#include <stdlib.h>

// 정사면체의 각 면(삼각형)의 정점 생성
void makeTriangle(float *va, float *vb, float *vc)
{
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
}

// 3D Sierpinski gasket의 sub 정사면체 생성
void makeTetra(float *newV1, float *newV2, float *newV3, float *newV4)
{	
	// 4가지 색상에 대한 RGB값을 저장
	float colorSet[4][3] = {
		{1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0},
		{1.0, 1.0, 0.5}
	};

	// 빨간색을 띄는 사면체 면을 생성
	glColor3fv(colorSet[0]);
	makeTriangle(newV1, newV2, newV3);
	// 초록색을 띄는 사면체 면을 생성
	glColor3fv(colorSet[1]);
	makeTriangle(newV1, newV3, newV4);
	// 파란색을 띄는 사면체 면을 생성
	glColor3fv(colorSet[2]);
	makeTriangle(newV1, newV4, newV2);
	// 노란색을 띄는 사면체 면을 생성
	glColor3fv(colorSet[3]);
	makeTriangle(newV2, newV4, newV3);
}

// 정사면체 분할을 이용하여 gasket을 구성하기 위한 알고리즘 구현
void divideTetra(float *v1, float *v2, float *v3, float *v4, int m)
{
	// sub-tetra를 구성하기 위해 필요한 정점들을 저장할 배열
	float midVertexs[6][3];

	// 더이상 사면체를 분할할 수 없는 횟수가 될 때까지 진행
	if (m > 0)
	{
		// 정사면체 분할을 통해 gasket을 만들기 위해 모든 2개 정점의 쌍에 대한 중점 계산
		for (int j = 0; j < 3; j++) {
			midVertexs[0][j] = (v1[j] + v2[j]) / 2.0;
			midVertexs[1][j] = (v1[j] + v3[j]) / 2.0;
			midVertexs[2][j] = (v1[j] + v4[j]) / 2.0;
			midVertexs[3][j] = (v2[j] + v3[j]) / 2.0;
			midVertexs[4][j] = (v3[j] + v4[j]) / 2.0;
			midVertexs[5][j] = (v2[j] + v4[j]) / 2.0;
		}
		
		// v1~v4로 구성된 정사면체를 크게 4개의 sub-tetra로 분할하여 각 sub-tetra의 gasket 생성
		divideTetra(v1, midVertexs[0], midVertexs[1], midVertexs[2], m - 1);
		divideTetra(midVertexs[0], v2, midVertexs[3], midVertexs[5], m - 1);
		divideTetra(midVertexs[1], midVertexs[3], v3, midVertexs[4], m - 1);
		divideTetra(midVertexs[2], midVertexs[4], v4, midVertexs[5], m - 1);
	}
	// 더이상 분할횟수가 남아있지 않으면 (2d로 따지면, 50000번 반복 끝남)
	else (
		// 현재 v1~v4로 tetra를 생성 (여기까지 오면, 가장 작은 tetra로 gasket을 만드는 과정 진행)
		makeTetra(v1, v2, v3, v4)
	);
}

// Sierpinski Gasket 알고리즘으로 생성되는 결과물을 출력
void displaySierpinski() {
	// v1, v2, v3, v4를 나타내줄 정점의 위치를 배열에 저장
	float vertices[4][3] = {
		{ 250.0, 500.0, 83.0 },	// v1
		{ 0.0, 0.0, 0.0 },		// v2
		{ 250.0, 0.0, 500.0 },	// v3
		{ 500.0, 0.0, 0.0 }		// v4
	};

	// 색 버퍼를 제거하여 기존에 버퍼에 저장된 그림을 제거 & 깊이 버퍼도 초기화
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Sierpinski Gasket를 구성하는 sub-tetra를 생성
	glBegin(GL_TRIANGLES);
		divideTetra(vertices[0], vertices[1], vertices[2], vertices[3], 4);
	glEnd();

	// 지금까지 쌓인 명령들을 실행할 수 있도록 process로 전달
	glFlush();
}

// window의 사이즈가 변할 때, 왜곡이 발생하지 않도록 가시부피와 viewport의 종횡비 일치
void reshapeSolution(int newWidth, int newHeight) {
	// viewport의 크기를 변경된 window의 사이즈로 설정
	glViewport(100, 100, newWidth, newHeight);

	// window의 사이즈 변경으로 인해 발생한 늘어난 비율을 계산
	GLfloat Widthfactor = (GLfloat)newWidth / (GLfloat)300;
	GLfloat Heightfactor = (GLfloat)newHeight / (GLfloat)300;

	// 투영변환을 위한 행렬을 선택
	glMatrixMode(GL_PROJECTION);
	// 해당 행렬에 적용되었던 setting 초기화
	glLoadIdentity();
	// 가시부피의 종횡비를 변경된 비율로 수정
	glOrtho(-500.0*Widthfactor, 500.0*Widthfactor, -500.0* Heightfactor, 500.0*Heightfactor, 500.0, -500.0);
}

// 배경 & 정점 color 결정 및 투영변환을 위한 과정 실행
void setting() {
	// window의 배경색을 흰색으로 설정
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// 투영 변환을 하기 위한 행렬 선택
	glMatrixMode(GL_PROJECTION);
	// 해당 행렬에 적용된 setting을 초기화
	glLoadIdentity();
	// 직교투영 변환 함수를 통해 500 * 600 * 500의 크기를 갖는 가시부피 결정
	glOrtho(-500.0, 500.0, -500.0, 500.0, -500.0, 500.0);
}

void main(int argc, char** argv)
{
	// OS와 Session 연결 / GLUT library 초기화
	glutInit(&argc, argv);
	// display mode를 RGB로 설정 & 은면 제거를 하기위한 준비
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	// window 크기의 초기값을 500,500으로 설정
	glutInitWindowSize(500, 500);
	// window의 위치를 모니터의 왼쪽 상단에 띄우도록 설정
	glutInitWindowPosition(0, 0);
	// 새로 생길 window의 타이틀을 'Sierpinski Gasket'로 설정
	glutCreateWindow("Sierpinski Gasket");

	//// 3D임을 확인할 수 있도록 카메라 위치, 기울기, 초점을 설정
	gluLookAt(350.0, 100.0, 300.0, 20.0, 0.0, 100.0, 0.0, 1.0, 0.5);
	// display callback함수를 등록
	glutDisplayFunc(displaySierpinski);
	// reshape callback함수를 등록
	glutReshapeFunc(reshapeSolution);
	// 앞 물체에 가려서 안 보이는 부분 제거(은면 제거)하기 위해 명시적으로 설정
	glEnable(GL_DEPTH_TEST);
	// 그림의 색상 및 투영변환 적용
	setting();

	// callback 함수로 등록한 event가 발생하는지 지속적으로 감지
	glutMainLoop();
}