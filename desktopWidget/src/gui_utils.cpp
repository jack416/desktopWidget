/****************************************************************************
** Copyright (c) 2019 Evgeny Teterin (nayk) <sutcedortal@gmail.com>
** All right reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
#include <QApplication>
#include <QScreen>
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QSpacerItem>

#include "AppCore"
#include "gui_utils.h"

namespace gui_utils { // =======================================================

//==============================================================================
void moveToCenterScreen(QWidget *widget, int screenNumber)
{
    if(!widget) return;
    if(screenNumber < 0 || screenNumber >= QApplication::screens().size() ) return;

    QScreen* screen = QApplication::screens().at(screenNumber);
    widget->move( screen->availableGeometry().left()
                  + (screen->availableGeometry().width() - widget->geometry().width()) / 2,
                  screen->availableGeometry().top()
                  + (screen->availableGeometry().height() - widget->geometry().height()) / 2
                  );
}
//==============================================================================
void messageError(QWidget *parent, const QString &text)
{
    QMessageBox::critical(parent, QObject::tr("Ошибка"), text, QMessageBox::Ok);
}
//==============================================================================
void messageWarning(QWidget *parent, const QString &text)
{
    QMessageBox::warning(parent, QObject::tr("Внимание"), text, QMessageBox::Ok);
}
//==============================================================================
void messageInfo(QWidget *parent, const QString &text)
{
    QMessageBox::information(parent, QObject::tr("Информация"), text, QMessageBox::Ok);
}
//==============================================================================
bool messageConfirm(QWidget *parent, const QString &text)
{
    return QMessageBox::question(parent,
                                 QObject::tr("Подтверждение"),
                                 text,
                                 QMessageBox::Yes, QMessageBox::Cancel
                                 )
            == QMessageBox::Yes;
}
//==============================================================================
int messageDialog(QWidget *parent, const QString &text)
{
    return QMessageBox::question(parent,
                                 QObject::tr("Вопрос"),
                                 text,
                                 QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel
                                 );
}
//==============================================================================
void messageError(const QString &text)
{
    messageError(mainWindowWidget(), text);
}
//==============================================================================
void messageWarning(const QString &text)
{
    messageWarning(mainWindowWidget(), text);
}
//==============================================================================
void messageInfo(const QString &text)
{
    messageInfo(mainWindowWidget(), text);
}
//==============================================================================
bool messageConfirm(const QString &text)
{
    return messageConfirm(mainWindowWidget(), text);
}
//==============================================================================
int messageDialog(const QString &text)
{
    return messageDialog(mainWindowWidget(), text);
}
//==============================================================================
QWidget *mainWindowWidget()
{
    for ( QWidget *widget : QApplication::topLevelWidgets() ) {
        if ( QString(widget->metaObject()->className()) == QString("MainWindow"))
            return widget;
    }
    return nullptr;
}
//==============================================================================
void showAboutDialog(const QString &developer, QWidget *parent)
{
    QDialog *dialogAbout {nullptr};

    if(parent) dialogAbout = parent->findChild<QDialog*>("dialogAbout");
    if(dialogAbout) return;

    dialogAbout = new QDialog(parent);
    dialogAbout->setObjectName("dialogAbout");
    dialogAbout->setAttribute(Qt::WA_DeleteOnClose);
    dialogAbout->setWindowTitle( dialogAbout->tr("О программе") );
    dialogAbout->setFixedSize(400, 400);

    QVBoxLayout *vBoxLayout = new QVBoxLayout(dialogAbout);
    vBoxLayout->setAlignment(Qt::AlignCenter);
    vBoxLayout->setMargin(0);
    vBoxLayout->setSpacing(10);

    vBoxLayout->addStretch(10);
    QLabel *titleLabel = new QLabel( QApplication::applicationDisplayName(), dialogAbout );
    titleLabel->setStyleSheet("font-size: 18pt;");
    titleLabel->setAlignment( Qt::AlignCenter );

    if(QFile::exists(imageMainIcon)) {

        QHBoxLayout *titleLayout = new QHBoxLayout;
        QLabel *labelIcon = new QLabel(dialogAbout);
        labelIcon->setPixmap( QPixmap(imageMainIcon) );
        labelIcon->setMinimumHeight( labelIcon->pixmap()->height() );
        labelIcon->setMaximumHeight( labelIcon->pixmap()->height() + 40 );
        labelIcon->setMinimumWidth( labelIcon->pixmap()->width() + 30 );
        labelIcon->setMaximumWidth( labelIcon->pixmap()->width() + 40 );
        labelIcon->setAlignment( Qt::AlignCenter );

        titleLayout->addStretch();
        titleLayout->addWidget(labelIcon);
        titleLayout->addWidget(titleLabel);
        titleLayout->addStretch();
        vBoxLayout->addLayout( titleLayout );
    }
    else {
        titleLabel->setMinimumHeight( 40 );
        titleLabel->setMaximumHeight( 80 );
        vBoxLayout->addWidget(titleLabel);
    }

    vBoxLayout->addStretch(20);
    QGridLayout *gridLayout = new QGridLayout;
    int row = 0;

    const QString labelStyle = "font-size: 11pt;";
    const QString valueStyle = "font-size: 11pt; font-weight: bold; padding-left: 10px;";

    QLabel *label = new QLabel( dialogAbout->tr("Версия:"), dialogAbout );
    label->setStyleSheet(labelStyle);
    gridLayout->addWidget(label, row, 0);
    label = new QLabel( QApplication::applicationVersion(), dialogAbout );
    label->setStyleSheet(valueStyle);
    gridLayout->addWidget(label, row, 1);
    row++;

#if defined (APP_BUILD_DATE)
    label = new QLabel( dialogAbout->tr("Дата:"), dialogAbout );
    label->setStyleSheet(labelStyle);
    gridLayout->addWidget(label, row, 0);
    label = new QLabel( QString(APP_BUILD_DATE), dialogAbout );
    label->setStyleSheet(valueStyle);
    gridLayout->addWidget(label, row, 1);
    row++;
#endif

    if(!developer.isEmpty()) {
        label = new QLabel( dialogAbout->tr("Автор:"), dialogAbout );
        label->setStyleSheet(labelStyle);
        gridLayout->addWidget(label, row, 0);
        label = new QLabel( developer, dialogAbout );
        label->setStyleSheet(valueStyle);
        gridLayout->addWidget(label, row, 1);
        row++;
    }

    QHBoxLayout *infoLayout = new QHBoxLayout;
    infoLayout->addStretch();
    infoLayout->addLayout(gridLayout);
    infoLayout->addStretch();
    vBoxLayout->addLayout(infoLayout);
    vBoxLayout->addStretch(80);

    QDialogButtonBox *buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok, Qt::Horizontal, dialogAbout );
    buttonBox->setCenterButtons(true);
    dialogAbout->connect( buttonBox, &QDialogButtonBox::accepted, dialogAbout, &QDialog::close );
    vBoxLayout->addStretch();
    vBoxLayout->addWidget(buttonBox);
    vBoxLayout->addSpacerItem( new QSpacerItem(20, 20) );
    dialogAbout->setLayout( vBoxLayout );
    dialogAbout->show();
}
//==============================================================================

} // namespace nayk ============================================================
