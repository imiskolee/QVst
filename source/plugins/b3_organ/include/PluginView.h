#ifndef PLUGINVIEW_H
#define PLUGINVIEW_H

#include <QString>
#include "QVstEditorView.h"

class QWidget;
class QVstWidget;


class PluginView : public QVstEditorView

{
public:
    PluginView(Steinberg::Vst::EditController *pController,
               Steinberg::ViewRect *size = nullptr);
    ~PluginView();

protected:
    QLayout* createLayout() override;

private:

    QWidget* createSlider(const QString &title, int paramId);
    QWidget* createDial(const QString &title, int paramId, double max = 1.0);
};

#endif // PLUGINVIEW_H

