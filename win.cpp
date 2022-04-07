#include "win.h"

Win::Win(QWidget *parent)
	: QWidget(parent)
{
    setWindowTitle("Возведение в квадрат"); // заголовок окна

    frame = new QFrame(this); // рамка, находящаяся в левой части
	frame->setFrameShadow(QFrame::Raised);
	frame->setFrameShape(QFrame::Panel);

    inputLabel = new QLabel("Введите число:", this); // надпись "Введите число"
    inputEdit = new QLineEdit("", this); // окошко для ввода числа, пока что пустое
    outputLabel = new QLabel("Результат:", this); // надпись "Результат"
    outputEdit = new QLineEdit("", this); // окошко для вывода ответа, пока что пустое
    nextButton = new QPushButton("Следующее", this); // кнопка "Следующее"
    exitButton = new QPushButton("Выход", this); // кнопка "Выход"

    QVBoxLayout *vLayout1 = new QVBoxLayout(frame); // первый вертикальный компоновщик, в нём содержатся элементы из левой части окна-приложения
	vLayout1->addWidget(inputLabel);
	vLayout1->addWidget(inputEdit);
	vLayout1->addWidget(outputLabel);
	vLayout1->addWidget(outputEdit);
	vLayout1->addStretch();

    QVBoxLayout *vLayout2 = new QVBoxLayout(); // второй вертикальный компоновщик, в нём содержатся элементы из правой части окна-приложения
	vLayout2->addWidget(nextButton);
	vLayout2->addWidget(exitButton);
	vLayout2->addStretch();

    QHBoxLayout *hLayout = new QHBoxLayout(this); // горизонтальный компоновщик, управляет расположением элементов двух вышеупомянутых компоновщиков
	hLayout->addWidget(frame);
	hLayout->addLayout(vLayout2);

	begin();

    connect(exitButton, &QPushButton::clicked, this, &Win::close); // настройки кнопки выхода
    connect(nextButton, &QPushButton::clicked, this, &Win::begin); // настройки кнопки "следующее"
    connect(inputEdit, &QLineEdit::returnPressed, this, &Win::calc); // настройки поля для ввода числа
}

void Win::begin()
{
    inputEdit->clear(); // поле ввода вначале должно быть пустым
    nextButton->setEnabled(false); // кнопка "следующее" пока что неактивна
	nextButton->setDefault(false);
    inputEdit->setEnabled(true); // окно для ввода активно
    outputLabel->setVisible(false); // надпись "результат" в определенный момент становится видимой
    outputEdit->setVisible(false); // окно дл ответа в определенный момент становится видимым
    outputEdit->setEnabled(false); // но оно же и становится неактивным
    inputEdit->setFocus(); // фокус ставится на окно для ввода (для удобства)
}

void Win::calc()
{
	bool Ok = true;
	float r, a;

    QString str = inputEdit->text(); // считывание введенного числа
    a = str.toDouble(&Ok); // возвращение строки, преобразованной в значение типа double

	if (Ok)
	{
        r = a * a; // a - переменная для введенного числа, r - для ответа

        str.setNum(r); // устанавливает строку в печатное представление числа

        outputEdit->setText(str); // вывод ответа, содержащегося в переменной str
        inputEdit->setEnabled(false); // окно для ввода становится неактивным, окна для вывода становятся видимыми, и т.д.
		outputLabel->setVisible(true);
		outputEdit->setVisible(true);
		nextButton->setDefault(true);
		nextButton->setEnabled(true);
		nextButton->setFocus();
	}
    else if (!str.isEmpty()) // проверка вводимой строки
	{
		QMessageBox msgBox(QMessageBox::Information, "Возведение в квадрат.", "Введено неверное значение.", QMessageBox::Ok);
		msgBox.exec();
	}
}
