/***************************************************************************/
/*                        HW#7 : 조명 종합 응용                            */
/*                                               날짜 : 2021년 11월 23일   */
/*                                                                         */
/* 문제 정의 : 실습과제4에서 계층적 모델링을 통해 구현한 <전신캔로봇>을    */
/*             아래의 기능들을 수행하도록 추가구현                         */
/*             또, 로봇에 조명을 적용하여 입체감을 부여                    */
/*                                                                         */
/* 기능                                                                    */
/*   1. <메뉴 "move head"를 누르면> 머리 움직이기                          */
/*   2. <메뉴 "move left arm"를 누르면> 왼쪽팔 움직이기					   */
/*   3. <메뉴 "move right arm"를 누르면> 오른팔 움직이기				   */
/*   4. <메뉴 "move left leg"를 누르면> 왼쪽다리 움직이기				   */
/*   5. <메뉴 "move right leg"를 누르면> 오른다리 움직이기				   */
/*   6. <R 또는 r 누르면> 달리는 모습으로 변경 <- 추가한 기능              */
/*   7. <S 누르면> 움직이는 신체가 멈춤						               */
/*   8. <i 누르면> 초기 기본자세로 변경	<- 추가한 기능   	               */
/***************************************************************************/

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

// 머리, 목 관절 각도 변수
static int headAngle = 0.0, neakAngle = 0.0;
// 각 팔 관절 각도 변수
static int armAngle[2][2] = {
	-30, 0,
	30, 0
};
// 각 다리 관절 각도 변수
static int legAngle[2][2] = {
	0, 0,
	0, 0
};
// 달리는 모습에서의 팔 관절 각도 변수
static int runArmAngle[2][2] = {
	50, -60,
	-40, -40
};
// 달리는 모습에서의 다리 관절 각도 변수
static int runLegAngle[2][2] = {
	40, 90,
	-100, 70
};
// 카메라의 위치 좌표 변수
//GLfloat c_position[3] = { 7.0*sin(-0.4), 0.0, 7.0*cos(-0.4) };
GLfloat c_position[3] = { 7.0*sin(-0.7), 0.0, 7.0*cos(-0.7) };
// 어떤 입력이 들어왔는지에 따라 그에 맞는 행동을 수행하도록 조절하는 변수
static int moveTimer = 0;
// 달리는 모습으로 변경해야 하는지를 결정하는 변수
static int isRun = 0;

void lightInti() {
	// 광원의 위치 좌표
	GLfloat light0_pos[4] = { 15.0*sin(0.4), 20.0, 15.0*cos(0.4), 1.0 };
	// 주변광 계수
	GLfloat ambient[4] = { 1.0, 1.0, 1.0, 1.0 };
	// 난반사광 계수
	GLfloat diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	// 0번 광원을 쓰기위해 활성화
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// 광원의 위치를 해당 좌표로 설정
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	// 주변광의 색 설정 (흰색)
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	// 난반사광의 색 설정 (흰색)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// 거리에 따른 빛의 감쇠효과 적용
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.7);

	// 고러드 쉐이딩 적용
	glShadeModel(GL_SMOOTH);
}

// 전신 can robot를 구성하는 그림을 그리는 callback function
void displayCallback() {
	// 각 빛에 대한 물체면의 특성 정의 (물체색 정의)
	GLfloat head_color[4] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat body_color[4] = { 0.6, 0.8, 0.9, 1.0 };
	GLfloat right_color[4] = { 1.0, 0.6, 0.0, 1.0 };
	GLfloat left_color[4] = { 0.2, 0.8, 0.2, 1.0 };

	GLfloat no_mat[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat no_shininess[4] = { 0.0, 0.0, 0.0, 0.0 };

	// buffer에 들어있는 그림 & 깊이 버퍼 초기화
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 모델뷰 행렬을 선택
	glMatrixMode(GL_MODELVIEW);
	// 해당 행렬에 적용되었던 setting을 초기화
	glLoadIdentity();

	// 카메라을 원점을 바라보도록 하고, 위치를 좌측으로 배치
	gluLookAt(c_position[0], c_position[1], c_position[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// 정반사광 계수, 발광색, 정반사광 광택 계수 기본값으로 설정
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);

	// 몸통 기준 모델 좌표계 구성
	glPushMatrix();
	glPushMatrix();
	glScalef(2.0, 2.5, 1.0);
	if (isRun == 1) {
		glRotatef(20.0, 1.0, 0.0, 0.0);
	}
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, body_color);
	glutSolidCube(1.0);
	glPopMatrix();

	// 목 기준 모델 좌표계 구성
	glPushMatrix();
	// 지금부터 그려질 그림들의 색을 노란색으로 설정
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, head_color);
	glTranslatef(0.0, 1.25, 0.0);
	glRotatef((GLfloat)neakAngle, 0.0, 0.0, 1.0);
	if (isRun == 1) {
		glRotatef(20.0, 1.0, 0.0, 0.0);
	}
	glTranslatef(0.0, 0.25, 0.0);
	glPushMatrix();
	glScalef(0.4, 0.5, 0.4);
	glutSolidCube(1.0);
	glPopMatrix();

	// 머리 기준 모델 좌표계 구성
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glRotatef((GLfloat)headAngle, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 1.0, 0.0);
	glPushMatrix();
	glutSolidSphere(1.0, 20, 20);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// 양쪽 팔을 구성하기 위한 for문 (특정 좌표빼고 동일한 구조라서)
	for (int i = 0; i < 2; i++) {
		// 왼쪽/오른쪽 어깨 기준 모델 좌표계 구성
		glPushMatrix();
		// 왼쪽 팔 구성 시
		if (i == 0) {
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, left_color);
			glTranslatef(-1.0, 1.25, 0.0);
		}
		// 오른쪽 팔 구성 시
		else {
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, right_color);
			glTranslatef(1.0, 1.25, 0.0);
		}
		glRotatef((GLfloat)armAngle[i][0], 0.0, 0.0, 1.0);
		if (isRun == 1) {
			glRotatef((GLfloat)runArmAngle[i][0], 1.0, 0.0, 0.0);
		}
		glTranslatef(0.0, -0.6, 0.0);
		glPushMatrix();
		glScalef(0.6, 1.2, 0.6);
		glutSolidCube(1.0);
		glPopMatrix();
		// 왼쪽/오른쪽 팔꿈치 기준 모델 좌표계 구성
		glPushMatrix();
		glTranslatef(0.0, -0.6, 0.0);
		glRotatef((GLfloat)armAngle[i][1], 0.0, 0.0, 1.0);
		if (isRun == 1) {
			glRotatef((GLfloat)runArmAngle[i][1], 1.0, 0.0, 0.0);
		}
		glTranslatef(0.0, -0.6, 0.0);
		glPushMatrix();
		glScalef(0.6, 1.2, 0.6);
		glutSolidCube(1.0);
		glPopMatrix();
		// 왼쪽/오른쪽 손 기준 모델 좌표계 구성
		glPushMatrix();
		glTranslatef(0.0, -0.6, 0.0);
		glRotatef((GLfloat)armAngle[i][1], 0.0, 0.0, 1.0);
		glTranslatef(0.0, -0.25, 0.0);
		glPushMatrix();
		glutSolidSphere(0.25, 10, 10);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
	}

	// 양쪽 다리를 구성하기 위한 for문 (특정 좌표빼고 동일한 구조라서)
	for (int i = 0; i < 2; i++) {
		// 왼쪽/오른쪽 고관절 기준 모델 좌표계 구성
		glPushMatrix();
		// 왼쪽 다리 구성 시
		if (i == 0) {
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, left_color);
			glTranslatef(-0.5, -1.25, 0.0);
		}
		// 오른쪽 다리 구성 시
		else {
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, right_color);
			glTranslatef(0.5, -1.25, 0.0);
		}
		glRotatef((GLfloat)legAngle[i][0], 0.0, 0.0, 1.0);
		if (isRun == 1) {
			glRotatef((GLfloat)runLegAngle[i][0], 1.0, 0.0, 0.0);
		}
		glTranslatef(0.0, -0.6, 0.0);
		glPushMatrix();
		glScalef(0.6, 1.2, 0.6);
		glutSolidCube(1.0);
		glPopMatrix();
		// 왼쪽/오른쪽 무릎 기준 모델 좌표계 구성
		glPushMatrix();
		glTranslatef(0.0, -0.6, 0.0);
		glRotatef((GLfloat)legAngle[i][1], 0.0, 0.0, 1.0);
		if (isRun == 1) {
			glRotatef((GLfloat)runLegAngle[i][1], 1.0, 0.0, 0.0);
		}
		glTranslatef(0.0, -0.6, 0.0);
		glPushMatrix();
		glScalef(0.6, 1.2, 0.6);
		glutSolidCube(1.0);
		glPopMatrix();
		// 왼쪽/오른쪽 발목 기준 모델 좌표계 구성
		glPushMatrix();
		// 왼쪽 다리를 구성 시
		if (i == 0) {
			glTranslatef(0.0, -0.6, 0.2);
		}
		// 오른쪽 다리를 구성 시
		else {
			glTranslatef(0.0, -0.6, 0.2);
		}
		glRotatef((GLfloat)legAngle[i][1], 0.0, 0.0, 1.0);
		glTranslatef(0.0, -0.2, 0.0);
		glPushMatrix();
		glScalef(0.6, 0.4, 0.8);
		glutSolidCube(1.0);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
	}
	glPopMatrix();


	// 그림이 그려질 buffer change (front buffer를 back buffer로 변환)
	glutSwapBuffers();
}

// reshape event 발생 시, 실행되는 callback function
void reshapeCallback(int newWidth, int newHeight) {
	// viewport를 변경된 window size로 크기 변경
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);

	GLfloat widthFactor = (GLfloat)newWidth / (GLfloat)1200;
	GLfloat heightFactor = (GLfloat)newHeight / (GLfloat)600;

	// 투영변환을 위한 행렬을 선택
	glMatrixMode(GL_PROJECTION);
	// 해당 행렬에 적용되었던 setting 초기화
	glLoadIdentity();
	// 가시부피의 종횡비 수정
	glOrtho(-10.0*widthFactor, 10.0*widthFactor, -5.0*heightFactor, 5.0*heightFactor, -10.0, 10.0);

	// 모델뷰 행렬을 선택
	glMatrixMode(GL_MODELVIEW);
	// 해당 행렬에 적용되었던 setting을 초기화
	glLoadIdentity();
}

// 일정시간마다 로봇을 움직여 줄 timer callback 함수
void timer(int value) {
	//더이상 로봇이 움직이지 않도록 timer을 호출 X
	if (moveTimer == 's') {

	}
	// 'move head'를 눌렀을 경우
	else if (value == 1) {
		// 머리를 왼쪽으로 움직이도록 각도 변경
		if (moveTimer == 'l') {
			if (neakAngle > -30) {
				neakAngle = (neakAngle - 5) % 180;
			}
			// 이제 오른쪽으로 움직이게 설정
			else {
				moveTimer = 'r';
			}
		}
		// 머리를 오른쪽으로 움직이도록 각도 변경
		else if (moveTimer == 'r') {
			if (neakAngle < 30) {
				neakAngle = (neakAngle + 5) % 180;
			}
			// 이제 다시 원래자리로 돌아오도록 설정
			else {
				moveTimer = 'b';
			}
		}
		// 원래자리로 돌아오도록 각도 변경
		else if (moveTimer == 'b') {
			if (neakAngle > 0) {
				neakAngle = (neakAngle - 5) % 180;
			}
			// 이제 멈추도록 설정
			else {
				moveTimer = 's';
			}
		}
		// 강제로 display event를 발생
		glutPostRedisplay();
		// timer 함수를 호출하여 일정주기마다 손가락 각도 변경
		glutTimerFunc(40, timer, value);
	}
	// 'move left arm'을 눌렀을 경우
	else if (value == 2) {
		// 왼팔을 올리도록 각도 변경
		if (moveTimer == 'u') {
			if (armAngle[0][0] > -150) {
				armAngle[0][0] = (armAngle[0][0] - 5) % 180;
				armAngle[0][1] = (armAngle[0][1] - 3) % 180;
			}
			// 이제 왼팔을 내리도록 설정
			else {
				moveTimer = 'd';
			}
			// 강제로 display event 발생
			glutPostRedisplay();
			// timer 함수를 호출하여 일정주기마다 손가락 각도 변경
			glutTimerFunc(40, timer, value);
		}
		// 왼팔을 내리도록 각도 변경
		else if (moveTimer == 'd') {
			if (armAngle[0][0] < -30) {
				armAngle[0][0] = (armAngle[0][0] + 5) % 180;
				armAngle[0][1] = (armAngle[0][1] + 3) % 180;
			}
			else {
				moveTimer = 's';
			}
			// 강제로 display event 발생
			glutPostRedisplay();
			// timer 함수를 호출하여 일정주기마다 손가락 각도 변경
			glutTimerFunc(40, timer, value);
		}
	}
	// 'move right arm'을 눌렀을 경우
	else if (value == 3) {
		// 오른팔을 올리도록 각도 변경
		if (moveTimer == 'u') {
			if (armAngle[1][0] < 150) {
				armAngle[1][0] = (armAngle[1][0] + 5) % 180;
				armAngle[1][1] = (armAngle[1][1] + 3) % 180;
			}
			// 이제 팔을 내리도록 설정
			else {
				moveTimer = 'd';
			}
			// 강제로 display event 발생
			glutPostRedisplay();
			// timer 함수를 호출하여 일정주기마다 손가락 각도 변경
			glutTimerFunc(40, timer, value);
		}
		// 오른팔을 내리도록 각도 변경
		else if (moveTimer == 'd') {
			if (armAngle[1][0] > 30) {
				armAngle[1][0] = (armAngle[1][0] - 5) % 180;
				armAngle[1][1] = (armAngle[1][1] - 3) % 180;
			}
			// 이제 팔을 움직이지 않도록 설정
			else {
				moveTimer = 's';
			}
			// 강제로 display event 발생
			glutPostRedisplay();
			// timer 함수를 호출하여 일정주기마다 손가락 각도 변경
			glutTimerFunc(40, timer, value);
		}
	}
	// 'move left leg'을 눌렀을 경우
	else if (value == 4) {
		// 왼쪽 다리를 올리도록 각도 변경
		if (moveTimer == 'u') {
			if (legAngle[0][0] > -80) {
				legAngle[0][0] = (legAngle[0][0] - 5) % 180;
				legAngle[0][1] = (legAngle[0][1] + 4) % 180;
			}
			// 이제 다리를 내리도록 설정
			else {
				moveTimer = 'd';
			}
			// 강제로 display event 발생
			glutPostRedisplay();
			// timer 함수를 호출하여 일정주기마다 손가락 각도 변경
			glutTimerFunc(40, timer, value);
		}
		// 오른 다리을 내리도록 각도 변경
		else if (moveTimer == 'd') {
			if (legAngle[0][0] < 0) {
				legAngle[0][0] = (legAngle[0][0] + 5) % 180;
				legAngle[0][1] = (legAngle[0][1] - 4) % 180;
			}
			// 이제 다리를 움직이지 않도록 설정
			else {
				moveTimer = 's';
			}
			// 강제로 display event 발생
			glutPostRedisplay();
			// timer 함수를 호출하여 일정주기마다 손가락 각도 변경
			glutTimerFunc(40, timer, value);
		}
	}
	// 'move right leg'을 눌렀을 경우
	else if (value == 5) {
		// 오른 다리을 올리도록 설정
		if (moveTimer == 'u') {
			if (legAngle[1][0] < 80) {
				legAngle[1][0] = (legAngle[1][0] + 5) % 180;
				legAngle[1][1] = (legAngle[1][1] - 4) % 180;
			}
			// 이제 다리를 내리도록 설정
			else {
				moveTimer = 'd';
			}
			// 강제로 display event 발생
			glutPostRedisplay();
			// timer 함수를 호출하여 일정주기마다 손가락 각도 변경
			glutTimerFunc(40, timer, value);
		}
		// 오른 다리를 내리도록 각도 변경
		else if (moveTimer == 'd') {
			if (legAngle[1][0] > 0) {
				legAngle[1][0] = (legAngle[1][0] - 5) % 180;
				legAngle[1][1] = (legAngle[1][1] + 4) % 180;
			}
			// 이제 다리를 움직이지 않도록 설정
			else {
				moveTimer = 's';
			}
			// 강제로 display event 발생
			glutPostRedisplay();
			// timer 함수를 호출하여 일정주기마다 손가락 각도 변경
			glutTimerFunc(40, timer, value);
		}
	}
}

// 선택한 main menu에 해당하는 기능을 수행하기 위한 작업을 하는 함수
void moveMenuCallback(int entryID) {
	// 'move head'메뉴를 선택
	if (entryID == 1) {
		// 머리를 움직이도록 변수 설정 및 timer 설정
		moveTimer = 'l';
		glutTimerFunc(0, timer, 1);
	}
	// 'move left arm'메뉴를 선택
	else if (entryID == 2) {
		// 왼팔을 움직이도록 변수 설정 및 timer 설정
		moveTimer = 'u';
		glutTimerFunc(0, timer, 2);
	}
	// 'move right arm'메뉴를 선택
	else if (entryID == 3) {
		// 오른팔을 움직이도록 변수 설정 및 timer 설정
		moveTimer = 'u';
		glutTimerFunc(0, timer, 3);
	}
	// 'move left leg'메뉴를 선택
	else if (entryID == 4) {
		// 왼쪽 다리를 움직이도록 변수 설정 및 timer 설정
		moveTimer = 'u';
		glutTimerFunc(0, timer, 4);
	}
	// 'move right leg'메뉴를 선택
	else if (entryID == 5) {
		// 오른 다리를 움직이도록 변수 설정 및 timer 설정
		moveTimer = 'u';
		glutTimerFunc(0, timer, 5);
	}
}

// keyboard event 발생 시, 실행되는 callback function
void keyboardCallback(unsigned char key, int x, int y) {
	switch (key) {
		// S키를 입력한 경우
	case 'S':
		// 더이상 손가락이 움직이지 않도록 설정
		moveTimer = 0;
		break;
		// R,r키를 입력한 경우
	case 'R':
	case 'r':
		// 달리는 모습으로 바꿀 수 있도록 변수값 설정
		isRun = 1;
		// 강제로 display event발생
		glutPostRedisplay();
		break;
		// i키를 입력한 경우
	case 'i':
		// 다시 초기자세로 돌아가도록 변수값 설정
		isRun = 0;
		// 강제로 display event발생
		glutPostRedisplay();
		break;
	}
}

// window 전반에 적용될 요소를 정의
void MyInit(void) {
	// window의 배경색을 검정색으로 설정
	glClearColor(0.0, 0.0, 0.0, 1.0);
	// 은면제거 활성화
	glEnable(GL_DEPTH_TEST);

	// moveMenuCallback 함수 등록 & 선택된 메뉴 아이디 값이 리턴
	GLint colorMenuID = glutCreateMenu(moveMenuCallback);
	// main menu로 'move head'를 추가하고 메뉴 아이디를 1로 설정
	glutAddMenuEntry("move head", 1);
	// main menu로 'move left arm'를 추가하고 메뉴 아이디를 2로 설정
	glutAddMenuEntry("move left arm", 2);
	// main menu로 'move right arm'를 추가하고 메뉴 아이디를 3로 설정
	glutAddMenuEntry("move right arm", 3);
	// main menu로 'move left leg'를 추가하고 메뉴 아이디를 4로 설정
	glutAddMenuEntry("move left leg", 4);
	// main menu로 'move right leg'를 추가하고 메뉴 아이디를 5로 설정
	glutAddMenuEntry("move right leg", 5);

	// 오늘쪽 마우스 버튼에 main menu 할당
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
	// OS와 Session 연결 / GLUT library 초기화
	glutInit(&argc, argv);
	// display mode를 RGB로 설정 & 더블 버퍼링 & 은면제거을 위한 mode 설정
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// 새로 생성된 window의 크기를 800 * 600로 설정
	glutInitWindowSize(1200, 600);
	// window의 위치를 왼쪽 상단으로 설정
	glutInitWindowPosition(100, 100);
	// window의 타이틀을 '전신 Can Robot 모델링'으로 설정
	glutCreateWindow("전신 Can Robot 모델링");

	// 색상과 변환과 관련된 함수 호출
	MyInit();
	// 조명과 관련된 값들을 조정하는 함수 호출
	lightInti();
	// display callback function 등록
	glutDisplayFunc(displayCallback);
	// reshape callback function 등록
	glutReshapeFunc(reshapeCallback);
	// keyboard callback function 등록
	glutKeyboardFunc(keyboardCallback);

	// callback 함수로 등록한 event가 발생하는지 지속적으로 감지
	glutMainLoop();

	return 0;
}