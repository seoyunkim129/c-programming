//1.��� ����
#include<stdio.h>
#include<Windows.h> //�����쿡 ���õ� ����, �Լ�, �������� ��� ����Ǿ� ����
#include<conio.h> //�ܼ� ����� �Լ� �����ϴ� ���.����, getch() �Լ��� ����Ͽ� Ű �Է��� ���� �� �ֽ��ϴ�
#include<time.h>//��¥�� �ð��� ���õ� �Լ� ����
#include<stdbool.h> //�����ؾ� C���� bool Ȱ�� ����
#include<stdlib.h> //C�Լ��� ��Ƴ��� �������

//2.��ũ�� ���(���߿� ��� ���� �����ؾ� �� �� �ڵ��� ���� �κ��� ������ �������� �ʰ� �� ������ ���� ����)
#define SOM_BOTTOM_Y 12//som�� �ٴڿ� ��ġ�� y ��ǥ(ȭ�� ��ܿ� ��ġ�� �ͺ��� �Ʒ��� ���ڰ� ����)
#define TREE_BOTTOM_Y 20//Tree�� ȭ�鿡�� �ٴڿ� ��ġ�� y ��ǥ(ȭ�� ��ܿ� ��ġ�� �ͺ��� �Ʒ��� ���ڰ� ����)
#define TREE_BOTTOM_X 50//Tree�� ȭ�鿡�� ������ ��ġ�� x ��ǥ(ȭ�� �������� �������� ���ڰ� ����)
#define HEART_BOTTOM_X 50//Heart�� ȭ�鿡�� ������ ��ġ�� x ��ǥ(ȭ�� �������� �������� ���ڰ� ����)
#define HEART_BOTTOM_Y 17//Heart�� ȭ�鿡�� �ٴڿ� ��ġ�� y ��ǥ(ȭ�� ��ܿ� ��ġ�� �ͺ��� �Ʒ��� ���ڰ� ����)


//3.SetConsoleView() : �ܼ� â�� ũ��� ������ ����
void SetConsoleView()
{
    system("mode con:cols=140 lines=25");//�ܼ� â�� ����(col) ũ�⸦ 140����, ����(lines) ũ�⸦ 25�� ����
}


//4.ColorSet �Լ�: �ܼ� â���� �ؽ�Ʈ�� ��� ������ �����ϱ� ���� ���. �Լ��� ���ڷ� backColor�� textColor�� ���޹���
void ColorSet(int backColor, int textColor)//backColor: ������ ��� ����(0~15 �� ����),textColor: ������ �ؽ�Ʈ ����(0~15 �� ����)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, (backColor << 4) + textColor);//��� ����� �ؽ�Ʈ ������ �����Ͽ� ���� �Ӽ� ���� ����
}


//5.GotoXY(int x, int y):Ŀ���� ��ġ�� x, y�� �̵�
void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;//Pos ����ü�� X ��� �������� 2 * x ���� ����(2 * x�� �ܼ� ��Ʈ�� ���� ���� ���� ���� �� ���� ����� ���� x ���� 2�� ������ ��)
    Pos.Y = y;//Pos ����ü�� Y ��� �������� ���� ���� ��ǥ ���� y�� ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


//6.GetKeyDown() : Ű������ �Է��� �ް�, �Էµ� Ű�� ���� ��ȯ
int GetKeyDown()
{
    if (_kbhit() != 0)//Ű �Է� ���θ� �Ǵ�
    {
        return _getch(); //Ű �Է��� ������ ��� _getch() �Լ��� ȣ��
    }
    return 0;//Ű �Է��� ���� ��� 0�� ��ȯ
}


//7.Drawsom(int somY):���� �׸��� �Լ�
void Drawsom(int somY)//somY: ���� ���� ��ġ�� ��Ÿ���� ����
{
    GotoXY(0, somY);//Ŀ�� ��ġ��(0, somY)�� �̵����� �׸��� ��µ� ��ġ�� ����
    static bool legFlag = TRUE;//�������� legFlag�� �����ϰ� true�� �ʱ�ȭ
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
    if (legFlag)//legFlag ������ ���� ���� �ٸ� �κ��� ���
    {
        printf("     $    $$$    \n");
        printf("     $$          ");//true�� ��� �ٸ��� ��Ÿ���� ���� ���
        legFlag = FALSE;// false�� ��� ������ ���->�ٸ��� �����ư��� �����̴� ȿ���� ��
    }
    else
    {
        printf("     $$$  $     \n");
        printf("          $$    ");
        legFlag = TRUE;
    }
}
//(���� ������ ����ϴ� ����: legFlag ������ Drawsom() �Լ� �������� ��ȿ�ϸ鼭 �Լ� ȣ�� ������ ���� ���� �����ϱ� ���ؼ�


//8.DrawTree(int treeX) : ������ �׸��� �Լ�
void DrawTree(int treeX)//treeX: ������ ���� ��ġ�� ��Ÿ���� ����
{
    GotoXY(treeX, TREE_BOTTOM_Y);//Ŀ���� ��ġ�� treeX�� TREE_BOTTOM_Y�� �̵����� �׸��� ��µ� ��ġ�� ����
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


//9.DrawHeart �Լ�: �ܼ� â�� ��Ʈ ����� �׸��� �Լ�.
void DrawHeart(int HeartX)////HeartX: ��Ʈ�� ���� ��ġ�� ��Ÿ���� ����
{
    GotoXY(HeartX, HEART_BOTTOM_Y);//Ŀ���� ��ġ�� HeartX��  HEART_BOTTOM_Y�� �̵����� �׸��� ��µ� ��ġ�� ����
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


//10.DrawGameOver(const int score) : �浹 ������ ���ӿ��� �׸��� �Լ�,(const�� ������ ����� �����ϴ� Ű����)
void DrawGameOver(const int score)
{
    system("cls");//ȭ���� ����
    int x = 27; //���� ���� ȭ���� ����� ��ǥ�� ����
    int y = 8;
    GotoXY(x, y);
    printf("===========================");
    GotoXY(x, y + 1);
    printf("======G A M E O V E R======");
    GotoXY(x, y + 2);
    printf("===========================");
    GotoXY(x, y + 5);
    printf("SCORE : %d", score);//������ ���

    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");
}


//11.�浹���� Ȯ���ϴ� �Լ�(�浹������ true, �ƴϸ� false)
bool isCollision(const int treeX, const int somY)
{
    GotoXY(0, 0);//Ŀ���� ��ġ�� �̵�
    if (treeX <= 8 && treeX >= 4//Ʈ���� X�� �ذ� ���η� ��ġ�� ������ �ִ���
        && somY > 8)//���� ���̰� ������� ���� ��
    {
        return TRUE;//�浹�Ѵٰ� �Ǵ��Ͽ� true�� ��ȯ
    }
    return FALSE;
}


//12.isHeartCollision �Լ�: ���� ��Ʈ�� �Ծ����� Ȯ���ϴ� �Լ�
bool isHeartCollision(const int HeartX, const int somY)
{
    GotoXY(0, 0);
    if (HeartX <= 8 && HeartX >= 4 && somY > 8)//��Ʈ�� �ذ� ���η� ��ġ�� ������ �ִ���
    {
        return TRUE;//��Ʈ ����
    }
    return FALSE;
}


//13.���� ȭ��(�������̺�Ʈ,����ڰ� Enter Ű�� ���� ������ ��ٸ� ��, ������ �����ϵ��� ����)
int openingEvent(void) {
    bool tik = TRUE;//tik:�����̴� ���� ǥ���ϱ� ���� �뵵�� ���
    srand((unsigned int)time(NULL));//���� rand �Լ��� �پ��� �ð����� �ٸ� ���� ��ȯ
    while (1) {
        if (tik) {//tik ���� TRUE�̹Ƿ� �����̴� ���� ���
            GotoXY((rand() % 300) / 2, rand() % 40);
            printf("��");
            Sleep(100);//100�и��� ���� �����̸� �־� ������ ȿ�� ����
            tik = FALSE;
        }
        else {
            GotoXY(27, 12);
            printf("Play The Game? Press Enter Key! \n\n");
            printf("\t\t\t\t\t\t\tJump : Press 'Z' key");
            if (GetKeyDown() == 13) { break; }//����ڰ� Enter Ű�� ������ ������ Ż���Ͽ� ������ ����
            tik = TRUE;
        }
    }
}


//14.ColorKinds��� ������(enum)�� ����:������ ��Ÿ���� ������� ����
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


//15.main()�Լ�
int main()
{
    SetConsoleView();//�ܼ�â ũ�� ����
    ColorKinds colorkinds; //���� ����
    ColorSet(black, brightwhite); //������ �̺�Ʈ ȭ���� ����,���ڻ� ����
    openingEvent();
    ColorSet(white, red);//���� ȭ���� ����,���ڻ� ����


    while (TRUE)        //���� ����
    {

        //���� ���۽� �ʱ�ȭ
        bool isJumping = FALSE;//���� ����: ���� �������� ���� �����̹Ƿ� false�� �ʱ�ȭ
        bool isBottom = TRUE;// �ٴ� ����: ���� �ٴڿ� �����Ƿ� true�� �ʱ�ȭ
        bool isBarricate = TRUE;//��ֹ� ����: isBarricate ������ ���� ��ֹ��� �������� ��Ʈ������ ��Ÿ���� ���� ����
        const int gravity = 3;// �߷� �� : �߷��� ���� ������ �������� �ӵ��� �����ϴµ�, �� ���� ������ ���̵��� ���ϴ� ���ۿ� ���� ������ �� �ֽ��ϴ�. �ʱⰪ���� 3�� �����Ͽ� �߷��� �Ϲ����� �ӵ��� ����ǵ��� ��.

        int somY = SOM_BOTTOM_Y;//������ ���۵� ���� ���� �ٴڿ� �� �ִ� �����̹Ƿ� �ش� ��ġ�� �ʱ�ȭ
        int treeX = TREE_BOTTOM_X;//������ ���۵� ���� ������ ������ ������ ����ϹǷ� �ش� ��ġ�� �ʱ�ȭ
        int HeartX = HEART_BOTTOM_X;//Tree�� ���Ͽ���

        int score = 0; //���� ����
        int time = 0;//��� �ð�
        clock_t start, curr;    //���� ���� �ʱ�ȭ(clock_t�� C ����� <time.h> ��� ���Ͽ� ���ǵ� ������ Ÿ��)
        start = clock();        //���۽ð� �ʱ�ȭ

        while (TRUE)    //�� �ǿ� ���� ����
        {
            //1)�浹üũ
            printf("treeX : %d, somY : %d", treeX, somY);
            if (isCollision(treeX, somY))//������ �� �浹�ϸ� ���� ������ ��������
                break;
            if (isHeartCollision(HeartX, somY))//���� ��Ʈ�� ���� ��� score�� 5 ����
            {
                score += 5;
            }

            //2)���� -> Ű �Է�: Ű������ 'z' Ű�� ������, ������ ����.
            if (GetKeyDown() == 'z' && isBottom)//zŰ�� ������ �ٴ��� ��-> ����
            {
                printf("\a");//������ �� �Ҹ���
                isJumping = TRUE;//���� ������ ��Ÿ���� ���� �������� ������Ʈ(�ʱ�ȭ���� �ݴ�)
                isBottom = FALSE;
            }

            //3)�� ��ġ ������Ʈ(���� ������ �ƴ���) 
            if (isJumping)
            {
                somY -= gravity;
            }//������:gravity ����ŭ Y�� ����
            else
            {
                somY += gravity;
            }//����x:  gravity ����ŭ ���� Y ��ǥ�� ����(�߷¿� ���� �����´�..)


            //Y�� ����ؼ� �����ϴ°� �������� �ٴ��� ����.
            //( ���� Y ��ǥ�� ���� �ִ� ������ SOM_BOTTOM_Y(12)���� ũ�ų� ������ ���� �ٴڿ� ������ ������ �Ǵ��ϰ�)
            if (somY >= SOM_BOTTOM_Y)
            {
                somY = SOM_BOTTOM_Y;
                isBottom = TRUE;
            }

            //4)������ ��Ʈ�� ��ġ�� �������� �̵���Ŵ
            if (isBarricate)//������ �ִ� ���
            {
                treeX -= 2;
            }
            else//��Ʈ�� �ִ� ���
            {
                HeartX -= 2;
            }
            //4-2)��ֹ����� ���� ȭ���� ����� �ٽ� �ʱ� ��ġ���� �����ϰ� �Ǹ�, ������ ��Ʈ�� �����ư��鼭 ��Ÿ���� ȿ��
            if (treeX <= 0)//������ ���� ȭ���� ���
            {
                treeX = TREE_BOTTOM_X;//������ X ��ǥ�� �ʱ� ��ġ�� �ǵ�����
                isBarricate = FALSE;//FALSE�� �����Ͽ� ��Ʈ�� ��Ÿ������ ����
            }
            if (HeartX <= 5)//��Ʈ�� ���� ȭ���� ����� ��
            {
                HeartX = HEART_BOTTOM_X;//��Ʈ�� X ��ǥ�� �ʱ� ��ġ�� �ǵ�����
                isBarricate = TRUE;//TRUE�� �����Ͽ� ������ ��Ÿ������ ����
            }

            //5)���� ���� ������ ����,�ر׸���: �ִ� ���� �� (Y ��ǥ(somY)�� 3���� �۰ų� �������� �� )..3)�� ����.
            if (somY <= 3)
            {
                isJumping = FALSE;//���� ������ ����
            }
            Drawsom(somY);

            //6)������ ��Ʈ �׸���...4)�� ����
            if (isBarricate)
            {
                DrawTree(treeX);
            }
            else
            {
                DrawHeart(HeartX);
            }

            //7)������ �ð��� ������ �����ϰ�, ȭ�鿡 ���
            curr = clock();            //����ð� �޾ƿ���
            if (((curr - start) / CLOCKS_PER_SEC) >= 1)    // 1�ʰ� �Ѿ����� (���� �ð��� ���� �ð��� ���̸� �� ������ ��ȯ�Ͽ� 1�� �̻����� Ȯ��)
            {
                time++;    //�ð� 1�ʾ� UP
                score++;    //���ھ� UP( 1�ʸ��� ���ھ ����)
                start = clock();    //���۽ð� �ʱ�ȭ
            }
            Sleep(60);
            system("cls");


            GotoXY(22, 0);
            printf("Time : %d \t", time);
            printf("Score : %d\t", score);
        }

        //���� ���� �޴�: �� ���� ������ ������, ���� ���� �޴��� ����ϰ�, �ٽ� ���� ������ ó������ ���ư��� ������ �ٽ� ����
        DrawGameOver(score);
    }
    return 0;
}