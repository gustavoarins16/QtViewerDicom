#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "DicomLoader.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void openDicomFile();

private:
    void setupUI();

    QGraphicsView *imageView;
    QGraphicsScene *imageScene;
    QPushButton *btnOpen;
    QLabel *lblInfo;

    DicomLoader dicomLoader;
};

#endif // MAIN_WINDOW_H
