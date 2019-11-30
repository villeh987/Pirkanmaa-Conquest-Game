#ifndef ENDGAMEDIALOG_HH
#define ENDGAMEDIALOG_HH

#include <QDialog>
#include <QLabel>
#include <QDebug>

#include "player.hh"
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "constants.hh"

namespace Ui {

/**
 * @class EndGameDialog
 * @brief The EndGameDialog class represents a dialog that is
 * presented when the Game ends.
 * This dialog is shown, when MAX_ROUNDS limit is reached.
 * This class shows the Player's final resources and calculates final scores.
 * Winner of the game is calculated based on the final scores.
 */
class EndGameDialog;
}

class EndGameDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Constructor for the class
     * @param parent Parent widget.
     * @param GEHandler GameEventHandler
     * @param Objectmanager Objectmanager
     */
    explicit EndGameDialog(QWidget *parent = nullptr,
                           std::shared_ptr<Game::GameEventHandler> GEHandler = nullptr,
                           std::shared_ptr<Game::ObjectManager> Objectmanager = nullptr);

    /**
      * @brief Destructor
      */
    ~EndGameDialog();

    /**
     * @brief Displays Player's final resources in the dialog UI.
     * Calls calculatewinner to determine who won the Game.
     * @post Exception guarantee: None.
     */
    void setResults();

private:
    Ui::EndGameDialog *ui;

    std::shared_ptr<Game::GameEventHandler> GEHandler_;
    std::shared_ptr<Game::ObjectManager> Objectmanager_;
    std::vector<QLabel*> p1_labels_ = {};
    std::vector<QLabel*> p2_labels_ = {};

    /**
     * @brief Calculates Player's scores based on GRADING_FACTORS.
     * Displays Player's final scores in the dialog UI.
     * Displays winner based on final scores in the UI.
     * @post Exception guarantee: None.
     */
    void calculateWinner();
};

#endif // ENDGAMEDIALOG_HH
