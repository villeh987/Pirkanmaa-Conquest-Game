#include "fightdialog.hh"
#include "ui_fightdialog.h"

FightDialog::FightDialog(QWidget *parent,
                         QString player1_name,
                         QString player2_name) :
    QDialog(parent),
    ui(new Ui::FightDialog),
    player1_name_(player1_name),
    player2_name_(player2_name)
{
    ui->setupUi(this);

    timer_ = new QElapsedTimer;

    connect(ui->startButton, &QPushButton::clicked, this, &FightDialog::startReactionGame);
}

FightDialog::~FightDialog()
{
    delete ui;
}

void FightDialog::setWagers(std::shared_ptr<Course::WorkerBase> &worker1, std::shared_ptr<Course::WorkerBase> &worker2)
{
    player1_wager_ = worker1;
    player2_wager_ = worker2;
}

void FightDialog::setNames(QString player1_name, QString player2_name)
{
    player1_name_ = player1_name;
    player2_name_ = player2_name;

    PLAYER1_TURN_TEXT = "Player <b>" + player1_name_ + "</b> goes first:";
    PLAYER2_TURN_TEXT = "Now it's <b>" + player2_name_ + "</b>'s turn:";
}

QString FightDialog::getWinner()
{
    if (player1_result_ < player2_result_) {
        winner_ = player1_name_;
    } else {
        winner_ = player2_name_;
    }

    return winner_;
}

QString FightDialog::getLoser()
{
    if (player1_result_ < player2_result_) {
        return player2_name_;
    } else {
        return player1_name_;
    }
}

std::shared_ptr<Course::WorkerBase> FightDialog::getLoserWager()
{
    if (player1_result_ < player2_result_) {
        if (player1_name_ == QString::fromStdString(player1_wager_->getOwner()->getName())) {
            return player2_wager_;
        } else {
            return player1_wager_;
        }

    } else {
        if (player1_name_ == QString::fromStdString(player1_wager_->getOwner()->getName())) {
            return player1_wager_;
        } else {
            return player2_wager_;
        }
    }
    return nullptr;
}

void FightDialog::resetGame()
{
    ui->infoLabel->setText(START_TEXT);
    ui->startButton->setText("Begin");
    ui->resultLabel->setText("");
    winner_ = "";
    player1_result_ = 0;
    player2_result_ = 0;

}

void FightDialog::startReactionGame()
{
    if (ui->startButton->text() == "Start") {
        timer_->restart();
        ui->startButton->setText("Stop");

    } else if (ui->startButton->text() == "Stop") {
        if (ui->infoLabel->text() == PLAYER1_TURN_TEXT) {
            player1_result_ = timer_->elapsed();
            ui->startButton->setText("Start");
            ui->infoLabel->setText(PLAYER2_TURN_TEXT);
        } else {
            player2_result_ = timer_->elapsed();
            ui->infoLabel->setText("The winner is player <b>" + getWinner() + "</b>!");

            ui->resultLabel->setText("<b>" + player1_name_
                                     + "</b>'s score: "
                                     + QString::number(player1_result_)
                                     + "ms, <b>"
                                     + player2_name_
                                     + "</b>'s score: "
                                     + QString::number(player2_result_)
                                     + "ms."
                                     );

            ui->startButton->setText("Close");
        }
    } else if (ui->startButton->text() == "Close") {
        //emit sendLoser(getLoser());
        qDebug() << "Send wager from:" << QString::fromStdString(getLoserWager()->getOwner()->getName());
        emit sendLoserWager(getLoserWager());

        resetGame();
        FightDialog::accept();

    } else {
        ui->infoLabel->setText(PLAYER1_TURN_TEXT);
        ui->startButton->setText("Start");
    }
}
