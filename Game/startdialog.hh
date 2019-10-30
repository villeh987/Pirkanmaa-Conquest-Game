#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include <QDialog>
#include <QTextStream>
#include <QFile>
#include <QDebug>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = nullptr);
    ~StartDialog();

private slots:
    void loadGame();
    void getFileName();
    void getFileData();

private:
    Ui::StartDialog *ui;

    QString file_to_load_ = "";
    QString file_data_ = "";


};

#endif // STARTDIALOG_HH
