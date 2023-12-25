#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QRandomGenerator>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QPainterPath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    graphScene(new QGraphicsScene(this))
{
    ui->setupUi(this);

    connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::generateMatrix);
    connect(ui->generateEulerButton, &QPushButton::clicked, this, &MainWindow::generateEulerianMatrix);
    connect(ui->findEulerianButton, &QPushButton::clicked, this, &MainWindow::findEulerianPath);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveMatrix);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::loadMatrix);
    connect(ui->manualInputButton, &QPushButton::clicked, this, &MainWindow::manualInputDialog);

    ui->graphView->setScene(graphScene);

    // Устанавливаем значения по умолчанию для densitySpinBox и sizeSpinBox
    ui->densitySpinBox->setValue(0.5);
    ui->sizeSpinBox->setValue(5);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::generateMatrix() {
    // Очистка графической сцены перед генерацией новой матрицы
    graphScene->clear();

    // Очистка текстового поля eulerianPathTextEdit
    ui->eulerianPathTextEdit->clear();

    // Получаем параметры размера и плотности рёбер
    int size = ui->sizeSpinBox->value();
    double density = ui->densitySpinBox->value();

    // Генерируем матрицу смежности
    QVector<QVector<int>> adjacencyMatrix(size, QVector<int>(size, 0));

    // Заполняем матрицу случайными рёбрами в соответствии с плотностью
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            double randomValue = QRandomGenerator::global()->generateDouble();
            if (randomValue < density) {
                adjacencyMatrix[i][j] = 1;
                adjacencyMatrix[j][i] = 1;
            }
        }
    }

    // Отображаем матрицу в текстовом виде
    displayMatrix(adjacencyMatrix);

    // Отображение матрицы в текстовом поле
    drawGraph(adjacencyMatrix);
}

void MainWindow::generateEulerianMatrix() {

    // Получаем параметры размера и плотности рёбер
    int size = ui->sizeSpinBox->value();
    double density = ui->densitySpinBox->value();
    QVector<QVector<int>> adjacencyMatrix(size, QVector<int>(size, 0));

    // Ограничение на количество попыток
    int maxAttempts = 20;
    int attempts = 0;

    // Генерируем эйлеров граф
    do {
        // Заполняем матрицу случайными рёбрами с учетом плотности
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                double randomValue = QRandomGenerator::global()->generateDouble();
                if (randomValue < density) {
                    adjacencyMatrix[i][j] = 1;
                    adjacencyMatrix[j][i] = 1;
                }
            }
        }

        // Проверяем, что граф стал эйлеровым
        if (isEulerian(adjacencyMatrix)) {
            break;
        }

        attempts++;
    } while (attempts < maxAttempts);

    // Проверяем, была ли успешно сгенерирована матрица
    if (attempts == maxAttempts) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сгенерировать эйлеров граф. Попробуйте изменить параметры.");
    } else {

        // Отображаем матрицу в текстовом виде
        displayMatrix(adjacencyMatrix);

        // Отображение матрицы в текстовом поле
        drawGraph(adjacencyMatrix);
    }
}

bool MainWindow::isEulerian(const QVector<QVector<int>> &adjacencyMatrix) {

    int numRows = adjacencyMatrix.size();

    // Проверка на нулевую матрицу
    bool hasNonZeroElement = false;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numRows; ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                hasNonZeroElement = true;
                break;
            }
        }
        if (hasNonZeroElement) {
            break;
        }
    }

    if (!hasNonZeroElement) {
        return false;
    }

    // Подсчитываем степени вершин
    QVector<int> degrees(adjacencyMatrix.size(), 0);
    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        for (int j = 0; j < adjacencyMatrix[i].size(); ++j) {
            degrees[i] += adjacencyMatrix[i][j];
        }
    }

    // Проверяем, что все вершины имеют чётные степени
    for (int degree : degrees) {
        if (degree % 2 != 0) {
            return false;
        }
    }

    // Проверяем связность графа с использованием обхода в глубину (DFS)
    QVector<bool> visited(adjacencyMatrix.size(), false);
    int startVertex = -1;

    for (int i = 0; i < visited.size(); ++i) {
        if (degrees[i] > 0) {
            startVertex = i;
            break;
        }
    }

    if (startVertex == -1) {
        // Граф пуст, считаем его связным
        return true;
    }

    dfsForConnectivity(adjacencyMatrix, visited, startVertex);

    // Проверяем, что все вершины были посещены
    for (bool visitStatus : visited) {
        if (!visitStatus) {
            return false;
        }
    }

    return true;
}

void MainWindow::dfsForConnectivity(const QVector<QVector<int>> &adjacencyMatrix, QVector<bool> &visited, int vertex) {
    visited[vertex] = true;

    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        if (adjacencyMatrix[vertex][i] == 1 && !visited[i]) {
            dfsForConnectivity(adjacencyMatrix, visited, i);
        }
    }
}

void MainWindow::findEulerianPath() {
    // Получаем матрицу смежности из текстового поля
    QString matrixText = ui->matrixTextEdit->toPlainText();
    QStringList rows = matrixText.split('\n', Qt::SkipEmptyParts);

    // Проверяем, что матрица не пуста
    if (rows.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Матрица смежности пуста.");
        return;
    }

    int size = rows.size();
    QVector<QVector<int>> adjacencyMatrix(size, QVector<int>(size, 0));

    // Заполняем матрицу смежности из текстового поля
    for (int i = 0; i < size; ++i) {
        QStringList elements = rows[i].split(' ', Qt::SkipEmptyParts);
        for (int j = 0; j < qMin(size, elements.size()); ++j) {
            adjacencyMatrix[i][j] = elements[j].toInt();
        }
    }

    // Проверяем, что граф является эйлеровым
    if (!isEulerian(adjacencyMatrix)) {
        QMessageBox::warning(this, "Ошибка", "Граф не является эйлеровым.");
        return;
    }

    QVector<int> path;
    DFS(adjacencyMatrix, path, 0);

    // Выводим эйлеров цикл в текстовое поле
    QString eulerianPathText;
    for (int i = 0; i < path.size(); ++i) {
        eulerianPathText += QString::number(path[i]+1) + " ";
    }

    ui->eulerianPathTextEdit->setPlainText(eulerianPathText);
}

void MainWindow::DFS(QVector<QVector<int>> &graph, QVector<int> &path, int v) {
    for (int i = 0; i < graph[v].size(); ++i) {
        if (graph[v][i] != 0) {
            graph[v][i] = 0;
            graph[i][v] = 0;
            DFS(graph, path, i);
        }
    }
    path.push_back(v);
}

void MainWindow::drawGraph(const QVector<QVector<int>> &adjacencyMatrix) {
    // Очищаем графическую сцену
    graphScene->clear();

    int size = adjacencyMatrix.size();
    qreal radius = 20.0;

    // Определяем центр QGraphicsView
    qreal centerX = ui->graphView->width() / 2.0;
    qreal centerY = ui->graphView->height() / 2.0;

    // Добавляем отступ от краев
    qreal margin = 20.0;

    // Определяем радиус круга с учетом отступа
    qreal circleRadius = qMin(centerX, centerY) - radius - margin;

    for (int i = 0; i < size; ++i) {
        qreal angle = 2.0 * M_PI * i / size;
        qreal x = centerX + circleRadius * qCos(angle);
        qreal y = centerY + circleRadius * qSin(angle);

        QGraphicsEllipseItem *node = new QGraphicsEllipseItem(x - radius, y - radius, 2 * radius, 2 * radius);
        node->setBrush(Qt::blue);
        node->setPen(QPen(Qt::black, 2.0)); // Устанавливаем толщину обводки вершины
        node->setZValue(1); // Устанавливаем Z-значение для вершины

        QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(i + 1));
        // Устанавливаем позицию текста по центру вершины
        text->setPos(x - text->boundingRect().width() / 1.3, y - text->boundingRect().height() / 1.3);

        text->setScale(1.5); // Увеличиваем размер цифры
        text->setZValue(2); // Устанавливаем более высокое Z-значение для текста
        text->setDefaultTextColor(Qt::white); // Устанавливаем белый цвет текста

        graphScene->addItem(node);
        graphScene->addItem(text);

        for (int i = 0; i < size; ++i) {
            qreal angle = 2.0 * M_PI * i / size;
            qreal x = centerX + circleRadius * qCos(angle);
            qreal y = centerY + circleRadius * qSin(angle);

            QGraphicsEllipseItem *node = new QGraphicsEllipseItem(x - radius, y - radius, 2 * radius, 2 * radius);
            node->setBrush(Qt::blue);
            node->setPen(QPen(Qt::black, 2.0)); // Устанавливаем толщину обводки вершины
            node->setZValue(1); // Устанавливаем Z-значение для вершины

            QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(i + 1));
            // Устанавливаем позицию текста по центру вершины
            text->setPos(x - text->boundingRect().width() / 1.3, y - text->boundingRect().height() / 1.3);

            text->setScale(1.5); // Увеличиваем размер цифры
            text->setZValue(2); // Устанавливаем более высокое Z-значение для текста
            text->setDefaultTextColor(Qt::white); // Устанавливаем белый цвет текста

            graphScene->addItem(node);
            graphScene->addItem(text);

            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    if (adjacencyMatrix[i][j] != 0) {
                        qreal x1 = centerX + circleRadius * qCos(2.0 * M_PI * i / size);
                        qreal y1 = centerY + circleRadius * qSin(2.0 * M_PI * i / size);

                        qreal x2 = centerX + circleRadius * qCos(2.0 * M_PI * j / size);
                        qreal y2 = centerY + circleRadius * qSin(2.0 * M_PI * j / size);

                        QGraphicsLineItem *edge = new QGraphicsLineItem(x1, y1, x2, y2);
                        edge->setZValue(0); // Устанавливаем Z-значение для ребра
                        edge->setPen(QPen(Qt::black, 2.0)); // Устанавливаем толщину линии ребра
                        graphScene->addItem(edge);
                    }
                }
            }
        }

    }
}

// Сохранение матрицы в файл
void MainWindow::saveMatrix() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить матрицу", QDir::homePath(), "Текстовые файлы (*.txt)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->matrixTextEdit->toPlainText();
            file.close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить матрицу.");
        }
    }
}

// Загрузка матрицы из файла
void MainWindow::loadMatrix() {
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить матрицу", QDir::homePath(), "Текстовые файлы (*.txt)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QVector<QVector<int>> loadedMatrix;

            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList values = line.split(" ", Qt::SkipEmptyParts);
                QVector<int> row;

                for (const QString &value : values) {
                    row.append(value.toInt());
                }

                loadedMatrix.append(row);
            }

            file.close();

            // Присваиваем загруженную матрицу
            adjacencyMatrix = loadedMatrix;

            // Отображаем матрицу в текстовом поле
            displayMatrix(adjacencyMatrix);

            drawGraph(adjacencyMatrix);
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось загрузить матрицу.");
        }
    }
}

void MainWindow::displayMatrix(const QVector<QVector<int>>& matrix) {
    int size = matrix.size();
    QString matrixText;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrixText += QString::number(matrix[i][j]) + " ";
        }
        matrixText += "\n";
    }

    ui->matrixTextEdit->setPlainText(matrixText);
}

void MainWindow::manualInputDialog() {
    bool ok;
    QString matrixText = QInputDialog::getMultiLineText(this, "Ввод матрицы", "Введите матрицу смежности (разделяйте числа пробелами и строки переносами):", "", &ok);

    if (ok && !matrixText.isEmpty()) {
        // Обработайте введенный текст и присвойте его adjacencyMatrix
        processMatrixInput(matrixText);

        // Очистка текстового поля перед генерацией новой матрицы
        ui->eulerianPathTextEdit->clear();
    }

}

void MainWindow::processMatrixInput(const QString& matrixText) {
    // Преобразуйте введенный текст матрицы в QVector<QVector<int>>
    QVector<QVector<int>> inputMatrix;
    QStringList rows = matrixText.split('\n', Qt::SkipEmptyParts);

    for (const QString &row : rows) {
        QStringList values = row.split(' ', Qt::SkipEmptyParts);
        QVector<int> matrixRow;

        for (const QString &value : values) {
            // Проверка на корректность введенных данных
            bool conversionOk;
            int intValue = value.toInt(&conversionOk);

            if (conversionOk) {
                matrixRow.append(intValue);
            } else {
                QMessageBox::warning(this, "Ошибка", "Введены некорректные данные. Пожалуйста, введите целые числа.");
                return;
            }
        }

        inputMatrix.append(matrixRow);
    }

    // Проверка на корректность матрицы
    if (!isValidMatrix(inputMatrix)) {
        QMessageBox::warning(this, "Ошибка", "Введена некорректная матрица. Пожалуйста, убедитесь, что это квадратная матрица, симметричная, и все значения являются целыми числами с нулями на главной диагонали.");
        return;
    }

    // Присвойте введенную матрицу
    adjacencyMatrix = inputMatrix;

    // Отображайте матрицу в текстовом поле или в вашем графическом представлении
    displayMatrix(adjacencyMatrix);
    drawGraph(adjacencyMatrix);
}

bool MainWindow::isValidMatrix(const QVector<QVector<int>>& matrix) const {
    size_t numRows = matrix.size();

    for (size_t i = 0; i < numRows; ++i) {
        // Проверка на квадратность матрицы и наличия только 0 и 1
        if (matrix[i].size() != numRows) {
            return false;
        }

        for (size_t j = 0; j < numRows; ++j) {
            int value = matrix[i][j];

            // Проверка наличия только 0 и 1 в матрице
            if (value != 0 && value != 1) {
                return false;
            }

            // Проверка наличия нулей на главной диагонали и симметричности
            if (i == j && value != 0) {
                return false; // Есть ненулевой элемент на главной диагонали
            }

            if (i != j && value != matrix[j][i]) {
                return false; // Несимметричная матрица
            }
        }
    }

    return true;
}

