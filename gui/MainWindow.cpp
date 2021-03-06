#include "MainWindow.h"

#include <QAction>
#include <QActionGroup>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QStackedWidget>

#include "SnapshotPane.h"
#include "ObservationPane.h"
#include "SweepingPane.h"
#include "ConfigurationDlg.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mStackedWidget(new QStackedWidget)
    , mSnapshotModeAction(new QAction("Take &snapshots", this))
    , mObservationModeAction(new QAction("Make &observations", this))
    , mSweepModeAction(new QAction("Sweep over &wavelength", this))
    , mConfigurationDlg(new ConfigurationDlg(this))
{
    // -------------------------------------------------------------------------
    // Central widget
    // -------------------------------------------------------------------------

    mStackedWidget->addWidget(new SnapshotPane());
    mStackedWidget->addWidget(new ObservationPane());
    mStackedWidget->addWidget(new SweepingPane());

    setCentralWidget(mStackedWidget);

    // -------------------------------------------------------------------------
    // Actions
    // -------------------------------------------------------------------------

    auto newAction = new QAction("&New", this);
    auto loadAction = new QAction("&Load", this);
    auto saveAction = new QAction("&Save", this);
    auto saveAsAction = new QAction("Save &as", this);
    connect(newAction, QAction::triggered, this, MainWindow::newSession);
    connect(loadAction, QAction::triggered, this, MainWindow::loadSession);
    connect(saveAction, QAction::triggered, this, MainWindow::saveSession);
    connect(saveAsAction, QAction::triggered, this, MainWindow::saveAsSession);

    auto configureAction = new QAction("&Configure", this);
    configureAction->setIcon(QIcon(":/icons/C-gold-24.png"));
    configureAction->setIconVisibleInMenu(false);
    configureAction->setShortcut(QKeySequence("Alt+C"));
    configureAction->setStatusTip(tr("Switch to configuration mode"));
    connect(configureAction, QAction::triggered, this, MainWindow::configure);

    auto exitAction = new QAction("E&xit", this);
    exitAction->setShortcut(QKeySequence("Alt+F4"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, &QAction::triggered, this, QMainWindow::close);

    auto modeGroup = new QActionGroup(this);
    modeGroup->addAction(mSnapshotModeAction);
    modeGroup->addAction(mObservationModeAction);
    modeGroup->addAction(mSweepModeAction);

    mSnapshotModeAction->setIcon(QIcon(":/icons/S-blue-24.png"));
    mSnapshotModeAction->setIconVisibleInMenu(false);
    mSnapshotModeAction->setCheckable(true);
    mSnapshotModeAction->setShortcut(QKeySequence("Alt+S"));
    mSnapshotModeAction->setStatusTip(tr("Switch to snapshot mode"));
    connect(mSnapshotModeAction, QAction::triggered, this, MainWindow::switchMode);

    mObservationModeAction->setIcon(QIcon(":/icons/O-blue-24.png"));
    mObservationModeAction->setIconVisibleInMenu(false);
    mObservationModeAction->setCheckable(true);
    mObservationModeAction->setShortcut(QKeySequence("Alt+O"));
    mObservationModeAction->setStatusTip(tr("Switch to observation mode"));
    connect(mObservationModeAction, QAction::triggered, this, MainWindow::switchMode);

    mSweepModeAction->setIcon(QIcon(":/icons/W-blue-24.png"));
    mSweepModeAction->setIconVisibleInMenu(false);
    mSweepModeAction->setCheckable(true);
    mSweepModeAction->setShortcut(QKeySequence("Alt+W"));
    mSweepModeAction->setStatusTip(tr("Switch to wavelength sweeping mode"));
    connect(mSweepModeAction, QAction::triggered, this, MainWindow::switchMode);

    auto releaseNotesAction = new QAction("&Release Notes", this);
    connect(releaseNotesAction, &QAction::triggered, this, &MainWindow::releaseNotes);

    auto aboutAction = new QAction("&About", this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

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
    modeMenu->addAction(mSnapshotModeAction);
    modeMenu->addAction(mObservationModeAction);
    modeMenu->addAction(mSweepModeAction);

    auto helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(releaseNotesAction);
    helpMenu->addAction(aboutAction);

    // --------------------------------------------------------------------------
    // Toolbar
    // --------------------------------------------------------------------------

    auto toolBar = addToolBar(tr("&Mode"));
    toolBar->addAction(mSnapshotModeAction);
    toolBar->addAction(mObservationModeAction);
    toolBar->addAction(mSweepModeAction);
    toolBar->addSeparator();
    toolBar->addAction(configureAction);

    // -------------------------------------------------------------------------
    // Varia
    // -------------------------------------------------------------------------

    setWindowTitle("NO2 Camera");
    setWindowIcon(QIcon(":/icons/video-camera-64.png"));
    setFixedSize(sizeHint());
    mSnapshotModeAction->setChecked(true);
}

MainWindow::~MainWindow()
{

}

void MainWindow::newSession()
{
    notImplemented("New");
}

void MainWindow::loadSession()
{
    notImplemented("Load");
}

bool MainWindow::saveSession()
{
    notImplemented("Save");
    return true;
}

bool MainWindow::saveAsSession()
{
    notImplemented("Save as");
    return true;
}

void MainWindow::switchMode()
{
    if (mSnapshotModeAction->isChecked())
    {
        mStackedWidget->setCurrentIndex(0);
    }
    else if (mObservationModeAction->isChecked())
    {
        mStackedWidget->setCurrentIndex(1);
    }
    else if (mSweepModeAction->isChecked())
    {
        mStackedWidget->setCurrentIndex(2);
    }
    else
    {
        mConfigurationDlg->exec();
    }
}

void MainWindow::configure()
{
    mConfigurationDlg->exec();
}

void MainWindow::about()
{
    QMessageBox::about
            (this,
             tr("About NO2_CAM"),
             tr("<h3>NO<sub>2</sub> Camera Control Software</h3>") +
             tr("<p>Version 0.1.0</p>") +
             tr("<p>Author: Didier Pieroux (didier.pieroux@aeronomie.be)</p>") +
             tr("<p>Copyright 2016 BIRA-IASB</p>") +
             tr("<p>This program is provided AS IS, with NO WARRANTY OF ANY "
                "KIND.</p>")
             );
}

void MainWindow::releaseNotes()
{
    QMessageBox::information
            (this,
             tr("NO2_CAM"),
             tr("<h2>Release notes</h2>"
                "<h3>Version 0.1.0</h3>"
                "<p>Only the GUI is implemented in this version.</p>"
                "<p>As a consequence of the lack of logic, the snapshot button"
                "   remains depressed when clicked. In the final version, it"
                "   will automatically get released once the snapshot is"
                "   acquired.</p>"
                ),
             QMessageBox::Ok
             );
}

void MainWindow::notImplemented(const QString &feature)
{
    QMessageBox::warning
            (this,
             "NO2_CAM",
             "<b>" + feature + "</b> " + tr("is not yet implemented"),
             QMessageBox::Ok);
}

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
