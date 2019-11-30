#ifndef WORKERDIALOG_HH
#define WORKERDIALOG_HH

#include <QDialog>
#include <QPushButton>
#include <QDebug>


namespace Ui {

/**
 * @class WorkerDialog
 * @brief The WorkerDialog class represents the window where workers are
 * assigned and removed.
 * This dialog is shown, when a Player clicks "Assign" or "Remove" in the Game.
 * The dialog asks for the type of worker to be assigned/remove on the current
 * tile.
 * A signal is emitted to MapWindow according to selected type.
 */
class WorkerDialog;
}

class WorkerDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Constructor for the class
     * @param parent Parent widget.
     * @param infotext What to display on the dialog.
     */
    explicit WorkerDialog(QWidget *parent = nullptr,
                          QString infotext = "Choose worker type:");

    /**
      * @brief Destructor
      */
    ~WorkerDialog();


    /**
     * @brief Dialog text to be given text.
     * @param text Text to be set.
     * @post Exception guarantee: No-throw.
     */
    void setInfoText(QString text);

private:
    Ui::WorkerDialog *ui;

private slots:

    /**
     * @brief Determines which type of worker is to be assigned/removed.
     * @post Exception guarantee: No-throw.
     */
    void getWorkerType();

    /**
     * @brief Disables/enables dialog button box according to given param.
     * @param action (Optional) If true, disable, if false, enable.
     * @post Exception guarantee: No-throw.
     */
    void disableAccept(bool action = true);

signals:

    /**
     * @brief Signal to build BasicWorker.
     */
    void sendBuildBasicWorker();

    /**
     * @brief Signal to build Miner.
     */
    void sendBuildMiner();

    /**
     * @brief Signal to build Teekkari.
     */
    void sendBuildTeekkari();

    /**
     * @brief Signal to free worker of given type.
     * @param worker_type Type of worker to be freed.
     */
    void sendFreeWorker(std::string worker_type);
};

#endif // WORKERDIALOG_HH
