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
    PLAYER1_TURN_TEXT = "Player <b>" + player1_name_ + "</b> goes first:";
    PLAYER2_TURN_TEXT = "Now it's <b>" + player2_name_ + "</b>'s turn:";

    timer_ = new QElapsedTimer;

    connect(ui->startButton, &QPushButton::clicked, this, &FightDialog::startReactionGame);
}

FightDialog::~FightDialog()
{
    delete ui;
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

void FightDialog::resetGame()
{
    ui->infoLabel->setText("");
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
        FightDialog::accept();
        emit sendWinner(winner_);

    } else {
        ui->infoLabel->setText(PLAYER1_TURN_TEXT);
        ui->startButton->setText("Start");
    }
}
