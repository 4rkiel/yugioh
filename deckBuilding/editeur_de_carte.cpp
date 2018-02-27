#include "editeur_de_carte.h"

editeur_de_carte::editeur_de_carte()
{
    createMenu();
    createHorizontalGroupBox();
    createGridGroupBox();
    createFormGroupBox();

    bigEditor = new QTextEdit;
    bigEditor->setPlainText(QString::fromUtf8("Description / Effet de la carte..."));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(bigEditor);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    setWindowTitle(tr("Basic Layouts"));
}

void editeur_de_carte::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
}

void editeur_de_carte::createHorizontalGroupBox()
{
    horizontalGroupBox = new QGroupBox("Horizontal layout");
    QHBoxLayout *layout = new QHBoxLayout;

    for (int i = 0; i < NumButtons; ++i)
    {
        buttons[i] = new QPushButton(tr("Button %1%2").arg(i + 1).arg(3));
        layout->addWidget(buttons[i]);
    }
    horizontalGroupBox->setLayout(layout);
}

void editeur_de_carte::createGridGroupBox()
{
    gridGroupBox = new QGroupBox(tr("Grid layout"));
    QGridLayout *layout = new QGridLayout;

    for (int i = 0; i < NumGridRows; ++i)
    {
        labels[i] = new QLabel(tr("Line %1:").arg(i + 1));
        lineEdits[i] = new QLineEdit;
        layout->addWidget(labels[i], i + 1, 0);
        layout->addWidget(lineEdits[i], i + 1, 1);
    }

    smallEditor = new QTextEdit;
    smallEditor->setPlainText(QString::fromUtf8("a remplacer par l'image selectionnée"));
    layout->addWidget(smallEditor, 0, 2, 4, 1);
    layout->setColumnStretch(1, 30);
    layout->setColumnStretch(2, 20);
    gridGroupBox->setLayout(layout);
}

void editeur_de_carte::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Form layout"));
    QFormLayout *layout = new QFormLayout;

    QSpinBox *spinAttaque = new QSpinBox;
    spinAttaque -> setSingleStep(500);
    spinAttaque -> setAccelerated(true);
    spinAttaque -> setMaximum(5000);
    spinAttaque -> setMinimum(0);

    QSpinBox *spinDefense = new QSpinBox;
    spinDefense -> setSingleStep(500);
    spinDefense -> setAccelerated(true);
    spinDefense -> setMaximum(5000);
    spinDefense -> setMinimum(0);

    layout->addRow(new QLabel(tr("Line 1:")), new QLineEdit);
    layout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
    layout->addRow(new QLabel(tr("Attaque:")), spinAttaque);
    layout->addRow(new QLabel(tr("Defense:")), spinDefense);
    formGroupBox->setLayout(layout);
}

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    editeur_de_carte w;
    w.resize(500, 700);
    w.setWindowTitle("editeur de cartes");

    w.show();


    return app.exec();
}
