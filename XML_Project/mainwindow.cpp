#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit); //remove side spaces
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_actionnew_triggered()
{
file_path="";
ui->textEdit->setText("");
}


void MainWindow::on_actionopen_triggered()
{
    QString filter="XML File (*.xml)";
QString file_name=QFileDialog::getOpenFileName(this,"open the XML file","c://",filter);
QFile file(file_name);
file_path=file_name;
if(!file.open(QFile :: ReadOnly |QFile:: Text) ){
  QMessageBox::warning(this,"..","file cant be open");
  return;

}
QTextStream in(&file);
QString text=in.readAll();
ui->textEdit->setText(text);
file.close();
}
void MainWindow::on_actionsave_as_triggered()
{
    //QString filter="XML File (*.xml)";
QString file_name=QFileDialog::getSaveFileName(this,"open the XML file","c://");
QFile file(file_name);
file_path=file_name;
if(!file.open(QFile :: WriteOnly |QFile:: Text) ){
  QMessageBox::warning(this,"..","file cant be open");
  return;

}
QTextStream out(&file);
QString text=ui->textEdit->toPlainText();
out<<text;
file.flush();
file.close();
}


void MainWindow::on_actionsave_triggered()
{


QFile file(file_path);

if(!file.open(QFile :: WriteOnly |QFile:: Text) ){
  QMessageBox::warning(this,"..","file cant be open");
  return;

}
QTextStream out(&file);
QString text=ui->textEdit->toPlainText();
out<<text;
file.flush();
file.close();
}


void MainWindow::on_actioncut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actioncopy_triggered()
{
 ui->textEdit->copy();
}


void MainWindow::on_actionpaste_triggered()
{
 ui->textEdit->paste();
}


void MainWindow::on_actionto_json_triggered()
{
      vector<string> XML_Strings, Right_XML;
      vector<int> Errors;
      Tree x;
      QString str1 = ui->textEdit->toPlainText();
      if (str1 != ""){
          string text = str1.toUtf8().constData();
          XML_Strings = XML_Parsing_Data(text);
          checking_errors(XML_Strings, Right_XML, Errors);
          string str = "";
          // Errors Position in Screen
           x.insert_node_2_tree(Right_XML, Errors);
          //this->x = x;
          str = x.xml_2_json();
          ui->textEdit->setPlainText(QString::fromStdString(str));
      }
      else
          ui->statusbar->showMessage("The file is empty");
}


void MainWindow::on_actioncorrect_triggered()
{
    vector<string> XML_Strings, Right_XML;
    vector<int> Errors;
    Tree x;
    QString str = ui->textEdit->toPlainText();
    if (str != ""){
        string text = str.toUtf8().constData();
        XML_Strings = XML_Parsing_Data(text);
        int e = checking_errors(XML_Strings, Right_XML, Errors);
        if (e){
            string str = "";
            // Errors Position in Screen
            x.insert_node_2_tree(Right_XML, Errors);
            // Pre-Order Traverse
            str = x.Pre_Order();
            ui->textEdit->setPlainText(QString::fromStdString(str));
        }
        else
            ui->statusbar->showMessage("No errors exist in the file");
    }
    else{
        ui->statusbar->showMessage("The file is empty");
    }
}


void MainWindow::on_actioncompress_triggered()
{
     QString filter="XML File (*.xml)";
    QString Path = QFileDialog::getOpenFileName(this, tr("Open XML File to compress"),"c://",filter);
      if(Path.isEmpty()) return;

      QFile File(Path);
      if(!File.open(QIODevice::ReadOnly | QFile::Text)){
          QMessageBox::critical(this, "Error", File.errorString());
          return;
      }

      QTextStream in(&File);
    QString  Text = in.readAll();

      int index;
      for(int i = 0; i < Path.length(); i++){
          if(Path[i] == '/')
              index = i;
      }
      QString Name = Path.mid(index+1, Path.length()-index-1);
      QString Path1 = Path.mid(0, index+1);
      QFileInfo fi(Path);                     // get the data of file
      QString Extension = fi.suffix();        // get the extension of the file

          string str = Text.toUtf8().constData();
          string File_Name = Name.toUtf8().constData();
          string File_Path = Path1.toUtf8().constData();
          vector<int> a = compress(str);
          writeFile(File_Path+File_Name.substr(0, File_Name.length()-4)+".dat", a);

      File.close();
}


void MainWindow::on_actiondetect_triggered()
{
    vector<string> XML_Strings, Right_XML;
    vector<int> Errors;
    QString str = ui->textEdit->toPlainText();
    if (str != ""){
        string text = str.toUtf8().constData();
        XML_Strings = XML_Parsing_Data(text);
        string error = "\t<<==== ERROR\t";
        int e = checking_errors(XML_Strings, Right_XML, Errors);
        if (e){
            // Errors Position in Screen
            QString str = "";
            string New = "";
            for(unsigned int i = 0; i < Errors.size(); i++){
                str += QString::fromStdString(to_string(Errors[i])) + ", ";
            }
            ui->statusbar->showMessage("     Number of errors = " +
                                       QString::fromStdString(to_string(e))+ ", Their Posistions: " + str);
            int count = 0;
            for(unsigned int i = 0; i < XML_Strings.size(); i++){
                if(Get_Type(XML_Strings[i]) == 'O'){
                    New=New+XML_Strings[i];
                    if(i == Errors[count]){
                        count++;
                        New=New+error;
                    }
                    New=New+"\n";
                }
                else if(Get_Type(XML_Strings[i]) == 'V'){
                    New=New+XML_Strings[i];
                    if(i == Errors[count]){
                        count++;
                        New=New+error;
                    }
                    New=New+"\n";
                }
                else if(Get_Type(XML_Strings[i]) == 'C'){
                    New=New+XML_Strings[i];
                    if(i == Errors[count]){
                        count++;
                        New=New+error;
                    }
                    New=New+"\n";
                }
            }
            ui->textEdit->setText(QString::fromStdString(New));
        }
        else
            ui->statusbar->showMessage("No errors exist in the file");
    }
    else
        ui->statusbar->showMessage("The file is empty");
}


void MainWindow::on_actionminify_triggered()
{
    QString str = ui->textEdit->toPlainText();
       string text = str.toUtf8().constData();
       if (str != ""){
           string str1 = "";
           for(unsigned int i = 0; i < text.length(); i++){
               if(text[i] == '<'){
                   while(text[i] != '>'){
                       str1 += text[i];
                       i++;
                   }
                   str1 += text[i];
               }
               else if((isValid(text[i+1]) || isValid(text[i-1]))&&(text[i] != '\n' && text[i] != '\t')) str1 += text[i];
               else if(text[i] != ' ' && text[i] != '\n' && text[i] != '\t')
                   str1 += text[i];
           }
           ui->textEdit->setPlainText(QString::fromStdString(str1));
       }
       else    ui->statusbar->showMessage("The file is empty");
}


void MainWindow::on_actionmakeindentions_triggered()
{
    vector<string> XML_Strings, Right_XML;
      vector<int> Errors;
      string str ="";
      QString str1 = ui->textEdit->toPlainText();
      if (str1 != ""){
          string text = str1.toUtf8().constData();
          XML_Strings = XML_Parsing_Data(text);
          checking_errors(XML_Strings, Right_XML, Errors);
          str = formatting(Right_XML);
          ui->textEdit->setPlainText(QString::fromStdString(str));
      }
      else    ui->statusbar->showMessage("The file is empty");
}


void MainWindow::on_actiondecompress_triggered()
{
    QString Path = QFileDialog::getOpenFileName(this, tr("Open Compressed File"));
    if(Path.isEmpty()) return;

    QFile File(Path);
    if(!File.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::critical(this, "Error", File.errorString());
        return;
    }

    QTextStream in(&File);


    int index;
    for(int i = 0; i < Path.length(); i++){
        if(Path[i] == '/')
            index = i;
    }
    string File_Path = Path.toUtf8().constData();;
    QFileInfo fi(Path);                     // get the data of file
    QString Extension = fi.suffix();        // get the extension of the file
    if(Extension == "dat"){
        vector<int>b;
        b = readFile(File_Path);			//read encoded numbers from .dat file to decode
        b.pop_back();						//delete end of file
        string str = decompress(b);				//decode to original file
        QString qstr = QString::fromStdString(str);

        ui->textEdit->setText(qstr);
    }
    else
        QMessageBox::critical(this, "Erorr", "File Type must be dat");

    File.close();
}

