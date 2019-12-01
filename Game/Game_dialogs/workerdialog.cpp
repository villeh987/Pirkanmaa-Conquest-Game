#include "workerdialog.hh"
#include "ui_workerdialog.h"

WorkerDialog::WorkerDialog(QWidget *parent, QString infotext) :
    QDialog(parent),
    ui(new Ui::WorkerDialog)
{
    ui->setupUi(this);

    ui->infoLabel->setText(infotext);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
            &WorkerDialog::getWorkerType);

    connect(ui->basicWorkerRadioButton, &QRadioButton::clicked, this, &WorkerDialog::setBasicWorkerCost);
    connect(ui->minerRadioButton, &QRadioButton::clicked, this, &WorkerDialog::setMinerCost);
    connect(ui->teekkariRadioButton, &QRadioButton::clicked, this, &WorkerDialog::setTeekkariCost);

    cost_labels_ = {
            ui->moneyValLabel,
            ui->foodValLabel,
            ui->woodValLabel,
            ui->stoneValLabel,
            ui->oreValLabel
        };

    setBasicWorkerCost();

}

WorkerDialog::~WorkerDialog()
{
    delete ui;
}

void WorkerDialog::setInfoText(QString text)
{
    ui->infoLabel->setText(text);
}

void WorkerDialog::showCost(bool val)
{
    ui->costLabel->setVisible(val);

    ui->moneyLabel->setVisible(val);
    ui->foodLabel->setVisible(val);
    ui->woodLabel->setVisible(val);
    ui->stoneLabel->setVisible(val);
    ui->oreLabel->setVisible(val);

    ui->moneyValLabel->setVisible(val);
    ui->foodValLabel->setVisible(val);
    ui->woodValLabel->setVisible(val);
    ui->stoneValLabel->setVisible(val);
    ui->oreValLabel->setVisible(val);
}

void WorkerDialog::getWorkerType()
{
    if (ui->basicWorkerRadioButton->isChecked()) {
        if (ui->infoLabel->text() == "Choose worker type to free:") {
            emit sendFreeWorker("BasicWorker");
        } else {
            emit sendBuildBasicWorker();
        }
    } else if (ui->minerRadioButton->isChecked()) {
        if (ui->infoLabel->text() == "Choose worker type to free:") {
            emit sendFreeWorker("Miner");
        } else {
            emit sendBuildMiner();
        }
    }
    else {
        if (ui->infoLabel->text() == "Choose worker type to free:") {
            emit sendFreeWorker("Teekkari");
        } else {
            emit sendBuildTeekkari();
        }
    }

}

void WorkerDialog::disableAccept(bool action)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(action);
}

void WorkerDialog::setBasicWorkerCost()
{
    int counter = 0;
    for (auto i : Course::ConstResourceMaps::BW_RECRUITMENT_COST) {
        cost_labels_.at(counter)->setText(QString::number(i.second));
        ++counter;
    }
}

void WorkerDialog::setMinerCost()
{
    int counter = 0;
    for (auto i : Game::GameResourceMaps::MINER_RECRUITMENT_COST) {
        cost_labels_.at(counter)->setText(QString::number(i.second));
        ++counter;
    }
}

void WorkerDialog::setTeekkariCost()
{
    int counter = 0;
    for (auto i : Game::GameResourceMaps::TEEKKARI_RECRUITMENT_COST) {
        cost_labels_.at(counter)->setText(QString::number(i.second));
        ++counter;
    }
}
