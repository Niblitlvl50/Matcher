
#pragma once

#include <stdexcept>

namespace game
{
    template <typename T, int ROWS, int COLUMNS>
    class ObjectMatrix
    {
    public:
        
        struct iterator;
        
        //! Return how many rows there is
        int Rows() const
        {
            return ROWS;
        }
        
        //! Returns how many columns there is
        int Columns() const
        {
            return COLUMNS;
        }

        //! Assign a object to a cell
        void Assign(T object, int row, int column)
        {
            if(!Validate(row, column))
                throw std::out_of_range("Row or column is out of range!");
            
            mObjects[row * ROWS + column] = object;
        }
        
        //! Get the object at the specified cell
        T& Get(int row, int column)
        {
            if(!Validate(row, column))
                throw std::out_of_range("Row or column is out of range!");
            
            return mObjects[row * ROWS + column];
        }
        
        //! Swap one cell with another
        void Swap(int row1, int column1, int row2, int column2)
        {
            std::swap(Get(row1, column1), Get(row2, column2));
        }
        
        //! Makes sure a row and column pair is a valid cell in the matrix
        bool Validate(int row, int column) const
        {
            const bool validRow = (row > -1 && row < ROWS);
            const bool validColumn = (column > -1 && column < COLUMNS);
            return validRow && validColumn;
        }
        
        //! Get an iterator to a row
        iterator iterate_row(int row)
        {
            const int offset = row * COLUMNS;
            return iterator(mObjects + offset, 1, COLUMNS);
        }
        
        //! Get an iterator to a column
        iterator iterate_column(int column)
        {
            const int offset = column;
            return iterator(mObjects + offset, COLUMNS, ROWS);
        }

        //! The iterator object
        struct iterator
        {
            iterator(T* objects, int advance, int steps)
                : mObjects(objects),
                  mAdvance(advance),
                  mSteps(steps),
                  mIndex(0)
            { }
            
            //! Will return true while there are still items to iterate
            bool HasMore() const
            {
                return mIndex < mSteps;
            }
            
            //! Index of the iterator
            int Index() const
            {
                return mIndex;
            }
            
            //! Steps the iterator one step
            void operator ++ ()
            {
                if(mIndex >= mSteps)
                    throw std::out_of_range("Iterator is out of bounds");
                
                mIndex++;
                mObjects += mAdvance;
            }
            
            //! Pointer access to the iterator object
            T* operator -> ()
            {
                return mObjects;
            }
            
            //! Reference access to the iterator object
            T& operator * ()
            {
                return *mObjects;
            }
            
        private:
            T* mObjects;
            const int mAdvance;
            const int mSteps;
            int mIndex;
        };
        
    private:
        
        T mObjects[ROWS * COLUMNS];
    };
}
