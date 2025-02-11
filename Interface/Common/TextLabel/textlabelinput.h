#ifndef TEXTLABELINPUT_H
#define TEXTLABELINPUT_H

#include <QLabel>
#include <QObject>
#include <QResizeEvent>

class TextLabelInput : public QLabel
{
    Q_OBJECT
public:
    explicit TextLabelInput(QWidget* parent = nullptr);
    int getWidth();
    int getHeight();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    int width = 0;
    int height = 0;
};

#endif // TEXTLABELINPUT_H
