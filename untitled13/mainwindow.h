#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void generateMatrix();
    void generateEulerianMatrix();
    void findEulerianPath();
    void saveMatrix();
    void loadMatrix();
    void displayMatrix(const QVector<QVector<int>> &matrix);
    void manualInputDialog();

private:
    Ui::MainWindow *ui;
    QVector<QVector<int>> adjacencyMatrix;
    QGraphicsScene *graphScene;
    void DFS(QVector<QVector<int>>& graph, QVector<int>& path, int v);
    bool isGraphOriented;
    void drawGraph(const QVector<QVector<int>> &adjacencyMatrix);
    bool isEulerian(const QVector<QVector<int>> &adjacencyMatrix);
    void drawEulerianPath(const QVector<int> &eulerianPath);
    void processMatrixInput(const QString& matrixText);
    bool isValidMatrix(const QVector<QVector<int>>& matrix) const;
    void dfsForConnectivity(const QVector<QVector<int>>& adjacencyMatrix, QVector<bool>& visited, int vertex);

};

#endif // MAINWINDOW_H
