/***************************************************************************/
/*               HW#2-2 : GLU Modeling - 3D Primitives 구현                */
/*                                               날짜 : 2021년 9월 28일    */
/*                                                                         */
/* 문제 정의 : 코드4-5와 코드4-7을 참고하여 Sphere, Cylinder, Disk,        */
/*             PartialDisk과 같은 3D Primitive 구현			               */
/* 기능                                                                    */
/*   1. 4개의 display list 생성 및 각 list의 ID를 저장                     */
/*   2. 4개의 Quadric object 생성 및 각각에 원하는 문제 정의에서 제시된    */
/*      primitive들의 설정 값을 저장                                       */
/*   3. 2번 과정에서 작성한 primitive 형성 code를 컴파일하여 각 display    */
/*      list에 저장                                                        */
/*   4. 조명 관련 옵션 설정 및 reshape callback 함수 정의 등록             */
/*   5. 각 display list를 실행하는 display callback 함수 정의 및 등록      */
/*      (but primitive의 위치 방법을 몰라 해당 함수에서 주석 on/off 필요   */
/***************************************************************************/

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

// 4개의 디스플레이 리스트 아이디를 저장할 변수
int listOne, listTwo, listThree, listFour;
// 새로운 Quadirc Object 4개 생성
GLUquadricObj *qobj[4] = { gluNewQuadric(), gluNewQuadric(), gluNewQuadric(), gluNewQuadric() };

// 조명 관련 옵션을 설정
void MyInit(void) {
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat model_ambient[] = { 0.5, 0.4, 0.3, 1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);

	// 특정방향을 가지지 않는 빛인 주변광
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);	
	// 특정방향으로 빛이 들어오고 특정방향으로 반사하는 반사광
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);	
	// 선명도 (값이 클수록 표면이 매끈매끈
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	// 조명을 사용하도록 설정
	glEnable(GL_LIGHTING);
	// LIGHT0인 조명을 사용하도록 설정
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

// 4개의 display list 생성 및 각 list에 제시된 3D Primitive를 생성하도록 명령 저장
void CreateList() {
	// 사용안된 4개의 디스플레이 리스트 생성
	// 그 중 1번째 display list ID 저장
	listOne = glGenLists(4);
	// 그 중 2번째 display list ID 저장
	listTwo = listOne + 1;
	// 그 중 3번째 display list ID 저장
	listThree = listTwo + 1;
	// 그 중 4번째 display list ID 저장
	listFour = listThree + 1;

	//command들이 컴파일되어 1번째 display list에 저장 (Sphere)
	glNewList(listOne, GL_COMPILE);
		// 0번째 Quadric 객체를 solid 형태로 렌더링
		gluQuadricDrawStyle(qobj[0], GLU_FILL);
		// 면이 부드럽게 모이도록 법선 벡터 생성
		gluQuadricNormals(qobj[0], GLU_SMOOTH);
		// 법선 벡터의 방향을 바깥쪽으로 가리키도록 설정
		gluQuadricOrientation(qobj[0], GLU_OUTSIDE);
		// Texture 좌표를 생성하지 않도록 설정
		gluQuadricTexture(qobj[0], GL_FALSE);

		// 반지름이 20인 구에 가까운 형태를 띄는 Sphere 생성
		gluSphere(qobj[0], 1.5, 50, 50);
	glEndList();

	//command들이 컴파일되어 2번째 display list에 저장 (Cylinder)
	glNewList(listTwo, GL_COMPILE);
		// 1번째 Quadric 객체의 외부 모서리만 모델링
		gluQuadricDrawStyle(qobj[1], GLU_SILHOUETTE);
		// 면이 부드럽게 모이도록 법선 벡터 생성
		gluQuadricNormals(qobj[1], GLU_SMOOTH);
		// 법선 벡터의 방향을 바깥쪽으로 가리키도록 설정
		gluQuadricOrientation(qobj[1], GLU_OUTSIDE);
		// Texture 좌표를 생성하지 않도록 설정
		gluQuadricTexture(qobj[1], GL_FALSE);
		
		// 윗면, 아래면의 크기가 다른 원기둥 형태로 Cylinder 생성 - 이상한 모양이 나옴(이유 모름)
		gluCylinder(qobj[1], 1.0, 0.3, 2.0, 20, 8);
	glEndList();

	//command들이 컴파일되어 3번째 display list에 저장 (Disk)
	glNewList(listThree, GL_COMPILE);
		// 2번째 Quadric 객체를 wire-frame 형태로 렌더링
		gluQuadricDrawStyle(qobj[2], GLU_LINE);
		// 면이 부드럽게 모이도록 법선 벡터 생성
		gluQuadricNormals(qobj[2], GLU_SMOOTH);
		// 법선 벡터의 방향을 바깥쪽으로 가리키도록 설정
		gluQuadricOrientation(qobj[2], GLU_OUTSIDE);
		// Texture 좌표를 생성하지 않도록 설정
		gluQuadricTexture(qobj[2], GL_FALSE);

		// 최대한 원에 가까운 외각을 가지고 중앙에 작은 구멍이 뚫린 형태로 Disk 생성
		gluDisk(qobj[2], 0.5, 1.5, 50, 3);
	glEndList();

	//command들이 컴파일되어 4번째 display list에 저장 (PartialDisk)
	glNewList(listFour, GL_COMPILE);
		// 3번째 Quadric 객체를 point로만 모델링
		gluQuadricDrawStyle(qobj[3], GLU_POINT);
		// 면이 부드럽게 모이도록 법선 벡터 생성
		gluQuadricNormals(qobj[3], GLU_SMOOTH);
		// 법선 벡터의 방향을 바깥쪽으로 가리키도록 설정
		gluQuadricOrientation(qobj[3], GLU_OUTSIDE);
		// Texture 좌표를 생성하지 않도록 설정
		gluQuadricTexture(qobj[3], GL_FALSE);

		// 원에 가까운 외각과 부채꼴 모양을 하는 PartialDisk 생성
		gluPartialDisk(qobj[3], 0.0, 1.5, 26, 13, 225.0, 120.0);
	glEndList();
}

// 버퍼 및 변환을 위한 행렬 선택, 각 display list를 실행
void MyDisplay() {
	// 색 버퍼와 깊이 버퍼를 초기화
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// viewport의 크기를 800 * 600으로 설정
	glViewport(0, 0, 800, 600);

	// 모델뷰 행렬을 선택
	glMatrixMode(GL_MODELVIEW);
	// 해당 행렬에 적용되었던 setting을 초기화
	glLoadIdentity();

	// 조명을 사용하도록 설정
	glEnable(GL_LIGHTING);
	// 조명에 의한 색 차이를 부드럽게 설정
	glShadeModel(GL_SMOOTH);

	// 컴파일이 완료된 리스트 4개를 실행하여 각각의 3D Primitive 그림
	glCallList(listOne);
	//glCallList(listTwo);
	//glCallList(listThree);
	//glCallList(listFour);

	// 지금까지 쌓인 명령들을 실행할 수 있도록 process로 전달
	glFlush();
}

// window의 사이즈가 변할 때, 
void Reshape(int newWidth, int newHeight) {
	// viewport를 변경된 window size로 크기 변경
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);

	// 투영변환을 위한 행렬을 선택
	glMatrixMode(GL_PROJECTION);
	// 해당 행렬에 적용되었던 setting 초기화
	glLoadIdentity();
	// 가시부피의 종횡비 수정
	glOrtho(-2.5, 2.5, -2.5*(GLfloat)newHeight / (GLfloat)newWidth, 2.5*(GLfloat)newHeight / (GLfloat)newWidth, -10.0, 10.0);

	// 모델뷰 행렬을 선택
	glMatrixMode(GL_MODELVIEW);
	// 해당 행렬에 적용되었던 setting을 초기화
	glLoadIdentity();
}

int main(int argc, char** argv) {
	// OS와 Session 연결 / GLUT library 초기화
	glutInit(&argc, argv);
	// display mode를 RGB로 설정 & 은면 제거를 위한 준비
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	// 새로 생성된 window의 크기를 800 * 600로 설정
	glutInitWindowSize(800, 600);
	// window의 위치를 왼쪽 상단으로 설정
	glutInitWindowPosition(0, 0);
	// window의 타이틀을 '3D Primitives 구현'으로 설정
	glutCreateWindow("3D Primitives 구현");

	// 3D primitive 구현 시, 조명 옵션을 설정
	MyInit();
	// display callback 함수를 등록
	glutDisplayFunc(MyDisplay);
	// reshape callback 함수를 등록
	glutReshapeFunc(Reshape);
	// 4개의 Display list를 생성
	CreateList();

	// callback 함수로 등록한 event가 발생하는지 지속적으로 감지
	glutMainLoop();

	return 0;
}
