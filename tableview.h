#ifndef TABLE_H
#define TABLE_H

#include <QTableView>

class Header;
class Model;
class QAbstractButton;

class TableView : public QTableView {
    Q_OBJECT
public:
    explicit TableView(QWidget* parent = nullptr);
    ~TableView();
    Model* model() const;
    void init();
    void initCheckBox();
    void initRadioButton();
    void initCheckBoxRadioButton();

private:
    Model* m_model;
    void createCornerCheckBox(Header* header);
};

#endif // TABLE_H
