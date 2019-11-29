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
class EndGameDialog;
}

class EndGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndGameDialog(QWidget *parent = nullptr,
                           std::shared_ptr<Game::GameEventHandler> GEHandler = nullptr,
                           std::shared_ptr<Game::ObjectManager> Objectmanager = nullptr);
    ~EndGameDialog();

    void setResults();

private:
    Ui::EndGameDialog *ui;

    std::shared_ptr<Game::GameEventHandler> GEHandler_;
    std::shared_ptr<Game::ObjectManager> Objectmanager_;
    std::vector<QLabel*> p1_labels_ = {};
    std::vector<QLabel*> p2_labels_ = {};

    void calculateWinner();
};

#endif // ENDGAMEDIALOG_HH
