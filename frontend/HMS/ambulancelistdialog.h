#ifndef AMBULANCELISTDIALOG_H
#define AMBULANCELISTDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>

class AmbulanceListDialog : public QDialog {
    Q_OBJECT
public:
    enum Mode { ALL, AVAILABLE_FOR_REQUEST };
    explicit AmbulanceListDialog(Mode m, QWidget *parent = nullptr);

private slots:
    void onRequestSelected();

private:
    Mode mode;
    QTableWidget *table;
    QPushButton  *btnRequest;
    void load();
};

#endif