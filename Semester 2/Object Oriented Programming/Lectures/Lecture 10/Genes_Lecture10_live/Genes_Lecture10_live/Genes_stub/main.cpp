#include "Genes_stub.h"
#include <QtWidgets/QApplication>
#include "Gene.h"
#include "GenesGUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font{ "Verdana", 18 };
    a.setFont(font);
    
    std::vector<Gene> genes{ Gene{ "yqgE", "E_Coli_K12", "ATGAATTTACAGCAT" },
                            Gene{ "ppiA", "M_tuberculosis", "TTTTCATCACCGTCGG" },
                            Gene{ "Col2a1", "Mouse", "TTAAAGCATGGCTCTGTG" } };

    // instantiate GUI
    GenesGUI gui{genes};
    gui.show();

    return a.exec();
}
