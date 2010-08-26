/****************************************************************************
**
** Copyright 2009, Jaco Naude
**
** This library is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License.
**  
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**  
** You should have received a copy of the GNU General Public License
** along with this library.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "CodeEditorWidgetConfig.h"
#include "ui_CodeEditorWidgetConfig.h"

#include "QtilitiesApplication.h"
#include "QtilitiesCoreGuiConstants.h"

#include <QSettings>
#include <QFontDatabase>

using namespace Qtilities::CoreGui::Constants;

Qtilities::CoreGui::CodeEditorWidgetConfig::CodeEditorWidgetConfig(QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent),
    ui(new Ui::CodeEditorWidgetConfig)
{
    ui->setupUi(this);
    setObjectName("Text Editor Config Page");

    // Populate font sizes combo box
    QFontDatabase db;
    foreach(int size, db.standardSizes())
        ui->fontSizeComboBox->addItem(QString::number(size));

    // Populate fields with values from QSettings
    QSettings settings;
    settings.beginGroup("GUI");
    settings.beginGroup("Editors");
    settings.beginGroup("Code Editor Widget");
    ui->fontComboBox->setEditText(settings.value("font_type","Courier").toString());
    ui->fontSizeComboBox->setEditText(settings.value("font_size",10).toString());
    settings.endGroup();
    settings.endGroup();
    settings.endGroup();
}

Qtilities::CoreGui::CodeEditorWidgetConfig::~CodeEditorWidgetConfig() {
    delete ui;
}

QIcon Qtilities::CoreGui::CodeEditorWidgetConfig::configPageIcon() const {
    return QIcon();//Constants::ICON_SHORTCUTS_22x22);
}

QWidget* Qtilities::CoreGui::CodeEditorWidgetConfig::configPageWidget() {
    return this;
}

QStringList Qtilities::CoreGui::CodeEditorWidgetConfig::configPageTitle() const {
    QStringList text;
    text << tr("Code Editor");
    return text;
}

void Qtilities::CoreGui::CodeEditorWidgetConfig::configPageApply() {
    // Save fields back to QSettings
    QSettings settings;
    settings.beginGroup("GUI");
    settings.beginGroup("Editors");
    settings.beginGroup("Code Editor Widget");
    settings.setValue("font_type",ui->fontComboBox->currentText());
    settings.setValue("font_size",ui->fontSizeComboBox->currentText().toInt());
    settings.endGroup();
    settings.endGroup();
    settings.endGroup();

    // Emit the settings update request signal
    // QtilitiesApplication::newSettingsUpdateRequest(CONTEXT_CODE_EDITOR_WIDGET);
}