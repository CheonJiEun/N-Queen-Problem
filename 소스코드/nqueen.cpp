#include "nqueen.h"
#include "ui_nqueen.h"

NQueen::NQueen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NQueen)
{
    ui->setupUi(this);
    connect(ui->pushButton_Start, &QPushButton::clicked, this, &NQueen::Check);
}

void NQueen::Check()
{
    if (ui->comboBox->currentIndex() == 0 || ui->lineEdit_queenCount->text() == "" || ui->lineEdit_MaxExeTime->text() == "" )
    {
        QMessageBox::warning(this, "Error", toKor("내용을 입력해주세요."));
    }
    else
    {
        int queen_count = ui->lineEdit_queenCount->text().toInt();
        if (queen_count < 4)
        {
            QMessageBox::information(this, "QueenCount", toKor("퀸 개수는 4 이상 입력가능합니다."));
            return;
        }
        g_exe_time = ui->lineEdit_MaxExeTime->text().toInt();

        for (int i=0;i<pre_queen_count && exeFlag==1;i++)
        {
            delete[] button[i];
        }
        delete button;

        pre_queen_count = queen_count;
        exeFlag=1;
        switch (ui->comboBox->currentIndex())
        {
        case EXHAUSTIVE:
            ExhaustiveSearch(queen_count);
            break;
        }
    }

}




////////////////////////////////////////////////////////////////////
// Exhaustive Search : 전체 탐색
//   입력 : queen의 개수
//   출력 : n-queens 문제의 해 또는 실패 출력
//   모든 가능해에 대해 n-queens 문제의 제약조건을 만족하는지 검사
//   STL의 순열 생성 알고리즘 next_permutation 사용

void NQueen::ExhaustiveSearch(int queen_count)
{
    clock_t initial_clock = clock();                // 시작 시각(clock) 저장

    vector<int> solution;                           // 현재해
    for (int i = 0; i < queen_count; i++)           // 1, 2, 3, 4, 5, ... 부터 시작
        solution.push_back(i + 1);

    int best_obj_value = INT_MAX;

    do
    {
        int obj_value = ViolateCount(solution);

        if (obj_value == 0)                         // n-queens 문제의 해라면(모두 직선 X) 결과 출력 후 종료
        {
            if (Validate(solution))
            {
                PrintResult(solution, queen_count, initial_clock);
            }
            else                            // 오류 발생
            {
                QMessageBox::warning(this, "ResultError", toKor("성공으로 나왔으나 결과가 이상합니다!"));
            }
            break;
        }
        else if (obj_value < best_obj_value)        // 좋은 해가 발견되면 출력
        {
            best_obj_value = obj_value;
        }

        if (GetExeClockTime(initial_clock) > g_exe_time)    // 최대 수행 시간을 초과하면 종료
        {
            QMessageBox::information(this, "TimeOver", toKor("최대 수행시간을 초과하였습니다."));
            break;
        }
    } while (next_permutation(solution.begin(), solution.end()));   // 다음 순열 생성
}

// 해 발견 시 queen의 개수, 해, 수행 시간을 화면에 출력
void NQueen::PrintResult(vector<int> &solution, int queen_count, clock_t initial_clock)
{
    QString strTime = QString(toKor("수행시간(초) : %1")).arg(GetExeClockTime(initial_clock));
    ui->label_exeTime->setText(strTime);


    QPixmap pixmap("C:\\Queen.png");

    button = new QPushButton*[queen_count];

    for (int i=0;i<queen_count;i++)
    {
        button[i]=new QPushButton[queen_count];
    }

    for (int i=0;i<queen_count;i++)
    {
        for (int j=0;j<queen_count;j++)
        {
            button[i][j].setMaximumSize(QSize(150,150));

            if ((i + j) % 2 == 0)
                button[i][j].setStyleSheet("background-color: rgb(255,255,255);");
            else
                button[i][j].setStyleSheet("background-color: rgb(0,0,0);");


            if (solution[i]-1 == j)
            {
                QIcon icon(pixmap);
                button[i][j].setIcon(icon);
                if (queen_count <= 12)
                    button[i][j].setIconSize(QSize(150-queen_count*11,150-queen_count*11));
                else
                    button[i][j].setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            }

            ui->gridLayout->addWidget(&button[i][j], i, j, 1,1);
            ui->gridLayout->setSpacing(0);
        }
    }
}


// 각 변수의 값이 모두 다를 경우 N-Queens 문제의 해가 되는지 검증
bool NQueen::Validate(vector<int> ary)
{
    for (int i = 0; i < ary.size() - 1; i++)
    {
        int row1 = ary[i];
        for (int j = i + 1; j < ary.size(); j++)
        {
            int row2 = ary[j];

            // 같은 행에 있으면 안됨 (같은 값이면 안됨) => 이미 모두 다르므로 검사 불필요

            // 대각선 / 방향으로 같은 위치에 있으면 안됨
            if (row1 == (row2 + (j - i)))
                return false;

            // 대각선 \ 방향으로 같은 위치에 있으면 안됨
            if (row1 == (row2 - (j - i)))
                return false;
        }
    }

    return true;
}

// 각 변수의 값이 모두 다를 경우 서로 직선 위치에 있는 쌍들의 개수 반환
int NQueen::ViolateCount(vector<int> ary)
{
    int count = 0;

    for (int i = 0; i < ary.size() - 1; i++)
    {
        int row1 = ary[i];
        for (int j = i + 1; j < ary.size(); j++)
        {
            int row2 = ary[j];

            // 같은 행에 있으면 안됨 (같은 값이면 안됨) => 이미 모두 다르므로 검사 불필요

            // 대각선 / 또는 \ 방향으로 같은 위치에 있으면 count 1 증가
            if (row1 == (row2 + (j - i)) || row1 == (row2 - (j - i)))
                count++;
        }
    }

    return count;
}

// initial_clock을 기준으로 현재까지의 경과 시간 반환
double NQueen::GetExeClockTime(clock_t initial_clock)
{
    clock_t current_clock = clock();
    return ((double)(current_clock - initial_clock) / CLOCKS_PER_SEC);
}


NQueen::~NQueen()
{
    delete ui;
}


