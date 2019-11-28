#include "endgamedialog.hh"
#include "ui_endgamedialog.h"

EndGameDialog::EndGameDialog(QWidget *parent, std::shared_ptr<Game::GameEventHandler> GEHandler, std::shared_ptr<Game::ObjectManager> Objectmanager) :
    QDialog(parent),
    ui(new Ui::EndGameDialog),
    GEHandler_(GEHandler),
    Objectmanager_(Objectmanager)
{
    ui->setupUi(this);

    connect(ui->closeButton, &QPushButton::clicked, this, &EndGameDialog::reject);

    p1_labels_ = {
        ui->p1MoneyVal,
        ui->p1FoodVal,
        ui->p1WoodVal,
        ui->p1StoneVal,
        ui->p1OreVal
    };

    p2_labels_ = {
        ui->p2MoneyVal,
        ui->p2FoodVal,
        ui->p2WoodVal,
        ui->p2StoneVal,
        ui->p2OreVal
    };
}

EndGameDialog::~EndGameDialog()
{
    delete ui;
}

void EndGameDialog::setResults()
{
    ui->player1NameLabel->setText(QString::fromStdString(GEHandler_->getPlayers().at(0)->getName()));
    ui->player2NameLabel->setText(QString::fromStdString(GEHandler_->getPlayers().at(1)->getName()));

    Course::ResourceMap p1_resources = GEHandler_->getPlayers().at(0)->getResources();
    Course::ResourceMap p2_resources = GEHandler_->getPlayers().at(1)->getResources();

    int counter = 0;
    for (auto i : p1_resources) {
        p1_labels_.at(counter)->setText(QString::number(i.second));
        ++counter;
    }

    counter = 0;
    for (auto i : p2_resources) {
        p2_labels_.at(counter)->setText(QString::number(i.second));
        ++counter;
    }

    calculateWinner();

}

void EndGameDialog::calculateWinner()
{
    double player1score = 0;
    double player2score = 0;

    for (auto i : GEHandler_->getPlayers().at(0)->getResources()) {
        for (auto j : GEHandler_->getPlayers().at(1)->getResources()) {
            if ( i.first == j.first) {
                player1score = player1score + (i.second * Game::GRADING_FACTORS.at(i.first));
                player2score = player2score + (j.second * Game::GRADING_FACTORS.at(j.first));
            }
        }
    }

    ui->p1Score->display(player1score);
    ui->p2Score->display(player2score);


    QString winner;
    if (player1score > player2score) {
        winner = QString::fromStdString(GEHandler_->getPlayers().at(0)->getName());
        ui->winnerLabel->setText("The winner is: <b>"
                                 + winner
                                 + "</b>"
                                 );

    } else if (player2score > player1score){
        winner = QString::fromStdString(GEHandler_->getPlayers().at(1)->getName());
        ui->winnerLabel->setText("The winner is: <b>"
                                 + winner
                                 + "</b>"
                                 );
    } else {
        ui->winnerLabel->setText("It's a <b>tie</b>!");
    }


}
