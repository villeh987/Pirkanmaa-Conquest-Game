#include "workerdialog.hh"
#include "ui_workerdialog.h"

WorkerDialog::WorkerDialog(QWidget *parent, QString infotext) :
    QDialog(parent),
    ui(new Ui::WorkerDialog)
{
    ui->setupUi(this);

    ui->infoLabel->setText(infotext);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &WorkerDialog::getWorkerType);

}

WorkerDialog::~WorkerDialog()
{
    delete ui;
}

void WorkerDialog::setInfoText(QString text)
{
    ui->infoLabel->setText(text);
}

void WorkerDialog::getWorkerType()
{
    if (ui->basicWorkerRadioButton->isChecked()) {
        if (ui->infoLabel->text() == "Choose worker type to free:") {
            emit sendFreeWorker("BasicWorker");
        } else {
            qDebug() << "Lähtee:";
            emit sendBuildBasicWorker();
        }

    }

}

void WorkerDialog::disableAccept(bool action)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(action);
}
