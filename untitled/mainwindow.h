#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Headers.h"
#include "compress.h"
#include "XML_Data.h"
#include "substring.h"
#include "Tree.h"
#include "format.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionnew_triggered();

    void on_actionopen_triggered();

    void on_actionsave_as_triggered();

    void on_actionsave_triggered();

    void on_actioncut_triggered();

    void on_actioncopy_triggered();

    void on_actionpaste_triggered();

    void on_actionto_json_triggered();

   void on_actioncorrect_triggered();

    void on_actioncompress_triggered();

    void on_actiondetect_triggered();

    void on_actionminify_triggered();

    void on_actionmakeindentions_triggered();

private:
    Ui::MainWindow *ui;
    QString file_path;
};
#endif // MAINWINDOW_H
