#include "ppi_manager.hpp"

int PPI = DEFAULT_PPI;

int get_ppi() {
   return PPI;
}

void set_ppi(int ppi) {
    PPI = ppi;
}
