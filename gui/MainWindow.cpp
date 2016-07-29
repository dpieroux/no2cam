#include "MainWindow.h"

#include <QAction>
#include <QActionGroup>
#include <QCloseEvent>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QStackedWidget>

#include "SnapshotPane.h"
#include "ObservationPane.h"
#include "SweepPane.h"
#include "ConfigurationDlg.h"

#include "core.h"
#include "core/Crystal.h"

namespace gui {

//------------------------------------------------------------------------------

MainWindow::MainWindow(const QString &version, QWidget *parent)
    : QMainWindow(parent)
    , stackedWidget_(new QStackedWidget)
    , snapshotModeAction_(new QAction("Take &snapshots", this))
    , observationModeAction_(new QAction("Make &observations", this))
    , sweepModeAction_(new QAction("Sweep over &wavelength", this))
    , configurationDlg_(new ConfigurationDlg(this))
    , version_(version)
    , snapshotPane_(new SnapshotPane)
{
    // -------------------------------------------------------------------------
    // Central widget
    // -------------------------------------------------------------------------

    stackedWidget_->addWidget(snapshotPane_);
    stackedWidget_->addWidget(new ObservationPane());
    stackedWidget_->addWidget(new SweepingPane());

    setCentralWidget(stackedWidget_);

    // -------------------------------------------------------------------------
    // Actions
    // -------------------------------------------------------------------------

    auto newAction = new QAction("&New", this);
    auto loadAction = new QAction("&Load", this);
    auto saveAction = new QAction("&Save", this);
    auto saveAsAction = new QAction("Save &as", this);
    connect(newAction, QAction::triggered, this, newSession);
    connect(loadAction, QAction::triggered, this, loadSession);
    connect(saveAction, QAction::triggered, this, saveSession);
    connect(saveAsAction, QAction::triggered, this, saveAsSession);

    auto configureAction = new QAction("&Configure", this);
    configureAction->setIcon(QIcon(":/icons/C-gold-24.png"));
    configureAction->setIconVisibleInMenu(false);
    configureAction->setShortcut(QKeySequence("Alt+C"));
    configureAction->setStatusTip(tr("Switch to configuration mode"));
    connect(configureAction, QAction::triggered, configurationDlg_, ConfigurationDlg::display);

    auto exitAction = new QAction("E&xit", this);
    exitAction->setShortcut(QKeySequence("Alt+F4"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, &QAction::triggered, this, close);

    auto modeGroup = new QActionGroup(this);
    modeGroup->addAction(snapshotModeAction_);
    modeGroup->addAction(observationModeAction_);
    modeGroup->addAction(sweepModeAction_);

    snapshotModeAction_->setIcon(QIcon(":/icons/S-blue-24.png"));
    snapshotModeAction_->setIconVisibleInMenu(false);
    snapshotModeAction_->setCheckable(true);
    snapshotModeAction_->setShortcut(QKeySequence("Alt+S"));
    snapshotModeAction_->setStatusTip(tr("Switch to snapshot mode"));
    connect(snapshotModeAction_, QAction::triggered, this, switchMode);

    observationModeAction_->setIcon(QIcon(":/icons/O-blue-24.png"));
    observationModeAction_->setIconVisibleInMenu(false);
    observationModeAction_->setCheckable(true);
    observationModeAction_->setShortcut(QKeySequence("Alt+O"));
    observationModeAction_->setStatusTip(tr("Switch to observation mode"));
    connect(observationModeAction_, QAction::triggered, this, switchMode);

    sweepModeAction_->setIcon(QIcon(":/icons/W-blue-24.png"));
    sweepModeAction_->setIconVisibleInMenu(false);
    sweepModeAction_->setCheckable(true);
    sweepModeAction_->setShortcut(QKeySequence("Alt+W"));
    sweepModeAction_->setStatusTip(tr("Switch to wavelength sweeping mode"));
    connect(sweepModeAction_, QAction::triggered, this, switchMode);

    auto cameraStatusAction = new QAction("&Camera status", this);
    connect(cameraStatusAction, QAction::triggered, this, cameraStatus);

    auto releaseNotesAction = new QAction("&Release Notes", this);
    connect(releaseNotesAction, QAction::triggered, this, releaseNotes);

    auto aboutAction = new QAction("&About", this);
    connect(aboutAction, QAction::triggered, this, about);

    // -------------------------------------------------------------------------
    // Menus
    // -------------------------------------------------------------------------

    auto fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(loadAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(configureAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    auto modeMenu = menuBar()->addMenu(tr("&Mode"));
    modeMenu->addAction(snapshotModeAction_);
    modeMenu->addAction(observationModeAction_);
    modeMenu->addAction(sweepModeAction_);

    auto deviceMenu = menuBar()->addMenu(tr("&Devices"));
    deviceMenu->addAction(cameraStatusAction);

    auto helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(releaseNotesAction);
    helpMenu->addAction(aboutAction);

    // -------------------------------------------------------------------------
    // Toolbar
    // -------------------------------------------------------------------------

    auto toolBar = addToolBar(tr("&Mode"));
    toolBar->addAction(snapshotModeAction_);
    toolBar->addAction(observationModeAction_);
    toolBar->addAction(sweepModeAction_);
    toolBar->addSeparator();
    toolBar->addAction(configureAction);

    // -------------------------------------------------------------------------
    // Varia
    // -------------------------------------------------------------------------

    setWindowTitle("NO2 Camera - " + version);
    setWindowIcon(QIcon(":/icons/video-camera-64.png"));
    setFixedSize(sizeHint());
    snapshotModeAction_->setChecked(true);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //snapshotPane_->persisteParams(); // TODO also for the other panes.
    QMainWindow::closeEvent(event);
}

//------------------------------------------------------------------------------

void MainWindow::newSession()
{
    qWarning("New session NOT IMPLEMENTED"); //TODO
}

//------------------------------------------------------------------------------

void MainWindow::loadSession()
{
    qWarning("Load session NOT IMPLEMENTED"); //TODO
}

//------------------------------------------------------------------------------

bool MainWindow::saveSession()
{
    qWarning("Save session NOT IMPLEMENTED"); //TODO
    return true;
}

//------------------------------------------------------------------------------

bool MainWindow::saveAsSession()
{
    qWarning("Save as session NOT IMPLEMENTED"); //TODO
    return true;
}


//------------------------------------------------------------------------------

void MainWindow::switchMode()
{
    if (snapshotModeAction_->isChecked())
    {
        stackedWidget_->setCurrentIndex(0);
    }
    else if (observationModeAction_->isChecked())
    {
        stackedWidget_->setCurrentIndex(1);
    }
    else if (sweepModeAction_->isChecked())
    {
        stackedWidget_->setCurrentIndex(2);
    }
    else
    {
        configurationDlg_->exec();
    }
}

//------------------------------------------------------------------------------

void MainWindow::configure()
{
    configurationDlg_->exec();
}

//------------------------------------------------------------------------------

void MainWindow::cameraStatus()
{
    qWarning("Save session NOT IMPLEMENTED");
}

//------------------------------------------------------------------------------

void MainWindow::about()
{
    QMessageBox::about
            (this,
             tr("About NO2_CAM"),
             tr("<h3>NO<sub>2</sub> Camera Control Software</h3>") +
             "<p>" + tr("Version") + ": " + version_ + "</p>" +
             tr("<p>Author: Didier Pieroux (didier.pieroux@aeronomie.be)</p>") +
             tr("<p>Copyright 2016 BIRA-IASB</p>") +
             tr("<p>This program is provided AS IS, with NO WARRANTY OF ANY "
                "KIND.</p>")
             );
}

//------------------------------------------------------------------------------

void MainWindow::releaseNotes()
{
    QMessageBox::information
            (this,
             tr("NO2_CAM"),
             "<h2>" + tr("Release notes") + "</h2>" +
             "<h3>" + tr("Version") + " " + version_ + "</h3>" +
             tr("<p>Only the GUI is implemented in this version.</p>"
                "<p>As a consequence of the lack of logic, the snapshot button"
                "   remains depressed when clicked. In the final version, it"
                "   will automatically get released once the snapshot is"
                "   acquired.</p>"
                ),
             QMessageBox::Ok);
}

//------------------------------------------------------------------------------

bool MainWindow::okToContinue()
{

    if (isWindowModified())
    {
        auto code = QMessageBox::warning
                (this,
                 tr("NO2_CAM"),
                 tr("The session has been modified.\n"
                    "Do you want to save your changes?"),
                 QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
                 );

        switch (code)
        {
        case QMessageBox::Yes:
            return saveSession();
        case QMessageBox::No:
            return true;
        case QMessageBox::Cancel:
            return false;
        default:
            Q_UNREACHABLE();
        }
    }
    else
        return true;
}

//------------------------------------------------------------------------------

}
