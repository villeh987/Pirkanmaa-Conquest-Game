#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include <QDialog>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QColorDialog>

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
    void startGame();
    void loadGame();
    void getFileName();
    void getFileData();
    void acceptDialog();

signals:
    void sendNamesAndColors(QList<QString> names, QList<QColor> colors);
    void sendLoadData(QString data);
    void sendColors(QList<QColor> colors);


private:
    void getPlayerColor();
    void displaySelectedColor(QPushButton *button, QColor color);
    Ui::StartDialog *ui;

    QColorDialog* color_dialog_ = nullptr;

    QString file_to_load_ = "";
    QString file_data_ = "";
    QColor player1_color_ = QColor(Qt::black);
    QColor player2_color_ = QColor(Qt::black);

    bool game_loaded_ = false;



};

#endif // STARTDIALOG_HH
