#ifndef VERTICE_H_
#define VERTICE_H_

#include <iostream>
using namespace std;

class Vertice {
public:
	Vertice(){};
	Vertice(float a, float b, int c)
	{
		setX(a);
		setY(b);
		setIndice(c);
		//cout << "Vertice " << c << " insertado ok " << endl;
	}

	void mostrar();
	void normalize();
	float largovector();
	float dot(Vertice);

    int getIndice() const
    {
        return indice;
    }

    float getX() const
    {
        return x;
    }

    float getY() const
    {
        return y;
    }

    void setIndice(int indice)
    {
        this->indice = indice;
    }

    void setX(float x)
    {
        this->x = x;
    }

    void setY(float y)
    {
        this->y = y;
    }

public:

	float x;
	float y;
	int indice;

};

#endif /*VERTICE_H_*/

