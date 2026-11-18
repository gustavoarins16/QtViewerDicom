# Qt DICOM Viewer

Aplicação desktop desenvolvida em **C++17** utilizando o framework **Qt 6** e a biblioteca **DCMTK** para leitura, descompressão e visualização de imagens médicas no formato DICOM (`.dcm`).

---

## 📋 Descrição da Solução

O projeto foi arquitetado seguindo princípios de **Programação Orientada a Objetos (POO)** e separação de responsabilidades (*Separation of Concerns*), dividindo o sistema em duas camadas principais:

* **Camada de Domínio / Backend (`DicomLoader`):** Responsável por encapsular a biblioteca DCMTK, registrar codecs de descompressão (suportando imagens comprimidas como JPEG Baseline/Lossless), validar a integridade do arquivo, extrair metadados básicos (Nome do Paciente e Modalidade) e normalizar o *Pixel Data* para um buffer seguro em memória utilizando recursos modernos do C++17 (`std::optional` e `std::vector`).
* **Camada de Apresentação / GUI (`MainWindow`):** Desenvolvida com **Qt Widgets**, oferece uma interface limpa e responsiva para seleção de arquivos via diálogo nativo do sistema (`QFileDialog`), exibição de metadados, tratamento visual de erros (`QMessageBox`) e renderização otimizada da imagem através de `QGraphicsView` e `QGraphicsScene`.

---

## 🛠️ Bibliotecas e Tecnologias Utilizadas

* **Linguagem:** C++17
* **Sistema de Build:** CMake (versão 3.16 ou superior)
* **Framework Gráfico:** **Qt 6** (módulos `Core`, `Gui` e `Widgets`)
* **Processamento DICOM:** **DCMTK** (DICOM Toolkit — módulos `dcmdata`, `dcmimgle`, `dcmimage`, `dcmjpeg`, `oflog` e `ofstd`)

---

## ⚙️ Pré-requisitos e Configuração (Ubuntu / Debian)

Para compilar e executar o projeto em ambiente Linux (Ubuntu), instale o compilador C++, o CMake e os pacotes de desenvolvimento do Qt 6 e DCMTK:

```bash
sudo apt update
sudo apt install build-essential cmake libdcmtk-dev qt6-base-dev pkgconf
