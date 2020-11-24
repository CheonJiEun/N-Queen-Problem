#ifndef NQUEEN_H
#define NQUEEN_H
#define toKor(str) QString::fromLocal8Bit(str)

#include <QMainWindow>
#include <QApplication>
#include <iostream>
#include <vector>
#include <algorithm>        // 순열 함수(알고리즘), swap 함수(알고리즘)
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
    void ExhaustiveSearch(int queen_count);             // 모든 경우를 하나씩 나열하면서 검사
    void PrintResult(vector<int> &solution, int queen_count, clock_t initial_clock);  // 해 발견 시 화면 출력
    /*
    void HillClimbingSearch(int queen_count);           // 모든 이웃해(pair 교환)들 중 가장 좋은 해로 이동. 현재해보다 모두 좋지 않으면 종료
    void SimpleHillClimbingSearch(int queen_count);     // 하나의 pair룰 교환해 보고 현재해와 같거나 좋으면 바로 이동
    void SimulatedAnnealing(int queen_count);           // SimpleHillClimbingSearch + 좋지 않은 경우에도 e^(deltaE/T)의 확률로 이동
    int GenInitSolutionRandom(vector<int> &solution, int queen_count);  // 무작위 초기해 생성. Hill-Climbing(Simple 포함)에서 사용
    // 각 변수의 값이 모두 다를 경우 N-Queens 문제의 해가 되는지 검증
    */
    bool Validate(vector<int> ary);         // 각 변수의 값이 모두 다를 경우 서로 직선 위치에 있는 쌍들의 개수 반환
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
