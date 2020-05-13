#include "GlobalTypes.h"
#include "MainWindow.h"
#include <QVBoxLayout>
#include "Q3TTableWidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createWidget();
    createLayout();
    createConnection();
}

MainWindow::~MainWindow()
{

}

QSize MainWindow::sizeHint() const
{
    return QSize(600, 400);
}

void MainWindow::createWidget()
{
    //QMainWindow不能增加添加布局，所以先定义一个QWidget
    m_pMainWidget = new QWidget(this);
    //把定义的QWidget设置为当前QMainWindow的主窗口
    this->setCentralWidget(m_pMainWidget);

    m_pTableWidget = new Q3TTableWidget(AMDATATYPE_double);
    m_pTableDescLabel = new QLabel("Table description");
    int actualRowCount;
    int actualColumnCount;
    m_pTableWidget->actualRowColumnCount(actualRowCount, actualColumnCount);
    setRowColumnDescription(actualRowCount, actualColumnCount);

    showMaximized();
}

void MainWindow::createLayout()
{
    m_pMainLayout = new QVBoxLayout(m_pMainWidget);
    m_pMainLayout->addWidget(m_pTableDescLabel);
    m_pMainLayout->addWidget(m_pTableWidget);
    m_pMainWidget->setLayout(m_pMainLayout);
}

void MainWindow::createConnection()
{
    connect(m_pTableWidget, SIGNAL(actualRowColumnCountChange(int, int)), this, SLOT(setRowColumnDescription(int, int)));
}

void MainWindow::setRowColumnDescription(int actualRowCount, int actualColumnCount)
{
    QString str = QString("type:%1\n actural row: %2, actual column: %3")
                      .arg("double").arg(actualRowCount).arg(actualColumnCount);
    m_pTableDescLabel->setText(str);
}

