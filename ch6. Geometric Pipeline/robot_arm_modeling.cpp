/***************************************************************************/
/*                  HW#4-1 : 로봇 손-팔 모델링                             */
/* 이름 : 유현진                                 날짜 : 2021년 10월 26일   */
/*                                                                         */
/* 문제 정의 : 코드6-7을 참고하여 손가락 3개를 가진 Robot Arm 제작         */
/*                                                                         */
/* 기능                                                                    */
/*   1. <1 키를 누르면> 첫번째 손가락을 접었다 펼쳤다 반복                 */
/*   2. <2 키를 누르면> 두번째 손가락을 접었다 펼쳤다 반복                 */
/*   3. <3 키를 누르면> 세번째 손가락을 접었다 펼쳤다 반복                 */
/*   4. <4 키를 누르면> 모든 손가락이 접었다 펼쳤다 반복                   */
/*   5. <S 키를 누르면> 움직이던 손가락이 움직임을 멈춤                    */
/* 추가 기능                                                               */
/*   1. <마우스 왼쪽 버튼을 클릭하면> 어깨, 팔꿈치 및 모든 손가락을        */ 
/*      움직여서 Robot Arm이 특정 물건을 잡는 것처럼 회전                  */
/*   2. <마우스 오른쪽 버튼을 클릭하면> 팔꿈치 및 모든 손가락을            */
/*      움직여서 Robot Arm의 원래 위치와 자세로 되돌아가도록 함            */
/***************************************************************************/

#include <gl/glut.h>
#include<stdlib.h>

// 어깨, 팔꿈치 각도 변수
static int shoulder = 0, elbow = 0;
// 각 손가락 관절 각도 변수
static int fingerAngle[3][2] = {
	30, 0,
	0, 0,
	-30, 0
};
// 어떤 입력이 들어왔는지에 따라 그에 맞는 행동을 수행하도록 조절하는 변수
static int moveTimer = 0;

void displayCallback() {
	// buffer에 들어있는 그림 초기화
	glClear(GL_COLOR_BUFFER_BIT);
	// 지금부터 그려질 그림들의 색을 흰색으로 설정
	glColor3f(1.0, 1.0, 1.0);

	// 어깨 기준 모델 좌표계 구성
	glPushMatrix();
		// 원점을 기준으로 회전
		glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0); 
		// Pivot으로 지정할 위치를 원점으로 이동
		glTranslatef(1.0, 0.0, 0.0);
		// wire cube을 scale을 적용하여 그림
		glPushMatrix(); 
			glScalef(2.0, 0.7, 0.7);
			glutWireCube(1.0);
		glPopMatrix();

		// 팔꿈치 기준 모델 좌표계 구성
		glPushMatrix(); 
			// pivot을 원하는 위치로 이동
			glTranslatef(1.0, 0.0, 0.0); 
			// 원점을 기준으로 회전
			glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0); 
			// Pivot으로 지정할 위치를 원점으로 이동
			glTranslatef(1.0, 0.0, 0.0); 
			// wire cube을 scale을 적용하여 그림
			glPushMatrix();
				glScalef(2.0, 0.7, 0.7);
				glutWireCube(1.0);
			glPopMatrix();

			// 3개의 손가락을 구성
			for (int i = 0; i < 3; i++) {
				// finger i번째의 first 뼈대 모델 좌표계 구성
				glPushMatrix();
					// pivot을 원하는 위치로 이동
					glTranslatef(1.0, 0.0, 0.05);
					// 원점을 기준으로 회전
					glRotatef((GLfloat)fingerAngle[i][0], 0.0, 0.0, 1.0);
					// Pivot으로 지정할 위치를 원점으로 이동
					glTranslatef(0.35, 0.0, 0.0);
					// wire cube를 scale을 적용하여 그림
					glPushMatrix();
						glScalef(0.7, 0.2, 0.2);
						glutWireCube(1.0);
					glPopMatrix();

					// finger i번째의 second 뼈대 모델 좌표계 구성
					glPushMatrix();
						// pivot을 원하는 위치로 이동
						glTranslatef(0.35, 0.0, 0.0);
						// 원점을 기준으로 회전
						glRotatef((GLfloat)fingerAngle[i][1], 0.0, 0.0, 1.0);
						// Pivot으로 지정할 위치를 원점으로 이동
						glTranslatef(0.35, 0.0, 0.0);
						// wire cube를 scale을 적용하여 그림
						glPushMatrix();
							glScalef(0.7, 0.2, 0.2);
							glutWireCube(1.0);
						glPopMatrix();

						// finger i번째의 second 뼈대 모델 좌표계 구성
						glPushMatrix(); 
							// pivot을 원하는 위치로 이동
							glTranslatef(0.35, 0.0, 0.0);
							// 원점을 기준으로 회전
							glRotatef((GLfloat)fingerAngle[i][1], 0.0, 0.0, 1.0); 
							// Pivot으로 지정할 위치를 원점으로 이동
							glTranslatef(0.35, 0.0, 0.0);
							// wire cube를 scale을 적용하여 그림
							glPushMatrix();
								glScalef(0.7, 0.2, 0.2);
								glutWireCube(1.0);
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			}
		glPopMatrix();
	glPopMatrix();

	// 그림이 그려질 buffer change (front buffer를 back buffer로 변환)
	glutSwapBuffers();
}

// window 전반에 적용될 요소를 정의
void MyInit(void) {
	// window의 배경색을 검정색으로 설정
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_FLAT);
}

// reshape event 발생 시, 실행되는 callback function
void reshapeCallback(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// 투영 행렬 스택 선택
	glMatrixMode(GL_PROJECTION);
	// CTM을 항등행렬로 변경
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	// 모델뷰 행렬 스택 선택
	glMatrixMode(GL_MODELVIEW);
	// CTM을 항등행렬로 변경
	glLoadIdentity();
	// 현재 좌표에 아래 translate값을 적용하여 이동
	glTranslatef(0.0, 0.0, -5.0);
}

// 일정시간마다 손가락을 움직여 줄 timer callback 함수
void timer(int value) {
	// 더이상 손가락이 움직이지 않도록 timer 호출X
	if (moveTimer == 0) {

	}
	// 1번, 2번, 3번을 클릭했을 때
	else if (moveTimer == 1) {
		// value+1번째 손가락을 접도록 설정
		if (value != 3 && fingerAngle[value][1] < 100) {
			fingerAngle[value][1] = (fingerAngle[value][1] + 5) % 180;
		}
		// 모든 손가락을 접도록 설정
		else if (value == 3 && fingerAngle[0][1] < 100) {
			for (int i = 0; i < 3; i++) {
				fingerAngle[i][1] = (fingerAngle[i][1] + 5) % 180;
			}
		}
		// 손가락을 다 접었다면
		else {
			// 손가락을 펼칠 수 있도록 moveTimer 설정
			moveTimer = 2;
		}
		// 강제로 display event를 발생
		glutPostRedisplay();
		// timer 함수를 호출하여 일정주기마다 손가락 각도 변경
		glutTimerFunc(40, timer, value);
	}
	// 손가락을 펴야되는 경우
	else if (moveTimer == 2 ) {
		// value+1번째 손가락을 펴도록 설정
		if (value != 3 && fingerAngle[value][1] > 0) {
			fingerAngle[value][1] = (fingerAngle[value][1] - 5) % 180;
			// 강제로 display event 발생
			glutPostRedisplay();
			// timer 함수를 호출하여 일정주기마다 손가락 각도 변경
			glutTimerFunc(40, timer, value);
		}
		// 모든 손가락을 펴도록 설정
		else if (value == 3 && fingerAngle[0][1] > 0) {
			for (int i = 0; i < 3; i++) {
				fingerAngle[i][1] = (fingerAngle[i][1] - 5) % 180;
			}
			// 강제로 display event 발생
			glutPostRedisplay();
			// timer 함수를 호출하여 일정주기마다 손가락 각도 변경
			glutTimerFunc(40, timer, value);
		}
		// 손가락을 다 폈다면
		else {
			// 다시 손가락을 접도록 변수 설정 및 timer 설정
			moveTimer = 1;
			glutTimerFunc(40, timer, value);
		}
	}
	//마우스 왼쪽 클릭했을 때
	if (moveTimer == 3) {
		// 어깨 각도를 어느정도 꺽었다면
		if (shoulder > 30) {
			// 더이상 움직이지 않도록 설정
			moveTimer = 0;
		}
		// 로봇 팔이 아직 물건을 잡는 것처럼 움직이기 못했다면
		else {
			// 어깨와 팔꿈치의 각도를 변경
			shoulder = (shoulder + 2) % 180;
			elbow = (elbow - 7) % 180;

			// 모든 손가락의 각도를 물건을 잡는 것처럼 변경
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 3; j++) {
					fingerAngle[j][i] = (fingerAngle[j][i] - 5) % 180;
				}
			}

			// 강제로 display event를 발생
			glutPostRedisplay();
			// timer 함수를 호출하여 일정주기마다 로봇 팔 각도 변경
			glutTimerFunc(40, timer, 1);
		}
	}
	//마우스 오른쪽 클릭했을 때
	if (moveTimer == 4) {
		if (shoulder == 0) {
			moveTimer = 0;
		}
		// 로봇 팔이 아직 원래 자세로 못돌아왔다면
		else {
			// 어깨와 팔꿈치의 각도를 변경
			shoulder = (shoulder - 2) % 180;
			elbow = (elbow + 7) % 180;

			// 모든 손가락의 각도를 물건을 잡는 것처럼 변경
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 3; j++) {
					fingerAngle[j][i] = (fingerAngle[j][i] + 5) % 180;
				}
			}

			// 강제로 display event를 발생
			glutPostRedisplay();
			// timer 함수를 호출하여 일정주기마다 로봇 팔 각도 변경
			glutTimerFunc(40, timer, 1);
		}
	}
}

// mouse event 발생 시, 실행되는 callback function
void mouseCallback(GLint Button, GLint State, GLint X, GLint Y) {
	// 왼쪽 마우스가 클릭되면
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		// 물건을 잡는 것처럼 움직이도록 moveTimer 설정 및 timer 실행
		moveTimer = 3;
		glutTimerFunc(0, timer, moveTimer);
	}
	// 오른쪽 마우스가 클릭되면
	else if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN) {
		// 로봇 팔이 원래 자세로 돌아가도록 moveTimer 설정 및 timer 실행
		moveTimer = 4;
		glutTimerFunc(0, timer, moveTimer);
	}
}

// keyboard event 발생 시, 실행되는 callback function
void keyboardCallback(unsigned char key, int x, int y) {
	switch (key) {
		// 1이 입력되었다면
		case '1':
			// 첫번째 손가락을 접었다 피도록 변수 설정 및 timer 설정
			moveTimer = 1;
			glutTimerFunc(0, timer, 0);
			break;
		// 2이 입력되었다면
		case '2':
			// 두번째 손가락을 접었다 피도록 변수 설정 및 timer 설정
			moveTimer = 1;
			glutTimerFunc(0, timer, 1);
			break;
		// 3이 입력되었다면
		case '3':
			// 세번째 손가락을 접었다 피도록 변수 설정 및 timer 설정
			moveTimer = 1;
			glutTimerFunc(0, timer, 2);
			break;
		// 4가 입력되었다면
		case '4':
			// 모든 손가락을 접었다 피도록 변수 설정 및 timer 설정
			moveTimer = 1;
			glutTimerFunc(0, timer, 3);
			break;
		// S가 입려되었다면
		case 'S':
			// 더이상 손가락이 움직이지 않도록 설정
			moveTimer = 0;
			break;
		default:
			break;
		}
}

int main(int argc, char** argv) {
	// OS와 Session 연결 / GLUT library 초기화
	glutInit(&argc, argv);
	// display mode를 RGB로 설정 & 더블 버퍼링을 위한 mode 설정
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// 새로 생성된 window의 크기를 800 * 600로 설정
	glutInitWindowSize(1500, 600);
	// window의 위치를 왼쪽 상단으로 설정
	glutInitWindowPosition(100, 100);
	// window의 타이틀을 'robot arm'으로 설정
	glutCreateWindow("robot arm");

	// 색상과 변환과 관련된 함수 호출
	MyInit();
	// display callback function 등록
	glutDisplayFunc(displayCallback);
	// reshape callback function 등록
	glutReshapeFunc(reshapeCallback);
	// keyboard callback function 등록
	glutKeyboardFunc(keyboardCallback);
	//glutTimerFunc(40, MyTimer, 1);
	glutMouseFunc(mouseCallback);

	// callback 함수로 등록한 event가 발생하는지 지속적으로 감지
	glutMainLoop();

	return 0;
}