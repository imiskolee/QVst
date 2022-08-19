#ifndef QVSTEDITORVIEW_H
#define QVSTEDITORVIEW_H

#include "public.sdk/source/vst/vsteditcontroller.h"

class QLayout;
class QWidget;
class QVstHostedWidget;
class QVstParameterContainer;

class QVstEditorView : public Steinberg::Vst::EditorView
{
public:
    QVstEditorView(Steinberg::Vst::EditController *pController,
                   Steinberg::ViewRect *size = nullptr);
    ~QVstEditorView();

    // IPlugView interface
    Steinberg::tresult PLUGIN_API isPlatformTypeSupported(Steinberg::FIDString type) override;
    Steinberg::tresult PLUGIN_API attached(void* parent, Steinberg::FIDString type) override;
    Steinberg::tresult PLUGIN_API removed() override;

    Steinberg::tresult PLUGIN_API canResize() override;
    Steinberg::tresult PLUGIN_API getSize(Steinberg::ViewRect* size) override;
    Steinberg::tresult PLUGIN_API onSize(Steinberg::ViewRect* newSize) override;
    Steinberg::tresult PLUGIN_API checkSizeConstraint(Steinberg::ViewRect* rect) override;

    //Steinberg::tresult PLUGIN_API onKeyDown (Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers);
    //Steinberg::tresult PLUGIN_API onKeyUp (Steinberg::char16 key, Steinberg::int16 keyCode, Steinberg::int16 modifiers);

    // TODO: Transform VST SDK calls into Qt Events
    /*
    tresult PLUGIN_API onWheel (float distance);
    tresult PLUGIN_API onFocus (TBool state);
    tresult PLUGIN_API setFrame (IPlugFrame* frame);
    */

    QWidget* centralWidget() const;

    QVstParameterContainer* parameters() const { return m_pParameterContainer; }

protected:

    /**
     * @brief Create a custom layout for this view.
     * By default no layout is created.
     * This method should create a new layout that will be assigned to
     * the editor GUI widget. Layouts and GUI items cannot be shared between
     * plugin instances, since they have separate life cycles.
     * @return Pointer to a newly created layout.
     */
    virtual QLayout* createLayout();

private:

    QVstHostedWidget *m_pHostedWidget;
    QVstParameterContainer *m_pParameterContainer;
};


#endif // QVSTEDITORVIEW_H

