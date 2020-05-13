#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QVBoxLayout;
QT_END_NAMESPACE

class Q3TTableWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    QSize sizeHint() const override;

private Q_SLOTS:
    void setRowColumnDescription(int actualRowCount, int actualColumnCount);

public:
    void createWidget();
    void createLayout();
    void createConnection();

private:
    QWidget *m_pMainWidget;
    QLabel* m_pTableDescLabel;
    QVBoxLayout *m_pMainLayout;
    Q3TTableWidget *m_pTableWidget;
};

#endif // MAINWINDOW_H
