#include <iostream>
#include <iomanip>
#include <time.h>


using namespace std;

void CreateRow(int** P, const int colCount, int rowNo, int colNo) {
    cout << "P[" << rowNo << "][" << colNo << "] = ";
    cin >> P[rowNo][colNo];
    if (colNo < colCount - 1) {
        CreateRow(P, colCount, rowNo, colNo + 1);
    }
}

void Create(int** P, const int rowCount, const int colCount, int rowNo) {
    if (rowCount == 0 || colCount == 0) {
        return;
    }
    CreateRow(P, colCount, rowNo, 0);
    if (rowNo < rowCount - 1) {
        Create(P, rowCount, colCount, rowNo + 1);
    }
}

void PrintRow(int** P, const int colCount, int rowNo, int colNo) {
    cout << setw(4) << P[rowNo][colNo];
    if (colNo < colCount - 1) {
        PrintRow(P, colCount, rowNo, colNo + 1);
    }
    else {
        cout << endl;
    }
}

void Print(int** P, const int rowCount, const int colCount, int rowNo) {
    if (rowCount == 0 || colCount == 0) {
        cout << "no matrix" << endl;
        return;
    }
    PrintRow(P, colCount, rowNo, 0);
    if (rowNo < rowCount - 1) {
        Print(P, rowCount, colCount, rowNo + 1);
    }
    else {
        cout << endl;
    }
}

void rowDel(int** P, int& rowCount, const int colCount, const int rowNum, int colNum) {
    P[rowNum - 1][colNum] = P[rowNum][colNum];
    if (colNum < colCount - 1) {
        rowDel(P, rowCount, colCount, rowNum, colNum + 1);
    }
    else if (rowNum - 1 < rowCount - 2) {
        rowDel(P, rowCount, colCount, rowNum + 1, 0);
    }
    else {
        rowCount--;
    }
}

void colDel(int** P, const int rowCount, int& colCount, const int colNum, int rowNum) {
    P[rowNum][colNum - 1] = P[rowNum][colNum];
    if (colNum - 1 < colCount - 2) {
        colDel(P, rowCount, colCount, colNum + 1, rowNum);
    }
    else if (rowNum < rowCount - 1) {
        colDel(P, rowCount, colCount, 0, rowNum + 1);
    }
    else {
        colCount--;
    }
}

void matrixColCompress(int** P, int& rowCount, int& colCount, int i, int j) {
    if (P[i][j] == 0 && i == rowCount - 1 && j < colCount) {
        colDel(P, rowCount, colCount, j + 1, 0);
        matrixColCompress(P, rowCount, colCount, 0, j);
    }
    else if (P[i][j] == 0 && i < rowCount) {
        matrixColCompress(P, rowCount, colCount, i + 1, j);
    }
    else if (j < colCount - 1) {
        matrixColCompress(P, rowCount, colCount, 0, j + 1);
    }
}

void matrixCompress(int** P, int& rowCount, int& colCount, int i, int j) {
    if (P[i][j] == 0 && j == colCount - 1 && i < rowCount) {
        rowDel(P, rowCount, colCount, i + 1, 0);
        matrixCompress(P, rowCount, colCount, i, 0);
    }
    else if (P[i][j] == 0 && j < colCount) {
        matrixCompress(P, rowCount, colCount, i, j + 1);
    }
    else if (i < rowCount - 1){
        matrixCompress(P, rowCount, colCount, i + 1, 0);
    }

    if (rowCount == 0) {
        return;
    }

    matrixColCompress(P, rowCount, colCount, 0, 0);
}


int matrixFirstPlus(int** P, const int rowCount, const int colCount, int i ,int j) {
    if (rowCount == 0 || colCount == 0) {
        return -1;
    }
    if (P[i][j] > 0) {
        return i + 1;
    }
    else if (P[i][j] <= 0 && i == rowCount - 1 && j == colCount - 1) {
        return -1;
    }
    if (j < colCount - 1) {
        matrixFirstPlus(P, rowCount, colCount, i, j + 1);
    }
    else if (i < rowCount - 1) {
        matrixFirstPlus(P, rowCount, colCount, i + 1, 0);
    }
}



int main()
{
    int rowCount;
    int colCount;

    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    int** P = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        P[i] = new int[colCount];


    Create(P, rowCount, colCount, 0);
    cout << "Before compression:" << endl;
    Print(P, rowCount, colCount, 0);
    cout << "First row with at least 1 element > 0: " << matrixFirstPlus(P, rowCount, colCount, 0, 0) << endl;

    cout << "After compression:" << endl;
    matrixCompress(P, rowCount, colCount, 0, 0);
    Print(P, rowCount, colCount, 0);
    cout << "First row with at least 1 element > 0: " << matrixFirstPlus(P, rowCount, colCount, 0, 0) << endl;

    system("pause");
    cin.get();
    return 0;
}


