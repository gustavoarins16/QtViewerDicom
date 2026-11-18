#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "DicomLoader.h"

/**
 * @brief Janela principal da aplicação. Gerencia a interface gráfica (GUI)
 * e faz a ponte entre as ações do usuário e a lógica do DicomLoader.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT // Macro obrigatória do Qt para suportar sinais e slots (MOC)

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    /**
     * @brief Slot acionado quando o usuário clica no botão de abrir arquivo.
     * Abre a caixa de diálogo de arquivos, chama o loader e renderiza a imagem.
     */
    void openDicomFile();

private:
    /**
     * @brief Inicializa e posiciona os componentes visuais da janela.
     */
    void setupUI();

    // Componentes da Interface Gráfica Qt
    QGraphicsView *imageView;   // Área de visualização gráfica com suporte a zoom/scroll
    QGraphicsScene *imageScene; // Cena que armazena o objeto QPixmap (imagem)
    QPushButton *btnOpen;       // Botão de seleção de arquivo DICOM
    QLabel *lblInfo;            // Rótulo de texto para exibir metadados e status

    // Instância da classe de backend DICOM
    DicomLoader dicomLoader;
};

#endif // MAIN_WINDOW_H
