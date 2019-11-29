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
class BuildingDialog;
}

class BuildingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuildingDialog(QWidget *parent = nullptr);
    ~BuildingDialog();

    void setInfoText(QString text);
    void setTileBuildings(std::vector<std::shared_ptr<Course::BuildingBase>> buildings);

private:
    Ui::BuildingDialog *ui;
    std::vector<std::shared_ptr<Course::BuildingBase>> tile_buildings_ = {};
    std::vector<QRadioButton*> ui_radio_buttons_ = {};

private slots:
    void getBuildingType();

signals:
    void sendRemoveBuilding(std::shared_ptr<Course::BuildingBase> building);
};

#endif // BUILDINGDIALOG_HH
