#include <iostream>
#include "utils/DcmReader.hh"
#include "utils/Mat3d.hh"
#include "visualizer/Visualizer.hh"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <DICOM file path>" << std::endl;
        return 1;
    }
    DcmReader& reader = DcmReader::getInstance();

    Mat3d mat = reader.getMat(argv[1]);

    Visualizer v(mat.getImgSize(), mat.getCols(), mat.getRows());

    v.attach(mat);

    v.show();

    return 0;
}
