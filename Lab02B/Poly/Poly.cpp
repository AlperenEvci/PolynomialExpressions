// 152120211124-AlperenEvci  --- 152120211106-EmirSelengil
#include <stdio.h>
#include "Poly.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;
//-------------------------------------------------
// Creates a polynomial from an expression.
// Returns a pointer to the first PolyNode in the list (head of the list)
//
// Expression will be of the following sort:
// Ex1: 2.3x^4 + 5x^3 - 2.64x - 4
// Ex2: -4.555x^10 - 45.44
// Ex3: x^6 + 2x^4 - x^3 - 6.3x + 4.223 
// Ex4: 34
// Ex5: -x+1
// Ex6: -3x^4    +   4x
// Ex7: -2x  - 5
//
PolyNode* CreatePoly(char* expr) {
	// Create a vector to store the individual terms of the polynomial expression
	vector<string> terms;
	string term;
	bool is_coef = true;

	// Variables to temporarily store coefficient and exponent values
	string temp_coefs = "";
	string temp_exps = "";
	double coef_value = 0;
	int exp_value = 0;

	// Create two pointers for the head and tail of the linked list
	PolyNode* head = new PolyNode();
	PolyNode* tail = new PolyNode();

	// Convert the input expression to a string and remove any spaces
	string str(expr);
	str.erase(remove(str.begin(), str.end(), ' '), str.end());

	// Split the expression into individual terms based on '+' or '-' characters
	for (char c : str) {
		if (c == '+' || c == '-') {
			if (!term.empty()) {
				terms.push_back(term);
				term.clear();
			}
		}
		term += c;
	}

	// Add the last term to the vector if it's not empty
	if (!term.empty()) {
		terms.push_back(term);
	}

	// Iterate through the individual terms
	for (int i = 0; i < terms.size(); i++) {
		// Iterate through the characters in each term
		for (int j = 0; j < terms[i].size(); j++) {
			if (terms[i][j] == 'x') {
				is_coef = false;
				// Determine the coefficient value
				if (temp_coefs == "-")
					coef_value = -1;
				else if (temp_coefs == "+" || temp_coefs == "")
					coef_value = 1;
				else
					coef_value = stod(temp_coefs);
				// Assume exponent of 1 if 'x' is present without '^'
				exp_value = 1;
			}
			if (is_coef)
				temp_coefs += terms[i][j];
			if (j == terms[i].size() - 1) {
				// Determine the coefficient value
				if (temp_coefs == "-")
					coef_value = -1;
				else if (temp_coefs == "+" || temp_coefs == "")
					coef_value = 1;
				else
					coef_value = stod(temp_coefs);
			}
			if (terms[i][j] == '^') {
				// Extract the exponent value from the term
				for (int k = j + 1; k < terms[i].size(); k++)
					temp_exps += terms[i][k];
				exp_value = stoi(temp_exps);
			}
		}
		// Create a new PolyNode for the current term and set its values
		PolyNode* newNode = new PolyNode();
		newNode->coef = coef_value;
		newNode->exp = exp_value;
		newNode->next = NULL;

		// Update the linked list, either by setting head or linking to the tail
		if (i == 0) {
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		// Reset temporary variables for the next term
		coef_value = 0;
		exp_value = 0;
		temp_coefs = "";
		temp_exps = "";
		is_coef = true;
	}
	// Return the head of the linked list representing the polynomial
	return head;
	
}

// -------------------------------------------------
// Walk over the poly nodes & delete them
//
void DeletePoly(PolyNode* poly) {
	// This function deletes a linked list representing a polynomial.

	// Loop through the linked list until the end is reached (poly becomes NULL).
	while (poly != NULL) {
		// Create a temporary pointer 'old' to the current node that needs to be deleted.
		PolyNode* old = poly;

		// Move the 'poly' pointer to the next node in the linked list.
		poly = poly->next;

		// Delete the old node to free up the memory it occupied.
		delete old;
	}
}
// end-DeletePoly
	
//-------------------------------------------------
// Adds a node (coefficient, exponent) to poly. If there already 
// is a node with the same exponent, then you simply add the coefficient
// to the existing coefficient. If not, you add a new node to polynomial
// Returns a pointer to the possibly new head of the polynomial.
//
// Polinomlarý temsil eden düðüm yapýsýný tanýmlar

PolyNode* AddNode(PolyNode* head, double coef, int exp) {
	// This function adds a new term (node) with the given coefficient and exponent to a linked list representing a polynomial.

	// Create a new node with the provided coefficient and exponent values.
	PolyNode* new_node = new PolyNode();
	new_node->coef = coef;
	new_node->exp = exp;
	new_node->next = NULL;

	if (head == NULL) {
		// If the linked list is empty, set the new node as the head of the list.
		head = new_node;
	}
	else {
		// If the linked list is not empty, iterate through it to find the appropriate place for the new node.
		PolyNode* p = head;
		PolyNode* prev = nullptr;
		bool is_equal = false;

		while (p != nullptr) {
			if (p->exp == exp) {
				// If a term with the same exponent is found, update its coefficient.
				p->coef += coef;
				is_equal = true;

				// If the coefficient becomes zero, remove the term from the list.
				if (p->coef == 0) {
					if (p == head) {
						head = p->next;
						delete p;
					}
					else {
						prev->next = p->next;
						delete p;
					}
				}
				break; // Processing is complete, exit the loop.
			}
			prev = p;
			p = p->next;
		}

		if (!is_equal) {
			// If no matching exponent was found, add the new node to the end of the linked list.
			p = head;
			while (p->next != nullptr) {
				p = p->next;
			}
			p->next = new_node;
		}
	}

	return head; // Return the updated head of the linked list.
}


// end-AddNode

//-------------------------------------------------
// Adds two polynomials and returns a new polynomial that contains the result
// Computes: poly3 = poly1 + poly2 and returns poly3
//
PolyNode* Add(PolyNode* poly1, PolyNode* poly2) {
	// This function adds two polynomials represented as linked lists and returns the resulting polynomial.

	PolyNode* result = nullptr; // Initialize a pointer for the resulting polynomial
	PolyNode* current = nullptr; // Initialize a pointer to track the current node in the result

	while (poly1 && poly2) {
		if (poly1->exp > poly2->exp) {
			// If the exponent of poly1 is greater, add its term to the result
			if (!result) {
				// If result is empty, create the first node
				result = new PolyNode();
				result->coef = poly1->coef;
				result->exp = poly1->exp;
				result->next = nullptr;
				current = result;
			}
			else {
				// Add a new node to the result and update the 'current' pointer
				current->next = new PolyNode();
				current->next->coef = poly1->coef;
				current->next->exp = poly1->exp;
				current->next->next = nullptr;
				current = current->next;
			}
			poly1 = poly1->next; // Move to the next term in poly1
		}
		else if (poly1->exp < poly2->exp) {
			// If the exponent of poly2 is greater, add its term to the result (similar to the previous block)
			if (!result) {
				result = new PolyNode();
				result->coef = poly2->coef;
				result->exp = poly2->exp;
				result->next = nullptr;
				current = result;
			}
			else {
				current->next = new PolyNode();
				current->next->coef = poly2->coef;
				current->next->exp = poly2->exp;
				current->next->next = nullptr;
				current = current->next;
			}
			poly2 = poly2->next; // Move to the next term in poly2
		}
		else {
			// If the exponents are equal, add the coefficients and create a term in the result if the sum is not zero
			int diff = poly1->coef + poly2->coef;
			if (diff != 0) {
				if (!result) {
					result = new PolyNode();
					result->coef = diff;
					result->exp = poly1->exp;
					result->next = nullptr;
					current = result;
				}
				else {
					current->next = new PolyNode();
					current->next->coef = diff;
					current->next->exp = poly1->exp;
					current->next->next = nullptr;
					current = current->next;
				}
			}
			poly1 = poly1->next; // Move to the next term in poly1
			poly2 = poly2->next; // Move to the next term in poly2
		}
	}

	// If there are remaining terms in poly1 or poly2, add them to the result (similar to the previous blocks)
	while (poly1) {
		if (!result) {
			result = new PolyNode();
			result->coef = poly1->coef;
			result->exp = poly1->exp;
			result->next = nullptr;
			current = result;
		}
		else {
			current->next = new PolyNode();
			current->next->coef = poly1->coef;
			current->next->exp = poly1->exp;
			current->next->next = nullptr;
			current = current->next;
		}
		poly1 = poly1->next;
	}

	while (poly2) {
		if (!result) {
			result = new PolyNode();
			result->coef = poly2->coef;
			result->exp = poly2->exp;
			result->next = nullptr;
			current = result;
		}
		else {
			current->next = new PolyNode();
			current->next->coef = poly2->coef;
			current->next->exp = poly2->exp;
			current->next->next = nullptr;
			current = current->next;
		}
		poly2 = poly2->next;
	}

	return result; // Return the resulting polynomial.
}


//-------------------------------------------------
// Subtracts poly2 from poly1 and returns the resulting polynomial
// Computes: poly3 = poly1 - poly2 and returns poly3
//
PolyNode* Subtract(PolyNode* poly1, PolyNode* poly2) {
	// This function subtracts one polynomial (poly2) from another polynomial (poly1) represented as linked lists and returns the resulting polynomial.

	PolyNode* result = nullptr; // Initialize a pointer for the resulting polynomial
	PolyNode* current = nullptr; // Initialize a pointer to track the current node in the result

	while (poly1 && poly2) {
		if (poly1->exp > poly2->exp) {
			// If the exponent of poly1 is greater, add its term to the result
			if (!result) {
				// If result is empty, create the first node
				result = new PolyNode();
				result->coef = poly1->coef;
				result->exp = poly1->exp;
				result->next = nullptr;
				current = result;
			}
			else {
				// Add a new node to the result and update the 'current' pointer
				current->next = new PolyNode();
				current->next->coef = poly1->coef;
				current->next->exp = poly1->exp;
				current->next->next = nullptr;
				current = current->next;
			}
			poly1 = poly1->next; // Move to the next term in poly1
		}
		else if (poly1->exp < poly2->exp) {
			// If the exponent of poly2 is greater, subtract its term from the result
			if (!result) {
				result = new PolyNode();
				result->coef = -poly2->coef;
				result->exp = poly2->exp;
				result->next = nullptr;
				current = result;
			}
			else {
				current->next = new PolyNode();
				current->next->coef = -poly2->coef;
				current->next->exp = poly2->exp;
				current->next->next = nullptr;
				current = current->next;
			}
			poly2 = poly2->next; // Move to the next term in poly2
		}
		else {
			// If the exponents are equal, subtract the coefficients and create a term in the result if the difference is not zero
			int diff = poly1->coef - poly2->coef;
			if (diff != 0) {
				if (!result) {
					result = new PolyNode();
					result->coef = diff;
					result->exp = poly1->exp;
					result->next = nullptr;
					current = result;
				}
				else {
					current->next = new PolyNode();
					current->next->coef = diff;
					current->next->exp = poly1->exp;
					current->next->next = nullptr;
					current = current->next;
				}
			}
			poly1 = poly1->next; // Move to the next term in poly1
			poly2 = poly2->next; // Move to the next term in poly2
		}
	}

	// If there are remaining terms in poly1 or poly2, add or subtract them from the result (similar to the previous blocks)
	while (poly1) {
		if (!result) {
			result = new PolyNode();
			result->coef = poly1->coef;
			result->exp = poly1->exp;
			result->next = nullptr;
			current = result;
		}
		else {
			current->next = new PolyNode();
			current->next->coef = poly1->coef;
			current->next->exp = poly1->exp;
			current->next->next = nullptr;
			current = current->next;
		}
		poly1 = poly1->next;
	}

	while (poly2) {
		if (!result) {
			result = new PolyNode();
			result->coef = -poly2->coef;
			result->exp = poly2->exp;
			result->next = nullptr;
			current = result;
		}
		else {
			current->next = new PolyNode();
			current->next->coef = -poly2->coef;
			current->next->exp = poly2->exp;
			current->next->next = nullptr;
			current = current->next;
		}
		poly2 = poly2->next;
	}

	return result; // Return the resulting polynomial.
}

 //end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//
PolyNode* Multiply(PolyNode* poly1, PolyNode* poly2) {
	// This function multiplies two polynomials represented as linked lists and returns the resulting polynomial.

	int coef, exp; // Initialize variables to store the coefficient and exponent of the current term in the result
	PolyNode* poly = new PolyNode(); // Initialize a pointer for the resulting polynomial
	struct PolyNode* temp = poly2; // Create a temporary pointer to maintain the original 'poly2'

	if (!poly1 && !poly2) {
		// If both input polynomials are empty, return an empty polynomial
		return poly;
	}

	if (!poly1) {
		// If the first polynomial is empty, set the result to the second polynomial
		poly = poly2;
	}
	else if (!poly2) {
		// If the second polynomial is empty, set the result to the first polynomial
		poly = poly1;
	}
	else {
		// If both input polynomials are non-empty, perform multiplication
		while (poly1) {
			while (poly2) {
				// Calculate the coefficient and exponent of the current term in the result
				coef = poly1->coef * poly2->coef;
				exp = poly1->exp + poly2->exp;

				poly2 = poly2->next; // Move to the next term in poly2

				// Add the current term to the result using the AddNode function
				poly = AddNode(poly, coef, exp);
			}
			poly2 = temp; // Reset poly2 to its original state
			poly1 = poly1->next; // Move to the next term in poly1
		}
	}

	return poly; // Return the resulting polynomial.
}


//-------------------------------------------------
// Evaluates the polynomial at a particular "x" value and returns the result
//
double Evaluate(PolyNode *poly, double x) {
    // This function evaluates a polynomial represented as a linked list at a given value of 'x' and returns the result.

    int temp = 0; // Temporary variable to store the intermediate result for each term
    int result = 0; // Initialize the result variable to store the final result

    while (poly != NULL) {
        temp = 0; // Reset the temporary variable for each term

        if (poly->exp == 0) {
            // If the exponent of the term is 0, it's a constant term
            result += poly->coef; // Add the coefficient to the result
        }
        else {
            // For terms with non-zero exponents, evaluate the term by raising 'x' to the power of the exponent and multiplying by the coefficient
            temp = pow(x, poly->exp) * poly->coef;
            result += temp; // Add the term's result to the overall result
        }
        poly = poly->next; // Move to the next term in the linked list
    }

    return result; // Return the final result of evaluating the polynomial at 'x'.
}


//-------------------------------------------------
// Computes the derivative of the polynomial and returns it
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//
PolyNode* Derivative(PolyNode* poly) {
	// This function computes the derivative of a polynomial represented as a linked list and returns the resulting polynomial.

	PolyNode* temp = poly; // Create a temporary pointer to traverse the input polynomial

	while (temp != NULL) {
		if (temp->exp == 0) {
			// If the exponent of the term is 0, it's a constant term, and its derivative is 0
			temp->coef = 0; // Set the coefficient to 0
		}
		else {
			// For terms with non-zero exponents, calculate the derivative
			temp->coef = temp->exp * temp->coef; // Multiply the coefficient by the exponent
			temp->exp -= 1; // Decrease the exponent by 1
		}
		temp = temp->next; // Move to the next term in the linked list
	}

	return poly; // Return the resulting polynomial, which represents the derivative.
}


//-------------------------------------------------
// Plots the polynomial in the range [x1, x2].
// -39<=x1<x2<=39
// -12<=y<=12
// On the middle of the screen you gotta have x & y axis plotted
// During evaluation, if "y" value does not fit on the screen,
// then just skip it. Otherwise put a '*' char depicting the curve
//
void Plot(PolyNode *poly, int x1, int x2){
	int minY = -25;
	int maxY = 25;

	for (int y = maxY; y >= minY; y--) {
		for (int x = x1; x <= x2; x++) {
			double polyValue = Evaluate(poly, x);

			// Check if the y-value fits within the screen range
			if (y == round(polyValue)) {
				printf("*");  // Print '*' if the y value matches the rounded polynomial value
			}
			else if (x == 0 && y == 0) {
				printf("+");  // Print '+' at the origin (intersection of x and y axes)
			}
			else if (x == 0 && y == maxY) {
				printf("^");  // Print '^' at the top of the y-axis
			}
			else if (y == 0 && x == x2) {
				printf(">");  // Print '>' at the end of the x-axis
			}
			else if (x == 0) {
				printf("|");  // Print '|' along the y-axis
			}
			else if (y == 0) {
				printf("-");  // Print '-' along the x-axis
			}
			else {
				printf(" ");  // Print a space for empty areas
			}
		}
		printf("\n");  // Move to the next row
	}
} //end-Plot
