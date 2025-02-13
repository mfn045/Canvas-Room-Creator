#ifndef TEXTLINEEDITINPUT_H
#define TEXTLINEEDITINPUT_H

#include <QLineEdit>
#include <QObject>
#include <QResizeEvent>

class TextLineEditInput : public QLineEdit
{
    Q_OBJECT
public:
    explicit TextLineEditInput(QWidget* parent = nullptr);
    int getWidth();
    int getHeight();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    int width = 0;
    int height = 0;
};

#endif // TEXTLINEEDITINPUT_H
