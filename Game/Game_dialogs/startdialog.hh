#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include <QDialog>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QColorDialog>

namespace Ui {

/**
 * @class StartDialog
 * @brief The StartDialog class represents the starting window.
 * This dialog is shown, when the Game is started.
 * In the dialog, players give their names and colors.
 * Color selection is done using QColorDialog.
 * After that, the Game may be started.
 *
 * @note Load Game has NOT been implemented!
 */
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Constructor for the class
     * @param parent Parent widget.
     */
    explicit StartDialog(QWidget *parent = nullptr);

    /**
      * @brief Destructor
      */
    ~StartDialog();

private slots:

    /**
     * @brief Starts the Game. Multiple signals are connected to this slots.
     * Depending on what button is shown in UI, does different actions.
     * @post Exception guarantee: None.
     */
    void startGame();

    /**
     * @brief Loads the Game.
     *
     * @note NOT IMPLEMENTED!
     */
    void loadGame();

    /**
     * @brief Gets user entered filename.
     * @post Exception guarantee: No-throw.
     */
    void getFileName();

    /**
     * @brief Loads the file data from file.
     * @post Exception guarantee: None.
     */
    void getFileData();

    /**
     * @brief Accepts the dialog.
     * @post Exception guarantee: No-throw.
     */
    void acceptDialog();

private:

    /**
     * @brief Sets player colors by using QColorDialog.
     * @post Exception guarantee: No-throw.
     */
    void getPlayerColor();

    /**
     * @brief Shows current selected player color in a preview box.
     * @param button Button on which the color is displayed.
     * @param color Color to be displayed.
     * @post Exception guarantee: No-throw.
     */
    void displaySelectedColor(QPushButton *button, QColor color);

    Ui::StartDialog *ui;

    QColorDialog* color_dialog_ = nullptr;

    QString file_to_load_ = "";
    QString file_data_ = "";
    QColor player1_color_ = QColor(255, 255, 51);
    QColor player2_color_ = QColor(255, 51, 255);

    bool game_loaded_ = false;

signals:

    /**
     * @brief Sends Player names and colors to MapWindow.
     * @param names List of Player names.
     * @param colors List of Player colors.
     */
    void sendNamesAndColors(QList<QString> names, QList<QColor> colors);

    /**
     * @brief Sends loaded file data to MapWindow.
     * @param data Data to send.
     */
    void sendLoadData(QString data);

    /**
     * @brief Sends only Player colors to MapWindow.
     *
     * @note This would have been needed in gase Load Game.
     * @param colors List of Player colors.
     */
    void sendColors(QList<QColor> colors);



};

#endif // STARTDIALOG_HH
