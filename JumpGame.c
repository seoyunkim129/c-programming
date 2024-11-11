//1.헤더 파일
#include<stdio.h>
#include<Windows.h> //윈도우에 관련된 정의, 함수, 변수들이 모두 저장되어 있음
#include<conio.h> //콘솔 입출력 함수 제공하는 헤더.예로, getch() 함수를 사용하여 키 입력을 받을 수 있습니다
#include<time.h>//날짜와 시간과 관련된 함수 제공
#include<stdbool.h> //선언해야 C에서 bool 활용 가능
#include<stdlib.h> //C함수들 모아놓은 헤더파일

//2.매크로 상수(나중에 상수 값을 변경해야 할 때 코드의 여러 부분을 일일이 수정하지 않고 한 곳에서 변경 가능)
#define SOM_BOTTOM_Y 12//som이 바닥에 위치할 y 좌표(화면 상단에 위치한 것부터 아래로 숫자가 증가)
#define TREE_BOTTOM_Y 20//Tree가 화면에서 바닥에 위치할 y 좌표(화면 상단에 위치한 것부터 아래로 숫자가 증가)
#define TREE_BOTTOM_X 50//Tree가 화면에서 우측에 위치할 x 좌표(화면 좌측에서 우측으로 숫자가 증가)
#define HEART_BOTTOM_X 50//Heart가 화면에서 우측에 위치할 x 좌표(화면 좌측에서 우측으로 숫자가 증가)
#define HEART_BOTTOM_Y 17//Heart가 화면에서 바닥에 위치할 y 좌표(화면 상단에 위치한 것부터 아래로 숫자가 증가)


//3.SetConsoleView() : 콘솔 창의 크기와 제목을 지정
void SetConsoleView()
{
    system("mode con:cols=140 lines=25");//콘솔 창의 가로(col) 크기를 140으로, 세로(lines) 크기를 25로 설정
}


//4.ColorSet 함수: 콘솔 창에서 텍스트와 배경 색상을 설정하기 위해 사용. 함수의 인자로 backColor와 textColor를 전달받음
void ColorSet(int backColor, int textColor)//backColor: 설정할 배경 색상(0~15 값 가짐),textColor: 설정할 텍스트 색상(0~15 값 가짐)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, (backColor << 4) + textColor);//배경 색상과 텍스트 색상을 결합하여 색상 속성 값을 생성
}


//5.GotoXY(int x, int y):커서의 위치를 x, y로 이동
void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;//Pos 구조체의 X 멤버 변수에는 2 * x 값을 대입(2 * x는 콘솔 폰트의 가로 폭이 세로 폭의 두 배인 관계로 인해 x 값에 2를 곱해준 것)
    Pos.Y = y;//Pos 구조체의 Y 멤버 변수에는 세로 방향 좌표 값인 y를 대입
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


//6.GetKeyDown() : 키보드의 입력을 받고, 입력된 키의 값을 반환
int GetKeyDown()
{
    if (_kbhit() != 0)//키 입력 여부를 판단
    {
        return _getch(); //키 입력이 감지된 경우 _getch() 함수를 호출
    }
    return 0;//키 입력이 없을 경우 0을 반환
}


//7.Drawsom(int somY):솜을 그리는 함수
void Drawsom(int somY)//somY: 솜의 세로 위치를 나타내는 변수
{
    GotoXY(0, somY);//커서 위치를(0, somY)로 이동시켜 그림이 출력될 위치를 설정
    static bool legFlag = TRUE;//정적변수 legFlag를 선언하고 true로 초기화
    printf("        * *     \n");
    printf("     **     **   \n");
    printf("    **        **  \n");
    printf("  *    O  O     *\n");
    printf("  **    ~    **\n");
    printf("     *   *   *   \n");
    printf("      **   **     \n");
    printf("    *      *    \n");
    printf("   *        *   \n");
    printf("  *          *  \n");
    printf("   **********   \n");
    if (legFlag)//legFlag 변수의 값에 따라 다리 부분을 출력
    {
        printf("     $    $$$    \n");
        printf("     $$          ");//true인 경우 다리를 나타내는 줄을 출력
        legFlag = FALSE;// false인 경우 공백을 출력->다리가 번갈아가며 움직이는 효과를 줌
    }
    else
    {
        printf("     $$$  $     \n");
        printf("          $$    ");
        legFlag = TRUE;
    }
}
//(정적 변수를 사용하는 이유: legFlag 변수가 Drawsom() 함수 내에서만 유효하면서 함수 호출 간에도 이전 값을 유지하기 위해서


//8.DrawTree(int treeX) : 나무를 그리는 함수
void DrawTree(int treeX)//treeX: 나무의 가로 위치를 나타내는 변수
{
    GotoXY(treeX, TREE_BOTTOM_Y);//커서의 위치를 treeX와 TREE_BOTTOM_Y로 이동시켜 그림이 출력될 위치를 설정
    printf("   $$");
    GotoXY(treeX, TREE_BOTTOM_Y + 1);
    printf("$  $");
    GotoXY(treeX, TREE_BOTTOM_Y + 2);
    printf(" $ $ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 3);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 4);
    printf(" $$ ");
}


//9.DrawHeart 함수: 콘솔 창에 하트 모양을 그리는 함수.
void DrawHeart(int HeartX)////HeartX: 하트의 가로 위치를 나타내는 변수
{
    GotoXY(HeartX, HEART_BOTTOM_Y);//커서의 위치를 HeartX와  HEART_BOTTOM_Y로 이동시켜 그림이 출력될 위치를 설정
    printf("  XXX        XXXX");
    GotoXY(HeartX, HEART_BOTTOM_Y + 1);
    printf("XXXXXXX    XXXXXXXX");
    GotoXY(HeartX, HEART_BOTTOM_Y + 2);
    printf("XXXXXXXXXXXXXXXXXXX");
    GotoXY(HeartX, HEART_BOTTOM_Y + 3);
    printf("  XXXXXXXXXXXXXXX");
    GotoXY(HeartX, HEART_BOTTOM_Y + 4);
    printf("    XXXXXXXXXXX");
    GotoXY(HeartX, HEART_BOTTOM_Y + 5);
    printf("      XXXXXXX");
    GotoXY(HeartX, HEART_BOTTOM_Y + 6);
    printf("        XXX");
    GotoXY(HeartX, HEART_BOTTOM_Y + 7);
    printf("         X");
}


//10.DrawGameOver(const int score) : 충돌 했을때 게임오버 그리는 함수,(const는 변수를 상수로 선언하는 키워드)
void DrawGameOver(const int score)
{
    system("cls");//화면을 지움
    int x = 27; //게임 오버 화면을 출력할 좌표를 설정
    int y = 8;
    GotoXY(x, y);
    printf("===========================");
    GotoXY(x, y + 1);
    printf("======G A M E O V E R======");
    GotoXY(x, y + 2);
    printf("===========================");
    GotoXY(x, y + 5);
    printf("SCORE : %d", score);//점수를 출력

    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");
}


//11.충돌여부 확인하는 함수(충돌했으면 true, 아니면 false)
bool isCollision(const int treeX, const int somY)
{
    GotoXY(0, 0);//커서의 위치를 이동
    if (treeX <= 8 && treeX >= 4//트리의 X가 솜과 가로로 겹치는 범위에 있는지
        && somY > 8)//솜의 높이가 충분하지 않을 때
    {
        return TRUE;//충돌한다고 판단하여 true를 반환
    }
    return FALSE;
}


//12.isHeartCollision 함수: 솜이 하트를 먹었는지 확인하는 함수
bool isHeartCollision(const int HeartX, const int somY)
{
    GotoXY(0, 0);
    if (HeartX <= 8 && HeartX >= 4 && somY > 8)//하트가 솜과 가로로 겹치는 범위에 있는지
    {
        return TRUE;//하트 먹음
    }
    return FALSE;
}


//13.시작 화면(오프닝이벤트,사용자가 Enter 키를 누를 때까지 기다린 후, 게임을 시작하도록 제어)
int openingEvent(void) {
    bool tik = TRUE;//tik:깜빡이는 별을 표시하기 위한 용도로 사용
    srand((unsigned int)time(NULL));//난수 rand 함수가 다양한 시간마다 다른 값을 반환
    while (1) {
        if (tik) {//tik 값이 TRUE이므로 깜빡이는 별을 출력
            GotoXY((rand() % 300) / 2, rand() % 40);
            printf("★");
            Sleep(100);//100밀리초 동안 딜레이를 주어 깜빡임 효과 생성
            tik = FALSE;
        }
        else {
            GotoXY(27, 12);
            printf("Play The Game? Press Enter Key! \n\n");
            printf("\t\t\t\t\t\t\tJump : Press 'Z' key");
            if (GetKeyDown() == 13) { break; }//사용자가 Enter 키를 누르면 루프를 탈출하여 게임을 시작
            tik = TRUE;
        }
    }
}


//14.ColorKinds라는 열거형(enum)을 정의:배경색을 나타내는 상수들의 집합
typedef enum ColorKinds
{
    black,
    blue,
    green,
    skyBlue,
    red,
    pink,
    Orange,
    white,
    lightBlue,
    brightGreen,
    sky,
    brightRed,
    brightpink,
    brightyellow,
    brightwhite,
}ColorKinds;


//15.main()함수
int main()
{
    SetConsoleView();//콘솔창 크기 설정
    ColorKinds colorkinds; //배경색 나열
    ColorSet(black, brightwhite); //오프닝 이벤트 화면의 배경색,글자색 설정
    openingEvent();
    ColorSet(white, red);//게임 화면의 배경색,글자색 설정


    while (TRUE)        //게임 루프
    {

        //게임 시작시 초기화
        bool isJumping = FALSE;//점프 상태: 솜이 점프하지 않은 상태이므로 false로 초기화
        bool isBottom = TRUE;// 바닥 상태: 솜이 바닥에 있으므로 true로 초기화
        bool isBarricate = TRUE;//장애물 상태: isBarricate 변수는 현재 장애물이 나무인지 하트인지를 나타내는 상태 변수
        const int gravity = 3;// 중력 값 : 중력은 솜이 땅으로 떨어지는 속도를 결정하는데, 이 값은 게임의 난이도나 원하는 동작에 따라 조정할 수 있습니다. 초기값으로 3을 설정하여 중력이 일반적인 속도로 적용되도록 함.

        int somY = SOM_BOTTOM_Y;//게임이 시작될 때는 솜이 바닥에 서 있는 상태이므로 해당 위치로 초기화
        int treeX = TREE_BOTTOM_X;//게임이 시작될 때는 나무가 오른쪽 끝에서 출발하므로 해당 위치로 초기화
        int HeartX = HEART_BOTTOM_X;//Tree랑 동일원리

        int score = 0; //게임 점수
        int time = 0;//경과 시간
        clock_t start, curr;    //점수 변수 초기화(clock_t는 C 언어의 <time.h> 헤더 파일에 정의된 데이터 타입)
        start = clock();        //시작시간 초기화

        while (TRUE)    //한 판에 대한 루프
        {
            //1)충돌체크
            printf("treeX : %d, somY : %d", treeX, somY);
            if (isCollision(treeX, somY))//나무와 솜 충돌하면 게임 루프를 빠져나옴
                break;
            if (isHeartCollision(HeartX, somY))//솜이 하트를 먹은 경우 score를 5 증가
            {
                score += 5;
            }

            //2)점프 -> 키 입력: 키보드의 'z' 키가 눌리면, 공룡이 점프.
            if (GetKeyDown() == 'z' && isBottom)//z키가 눌리고 바닥일 때-> 점프
            {
                printf("\a");//점프할 때 소리남
                isJumping = TRUE;//점프 중임을 나타내는 상태 변수들을 업데이트(초기화때와 반대)
                isBottom = FALSE;
            }

            //3)솜 위치 업데이트(점프 중인지 아닌지) 
            if (isJumping)
            {
                somY -= gravity;
            }//점프중:gravity 값만큼 Y를 감소
            else
            {
                somY += gravity;
            }//점프x:  gravity 값만큼 솜의 Y 좌표를 증가(중력에 따라 내려온다..)


            //Y가 계속해서 증가하는걸 막기위해 바닥을 지정.
            //( 솜의 Y 좌표가 솜의 최대 높이인 SOM_BOTTOM_Y(12)보다 크거나 같으면 솜은 바닥에 도달한 것으로 판단하고)
            if (somY >= SOM_BOTTOM_Y)
            {
                somY = SOM_BOTTOM_Y;
                isBottom = TRUE;
            }

            //4)나무와 하트의 위치를 왼쪽으로 이동시킴
            if (isBarricate)//나무가 있는 경우
            {
                treeX -= 2;
            }
            else//하트가 있는 경우
            {
                HeartX -= 2;
            }
            //4-2)장애물들이 왼쪽 화면을 벗어나면 다시 초기 위치에서 등장하게 되며, 나무와 하트가 번갈아가면서 나타나는 효과
            if (treeX <= 0)//나무가 왼쪽 화면을 벗어남
            {
                treeX = TREE_BOTTOM_X;//나무의 X 좌표를 초기 위치로 되돌리고
                isBarricate = FALSE;//FALSE로 설정하여 하트가 나타내도록 설정
            }
            if (HeartX <= 5)//하트가 왼쪽 화면을 벗어났을 때
            {
                HeartX = HEART_BOTTOM_X;//하트의 X 좌표를 초기 위치로 되돌리고
                isBarricate = TRUE;//TRUE로 설정하여 나무를 나타내도록 설정
            }

            //5)솜의 점프 동작을 제어,솜그리기: 최대 점프 시 (Y 좌표(somY)가 3보다 작거나 같아지는 때 )..3)과 관련.
            if (somY <= 3)
            {
                isJumping = FALSE;//점프 동작이 종료
            }
            Drawsom(somY);

            //6)나무와 하트 그리기...4)와 관련
            if (isBarricate)
            {
                DrawTree(treeX);
            }
            else
            {
                DrawHeart(HeartX);
            }

            //7)게임의 시간과 점수를 관리하고, 화면에 출력
            curr = clock();            //현재시간 받아오기
            if (((curr - start) / CLOCKS_PER_SEC) >= 1)    // 1초가 넘었을때 (현재 시간과 시작 시간의 차이를 초 단위로 변환하여 1초 이상인지 확인)
            {
                time++;    //시간 1초씩 UP
                score++;    //스코어 UP( 1초마다 스코어를 증가)
                start = clock();    //시작시간 초기화
            }
            Sleep(60);
            system("cls");


            GotoXY(22, 0);
            printf("Time : %d \t", time);
            printf("Score : %d\t", score);
        }

        //게임 오버 메뉴: 한 판의 게임이 끝나면, 게임 오버 메뉴를 출력하고, 다시 무한 루프의 처음으로 돌아가서 게임을 다시 시작
        DrawGameOver(score);
    }
    return 0;
}