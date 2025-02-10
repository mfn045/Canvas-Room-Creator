#ifndef LOADINGBAR_H
#define LOADINGBAR_H

#include "../../CanvasObject/Multi/multicanvasobject.h"
#include "../../CanvasObject/Multi/Masked/maskedmulticanvasobject.h"

class LoadingBar : public MultiCanvasObject
{
    Q_OBJECT
public:
    explicit LoadingBar(MultiCanvasObject* parent = nullptr);

    MaskedMultiCanvasObject* getBar();
    MultiCanvasObject* getSpinner();

    void setPercent(float percent);
    float getPercent();

private:
    MaskedMultiCanvasObject* bar = nullptr;
    MultiCanvasObject* spinner = nullptr;

    const float barOffset_X = 23.5;
    const float barOffset_Y = 7;

    const float spinnerOffset_X = 2;
    const float spinnerOffset_Y = 2;

    int percent = 0;

signals:
    void finished();
};

#endif // LOADINGBAR_H
