#include "hardcode.h"

Rule createFirsts() {
	Rule r = NULL;
	List l = createNode(brop, 1);
	List l10 = createNode(brop, 1);
	List l13 = createNode(brop, 1);
	List l2 = createNode(idd, 1);
	List l11 = createNode(idd, 1);
	List l14 = createNode(idd, 1);
	List l3 = createNode(plus, 1);
	List l4 = createNode(eps, 1);
	List l12 = createNode(eps, 1);
	List l5 = createNode(star, 1);
	List l6 = createNode(brcl, 1);
	List fin = NULL;
	
	
	fin = addNode(fin, l);
	fin = addNode(fin, l2);
	Rule temp = createRule(E, fin);
	r = addRule(r, temp);

	
	List fin2 = NULL;
	fin2 = addNode(fin2, l3);
	fin2 = addNode(fin2, l4);
	Rule temp2 = createRule(E_, fin2);
	r = addRule(r, temp2);



	List fin3 = NULL;
	fin3 = addNode(fin3, l10);
	fin3 = addNode(fin3, l11);
	Rule temp3 = createRule(T, fin3);
	r = addRule(r, temp3);



	List fin4 = NULL;
	fin4 = addNode(fin4, l5);
	fin4 = addNode(fin4, l12);
	Rule temp4 = createRule(T_, fin4);
	r = addRule(r, temp4);



	List fin5 = NULL;
	fin5 = addNode(fin5, l13);
	fin5 = addNode(fin5, l14);
	Rule temp5 = createRule(F, fin5);
	r = addRule(r, temp5);
	return r;
}


Rule createFollow() {
	Rule r = NULL;
	List l = createNode(brcl, 1);
	List l10 = createNode(dollar, 1);
	List l13 = createNode(brcl, 1);
	List l2 = createNode(dollar, 1);
	List l11 = createNode(plus, 1);
	List l14 = createNode(dollar, 1);
	List l3 = createNode(brcl, 1);
	List l4 = createNode(plus, 1);
	List l12 = createNode(dollar, 1);
	List l5 = createNode(brcl, 1);
	List l20 = createNode(plus, 1);
	List l21 = createNode(dollar, 1);
	List l22 = createNode(brcl, 1);
	List l23 = createNode(star, 1);


	List fin = NULL;	
	fin = addNode(fin, l10);
	fin = addNode(fin, l);
	Rule temp = createRule(E, fin);
	r = addRule(r, temp);

	
	List fin2 = NULL;
	fin2 = addNode(fin2, l13);
	fin2 = addNode(fin2, l2);
	Rule temp2 = createRule(E_, fin2);
	r = addRule(r, temp2);



	List fin3 = NULL;
	fin3 = addNode(fin3, l11);
	fin3 = addNode(fin3, l14);
	fin3 = addNode(fin3, l3);
	Rule temp3 = createRule(T, fin3);
	r = addRule(r, temp3);



	List fin4 = NULL;
	fin4 = addNode(fin4, l4);
	fin4 = addNode(fin4, l12);
	fin4 = addNode(fin4, l5);
	Rule temp4 = createRule(T_, fin4);
	r = addRule(r, temp4);



	List fin5 = NULL;
	fin5 = addNode(fin5, l20);
	fin5 = addNode(fin5, l21);
	fin5 = addNode(fin5, l22);
	fin5 = addNode(fin5, l23);
	Rule temp5 = createRule(F, fin5);
	r = addRule(r, temp5);
	return r;
}
