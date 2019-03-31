# ConnectFour
Connect Four Game for CS201 Portfolio Project

INSTRUCTIONS:

1) "make" will run the makefile to compile the program, named C4, rather than a.out
2) Run/Execute the program using ./C4
3) The main menu will be displayed, enter your desired choice (1 - Solo, 2 - multiplayer, 3 - vs Computer/AI) followed by ENTER
4) You will then be prompted to enter the board size, a standard board has 6 rows and 7 columns.
5) Then PLAY!!!!! Player one will be "X" and player 2 will be "O", players may take turns, entering the 
   column they would like to place their piece in, followed by ENTER.
6) When the game is over, players may choose to continue playing and keep track of wins, or Exit.




AI FUNCTIONALITY:

1) Search board, for each possible 4 in a row add for AI favored, subtract for player favored
2) place tile in each column possible, then calculate points on new board
3) add points, 1 for each open spot adjacent to a piece, 1+4+13 for tiles in a row with a space at the end
4) if win is possible, set points to max
5) if enemy win is possible, block it (or never allow the situation to happen if possible)

More Details are Available in comments throughout the code

WEB SOURCES USED FOR REFERENCE:

https://stackoverflow.com/questions/46512314/graph-with-adjacency-matrix-in-c
https://stackoverflow.com/questions/21073714/safe-way-to-determine-the-maximum-integer-value-without-resorting-to-limits-h
https://stackoverflow.com/questions/13366083/why-does-the-arrow-operator-in-c-exist

https://www.cprogramming.com/tutorial/c/lesson18.html
https://roadtolarissa.com/connect-4-ai-how-it-works/
http://blog.gamesolver.org/
