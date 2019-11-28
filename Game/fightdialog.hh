#ifndef FIGHTDIALOG_HH
#define FIGHTDIALOG_HH

#include <QDialog>
#include <QElapsedTimer>
#include <QDebug>
#include <memory>
#include "workers/workerbase.h"
#include "core/playerbase.h"
#include <chrono>
#include <thread>
#include <QApplication>

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

    void setWagers(std::shared_ptr<Course::WorkerBase> &worker1,
                   std::shared_ptr<Course::WorkerBase> &worker2);
    void setNames(QString player1_name, QString player2_name);

private:
    Ui::FightDialog *ui;

    QElapsedTimer* timer_ = nullptr;

    QString player1_name_ = "";
    QString player2_name_ = "";

    std::shared_ptr<Course::WorkerBase> player1_wager_ = nullptr;
    std::shared_ptr<Course::WorkerBase> player2_wager_ = nullptr;


    QString winner_ = "";

    qint64 player1_result_ = 0;
    qint64 player2_result_ = 0;

    QString PLAYER1_TURN_TEXT = "";
    QString PLAYER2_TURN_TEXT = "";
    QString START_TEXT = "Time to test your reactions"
                         "in a Teekkari reaction fight!";

    QString getWinner();
    QString getLoser();
    std::shared_ptr<Course::WorkerBase> getLoserWager();
    void resetGame();
    void initReaction();
    bool disableStart();


private slots:
    void startReactionGame();

signals:
    void sendLoser(QString loser);
    void sendLoserWager(std::shared_ptr<Course::WorkerBase> wager);
};

#endif // FIGHTDIALOG_HH
