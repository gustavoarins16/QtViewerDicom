#include "DicomLoader.h"
#include <iostream>

// Cabeçalhos do DCMTK
#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <dcmtk/dcmjpeg/djdecode.h>
#include <dcmtk/dcmdata/dcdeftag.h>

void DicomLoader::registerCodecs() {
    DJDecoderRegistration::registerCodecs();
}

void DicomLoader::unregisterCodecs() {
    DJDecoderRegistration::cleanup();
}

std::optional<DicomImageResult> DicomLoader::loadFile(const std::string& filePath) {
    registerCodecs();

    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile(filePath.c_str());

    if (status.bad()) {
        unregisterCodecs();
        return std::nullopt; // Falha ao ler arquivo físico ou formato inválido
    }

    DcmDataset* dataset = fileformat.getDataset();
    DicomImage* dimage = new DicomImage(dataset, dataset->getOriginalXfer());

    if (!dimage || dimage->getStatus() != EIS_Normal) {
        delete dimage;
        unregisterCodecs();
        return std::nullopt; // Falha no processamento de pixel do DICOM
    }

    DicomImageResult result;
    result.width = static_cast<int>(dimage->getWidth());
    result.height = static_cast<int>(dimage->getHeight());

    // Extração segura dos pixels convertidos para 8-bits
    int depth = 8;
    const void* pixelData = dimage->getOutputData(depth);

    if (!pixelData) {
        delete dimage;
        unregisterCodecs();
        return std::nullopt;
    }

    size_t dataSize = result.width * result.height * (dimage->isMonochrome() ? 1 : 3);
    result.pixels.assign(
        static_cast<const unsigned char*>(pixelData),
        static_cast<const unsigned char*>(pixelData) + dataSize
    );

    // Opcional: Extração de metadados básicos (ótimo diferencial para o teste!)
    OFString valStr;
    if (dataset->findAndGetOFString(DCM_PatientName, valStr).good()) {
        result.patientName = valStr.c_str();
    } else {
        result.patientName = "Anônimo / Não informado";
    }

    if (dataset->findAndGetOFString(DCM_Modality, valStr).good()) {
        result.modality = valStr.c_str();
    } else {
        result.modality = "N/A";
    }

    delete dimage;
    unregisterCodecs();

    return result;
}
