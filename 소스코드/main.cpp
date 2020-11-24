#include "nqueen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NQueen w;
    w.setWindowTitle("N-Queen Problem");
    w.show();

    return a.exec();
}
