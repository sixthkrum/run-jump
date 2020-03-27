Game for the terminal using ncurses, play yourself or build a version with AI that plays itself

to build:

run 'make' or 'make game' in directory to make game (run-jump)

run 'make ai' to make game with ai (run-jump-ai)

run 'make clean' to remove game, game with ai, all object files and ai files

run 'make gameclean' to remove game and all object files for the game

run 'make aiclean' to remove game with ai and all object files for it and ai files

to play:

run './run-jump' in the directory to play game after building game

run './run-jump-ai' instead to play the ai version after building ai-version

Regular game:

  on the screen:

    '-' is controlled by the up and down direction keys

    touching 'o' adds 100 points to the score

    touching '|' ends the run


press 'p' to pause the game

press 'esc' to escape the game    


AI:

  AI controls '-'

  press 'f' to fast forward the game

  press 'p' to pause the game

  press 'esc' to end the game    

  The layout is procedurally generated and there is always at least one viable path available.

  40 players are generated in each generation using the previous generations best player by randomly changing its attributes.

  The players can see their position and the full layout of the screen.

  The decision to either go up or down is made by seeing how the parts of the screen layout ('|' 'o' '_') influence the decision when they are at different positions on the screen.

  The parts of the layout have different values of how much they influence up and down movement at different positions of the screen.

  The values for up and down influences are added for every part on the screen.

  The decision taken is the one which has the greater sum.

  The players use the same layout upto the point that the player with the best distance in the last generation got to after that the layout is procedurally generated.

  When the program is ran multiple files are generated:

    scores.txt shows the best scores in each generation. ('generation #' 'score')

    top.txt shows the top two scorers of each generation. ('score' 'score') (each new generation is in a new line)

    level.bin is the file for the level.

    last_gen.bin is the list of players of the last gen with their attributes.

    mcs.bin collects the players of the current generation as their runs end.
