#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ReadFile();

private slots:
    void on_Save_clicked();
    void on_Remove_clicked();
    void on_Paste_clicked();
    void on_Run_clicked();
    void on_lineEdit_returnPressed();
    void on_connect_clicked();


private:
    Ui::MainWindow *ui;
    QTcpSocket* socket;
    QByteArray Data;
    void SendToServer(QString str);
public slots:
    void slotReadyRead();
};
#endif // MAINWINDOW_H
