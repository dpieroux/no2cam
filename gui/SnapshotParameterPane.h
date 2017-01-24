#ifndef SNAPSHOTPARAMETERPANE_H
#define SNAPSHOTPARAMETERPANE_H

#include "BaseParameterPane.h"

//------------------------------------------------------------------------------

class QRadioButton;

namespace core {
class Crystal;
class AbstractCrysTempProbe; // should be set via a signal
}

namespace gui {

class DoubleLineEdit;
class IntLineEdit;

//------------------------------------------------------------------------------

class SnapshotParameterPane : public BaseParameterPane
{
    Q_OBJECT
public:
    explicit SnapshotParameterPane(const core::Crystal *crystal,
                                   core::AbstractCrysTempProbe *crysTempProbe);
    void updateState(bool isAppReady);
    void persiste() const;

    void start(bool burst,
               bool record,
               double stabilisationTime,
               QString session) override;

signals:
    void spectralSnapshot(double wavelength,
                          double exposure,
                          double cooldownTime,
                          double cooldownPwr,
                          double stabilisationTime,
                          bool burst,
                          bool record,
                          const QString& session);

    void acousticSnapshot(double frequency,
                          double power,
                          double exposure,
                          double cooldownTime,
                          double cooldownPwr,
                          double stabilisationTime,
                          bool burst,
                          bool record,
                          const QString& session);
public slots:
    void recomputeParams();


protected:
    bool areParametersValid() const override;

private slots:
    void enableFieldsWrtMode();

private:
    void restore();

    const core::Crystal *_crystal;
    const core::AbstractCrysTempProbe *_crystalTempProbe;

    QRadioButton   *_spectralBtn;
    QRadioButton   *_acousticBtn;
    DoubleLineEdit *_wavelengthEdit;
    DoubleLineEdit *_frequencyEdit;
    IntLineEdit    *_powerEdit;
};

//------------------------------------------------------------------------------

}

#endif // SNAPSHOTPARAMETERPANE_H
