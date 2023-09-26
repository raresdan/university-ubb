#include "Lecture11_live.h"
#include <QtWidgets/QApplication>
#include "GenesGUI.h"
#include "Gene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::vector<Gene> genes{ Gene{ "yqgE", "E_Coli_K12", "ATGAATTTACAGCAT" },
                            Gene{ "ppiA", "M_tuberculosis", "TTTTCATCACCGTCGG" },
                            Gene{ "Col2a1", "Mouse", "TTAAAGCATGGCTCTGTG" } };

    
    GenesGUI ui{genes};
    ui.show();

    return a.exec();
}
