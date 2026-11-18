#include "MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QImage>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI(); // Constrói a interface ao iniciar a janela
}

void MainWindow::setupUI() {
    setWindowTitle("Qt DICOM Viewer - Teste Técnico C++");
    resize(900, 700);

    // Widget central principal da janela
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Criação do Botão de Seleção de Arquivo (Atende ao Escopo Funcional 1)
    btnOpen = new QPushButton("Selecionar Arquivo DICOM (.dcm)", this);
    btnOpen->setStyleSheet("font-size: 14px; padding: 8px;");
    connect(btnOpen, &QPushButton::clicked, this, &MainWindow::openDicomFile);
    mainLayout->addWidget(btnOpen);

    // Criação do Label de Status e Metadados
    lblInfo = new QLabel("Nenhum arquivo carregado.", this);
    lblInfo->setStyleSheet("font-size: 12px; color: #333; margin-bottom: 5px;");
    mainLayout->addWidget(lblInfo);

    // Criação da Área Gráfica de Exibição (Atende ao Escopo 3 e 4)
    imageView = new QGraphicsView(this);
    imageScene = new QGraphicsScene(this);
    imageView->setScene(imageScene);
    mainLayout->addWidget(imageView);

    setCentralWidget(centralWidget);
}

void MainWindow::openDicomFile() {
    // 1. Abre a caixa de diálogo nativa para seleção do arquivo .dcm (Exigência do Requisito 1)
    QString filePath = QFileDialog::getOpenFileName(
        this, 
        tr("Abrir Arquivo DICOM"), 
        "", 
        tr("Arquivos DICOM (*.dcm);;Todos os Arquivos (*.*)")
    );

    // Se o usuário cancelar a janela de seleção, encerra o fluxo
    if (filePath.isEmpty()) {
        return;
    }

    // 2. Delega o carregamento para o backend orientado a objetos (DicomLoader)
    auto result = dicomLoader.loadFile(filePath.toStdString());

    // 3. Tratamento de Erros: Se falhar, exibe mensagem crítica (Exigência do Escopo 4)
    if (!result.has_value()) {
        QMessageBox::critical(
            this, 
            tr("Erro de Leitura"), 
            tr("Não foi possível carregar o arquivo DICOM selecionado.\nO arquivo pode estar corrompido ou em formato inválido.")
        );
        lblInfo->setText("Erro ao carregar o arquivo anterior.");
        return;
    }

    // 4. Renderização bem-sucedida: Mapeia o buffer de pixels para QImage do Qt
    const DicomImageResult& data = result.value();
    
    QImage qimg(data.pixels.data(), data.width, data.height, data.width, QImage::Format_Grayscale8);

    // Limpa a cena anterior e adiciona a nova imagem renderizada
    imageScene->clear();
    QPixmap pixmap = QPixmap::fromImage(qimg);
    imageScene->addPixmap(pixmap);
    imageScene->setSceneRect(pixmap.rect());

    // 5. Atualiza o rótulo de informações com os metadados extraídos (Diferencial técnico)
    QString infoText = QString("Arquivo: %1 | Resolução: %2x%3 px | Modalidade: %4 | Paciente: %5")
                       .arg(filePath.section('/', -1, -1))
                       .arg(data.width)
                       .arg(data.height)
                       .arg(QString::fromStdString(data.modality))
                       .arg(QString::fromStdString(data.patientName));
    
    lblInfo->setText(infoText);
}
