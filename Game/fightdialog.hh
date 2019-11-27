#ifndef FIGHTDIALOG_HH
#define FIGHTDIALOG_HH

#include <QDialog>
#include <QElapsedTimer>

namespace Ui {
class FightDialog;
}

class FightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FightDialog(QWidget *parent = nullptr,
                         QString player1_name = "Player1",
                         QString player2_name = "Player2");
    ~FightDialog();

private:
    Ui::FightDialog *ui;

    QElapsedTimer* timer_ = nullptr;

    QString player1_name_ = "";
    QString player2_name_ = "";

    QString winner_ = "";

    qint64 player1_result_ = 0;
    qint64 player2_result_ = 0;

    QString PLAYER1_TURN_TEXT = "";
    QString PLAYER2_TURN_TEXT = "";

    QString getWinner();
    void resetGame();


private slots:
    void startReactionGame();

signals:
    void sendWinner(QString winner_);
};

#endif // FIGHTDIALOG_HH
