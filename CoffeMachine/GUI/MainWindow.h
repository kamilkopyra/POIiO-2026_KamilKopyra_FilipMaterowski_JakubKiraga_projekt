#pragma once
#include <QMainWindow>
#include "Ingredient.h"   

// Ten plik generuje CMake automatycznie z MainWindow.ui
// Nazwa: ui_MainWindow.h, prefix "Ui::"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT  // ← WYMAGANE dla sygnałów i slotów

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow* ui;       // ← wskaźnik do wygenerowanego U
};