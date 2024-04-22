#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QRadioButton>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSpinBox>



class mainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit mainWidget(QWidget *parent = nullptr);


    void setGridLayout(QGridLayout *layout);

    QLineEdit *exprEdit;
    QRadioButton *interpButton, *pretty_print_Button;
    QPushButton *submitButton, *resetButton;
    QTextEdit *resultTextEdit;
    QVBoxLayout *mainLayout;

    void setGridLayout();
    void clearWidgets();

    void fillResult();

    void handleInput();
    void handleInterp();
    void handlePrint();

    QString result;

signals:
};

#endif // MAINWIDGET_H
