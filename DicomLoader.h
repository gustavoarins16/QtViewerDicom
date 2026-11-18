#ifndef DICOM_LOADER_H
#define DICOM_LOADER_H

#include <string>
#include <vector>
#include <optional>
#include <QImage>

/**
 * @brief Estrutura para armazenar os dados extraídos do DICOM de forma segura.
 * Utiliza tipos nativos e std::vector para evitar vazamentos de memória.
 */
struct DicomImageResult {
    int width = 0;
    int height = 0;
    std::vector<unsigned char> pixels; // Buffer contendo os pixels da imagem processada
    std::string patientName;           // Metadatak: Nome do paciente
    std::string modality;              // Metadados: Modalidade do exame (ex: CT, MR)
};

/**
 * @brief Classe responsável exclusivamente pelo carregamento, descompressão 
 * e processamento de arquivos DICOM utilizando a biblioteca DCMTK.
 */
class DicomLoader {
public:
    DicomLoader() = default;
    ~DicomLoader() = default;

    /**
     * @brief Carrega um arquivo DICOM do disco.
     * @param filePath Caminho absoluto ou relativo do arquivo .dcm.
     * @return std::optional contendo o DicomImageResult se bem-sucedido, ou std::nullopt em caso de falha.
     */
    std::optional<DicomImageResult> loadFile(const std::string& filePath);

private:
    // Métodos auxiliares para gerenciar codecs de descompressão do DCMTK (como JPEG)
    void registerCodecs();
    void unregisterCodecs();
};

#endif // DICOM_LOADER_H
