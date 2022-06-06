#include "SettingsView.h"
#include "ui_SettingsView.h"

SettingsView::SettingsView(Settings_t* settings,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsView),
    _settingsInfo(settings)
{
    ui->setupUi(this);
    initUIbySettings();
}

SettingsView::~SettingsView()
{
    delete ui;
}

void SettingsView::on_SettingsButtonColorEdge_clicked()
{
    QColor color=QColorDialog::getColor();
    if(color.isValid()){
        _settingsInfo->_edgesColor = color;
        std::string red_str=std::to_string(_settingsInfo->_edgesColor.red());
        std::string green_str=std::to_string(_settingsInfo->_edgesColor.green());
        std::string blue_str=std::to_string(_settingsInfo->_edgesColor.blue());
        ui->SettingColorEdgesCurrent->setStyleSheet(QString::fromUtf8("background-color: rgb("+red_str+","+green_str+","+blue_str+");"));
    }
//    this->show();
    emit updateImage();
    this->activateWindow();
    this->raise();
    this->setFocus();
}

void SettingsView::on_SettingButtonColorVer_clicked()
{
    QColor color=QColorDialog::getColor();
    if(color.isValid()){
        _settingsInfo->_verticesColor = color;
        std::string red_str=std::to_string(_settingsInfo->_verticesColor.red());
        std::string green_str=std::to_string(_settingsInfo->_verticesColor.green());
        std::string blue_str=std::to_string(_settingsInfo->_verticesColor.blue());
        ui->SettingColorVerticesCurrent->setStyleSheet(QString::fromUtf8("background-color: rgb("+red_str+","+green_str+","+blue_str+");"));
    }
    emit updateImage();
//    this->show();
    this->activateWindow();
    this->raise();
    this->setFocus();
}

void SettingsView::on_SettingsButtonColorBack_clicked()
{
    QColor color=QColorDialog::getColor();
    if(color.isValid()){
        _settingsInfo->_backColor = color;
        std::string red_str=std::to_string(_settingsInfo->_backColor.red());
        std::string green_str=std::to_string(_settingsInfo->_backColor.green());
        std::string blue_str=std::to_string(_settingsInfo->_backColor.blue());
        ui->SettingColorBackCurrent->setStyleSheet(QString::fromUtf8("background-color: rgb("+red_str+","+green_str+","+blue_str+");"));
    }
    emit updateImage();
    this->activateWindow();
    this->raise();
    this->setFocus();
}

void SettingsView::saveSettingsByConf() {
    // В ТАКОМ ФОРМАТЕ НЕ ВИДИТ ФАЙЛ
//    QFile f(":/SettingsFiles/set_curr.conf");
    QFile f("./setting_current.conf");
    if (f.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "OPEN";
        QTextStream file(&f);
// edges color
        file << _settingsInfo->_edgesColor.name(QColor::HexArgb) << "\n";
// edges thickness
        file << ui->SettingsButtonThickness->text() << "\n";
// edges type
        if (ui->SettinngsButtonType->currentIndex() == 0) {
            file << "0" << "\n";
        } else if (ui->SettinngsButtonType->currentIndex() == 1) {
            file << "1" << "\n";
        }
// vertices color
        file << _settingsInfo->_verticesColor.name(QColor::HexArgb) << "\n";
// vertices size
        file << ui->SettingsButtonSize->text() << "\n";
// vertices shape
        if (ui->SettingsButtonShape->currentIndex() == 0) {
            file << "0" << "\n";
        } else if (ui->SettingsButtonShape->currentIndex() == 1) {
            file << "1" << "\n";
        } else if (ui->SettingsButtonShape->currentIndex() == 2) {
            file << "2" << "\n";
        }
// projection type
        if (ui->SettingsButtonProjectionType->currentIndex() == 0) {
            file << "0" << "\n";
        } else if (ui->SettingsButtonProjectionType->currentIndex() == 1) {
            file << "1" << "\n";
        }
// back color
        file << _settingsInfo->_backColor.name(QColor::HexArgb) << "\n";

        f.close();
    } else {
        qDebug() << "FAIL";
    }
}

void SettingsView::initUIbySettings() {
// edges color
    if(_settingsInfo->_edgesColor.isValid()){
        std::string red_str=std::to_string(_settingsInfo->_edgesColor.red());
        std::string green_str=std::to_string(_settingsInfo->_edgesColor.green());
        std::string blue_str=std::to_string(_settingsInfo->_edgesColor.blue());
        ui->SettingColorEdgesCurrent->setStyleSheet(QString::fromUtf8("background-color: rgb("+red_str+","+green_str+","+blue_str+");"));
    }
// edges thickness
    ui->SettingsButtonThickness->setValue(_settingsInfo->_edgesThickness);
// edges type
    if (_settingsInfo->_edgesType == EdgesType::SOLID) {
        ui->SettinngsButtonType->setCurrentIndex(0);
    } else if (_settingsInfo->_edgesType == EdgesType::SHADED) {
        ui->SettinngsButtonType->setCurrentIndex(1);
    }
// vertices color
    if(_settingsInfo->_verticesColor.isValid()){
        std::string red_str=std::to_string(_settingsInfo->_verticesColor.red());
        std::string green_str=std::to_string(_settingsInfo->_verticesColor.green());
        std::string blue_str=std::to_string(_settingsInfo->_verticesColor.blue());
        ui->SettingColorVerticesCurrent->setStyleSheet(QString::fromUtf8("background-color: rgb("+red_str+","+green_str+","+blue_str+");"));
    }
// vertices size
    ui->SettingsButtonSize->setValue(_settingsInfo->_verticesSize);
// vertices shape
    if (_settingsInfo->_verticesShape == VerticesShape::NONE) {
        ui->SettingsButtonShape->setCurrentIndex(0);
    } else if (_settingsInfo->_verticesShape == VerticesShape::CIRCLE) {
        ui->SettingsButtonShape->setCurrentIndex(1);
    } else if (_settingsInfo->_verticesShape == VerticesShape::SQUARE) {
        ui->SettingsButtonShape->setCurrentIndex(2);
    }
// projection type
    if (_settingsInfo->_projectionType == ProjectionType::PARALLEL) {
        ui->SettingsButtonProjectionType->setCurrentIndex(0);
    } else if (_settingsInfo->_projectionType == ProjectionType::CENTRAL) {
        ui->SettingsButtonProjectionType->setCurrentIndex(1);
    }
// background color
    if(_settingsInfo->_backColor.isValid()){
        std::string red_str=std::to_string(_settingsInfo->_backColor.red());
        std::string green_str=std::to_string(_settingsInfo->_backColor.green());
        std::string blue_str=std::to_string(_settingsInfo->_backColor.blue());
        ui->SettingColorBackCurrent->setStyleSheet(QString::fromUtf8("background-color: rgb("+red_str+","+green_str+","+blue_str+");"));
    }
}

void SettingsView::on_SettingsButtonReset_clicked()
{
    //initByDefaultConf();
    _settingsInfo->initByFileConf(FileType::DEFAULT);
    initUIbySettings();
    emit updateImage();
}


void SettingsView::on_SettingsButtonOK_clicked()
{
    saveSettingsByConf();
    _settingsInfo->initByFileConf(FileType::CUSTOM);
}


void SettingsView::on_SettingsButtonThickness_valueChanged(int arg1)
{
    _settingsInfo->_edgesThickness=arg1;
    emit updateImage();
}


void SettingsView::on_SettingsButtonSize_valueChanged(int arg1)
{
    _settingsInfo->_verticesSize = arg1;
    emit updateImage();
}


void SettingsView::on_SettingsButtonShape_currentIndexChanged(int index)
{
    _settingsInfo->_verticesShape = index==0?VerticesShape::NONE:
                                    index==1?VerticesShape::CIRCLE:VerticesShape::SQUARE;
    emit updateImage();
}


void SettingsView::on_SettinngsButtonType_currentIndexChanged(int index)
{
    _settingsInfo->_edgesType = index==0?EdgesType::SOLID :EdgesType::SHADED;
    emit updateImage();
}


void SettingsView::closeEvent(QCloseEvent* e)
{
    _settingsInfo->initByFileConf(FileType::CUSTOM);
    initUIbySettings();
    emit updateImage();
    e->accept();
}

