#include "confirmdialog.hh"
#include "ui_confirmdialog.h"

ConfirmDialog::ConfirmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
            &ConfirmDialog::confirmBuilding);

    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &ConfirmDialog::clearResources);
    connect(this, &ConfirmDialog::rejected, this, &ConfirmDialog::clearResources);

    cost_labels_ = {
            ui->moneyValLabel,
            ui->foodValLabel,
            ui->woodValLabel,
            ui->stoneValLabel,
            ui->oreValLabel
        };

    resource_labels_ = {
        ui->moneyLabel,
        ui->foodLabel,
        ui->woodLabel,
        ui->stoneLabel,
        ui->oreLabel
    };

    resource_types_to_int_ = {
        {1, "Money"},
        {2, "Food"},
        {3, "Wood"},
        {4, "Stone"},
        {5, "Ore"}
    };
}

ConfirmDialog::~ConfirmDialog()
{
    delete ui;
}

void ConfirmDialog::setBuildingToBuild(std::shared_ptr<Course::BuildingBase> &building)
{
    building_to_build_ = building;

    cost_ = building_to_build_->BUILD_COST;

    ui->infoLabel->setText("Are you sure that you want to build a <b>"
                           + QString::fromStdString(building->getType())
                           + "</b>?"
                           );

    setCostLabels();
}

void ConfirmDialog::setCostLabels()
{

    int counter = 0;
    for (auto i : resource_labels_) {

        for (auto j : cost_) {

            if (i->text() == QString::fromStdString(resource_types_to_int_.at(j.first))) {
                cost_labels_.at(counter)->setText(QString::number(j.second));
            }
        }
        ++counter;
    }
}

void ConfirmDialog::clearResources()
{
    for (auto i : cost_labels_) {
        i->setText(QString::number(0));
    }
}

void ConfirmDialog::confirmBuilding()
{
    clearResources();
    emit sendBuilding(building_to_build_);
}
