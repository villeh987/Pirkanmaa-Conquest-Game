#include "startdialog.hh"
#include "ui_startdialog.h"



StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);

    connect(ui->startDialogNewButton, &QPushButton::clicked, this, &StartDialog::startGame);
    connect(ui->startDialogLoadButton, &QPushButton::clicked, this, &StartDialog::loadGame);

    connect(ui->loadFileEntry, &QLineEdit::editingFinished, this, &StartDialog::getFileName);

    // Hide
    ui->loadFileEntry->setVisible(false);
    ui->startDialogNameEntry1->setVisible(false);
    ui->startDialogNameEntry2->setVisible(false);
    ui->startDialogPlayer1Label->setVisible(false);
    ui->startDialogPlayer2Label->setVisible(false);
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::startGame()
{
    if (ui->startDialogNewButton->text() == "Cancel") {
        ui->loadFileEntry->setVisible(false);
        ui->startDialogLoadButton->setText("Load Game");
        ui->startDialogNewButton->setText("New Game");
        ui->startDialogInfoLabel->setText("Start/Load game:");
        game_loaded_ = false;
        qDebug() << "Game_loaded set to:" << game_loaded_;

    } else if (game_loaded_) {
        // Send save file data to mainwindow
        emit sendLoadData(file_data_);
        acceptDialog();

    } else if (ui->startDialogNewButton->text() == "Start Game") {
        // Send player names to mainwindow and
        QString player1 = ui->startDialogNameEntry1->text();
        QString player2 = ui->startDialogNameEntry2->text();
        if (player1 == "" || player2 == "") {
            ui->startDialogInfoLabel->setText("Name cannot be empty!");

        } else {

            QList<QString> player_names = {player1, player2};
            emit sendNames(player_names);
            acceptDialog();
        }

    } else {
        // Ask for player names, show correct widgets

        // Change label to "Start Game" and "Cancel"
        ui->startDialogNewButton->setText("Start Game");
        ui->startDialogLoadButton->setText("Cancel");


        // Move start and "cancel" button a bit down
        ui->startDialogNewButton->setGeometry(65, 230, 100, 40);
        ui->startDialogLoadButton->setGeometry(235, 230, 100, 40);


        ui->startDialogInfoLabel->setText("Enter player names:");

        ui->startDialogNameEntry1->setVisible(true);
        ui->startDialogNameEntry2->setVisible(true);
        ui->startDialogPlayer1Label->setVisible(true);
        ui->startDialogPlayer2Label->setVisible(true);



    }
}

void StartDialog::loadGame()
{
    if (ui->startDialogLoadButton->text() == "Load Game") {
        ui->startDialogInfoLabel->setText("Enter name of file to load:");

        ui->startDialogLoadButton->setText("Load");
        ui->startDialogNewButton->setText("Cancel");

        ui->loadFileEntry->setVisible(true);


    } else if (ui->startDialogLoadButton->text() == "Load") {
        getFileData();

    } else if (ui->startDialogLoadButton->text() == "Cancel") {
        // Cancel name selection "window"

        ui->startDialogLoadButton->setText("Load Game");
        ui->startDialogNewButton->setText("New Game");
        ui->startDialogInfoLabel->setText("Start/Load game:");

        ui->startDialogNewButton->setGeometry(60, 150, 121, 51);
        ui->startDialogLoadButton->setGeometry(230, 150, 121, 51);

        ui->startDialogNameEntry1->setVisible(false);
        ui->startDialogNameEntry2->setVisible(false);
        ui->startDialogPlayer1Label->setVisible(false);
        ui->startDialogPlayer2Label->setVisible(false);
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
           game_loaded_ = true;
           qDebug() << "Game_loaded set to:" << game_loaded_;


           file.close();
       } else {
            ui->startDialogInfoLabel->setText("File not found.");
       }


}

void StartDialog::acceptDialog()
{
    if (ui->startDialogNewButton->text() != "Cancel") {
        StartDialog::accept();
    }
}

