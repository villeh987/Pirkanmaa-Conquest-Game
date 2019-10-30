#include "startdialog.hh"
#include "ui_startdialog.h"



StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);

    connect(ui->startDialogNewButton, &QPushButton::clicked, this, &StartDialog::accept);
    connect(ui->startDialogLoadButton, &QPushButton::clicked, this, &StartDialog::loadGame);

    connect(ui->loadFileEntry, &QLineEdit::editingFinished, this, &StartDialog::getFileName);

    // Hide
    ui->loadFileEntry->setVisible(false);
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::loadGame()
{
    if (ui->startDialogLoadButton->text() == "Load Game") {
        ui->startDialogInfoLabel->setText("Enter name of file to load:");

        ui->startDialogLoadButton->setText("Load");
        ui->startDialogNewButton->setText("Cancel");

        ui->loadFileEntry->setVisible(true);
        //ui->startDialogLoadButton->setDisabled(true);
    } else if (ui->startDialogLoadButton->text() == "Load") {
        getFileData();
    }


}

void StartDialog::getFileName()
{
    file_to_load_ = ui->loadFileEntry->text();
}

void StartDialog::getFileData()
{

    QFile file(file_to_load_);

       if (file.exists()) {

           file.open(QIODevice::ReadWrite);

           QTextStream in (&file);

           file_data_ = in.readAll();
           ui->startDialogInfoLabel->setText("Game loaded succesfully!");
           ui->loadFileEntry->setVisible(false);
           ui->startDialogNewButton->setText("Start Game");
           ui->startDialogLoadButton->setText("Load Game");


           file.close();
       } else {
            ui->startDialogInfoLabel->setText("File not found.");
       }


}
