#ifndef BUILDINGDIALOG_HH
#define BUILDINGDIALOG_HH

#include <QDialog>
#include <QPushButton>
#include <QRadioButton>
#include <QDebug>
#include <vector>
#include <memory>

#include "buildings/buildingbase.h"

namespace Ui {

/**
 * @class BuildingDialog
 * @brief The BuildingDialog class represents the BuildingDialog window
 * This dialog is shown, when a Player clicks Destroy in the Game.
 * This class prepares the removal of opponent's bulding with his Teekkari.
 * Selected type of building is removed by emitting a signal to MapWindow.
 */
class BuildingDialog;
}

class BuildingDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the class
     * @param parent Parent widget.
     */
    explicit BuildingDialog(QWidget *parent = nullptr);

    /**
      * @brief Destructor
      */
    ~BuildingDialog();

    /**
     * @brief Adds possible buildings to be destroyed from MapWindow.
     * @param buildings Buildings that are available to be
     * removed on current tile.
     * @post Exception guarantee: No-throw.
     */
    void setTileBuildings(std::vector<std::shared_ptr<Course::BuildingBase>> buildings);

private:
    Ui::BuildingDialog *ui;
    std::vector<std::shared_ptr<Course::BuildingBase>> tile_buildings_ = {};
    std::vector<QRadioButton*> ui_radio_buttons_ = {};

private slots:

    /**
     * @brief Determines which building will be set to be destroyed.
     * Emits a signal with the building to be destroyed.
     * @post Exception guarantee: No-throw.
     */
    void getBuildingType();

signals:

    /**
     * @brief Sens building to be destroyed to MapWindow.
     * @param building Building to be destroyed.
     */
    void sendRemoveBuilding(std::shared_ptr<Course::BuildingBase> building);
};

#endif // BUILDINGDIALOG_HH
