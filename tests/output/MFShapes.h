#ifndef MFSHAPES_H
#define MFSHAPES_H

#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x < y ? y : x)

//! TYPES OF SHAPE FOR THE MEMBER FUNCTIONS
typedef enum memFuncShape {
	TRAP_MF,			 //!< Trapezoidal shape
	TRI_MF, 			 //!< Triangular shape
	SPIKE_MF,			 //!< Spike shape
} memFuncShape;

/*! INFORMATION ABOUT THE NUMBER OF THE POINTS OF INTEREST
 *			input		ms				Type of the shape (Triangular, Trapezoidal, Spyke)
 *
 *			return		int				Return the number of the points of interest
 */
int getMFPoiNum(memFuncShape ms);

#endif
