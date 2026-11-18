#include "MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QImage>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
}

void MainWindow::setupUI() {
    setWindowTitle("Qt DICOM Viewer - Teste Técnico C++");
    resize(900, 700);

    // Widget Central e Layouts
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Botão de Seleção de Arquivo
    btnOpen = new QPushButton("Selecionar Arquivo DICOM (.dcm)", this);
    btnOpen->setStyleSheet("font-size: 14px; padding: 8px;");
    connect(btnOpen, &QPushButton::clicked, this, &MainWindow::openDicomFile);
    mainLayout->addWidget(btnOpen);

    // Rótulo de Informações / Metadados
    lblInfo = new QLabel("Nenhum arquivo carregado.", this);
    lblInfo->setStyleSheet("font-size: 12px; color: #333; margin-bottom: 5px;");
    mainLayout->addWidget(lblInfo);

    // Área de Visualização Gráfica (Zoom e Navegação fluidos)
    imageView = new QGraphicsView(this);
    imageScene = new QGraphicsScene(this);
    imageView->setScene(imageScene);
    mainLayout->addWidget(imageView);

    setCentralWidget(centralWidget);
}

void MainWindow::openDicomFile() {
    // 1. Janela de seleção de arquivos exigida pelo escopo funcional
    QString filePath = QFileDialog::getOpenFileName(
        this, 
        tr("Abrir Arquivo DICOM"), 
        "", 
        tr("Arquivos DICOM (*.dcm);;Todos os Arquivos (*.*)")
    );

    if (filePath.isEmpty()) {
        return; // Usuário cancelou a seleção
    }

    // 2. Carrega o arquivo usando nossa classe orientada a objetos
    auto result = dicomLoader.loadFile(filePath.toStdString());

    if (!result.has_value()) {
        // Mensagem de erro obrigatória para arquivos inválidos
        QMessageBox::critical(
            this, 
            tr("Erro de Leitura"), 
            tr("Não foi possível carregar o arquivo DICOM selecionado.\nO arquivo pode estar corrompido ou em um formato não suportado.")
        );
        lblInfo->setText("Erro ao carregar o arquivo anterior.");
        return;
    }

    // 3. Renderiza a imagem no Qt
    const DicomImageResult& data = result.value();
    
    QImage qimg(data.pixels.data(), data.width, data.height, data.width, QImage::Format_Grayscale8);

    imageScene->clear();
    QPixmap pixmap = QPixmap::fromImage(qimg);
    imageScene->addPixmap(pixmap);
    imageScene->setSceneRect(pixmap.rect());

    // Atualiza texto de status com informações úteis (Diferencial de qualidade!)
    QString infoText = QString("Arquivo: %1 | Resolução: %2x%3 px | Modalidade: %4 | Paciente: %5")
                       .arg(filePath.section('/', -1, -1))
                       .arg(data.width)
                       .arg(data.height)
                       .arg(QString::fromStdString(data.modality))
                       .arg(QString::fromStdString(data.patientName));
    
    lblInfo->setText(infoText);
}
