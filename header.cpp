#include "header.h"

#include <QFile>
#include <QMouseEvent>
#include <QPainter>

Header::Header(Qt::Orientation orientation, QWidget* parent)
    : QHeaderView(orientation, parent)

{
    //    QFile file(orientation == Qt::Horizontal ? "Horizontal.data" : "Vertical.data");
    //    if (file.open(QFile::ReadOnly)) {
    //        QDataStream in(&file);
    //        in >> m_checked;
    //    }
    connect(this, &QHeaderView::sectionCountChanged, [this, orientation](int /*oldCount*/, int newCount) {
        m_checked.resize(newCount);
        m_checkRect.resize(newCount);
        emit onCheckedV(m_checked, orientation);
    });
    setSectionsClickable(true);
    setHighlightSections(true);
}

Header::~Header()
{
    //    QFile file(orientation() == Qt::Horizontal ? "Horizontal.data" : "Vertical.data");
    //    if (file.open(QFile::WriteOnly)) {
    //        QDataStream out(&file);
    //        out << m_checked;
    //    }
}

void Header::setAll(bool checked)
{
    for (int i = 0; i < count(); ++i) {
        if (m_checked[i] != checked) {
            m_checked[i] = checked;
            emit onChecked(i, orientation());
            updateSection(i);
        }
    }
    emit onCheckedV(m_checked, orientation());
}

void Header::togle(int index)
{
    m_checked[index] = !m_checked[index];
    updateSection(index);
    emit onCheckedV(m_checked, orientation());
    emit onChecked(index, orientation());
}

void Header::setSingle(int index)
{
    for (int i = 0, fl = i == index; i < count(); fl = ++i == index) {
        if (m_checked[i] != fl) {
            m_checked[i] = fl;
            emit onChecked(i, orientation());
            updateSection(i);
        }
    }
    emit onCheckedV(m_checked, orientation());
}

QRect Header::getRect(const QRect& rect)
{
    return QRect(
        rect.left() + XOffset,
        rect.top() + (rect.height() - DelegateSize) / 2,
        DelegateSize,
        DelegateSize);
}

void Header::mouseMoveEvent(QMouseEvent* event)
{
    static int index = 0;
    do {
        //        if (!m_checkBoxRect[logicalIndexAt(event->pos())].contains(event->pos()))
        //            break;
        if (index == logicalIndexAt(event->pos()))
            break;
        index = logicalIndexAt(event->pos());
        if (index < 0)
            break;
        if (event->buttons() != Qt::RightButton)
            break;
        if (orientation() == Qt::Horizontal) {
            //setSingle(index);
        } else
            togle(index);
        event->accept();
        return;
    } while (0);
    QHeaderView::mouseMoveEvent(event);
}

void Header::mousePressEvent(QMouseEvent* event)
{
    int index = logicalIndexAt(event->pos());
    do {
        if (index < 0)
            break;
        if (!m_checkRect[index].contains(event->pos()) && event->buttons() != Qt::RightButton)
            break;
        if (orientation() == Qt::Horizontal)
            setSingle(index);
        else
            togle(index);
        event->accept();
        return;
    } while (0);
    QHeaderView::mousePressEvent(event);
}

void Header::paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    QStyleOptionButton option;
    m_checkRect[logicalIndex] = option.rect = getRect(rect);

    option.state = m_checked[logicalIndex]
        ? QStyle::State_On
        : QStyle::State_Off;

    option.state |= isEnabled()
        ? QStyle::State_Enabled
        : QStyle::State_None;

    if (orientation() == Qt::Horizontal)
        style()->drawPrimitive(QStyle::PE_IndicatorRadioButton, &option, painter);
    else
        style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
}
