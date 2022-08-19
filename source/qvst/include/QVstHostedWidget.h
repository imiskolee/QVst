#ifndef QVSTHOSTEDWIDGET_H
#define QVSTHOSTEDWIDGET_H

#ifdef WIN32
#   include <Windows.h>
#endif
#include <QWidget>

class QVstHostedWidget : public QWidget
{
    Q_OBJECT

    friend class QVstEditorView;
public:

    QVstHostedWidget(HWND hParentWnd, QObject *pParent = nullptr, Qt::WindowFlags f = Qt::WindowType::Desktop);
    ~QVstHostedWidget();

    void setVisible(bool visible) override;

private:

    void adjustSize(const QSize &size);

    void initialize();
    void saveFocus();
    void resetFocus();

    struct Private;
    Private *m;
};

#endif // QVSTWIDGET_H

