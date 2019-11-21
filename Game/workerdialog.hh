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

    void setInfoText(QString text);

private:
    Ui::WorkerDialog *ui;

private slots:
    void getWorkerType();
    void disableAccept(bool action = true);

signals:
    void sendBuildBasicWorker();
    void sendFreeWorker(std::string worker_type);
};

#endif // WORKERDIALOG_HH
