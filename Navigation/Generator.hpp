#if !defined(GENERATOR_HPP)
#define GENERATOR_HPP

class Generator
{
public:
    Generator() {}
    virtual int get(const int i) const = 0;
    ~Generator() {}
};

#endif // GENERATOR_HPP
