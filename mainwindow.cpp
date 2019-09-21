#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    //Open file dialog box and store filename
    QString filename = QFileDialog::getOpenFileName(this, "Open File");

    //Initialize file object
    QFile file(filename);

    //Store current filename
    currentFile = filename;

    //Open file
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        //Warning if file opening fails
        QMessageBox::warning(this, "Warning", "Cannot Open File : " + file.errorString());
        return;
    }
    //Set window title to filename
    setWindowTitle(filename);

    //Stream through file content
    QTextStream in(&file);

    //read file into text
    QString text = in.readAll();

    //Display the text in textEdit
    ui->textEdit->setText(text);

    //Close file
    file.close();



}

void MainWindow::on_actionSave_as_triggered()
{
    //Open file dialog box to save file
    QString fileName = QFileDialog::getSaveFileName(this, "Save as...");

    //Initialize file object
    QFile file(fileName);

    //Open file to write
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        //If opening fails, show warning dialog box
        QMessageBox::warning(this, "Warning", "Cannot Save File : " + file.errorString());
        return;
    }

    //Save filename
    currentFile = fileName;

    //Set window title to filename
    setWindowTitle(fileName);

    //Stream out of file
    QTextStream out(&file);

    //Copy text from textEdit
    QString text = ui->textEdit->toPlainText();

    //Write to file
    out << text;

    //Close file
    file.close();
}

void MainWindow::on_actionPrint_triggered()
{
    //Initialize printer object (Interacts with any printer on the network)
    QPrinter printer;

    //Set printer name if known
    printer.setPrinterName("Printer Name");

    //Open Printer Dialog box
    QPrintDialog pDialog(&printer, this);

    //If Printer is not accessible
    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot access printer");
        return;
    }

    //Send text to printer
    ui->textEdit->print(&printer);

}


void MainWindow::on_actionExit_triggered()
{
    //Quit application
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
