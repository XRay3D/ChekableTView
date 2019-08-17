#ifndef MYHEADER_H
#define MYHEADER_H

#include <QHeaderView>

class Header : public QHeaderView {
    Q_OBJECT

public:
    Header(Qt::Orientation orientation, QWidget* parent = nullptr);
    ~Header() override;

    enum {
        XOffset = 5,
        DelegateSize = 16
    };

    void setAll(bool checked);
    void togle(int index);
    void setSingle(int index);

    const QVector<bool>* checked() const { return &m_checked; }
    static QRect getRect(const QRect& rect);

signals:
    void onCheckedV(const QVector<bool>&, int);
    void onChecked(int, int);

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const override;

private:
    mutable QVector<bool> m_checked;
    mutable QVector<QRect> m_checkRect;
};

#endif // MYHEADER_H
