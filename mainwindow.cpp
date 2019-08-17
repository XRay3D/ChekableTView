#include "mainwindow.h"
#include "model.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->init();
    connect(ui->spinBoxR, QOverload<int>::of(&QSpinBox::valueChanged), ui->tableView->model(), &Model::setRowCount);
    connect(ui->spinBoxC, QOverload<int>::of(&QSpinBox::valueChanged), ui->tableView->model(), &Model::setColumnCount);

    ui->tableView_2->initCheckBox();
    connect(ui->spinBoxR, QOverload<int>::of(&QSpinBox::valueChanged), ui->tableView_2->model(), &Model::setRowCount);
    connect(ui->spinBoxC, QOverload<int>::of(&QSpinBox::valueChanged), ui->tableView_2->model(), &Model::setColumnCount);

    ui->tableView_3->initRadioButton();
    connect(ui->spinBoxR, QOverload<int>::of(&QSpinBox::valueChanged), ui->tableView_3->model(), &Model::setRowCount);
    connect(ui->spinBoxC, QOverload<int>::of(&QSpinBox::valueChanged), ui->tableView_3->model(), &Model::setColumnCount);

    ui->tableView_4->initCheckBoxRadioButton();
    connect(ui->spinBoxR, QOverload<int>::of(&QSpinBox::valueChanged), ui->tableView_4->model(), &Model::setRowCount);
    connect(ui->spinBoxC, QOverload<int>::of(&QSpinBox::valueChanged), ui->tableView_4->model(), &Model::setColumnCount);

    connect(ui->checkBox_3, &QCheckBox::toggled, [this](bool checked) {
        ui->tableView->setEnabled(checked);
        ui->tableView_2->setEnabled(checked);
        ui->tableView_3->setEnabled(checked);
        ui->tableView_4->setEnabled(checked);
    });

    QTimer::singleShot(1, [this] {
        ui->spinBoxR->setValue(5);
        ui->spinBoxC->setValue(3);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
