using System;
using System.Collections.Generic;
using System.Text;

namespace _3._1._2 {
    /// <summary>
    /// A two dimensional Grid representation.
    /// </summary>
    class Grid {
        /// <summary>
        /// A two dimensional array representing the grid.
        /// </summary>
        private int[,] array;
        /// <summary>
        /// Grid constructor.
        /// </summary>
        /// <param name="rows">Rows number.</param>
        /// <param name="columns">Columns number.</param>
        public Grid(int rows, int columns) {
            array = new int[rows, columns];
        }
        /// <summary>
        /// Get one, entire row.
        /// </summary>
        /// <param name="row">Number of row to get.</param>
        /// <returns>An array containing the row.</returns>
        private int[] GetRow(int row) {
            int[] row_ = new int[array.GetLength(1)];
            for(int i = 0; i < array.GetLength(1); ++i) {
                row_[i] = array[row, i];
            }
            return row_;
        }
        /// <summary>
        /// Fill entire row at once.
        /// </summary>
        /// <param name="row">Row to fill.</param>
        /// <param name="row_">An array of values to fill row with.</param>
        private void SetRow(int row, int[] row_) {
            for(int i = 0; i < row_.Length; ++i) {
                array[row, row_[i]] = row_[i];
            }
        }
        /// <summary>
        /// Get/Set entire row at once.
        /// </summary>
        /// <param name="row">Row number.</param>
        /// <returns>An array contains values from the row.</returns>
        public int[] this[int row] {
            get {
                try {
                    return GetRow(row);
                }
                catch(System.IndexOutOfRangeException) {
                    Console.WriteLine("Index out of bounds!");
                    return new int[0];
                }
            }
            set {
                try {
                    SetRow(row, value);
                }
                catch(System.IndexOutOfRangeException) {
                    Console.WriteLine("Index out of bounds!");
                }
            }
        }
        /// <summary>
        /// An specific value indekser.
        /// </summary>
        /// <param name="row">Row number.</param>
        /// <param name="column">Column number.</param>
        /// <returns>Value from specified row and column.</returns>
        public int this[int row, int column] {
            get {
                try {
                    return array[row, column];
                }
                catch(System.IndexOutOfRangeException) {
                    Console.WriteLine("Index out of bounds!");
                    return -1;
                }
            }
            set {
                try {
                    array[row, column] = value;
                }
                catch(System.IndexOutOfRangeException) {
                    Console.WriteLine("Index out of bounds!");
                }
            }
        }
    }
    /// <summary>
    /// Main program class.
    /// </summary>
    class Program {
        /// <summary>
        /// Main program method.
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args) {
            Grid grid = new Grid(4, 4);
            grid[1, 1] = 1;
            grid[1, 2] = 2;
            grid[1, 3] = 3;
            grid[2, 1] = 4;
            Console.WriteLine("Second row:");
            foreach(int i in grid[1]) {
                Console.Write(i);
                Console.Write(" ");
            }
            Console.WriteLine();
            Console.WriteLine("Second element of third row:");
            Console.WriteLine(grid[2, 1]);
            int[] lol = grid[5];
        }
    }
}
