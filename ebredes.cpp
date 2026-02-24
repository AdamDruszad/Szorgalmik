#include <iostream>
#include <string>

struct Naplo {
    std::string nap;
    std::string ora;
};

int main() {
    Naplo hetiNaplo[7] = {
        {"hetfo", "6:40"},
        {"kedd", "8:00"},
        {"szerda", "8:00"},
        {"csutortok", "6:40"},
        {"pentek", "8:00"},
        {"szombat", "9:00"},
        {"vasarnap", "8:00"}
    };

    for (const auto& Naplo :hetiNaplo) {
        std::cout << Naplo.nap
                  << " - "
                  << Naplo.ora
                  << " "
                  << "ora\n";
    }

}