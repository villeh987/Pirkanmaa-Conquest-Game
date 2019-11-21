#ifndef WORKERDIALOG_HH
#define WORKERDIALOG_HH

#include <QDialog>
#include <QPushButton>
#include <QDebug>


namespace Ui {
class WorkerDialog;
}

class WorkerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WorkerDialog(QWidget *parent = nullptr, QString infotext = "Choose worker type:");
    ~WorkerDialog();

private:
    Ui::WorkerDialog *ui;

private slots:
    void getWorkerType();
    void disableAccept(bool action = true);

signals:
    void sendBuildBasicWorker();
};

#endif // WORKERDIALOG_HH
