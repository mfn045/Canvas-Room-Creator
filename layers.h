#ifndef LAYERS_H
#define LAYERS_H

#include <QTreeWidget>
#include <QEvent>
#include <QDropEvent>

class Layers : public QTreeWidget
{
    Q_OBJECT
public:
    explicit Layers(QWidget* parent = nullptr);

protected:
    void dropEvent(QDropEvent *event) override;

signals:
    void dropped();
};

#endif // LAYERS_H
