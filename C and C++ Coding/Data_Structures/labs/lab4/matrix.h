#ifndef MATRIX_H
#define MATRIX_H

using namespace std;

template<typename Tbuf>
class matrix
{
	private:
		int Nrows, Ncols;
		Tbuf *buf;
	public:
		matrix(){buf = NULL;} //Constructor
		~matrix() {if (buf) delete [] buf;} //Destructor
		
		//Assigns the values for rows and columns that make up the matrix
		void assign(int newRows, int newCols)
		{
			Nrows = newRows;
			Ncols = newCols;
			buf = new Tbuf[Nrows * Ncols];
		}
	
		//Data function that points a 1d array to the 2d array data
		Tbuf *data(){return buf;}

		//Allows access to private variables
		int get_nRows() {return Nrows;}
		int get_nCols() {return Ncols;}
		
		//Overloads the bracket operator to allow for direct access
		Tbuf *operator[](int i) {return &buf[i * Ncols];}
};

#endif
