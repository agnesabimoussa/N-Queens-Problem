# Problem Description
N-Queens problem consists of placing N queens on an NxN chessboard sucj that no two queens attack each other.
Queens should be placed such that there is no more than one queen on a row / column / diagonal.

Check the illustration below:

<div style="display: flex; justify-content: center;">
  <img src="assets/constraint.jpg" alt="figure 1" width="450">
</div>


# Algorithm
A common solution to solve the N-Queens problem is backtracking.

How I would think about it:
- Place the first queen at a random position
- Attempt to place to other queen at a random position
- If any of the queens can attack each other on the chessboard, move the second queen to another position untill they cannot attack each other. Else, leave in same positions
- Repeat


# Steps
- solution(N) -> NxN (1 for queen, 0 for no queen)
- draw(nxN)

The illustration below shows an example output for a 8x8 chessboard:

<div style="display: flex; justify-content: center;">
  <img src="assets/chessboard.webp" alt="figure 1" width="450">
</div>


# Technology
- C++ (appears in course materials + best for me to remember + good performance)
RayLib library for rendering chessboard