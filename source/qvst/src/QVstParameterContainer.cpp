#include <QDebug>
#include "public.sdk/source/vst/vsteditcontroller.h"
#include "QVstParameterContainer.h"


QVstParameterContainer::QVstParameterContainer(Steinberg::Vst::EditController *pEditController,
                                               QObject *pParent)
    : QObject(pParent),
      m_pEditController(pEditController)
{
}

QVstParameterContainer::~QVstParameterContainer()
{
}

int QVstParameterContainer::count()
{
    return m_pEditController->getParameterCount();
}

void QVstParameterContainer::setValue(const QString &name, double value)
{
    int n = m_pEditController->getParameterCount();
    for (int i = 0; i < n; i++) {
        Steinberg::Vst::ParameterInfo info;
        m_pEditController->getParameterInfo(i, info);

        QString title = QString::fromWCharArray(info.title);
        if (title == name) {
            setValue(info.id, value);
            return;
        }
    }
}

void QVstParameterContainer::setValue(int id, double value)
{
    return;
    // Pass the parameter change to the related controller
    m_pEditController->beginEdit(id);
    m_pEditController->performEdit(id, value);
    m_pEditController->endEdit(id);
}
