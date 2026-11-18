#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    // Inicializa o ecossistema de aplicação do Qt com os argumentos do sistema
    QApplication app(argc, argv);

    // Instancia e exibe a janela principal da interface gráfica
    MainWindow window;
    window.show();

    // Inicia o loop principal de eventos gráficos da aplicação Qt
    return app.exec();
}
