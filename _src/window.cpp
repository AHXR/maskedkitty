/*
    @title
        maskedkitty
    @author
        AHXR (https://github.com/AHXR)
    @copyright
        2018

    maskedkitty is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    maskedkitty is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with maskedkitty.  If not, see <http://www.gnu.org/licenses/>.
*/
//=======================================================
#include    "window.h"
#include    "ui_window.h"
#include    "file_pump.h"
#include    <fstream>
#include    <QProcess>

bool        b_file_opened;
QString     qs_file_path;
QString     qs_icon_path;
QString     qs_pump;
char        c_tmp[ 516 ];

#define     MAX_PATH 260

using namespace std;

// QString to const char *
#define qstr_char toStdString().c_str()

window::window(QWidget *parent) : QMainWindow(parent), ui(new Ui::window) {
    ui->setupUi(this);

    // Presetting the File Pumper listbox.
    QStringList qstr_list;

    // fileSizes -> filepump.h
    for( unsigned short us = 0; us < MAX_FILE_SIZES; us ++)
        qstr_list += (QStringList() << fileSizes[ us ]);

    ui->lstTypes->addItems( qstr_list );
}

window::~window() {
    delete ui;
}

void window::on_btnOpen_pressed() {
    // Creating the open file dialog and setting the textbox.
    qs_file_path = QFileDialog::getOpenFileName( this, tr("Open .EXE File"), NULL, tr("Executable Files (*.exe)"));
    ui->txtFile->setText( qs_file_path );

    // Enabling the build button
    b_file_opened = true;
}

void window::on_btnOpenIcon_pressed() {
    // Creating the open file dialog and setting the textbox.
    qs_icon_path = QFileDialog::getOpenFileName( this, tr("Open .ico File"), NULL, tr("Icon Files (*.ico)"));
    ui->txtIconFile->setText( qs_icon_path );
}

void window::on_btnBuild_pressed() {
    QMessageBox qmb_output; // Used for error dialog.

    if( b_file_opened ) {

        // Icon Changer
        if( ui->chkEnableChanger->isChecked() ) {
            ui->lblStatus->setText("Injecting Icon...");

            QProcess * qp_icon = new QProcess( this );
            qp_icon->start( "iconinjector.exe", QStringList() << qs_file_path << qs_icon_path );

            ui->lblStatus->setText("Icon changed");
        }

        // Extension Spoofer
        if( ui->chkEnable->isChecked() ) {
            ui->lblStatus->setText("Spoofing...");

            char c_file[ MAX_PATH ];
            QString qs_new_path;

            qs_new_path = qs_file_path;
            qs_new_path.replace( ".exe", ui->txtExtension->text() );

            strcpy( c_file, qs_new_path.qstr_char );
            strcat( c_file, ".exe");

            rename( qs_file_path.qstr_char, c_file );
            qs_file_path = c_file;
            ui->lblStatus->setText("Spoofing completed");
        }

        // File pumper.
        if( ui->spnAmount->value() > 0 ) {
            ui->lblStatus->setText("Pumping file...");

            long long l_file_dest = generateEstimation( c_tmp, qs_file_path.qstr_char, qs_pump.qstr_char, ui->spnAmount->value() );
            long long l_file_size = getFileSize( qs_file_path.qstr_char );

            fstream f_pumper( qs_file_path.qstr_char, ios::app | ios::binary );

            while( l_file_size < l_file_dest ) {
                f_pumper << 0;
                l_file_size ++;
            }
            f_pumper.close();
            ui->lblStatus->setText("Pumping completed");
        }
   }
   else
        qmb_output.critical( NULL, "ERROR", "Please open an executable file (.exe)" );
}

void window::on_spnAmount_valueChanged(int arg1) {
    updateEstimate(arg1);
}

void window::on_lstTypes_itemSelectionChanged() {
    ui->spnAmount->setReadOnly( false );
    qs_pump = ui->lstTypes->currentItem()->text();
    updateEstimate(ui->spnAmount->value());
}

void window::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void window::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}
