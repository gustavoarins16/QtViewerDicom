#ifndef DICOM_LOADER_H
#define DICOM_LOADER_H

#include <string>
#include <vector>
#include <optional>
#include <QImage>

// Estrutura para retornar os metadados e o buffer da imagem de forma segura
struct DicomImageResult {
    int width = 0;
    int height = 0;
    std::vector<unsigned char> pixels;
    std::string patientName;
    std::string modality;
};

class DicomLoader {
public:
    DicomLoader() = default;
    ~DicomLoader() = default;

    // Retorna um std::optional contendo a imagem se bem-sucedido, ou std::nullopt se falhar
    std::optional<DicomImageResult> loadFile(const std::string& filePath);

private:
    void registerCodecs();
    void unregisterCodecs();
};

#endif // DICOM_LOADER_H
