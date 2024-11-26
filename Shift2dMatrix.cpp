
// input matrix a can be rect  
// 1, 2, 3, 
// 4, 5, 6,
// 7, 8, 9,

// input int , shift_k [0 to max]
// if k = 2 

// 8 9 1
// 2 3 4
// 5 6 7

#include <vector>

using Matrix2d  =  std::vector<std::vector<int>> ;
constexpr int M  = 3;
constexpr int N  = 3;

void PrintMatrix(const Matrix2d& outm)
{
    for(int r=0; r<outm.size(); r++)
    {
        for(int c=0; c< outm[r].size(); c++)
        {
            std::cout << outm[r][c] << ",";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void getNewRowCol(int& Row, int& Col, int k, int RowSize, int ColSize)
{
    k=k<1?0:(k-1);
    int newk = Row*ColSize +  Col + k;
    int newRow = (newk)/(ColSize);
    int newCol = (newk) - (newRow*ColSize) ;
    Row = newRow%RowSize;
    Col = newCol;
}


void Shift(Matrix2d& outm, int row, int col, int k)
{
    int newrow = row;
    int newcol = col;

    Matrix2d tmpm(row); 
    tmpm.resize(row); 
    for(int r=0; r<row; r++) { tmpm[r].resize(col); }
    PrintMatrix(tmpm);
    
    for(int r=0; r<row; r++)
    {
        for(int c=0; c<col; c++)
        {
            int newrow = r;
            int newcol = c;
            getNewRowCol(newrow, newcol, k, row, col);
            std::cout<<"newN:"<< newrow << " newC:" << newcol << std::endl;
            tmpm[newrow][newcol] = outm[r][c];
            //tmpm[newrow][newcol] = 0;
        }
    }
    outm = tmpm;
}


int main()
{
    Matrix2d m1{{1,2,3}, {4,5,6}, {7,8,9}}; 
    PrintMatrix(m1);
    int k = 5;
    int nrow = 0;
    int ncol = 0;
    getNewRowCol(nrow, ncol, k, 3, 3);

    std::cout<<"newN:"<< nrow << " newC:" << ncol << std::endl ;
    Shift(m1, 3,3,5);
    PrintMatrix(m1);
    
    return 0;
}
