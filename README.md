# Qt DICOM Viewer

Aplicação desktop desenvolvida em **C++17** utilizando o framework **Qt 6** e a biblioteca **DCMTK** para leitura, descompressão e visualização de imagens médicas no formato DICOM (`.dcm`).

---

## 📋 Descrição da Solução

O projeto foi arquitetado seguindo princípios de **Programação Orientada a Objetos (POO)** e separação de responsabilidades (*Separation of Concerns*), dividindo o sistema em duas camadas principais:

- **Camada de Backend (`DicomLoader`):** Responsável por encapsular a biblioteca DCMTK, registrar codecs de descompressão (suportando imagens comprimidas como JPEG), validar a integridade do arquivo, extrair metadados básicos (Nome do Paciente e Modalidade) e normalizar o *Pixel Data* para um buffer seguro em memória utilizando recursos modernos do C++17 (`std::optional` e `std::vector`).
- **Camada de Apresentação / GUI (`MainWindow`):** Desenvolvida com **Qt Widgets**, oferece uma interface limpa e responsiva para seleção de arquivos via diálogo nativo do sistema (`QFileDialog`), exibição de metadados, tratamento visual de erros (`QMessageBox`) e renderização otimizada da imagem através de `QGraphicsView` e `QGraphicsScene`.

---

## 🛠️ Bibliotecas e Tecnologias Utilizadas

- **Linguagem:** C++17
- **Sistema de Build:** CMake (versão 3.16 ou superior)
- **Framework Gráfico:** **Qt 6** (módulos `Core`, `Gui` e `Widgets`)
- **Processamento DICOM:** **DCMTK** (DICOM Toolkit — módulos `dcmdata`, `dcmimgle`, `dcmimage`, `dcmjpeg`, `oflog` e `ofstd`)

---

## ⚙️ Pré-requisitos e Configuração (Ubuntu / Linux)

Para compilar e executar o projeto em ambiente Linux, instale o compilador C++, o CMake e os pacotes de desenvolvimento do Qt 6 e DCMTK:

```bash
sudo apt update
sudo apt install build-essential cmake libdcmtk-dev qt6-base-dev pkgconf


## 🚀 Compilação e execução

## 1. Clone o repositório e acesse o diretório raiz do projeto:

git clone [https://github.com/gustavoarins16/QtViewerDicom.git](https://github.com/gustavoarins16/QtViewerDicom.git)
cd QtViewerDicom

## 2. Configure e compile o projeto utilizando o CMake:

mkdir build
cd build
cmake ..
make

## 3. Execução:

./QtViewerDicom

## 4. Uso da aplicação:
 **Clique no botão "Selecionar Arquivo DICOM (.dcm)".
- Escolha um arquivo .dcm válido no seu sistema de arquivos.
- A imagem é renderizada e é mostrada na área centrar do software.

## 🛠️ Estrutura do projeto


├── CMakeLists.txt      # Configuração de build, dependências, MOC e automação do Qt
├── DicomLoader.h       # Declaração da classe de backend e estruturas de dados DICOM
├── DicomLoader.cpp     # Implementação do parser DICOM via DCMTK, codecs e extração de pixels
├── MainWindow.h        # Declaração da janela principal e slots de interação da GUI
├── MainWindow.cpp      # Implementação da interface Qt, QFileDialog, renderização e erros
├── main.cpp            # Ponto de entrada da aplicação Qt
└── README.md           # Documentação e instruções do projeto


