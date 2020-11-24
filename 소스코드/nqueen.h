#ifndef NQUEEN_H
#define NQUEEN_H
#define toKor(str) QString::fromLocal8Bit(str)

#include <QMainWindow>
#include <QApplication>
#include <iostream>
#include <vector>
#include <algorithm>        // ���� �Լ�(�˰���), swap �Լ�(�˰���)
#include <cstdlib>
#include <ctime>
using namespace std;
#include "conio.h"

#include <QMessageBox>

#include <QPushButton>
#include <QtGlobal>
#include <QIcon>
#include <QSize>
#include <QPixmap>
#include <QBitmap>


enum SearchMethod
{
    EXHAUSTIVE = 1,
    HILL_CLIMBING = 2,
    SIMPLE_HILL_CLIMBING = 3,
    SIMULATED_ANNEALING = 4
};

namespace Ui {
class NQueen;
}

class NQueen : public QMainWindow
{
    Q_OBJECT

public:
    explicit NQueen(QWidget *parent = nullptr);
    void Check();
    void ExhaustiveSearch(int queen_count);             // ��� ��츦 �ϳ��� �����ϸ鼭 �˻�
    void PrintResult(vector<int> &solution, int queen_count, clock_t initial_clock);  // �� �߰� �� ȭ�� ���
    /*
    void HillClimbingSearch(int queen_count);           // ��� �̿���(pair ��ȯ)�� �� ���� ���� �ط� �̵�. �����غ��� ��� ���� ������ ����
    void SimpleHillClimbingSearch(int queen_count);     // �ϳ��� pair�� ��ȯ�� ���� �����ؿ� ���ų� ������ �ٷ� �̵�
    void SimulatedAnnealing(int queen_count);           // SimpleHillClimbingSearch + ���� ���� ��쿡�� e^(deltaE/T)�� Ȯ���� �̵�
    int GenInitSolutionRandom(vector<int> &solution, int queen_count);  // ������ �ʱ��� ����. Hill-Climbing(Simple ����)���� ���
    // �� ������ ���� ��� �ٸ� ��� N-Queens ������ �ذ� �Ǵ��� ����
    */
    bool Validate(vector<int> ary);         // �� ������ ���� ��� �ٸ� ��� ���� ���� ��ġ�� �ִ� �ֵ��� ���� ��ȯ
    int ViolateCount(vector<int> ary);
    double GetExeClockTime(clock_t initial_clock);
    int g_exe_time;
    int g_queen_count;
    int pre_queen_count;
    int exeFlag=0;
    QPushButton **button;
    ~NQueen();


private:
    Ui::NQueen *ui;
};

#endif // NQUEEN_H
