#ifndef AMBULANCEUPDATEDIALOG_H
#define AMBULANCEUPDATEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

class AmbulanceUpdateDialog : public QDialog {
    Q_OBJECT
public:
    explicit AmbulanceUpdateDialog(QWidget *parent = nullptr);

private slots:
    void onApply();

private:
    QLineEdit *txtAmbulanceId;
    QComboBox *cmbField;
    QLineEdit *txtValue;

    void rewriteAmbulance(const QString &targetId, int field, const QString &val);
};

#endif
