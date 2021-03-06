#include "MFHexagonal.h"
//#include "opencv2/core/core.hpp"

class MFHColor: public MFHexagonal
{
	protected:
		/***************************************************************
		 * ATTRIBUTES
		 **************************************************************/
		
		vector<Scalar> colors;
		
		/***************************************************************
		 * INITALIZATION METHODS
		 **************************************************************/
		
		void init();
		
		void initColors();
		
		/***************************************************************
		 * CHECK ATTRIBUTES
		 **************************************************************/
		
		virtual void checkAttributes();
		
		void checkColors();
		
		/***************************************************************
		 * COST AND COFLICT CALCULATIONS
		 **************************************************************/
		
		void checkNeighbors();
		
		void incCostNeighborWrap(unsigned long i1, Scalar v1, unsigned long i2, Scalar v2);

		/***************************************************************
		 * IMPLEMENTED PURE VIRTUAL FUNCTIONS FROM MFSquare
		 **************************************************************/
		
		void recalculateCost();
		 
		unsigned char compareTwo(unsigned int first, unsigned int second);
		
		virtual Scalar getRGBValue(unsigned int v);
		
	public:
		/***************************************************************
		 * (DE)CONSTRUCTOR(S)
		 **************************************************************/
		//MFHColor(unsigned int w, unsigned int h, unsigned int k, unsigned int k_t, unsigned int t, unsigned char sE, unsigned char sN, float cE, float cD, const char* c, string d);
		MFHColor(unsigned int w, unsigned int h, unsigned int k, unsigned int k_t, unsigned int t, unsigned char sE, const char *cn, float cs, const char* c, string d);

		/***************************************************************
		 * IMPLEMENTED PURE VIRTUAL FUNCTIONS FROM MARKERFIELD
		 **************************************************************/
		const char* getClassName();
};
