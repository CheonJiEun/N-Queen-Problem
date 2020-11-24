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
        QMessageBox::warning(this, "Error", toKor("������ �Է����ּ���."));
    }
    else
    {
        int queen_count = ui->lineEdit_queenCount->text().toInt();
        if (queen_count < 4)
        {
            QMessageBox::information(this, "QueenCount", toKor("�� ������ 4 �̻� �Է°����մϴ�."));
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
// Exhaustive Search : ��ü Ž��
//   �Է� : queen�� ����
//   ��� : n-queens ������ �� �Ǵ� ���� ���
//   ��� �����ؿ� ���� n-queens ������ ���������� �����ϴ��� �˻�
//   STL�� ���� ���� �˰��� next_permutation ���

void NQueen::ExhaustiveSearch(int queen_count)
{
    clock_t initial_clock = clock();                // ���� �ð�(clock) ����

    vector<int> solution;                           // ������
    for (int i = 0; i < queen_count; i++)           // 1, 2, 3, 4, 5, ... ���� ����
        solution.push_back(i + 1);

    int best_obj_value = INT_MAX;

    do
    {
        int obj_value = ViolateCount(solution);

        if (obj_value == 0)                         // n-queens ������ �ض��(��� ���� X) ��� ��� �� ����
        {
            if (Validate(solution))
            {
                PrintResult(solution, queen_count, initial_clock);
            }
            else                            // ���� �߻�
            {
                QMessageBox::warning(this, "ResultError", toKor("�������� �������� ����� �̻��մϴ�!"));
            }
            break;
        }
        else if (obj_value < best_obj_value)        // ���� �ذ� �߰ߵǸ� ���
        {
            best_obj_value = obj_value;
        }

        if (GetExeClockTime(initial_clock) > g_exe_time)    // �ִ� ���� �ð��� �ʰ��ϸ� ����
        {
            QMessageBox::information(this, "TimeOver", toKor("�ִ� ����ð��� �ʰ��Ͽ����ϴ�."));
            break;
        }
    } while (next_permutation(solution.begin(), solution.end()));   // ���� ���� ����
}

// �� �߰� �� queen�� ����, ��, ���� �ð��� ȭ�鿡 ���
void NQueen::PrintResult(vector<int> &solution, int queen_count, clock_t initial_clock)
{
    QString strTime = QString(toKor("����ð�(��) : %1")).arg(GetExeClockTime(initial_clock));
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


// �� ������ ���� ��� �ٸ� ��� N-Queens ������ �ذ� �Ǵ��� ����
bool NQueen::Validate(vector<int> ary)
{
    for (int i = 0; i < ary.size() - 1; i++)
    {
        int row1 = ary[i];
        for (int j = i + 1; j < ary.size(); j++)
        {
            int row2 = ary[j];

            // ���� �࿡ ������ �ȵ� (���� ���̸� �ȵ�) => �̹� ��� �ٸ��Ƿ� �˻� ���ʿ�

            // �밢�� / �������� ���� ��ġ�� ������ �ȵ�
            if (row1 == (row2 + (j - i)))
                return false;

            // �밢�� \ �������� ���� ��ġ�� ������ �ȵ�
            if (row1 == (row2 - (j - i)))
                return false;
        }
    }

    return true;
}

// �� ������ ���� ��� �ٸ� ��� ���� ���� ��ġ�� �ִ� �ֵ��� ���� ��ȯ
int NQueen::ViolateCount(vector<int> ary)
{
    int count = 0;

    for (int i = 0; i < ary.size() - 1; i++)
    {
        int row1 = ary[i];
        for (int j = i + 1; j < ary.size(); j++)
        {
            int row2 = ary[j];

            // ���� �࿡ ������ �ȵ� (���� ���̸� �ȵ�) => �̹� ��� �ٸ��Ƿ� �˻� ���ʿ�

            // �밢�� / �Ǵ� \ �������� ���� ��ġ�� ������ count 1 ����
            if (row1 == (row2 + (j - i)) || row1 == (row2 - (j - i)))
                count++;
        }
    }

    return count;
}

// initial_clock�� �������� ��������� ��� �ð� ��ȯ
double NQueen::GetExeClockTime(clock_t initial_clock)
{
    clock_t current_clock = clock();
    return ((double)(current_clock - initial_clock) / CLOCKS_PER_SEC);
}


NQueen::~NQueen()
{
    delete ui;
}


