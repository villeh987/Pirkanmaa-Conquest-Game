#ifndef FIGHTDIALOG_HH
#define FIGHTDIALOG_HH

#include <QDialog>
#include <QElapsedTimer>
#include <QDebug>
#include <QApplication>
#include <memory>
#include <chrono>
#include <thread>

#include "workers/workerbase.h"
#include "core/playerbase.h"



namespace Ui {

/**
 * @class FightDialog
 * @brief The FightDialog class represents the Teekkarifight window
 * This dialog is shown, when a Player clicks Fight in the Game.
 * This class handles a simple reaction minigame called Teekkarifight.
 * In the minigame, Players take turns to see which Player has a better
 * reaction time.
 * The loser gets their Teekkari removed from the Game.
 */
class FightDialog;
}

class FightDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Constructor for the class
     * @param parent Parent widget.
     * @param player1_name Name of first Player.
     * @param player2_name Name of second Player.
     */
    explicit FightDialog(QWidget *parent = nullptr,
                         QString player1_name = "Player1",
                         QString player2_name = "Player2");

    /**
      * @brief Destructor
      */
    ~FightDialog();

    /**
     * @brief Sets given Player names to the dialog.
     * Also set info texts based on Player names.
     * @param player1_name Name of first Player.
     * @param player2_name Name of second Player.
     * @post Exception guarantee: No-throw.
     */
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

    /**
     * @brief Returns winner based on player results.
     * @return Name of winner.
     * @post Exception guarantee: No-throw.
     */
    QString getWinner();

    /**
     * @brief Returns loser based on player results.
     * @return Name of loser.
     * @post Exception guarantee: No-throw.
     */
    QString getLoser();

    /**
     * @brief Resets Teekkarifight minigame to initial state.
     * @post Exception guarantee: No-throw.
     */
    void resetGame();

    /**
     * @brief Wait for a random amount of milliseconds from
     * 1 to 10 000 milliseconds, and start timing players reaction time.
     * @post Exception guarantee: No-throw.
     */
    void initReaction();


private slots:
    /**
     * @brief Starts and handles Teekkarifight reaction minigame.
     * @post Exception guarantee: None.
     */
    void startReactionGame();

signals:

    /**
     * @brief Sends the loser's name of the Teekkarifight to MapWindow.
     */
    void sendLoser(QString loser);
};

#endif // FIGHTDIALOG_HH
