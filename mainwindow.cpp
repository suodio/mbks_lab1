#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdlib.h"
#include <QMessageBox>

int clicked = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //tab 1 set and fill table
    ui->processTableWidget->setVisible(false);

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Процесс" << "info1" << "info2" << "info3" << "info4");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //Example how to fill table with data
    int count = 1;
    for(int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        for(int j = 0; j < ui->tableWidget->columnCount(); ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(count));
            ui->tableWidget->setItem(i, j, item);
            count++;
        }
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(tr("%1_%2").arg("процесс").arg(i)));
    }

    //tab 2 set and fill list of items
    ui->treeWidgetSelectedItem->setVisible(false);
    ui->treeWidget->setColumnCount(5);

    QStringList labels;
    labels << "Name" << "Path" << "ACL" << "Owner" << "Integrity level";
    ui->treeWidget->setHeaderLabels(labels);

    QTreeWidgetItem *root = new QTreeWidgetItem(ui->treeWidget);
    root->setText(0, "RootFile");
    root->setText(1, "Root File Path");
    root->setText(2, "");
    root->setText(3, "");
    root->setText(4, "");
    ui->treeWidget->addTopLevelItem(root);

    QTreeWidgetItem *child1 = new QTreeWidgetItem();
    child1->setText(0, "ChildFile1");
    child1->setText(1, "child1 File Path");
    child1->setText(2, "child1 ACL");
    child1->setText(3, "child1 OWNER");
    child1->setText(4, "child1 IL");
    root->addChild(child1);

    QTreeWidgetItem *child2 = new QTreeWidgetItem();
    child2->setText(0, "ChildFile2");
    child2->setText(1, "child2 File Path");
    child2->setText(2, "child2 ACL");
    child2->setText(3, "child2 OWNER");
    child2->setText(4, "child2 IL");
    child1->addChild(child2);

    QTreeWidgetItem *child3 = new QTreeWidgetItem();
    child3->setText(0, "ChildFile3");
    child3->setText(1, "child3 File Path");
    child3->setText(2, "child3 ACL");
    child3->setText(3, "child3 OWNER");
    child3->setText(4, "child3 IL");
    root->addChild(child3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//If cell in the main table was double clicked, create a new table with additional info
void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    ui->processTableWidget->setVisible(true);
    ui->processTableWidget->setRowCount(1);
    ui->processTableWidget->setColumnCount(3);
    ui->processTableWidget->setHorizontalHeaderLabels(QStringList() << "Имя процесса" << "info1" << "info2");

    ui->tableWidget->model()->index(row, 0).data().toString();
    ui->processTableWidget->setItem(0, 0, new QTableWidgetItem(tr("%1").arg(ui->tableWidget->model()->index(row, 0).data().toString())));
}

void MainWindow::on_treeWidget_itemSelectionChanged()
{
    //This show how to get content of selected item
    ui->treeWidgetSelectedItem->setVisible(true);
    ui->treeWidgetSelectedItem->setText(ui->treeWidget->currentItem()->text(0) + "<br>" +
                                        ui->treeWidget->currentItem()->text(1) + "<br>" +
                                        ui->treeWidget->currentItem()->text(2) + "<br>" +
                                        ui->treeWidget->currentItem()->text(3) + "<br>" +
                                        ui->treeWidget->currentItem()->text(4) + "<br>");
}

