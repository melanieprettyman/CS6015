#include "mainwidget.h"
#include "parse.hpp"
#include "pointer.h"
#include "val.h"

mainWidget::mainWidget(QWidget *parent)
    : QWidget{parent},
    exprEdit(new QLineEdit),
    interpButton(new QRadioButton("Interp")),
    pretty_print_Button(new QRadioButton("Pretty print")),
    submitButton(new QPushButton("Submit")),
    resetButton(new QPushButton("Reset")),
    resultTextEdit(new QTextEdit),
    mainLayout(new QVBoxLayout)
{

    setGridLayout();
    setLayout(mainLayout);

    connect(submitButton, &QPushButton::clicked, this, &mainWidget::fillResult);
    connect(resetButton, &QPushButton::clicked, this, &mainWidget::clearWidgets);

}

//Function to create gridLayout
void mainWidget::setGridLayout() {

    //Create grid-layout
    QGridLayout *gridLayout = new QGridLayout;

    //Expression box
    QGroupBox *exprBox = new QGroupBox();
    QHBoxLayout *exprLayout = new QHBoxLayout;
    exprLayout->addWidget(new QLabel("Expression:"));
    exprEdit->setPlaceholderText("Enter your expression");
    exprLayout->addWidget(exprEdit);
    exprBox->setLayout(exprLayout);

    //MSD options box
    QGroupBox *msdBox = new QGroupBox();
    QVBoxLayout *radioLayout = new QVBoxLayout;
    radioLayout->addWidget(interpButton);
    radioLayout->addWidget(pretty_print_Button);
    msdBox->setLayout(radioLayout);


    //Result box
    QGroupBox *resultBox = new QGroupBox();
    QHBoxLayout *resultLayout = new QHBoxLayout;
    resultLayout->addWidget(new QLabel("Result:"));
    resultLayout->addWidget(resultTextEdit);
    resultBox->setLayout(resultLayout);


    //Add name, gender, and summary boxes
    gridLayout->addWidget(exprBox, 0, 0, 1, 2);
    gridLayout->addWidget(msdBox, 1, 0, 1, 2);
    gridLayout->addWidget(submitButton, 2, 0);
    gridLayout->addWidget(resultBox, 3, 0, 1, 2);
    gridLayout->addWidget(resetButton, 4, 0);

    //Add gridLayout to mainlayout
    mainLayout->addItem(gridLayout);

    mainLayout->setSpacing(10); // Adjusts spacing between widgets in the main layout
    gridLayout->setSpacing(10); // Adjusts spacing between widgets in the grid layout

}



//Function is called when the 'Submit' button is clicked. Collects the inputed from exprEdit and converts it to QString. If interp is selected
//sets results equal the parsed/interped string. If pretty print is selected, sets results equals to the string after pretty-print call.
//Sets result as the text in the result box.
void mainWidget::fillResult() {

    QString input_str = exprEdit->text();
    std::string str_to_be_parsed = input_str.toUtf8().constData();


    if(interpButton->isChecked()){

        PTR(Val) expr = parse_str(str_to_be_parsed)->interp(Env::empty);
        result = QString::fromStdString(expr->to_string());

    }

    if(pretty_print_Button->isChecked()){
        std::string output = parse_str(str_to_be_parsed)->to_pp_string();
        result = QString::fromStdString(output);
    }

    resultTextEdit->setText(result);
}

//Function is called when the 'Clear' button is clicked. Clears all input fields.
void mainWidget::clearWidgets() {
    exprEdit->clear();
    interpButton->setChecked(false);
    pretty_print_Button->setChecked(false);
    resultTextEdit->clear();
}
