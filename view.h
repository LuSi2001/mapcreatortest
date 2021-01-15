#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget *parent = nullptr);
    const QPixmap snapshot(qreal curScale);

protected:
    void scrollContentsBy(int, int) override;
};

#endif // VIEW_H
