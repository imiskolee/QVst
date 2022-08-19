#include <QFont>
#include <QColor>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QSlider>
#include <QDial>
#include <QLabel>
#include "QVstParameterContainer.h"
#include "QVstApplication.h"
#include "ids.h"
#include "PluginView.h"

const QFont cLabelFont("Tahoma", -1, QFont::Bold);

PluginView::PluginView(Steinberg::Vst::EditController *pController, Steinberg::ViewRect *size)
    : QVstEditorView(pController, size)
{
}

PluginView::~PluginView()
{
}

QLayout* PluginView::createLayout()
{
    QHBoxLayout *pHLayout = new QHBoxLayout();

    QVBoxLayout *pVLayout = new QVBoxLayout();

    QGroupBox *pDrawBarsGroupBox = new QGroupBox("Drawbars");
    QHBoxLayout *pDrawBarsLayout = new QHBoxLayout();
    pDrawBarsLayout->addWidget(createSlider("16", Param_DrawBar_16));
    pDrawBarsLayout->addWidget(createSlider("5 1/3", Param_DrawBar_5_13));
    pDrawBarsLayout->addWidget(createSlider("8", Param_DrawBar_8));
    pDrawBarsLayout->addWidget(createSlider("4", Param_DrawBar_4));
    pDrawBarsLayout->addWidget(createSlider("2 3/5", Param_DrawBar_2_35));
    pDrawBarsLayout->addWidget(createSlider("2", Param_DrawBar_2));
    pDrawBarsLayout->addWidget(createSlider("1 3/5", Param_DrawBar_1_35));
    pDrawBarsLayout->addWidget(createSlider("1 1/3", Param_DrawBar_1_13));
    pDrawBarsLayout->addWidget(createSlider("1", Param_DrawBar_1));
    pDrawBarsGroupBox->setLayout(pDrawBarsLayout);

    QGroupBox *pADSRGroupBox = new QGroupBox("ADSR");
    QHBoxLayout *pADSRLayout = new QHBoxLayout();
    pADSRLayout->addWidget(createDial("Attack", Param_Attack, 0.2));
    pADSRLayout->addWidget(createDial("Decay", Param_Decay, 0.2));
    pADSRLayout->addWidget(createDial("Sustain", Param_Sustain));
    pADSRLayout->addWidget(createDial("Release", Param_Release, 0.2));
    pADSRGroupBox->setLayout(pADSRLayout);



    pVLayout->addWidget(pDrawBarsGroupBox);
    pVLayout->addWidget(pADSRGroupBox);

    pHLayout->addLayout(pVLayout);
    pHLayout->addWidget(createSlider("Gain", Param_Volume));
    pHLayout->addWidget(createSlider("Vibrato", Param_Modulation));

    return pHLayout;
}

QWidget* PluginView::createSlider(const QString &title, int paramId)
{
    QWidget *pWidget = new QWidget();
    QVBoxLayout *pLayout = new QVBoxLayout();
    QLabel *pLabel = new QLabel(title);
    pLabel->setFont(cLabelFont);
    pLabel->setAlignment(Qt::AlignCenter);
    QSlider *pSlider = new QSlider(Qt::Vertical);
    pSlider->setMinimumHeight(96);
    pSlider->setMinimum(0);
    pSlider->setMaximum(127);
    pSlider->setSingleStep(1);
    pSlider->setTickInterval(16);
    pSlider->setTickPosition(QSlider::TicksBothSides);
    pSlider->setTracking(true);
    QObject::connect(pSlider, &QSlider::valueChanged, [this, paramId](int value) {
        double n = double(value) / 127.0;
        parameters()->setValue(paramId, n);
    });

    pLayout->addWidget(pLabel);
    pLayout->addWidget(pSlider);
    pWidget->setLayout(pLayout);

    return pWidget;
}

QWidget* PluginView::createDial(const QString &title, int paramId, double max)
{
    QWidget *pWidget = new QWidget;
    QVBoxLayout *pLayout = new QVBoxLayout();

    QLabel *pValueLabel = new QLabel();
    pValueLabel->setAlignment(Qt::AlignCenter);

    QDial *pDial = new QDial();
    pDial->setMaximumSize(64, 64);
    pDial->setMinimum(0);
    pDial->setMaximum(100);
    pDial->setSingleStep(1);
    pDial->setNotchesVisible(true);
    pDial->setTracking(true);
    QObject::connect(pDial, &QDial::valueChanged, [this, pValueLabel, paramId, max](int value) {
        double n = max * double(value) / 100.0;
        parameters()->setValue(paramId, n);
        if (paramId == Param_Sustain) {
            pValueLabel->setText(QString::number(n, 'f', 2));
        } else {
            pValueLabel->setText(QString("%1 ms").arg(QString::number(int(1000 * n))));
        }
    });

    QLabel *pLabel = new QLabel(title);
    pLabel->setFont(cLabelFont);
    pLabel->setAlignment(Qt::AlignCenter);

    pLayout->addWidget(pLabel);
    pLayout->addWidget(pDial);
    pLayout->addWidget(pValueLabel);
    pWidget->setLayout(pLayout);

    return pWidget;
}
