#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lsystemView->setLSystem(&lSystem);

    connect(ui->depthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(gen()));
    connect(ui->boldLines, SIGNAL(stateChanged(int)), this, SLOT(onDisplayChanged()));
    connect(ui->submit, SIGNAL(clicked()), this, SLOT(onSubmitTriggered()));

    updateRulesetFromLSystem();
    ui->depthSpinBox->setValue(6);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDisplayChanged()
{
    ui->lsystemView->setBoldLines(ui->boldLines->isChecked());
    ui->lsystemView->repaint();
}

void MainWindow::updateRulesetFromLSystem()
{
    Ruleset r = lSystem.getRules();
    ui->axiom->setText(QString(r.axiom.c_str()));
    ui->constF->setChecked(r.constants.F);
    ui->constX->setChecked(r.constants.X);
    ui->constY->setChecked(r.constants.Y);
    ui->constA->setChecked(r.constants.A);
    ui->constB->setChecked(r.constants.B);
    ui->ruleF->setText(QString(r.F.c_str()));
    ui->ruleX->setText(QString(r.X.c_str()));
    ui->ruleY->setText(QString(r.Y.c_str()));
    ui->ruleA->setText(QString(r.A.c_str()));
    ui->ruleB->setText(QString(r.B.c_str()));
    ui->angle->setValue(r.angle);
}

void MainWindow::onSubmitTriggered()
{
    Ruleset r;
    r.axiom = ui->axiom->text().toStdString();
    r.constants.F = ui->constF->isChecked();
    r.constants.X = ui->constX->isChecked();
    r.constants.Y = ui->constY->isChecked();
    r.constants.A = ui->constA->isChecked();
    r.constants.B = ui->constB->isChecked();
    r.F = ui->ruleF->text().toStdString();
    r.X = ui->ruleX->text().toStdString();
    r.Y = ui->ruleY->text().toStdString();
    r.A = ui->ruleA->text().toStdString();
    r.B = ui->ruleB->text().toStdString();
    r.angle = ui->angle->value();
    lSystem.setRules(r);
    gen();
}

void MainWindow::gen()
{
    lSystem.gen(static_cast<unsigned>(ui->depthSpinBox->value()));
    ui->lsystemView->repaint();
}
