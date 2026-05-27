#pragma once
#include <string>

// Interfață pur abstractă (Polimorfism)
class IObserver {
public:
    virtual void notificare(const std::string& mesaj) = 0;
    virtual ~IObserver() = default;
};