#include "buildingdialog.hh"
#include "ui_buildingdialog.h"

BuildingDialog::BuildingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuildingDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &BuildingDialog::getBuildingType);

    ui_radio_buttons_ = {
        ui->hqRadioButton,
        ui->outpostRadioButton,
        ui->farmRadioButton,
        ui->mineRadioButton,
        ui->tuniTowerRadioButton
    };
}

BuildingDialog::~BuildingDialog()
{
    delete ui;
}

void BuildingDialog::setTileBuildings(std::vector<std::shared_ptr<Course::BuildingBase>> buildings)
{
    tile_buildings_ = buildings;
}

void BuildingDialog::getBuildingType()
{
    for (auto i : ui_radio_buttons_) {
        for (auto j : tile_buildings_) {
            if ( i->isChecked() && (i->text() == QString::fromStdString(j->getType())) ) {
                emit sendRemoveBuilding(j);
            }
        }
    }
}
