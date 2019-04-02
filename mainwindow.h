#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lsystem.h"
#include "lsystemcontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDisplayChanged();
    void onSubmitTriggered();
    void gen();

private:
    Ui::MainWindow *ui;
    LSystem lSystem;

    void updateRulesetFromLSystem();
};

#endif // MAINWINDOW_H
