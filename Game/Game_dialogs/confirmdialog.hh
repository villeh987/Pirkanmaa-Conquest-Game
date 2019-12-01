#ifndef CONFIRMDIALOG_HH
#define CONFIRMDIALOG_HH

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include "Game_resourcemaps/resources.hh"

namespace Ui {
class ConfirmDialog;
}

/**
 * @class ConfirmDialog
 * @brief The ConfirmDialog class represents the confirm build window.
 * This dialog is shown, when a Player clicks to build a building.
 * In the dialog, the build cost is displayed, and confirmation is asked.
 * If Player confirms, a signal is send to MapWindow to addBuilding.
 */
class ConfirmDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Constructor for the class
     * @param parent Parent widget.
     */
    explicit ConfirmDialog(QWidget *parent = nullptr);

    /**
      * @brief Destructor
      */
    ~ConfirmDialog();


    /**
     * @brief Sets given building and it's build cost.
     * Updates dialog info text.
     * Calls setCostLabels.
     * @param building Building to be set.
     * @post Exception guarantee: None.
     */
    void setBuildingToBuild(std::shared_ptr<Course::BuildingBase>& building);

private:

    /**
     * @brief Displays buildings build cost in the dialog.
     * @post Exception guarantee: None.
     */
    void setCostLabels();

    /**
     * @brief Clears dialog cost values.
     * @post Exception guarantee: No-throw.
     */
    void clearResources();


    Ui::ConfirmDialog *ui;

    std::shared_ptr<Course::BuildingBase> building_to_build_ = nullptr;

    std::vector<QLabel*> cost_labels_ = {};
    std::vector<QLabel*> resource_labels_ = {};
    Course::ResourceMap cost_ = {};
    std::map<int, std::string> resource_types_to_int_ = {};



private slots:

    /**
     * @brief Calls clearResources and emits signal to build building.
     * @post Exception guarantee: No-throw.
     */
    void confirmBuilding();

signals:

    /**
     * @brief Signal to MapWindow to build given building.
     * @param building Building to be built.
     */
    void sendBuilding(std::shared_ptr<Course::BuildingBase> building);

};

#endif // CONFIRMDIALOG_HH
