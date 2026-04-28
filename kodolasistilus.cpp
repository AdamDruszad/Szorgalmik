#include <iostream>
#include <cstdint>
#include <array>
#include <string>


class Doboz {
public:
    Doboz() noexcept : length{0}, width{0}, height{0} {}
    Doboz(std::int32_t l, std::int32_t w, std::int32_t h) noexcept
        : length{l}, width{w}, height{h} {}

    std::int32_t getHeight() const noexcept { return height; }

private:
    std::int32_t length;
    std::int32_t width;
    std::int32_t height;
};

std::int32_t bigfibo(std::int32_t a, std::int32_t b) noexcept {
    if (b < 0) { 
        return -1; 
    }

    std::int32_t legnagyobb_fibo{-1};
    std::int32_t elozo{0};
    std::int32_t jelenlegi{1};
    
    if ((a <= 0) && (b >= 0)) {
        legnagyobb_fibo = 0;
    }

    while (jelenlegi <= b) {
        if (jelenlegi >= a) {
            legnagyobb_fibo = jelenlegi; 
        }
        
        const std::int32_t kovetkezo{elozo + jelenlegi};
        elozo = jelenlegi;
        jelenlegi = kovetkezo;
    }

    return legnagyobb_fibo;
}

std::array<float, 4U> egydim(const std::array<std::array<std::int32_t, 4U>, 4U>& arr) noexcept {
    std::array<float, 4U> avgArr{}; 
    for (std::size_t i{0U}; i < 4U; ++i) {
        float avg{0.0F};
        for (std::size_t j{0U}; j < 4U; ++j) {
            avg += static_cast<float>(arr[i][j]);
        }
        avgArr[i] = avg / 4.0F;
    }
    
    return avgArr;
}

void beKer() noexcept {
    std::int32_t n{0};
    std::cout << "Hany szot szeretnel beirni (max 10): ";
    std::cin >> n;

    if ((n <= 0) || (n > 10)) {
        std::cout << "Hiba: Ervenytelen mennyiseg!\n";
        return;
    }

    std::array<std::string, 10U> sztringek{};
    for (std::int32_t i{0}; i < n; ++i) {
        std::cout << "Add meg a szot: ";
        std::cin >> sztringek[static_cast<std::size_t>(i)];
    }

    std::string legkisebb{sztringek[0]};
    std::string legnagyobb{sztringek[0]};
    
    for(std::int32_t i{0}; i < n; ++i) {
        const auto& aktualis_szo = sztringek[static_cast<std::size_t>(i)];
        if (aktualis_szo.length() > legnagyobb.length()) {
            legnagyobb = aktualis_szo;
        }
        if (aktualis_szo.length() < legkisebb.length()) {
            legkisebb = aktualis_szo;
        }
    }
    
    std::cout << "Legkisebb: " << legkisebb << " Legnagyobb: " << legnagyobb << "\n";
}

std::int32_t main() noexcept {
    std::cout << bigfibo(1, 10) << "\n";

    std::array<std::array<std::int32_t, 4U>, 4U> twoDimArr{{
        {{1, 2, 3, 4}},
        {{5, 6, 7, 8}},
        {{9, 10, 11, 12}},
        {{13, 14, 15, 16}}
    }};
    
    std::array<float, 4U> eredmeny{egydim(twoDimArr)};
    for (const float& atlag : eredmeny) {
        std::cout << atlag << " ";
    }
    std::cout << "\n";
    
    beKer();
    
    std::array<Doboz, 5U> dobozok{};
    for (std::size_t i{0U}; i < 5U; ++i) {
        dobozok[i] = Doboz(static_cast<std::int32_t>(i) + 1,
                           static_cast<std::int32_t>(i) + 4,
                           static_cast<std::int32_t>(i) + 2);
    }
    
    std::int32_t magassag{0};
    for (const auto& doboz : dobozok) {
        magassag += doboz.getHeight();
    }
    
    std::cout << "A torony teljes magassaga: " << magassag << "\n";
    
    return 0;
}