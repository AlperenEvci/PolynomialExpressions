#ifndef _POLY_H_
#define _POLY_H_

#include "PolyNode.h"

PolyNode* CreatePoly(char* expr);
void DeletePoly(PolyNode* poly);
PolyNode* AddNode(PolyNode* head, double coef, int exp);
PolyNode* Add(PolyNode* poly1, PolyNode* poly2);
PolyNode* Subtract(PolyNode* poly1, PolyNode* poly2);
PolyNode* Multiply(PolyNode* poly1, PolyNode* poly2);
double Evaluate(PolyNode* poly, double x);
PolyNode* Derivative(PolyNode *poly);
void Plot(PolyNode* poly, int x1, int x2);
void Print(PolyNode* poly);

#endif
