#ifndef VISITEE_H
#define VISITEE_H

class Visitor;

class Visitee
{
public:
    virtual void accept(Visitor &visitor) = 0;
};

#endif // VISITEE_H
