#include "calculator.h"
#include "ui_calculator.h"

#include <stack>

#include <QLabel>

Calculator::Calculator(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
}

Calculator::~Calculator()
{
    delete ui;
}


void Calculator::on_pushButton_clicked()
{
    std::string function = ui->lineEdit->text().toStdString();

    // This is a very simple calculator
    // We perform PEMDAS operations
    // Parentheses, Exponents, Multiplication and Division, Addition and Subtraction

    // We will use a stack to store the numbers and the operations
    std::stack<double> numbers;
    std::stack<char> operations;

    // We will iterate over the function

    // We will use a variable to store the number we are reading
    double number = 0;
    // We will use a variable to store the sign of the number
    int sign = 1;
    // We will use a variable to store the exponent
    int exponent = 0;
    // We will use a variable to store the decimal part
    double decimal = 0;
    // We will use a variable to store the decimal exponent
    int decimal_exponent = 0;

    for (char c : function) {
        if (c == ' ') {
            continue;
        }
        if (c == '(') {
            // We push the number and the operation to the stacks
            numbers.push(number);
            number = 0;
            operations.push('(');
            continue;
        }
        if (c == ')') {
            // We push the number and the operation to the stacks
            numbers.push(number);
            number = 0;
            // We will calculate the result of the parentheses
            double result = 0;
            while (operations.top() != '(') {
                char operation = operations.top();
                operations.pop();
                double num2 = numbers.top();
                numbers.pop();
                double num1 = numbers.top();
                numbers.pop();
                if (operation == '+') {
                    result = num1 + num2;
                } else if (operation == '-') {
                    result = num1 - num2;
                } else if (operation == '*') {
                    result = num1 * num2;
                } else if (operation == '/') {
                    result = num1 / num2;
                }
                numbers.push(result);
            }
            operations.pop();
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            // We push the number and the operation to the stacks
            numbers.push(number);
            number = 0;
            operations.push(c);
            continue;
        }
        if (c == '^') {
            // We push the number and the operation to the stacks
            numbers.push(number);
            number = 0;
            operations.push(c);
            continue;
        }
        if (c == '.') {
            decimal_exponent = 0;
            continue;
        }
        if (c >= '0' && c <= '9') {
            if (decimal_exponent == 0) {
                number = number * 10 + (c - '0');
            } else {
                decimal = decimal * 10 + (c - '0');
                decimal_exponent++;
            }
            continue;
        }
    }

    // We push the last number to the stack
    numbers.push(number);

    // We will calculate the result
    double result = 0;

    while (!operations.empty()) {
        char operation = operations.top();
        operations.pop();
        double num2 = numbers.top();
        numbers.pop();
        double num1 = numbers.top();
        numbers.pop();
        if (operation == '+') {
            result = num1 + num2;
        } else if (operation == '-') {
            result = num1 - num2;
        } else if (operation == '*') {
            result = num1 * num2;
        } else if (operation == '/') {
            result = num1 / num2;
        } else if (operation == '^') {
            result = pow(num1, num2);
        }
        numbers.push(result);
    }

    // We will display the result
    // Create a new label in the form to display
    QLabel *label = new QLabel(QString::number(result));
    label->setStyleSheet("font: 75 16pt;");
    ui->verticalLayout->addWidget(label);

    if (ui->verticalLayout->count() > 10) {
        delete ui->verticalLayout->itemAt(0)->widget();
    }
    // We will clear the line edit
    ui->lineEdit->clear();
}

