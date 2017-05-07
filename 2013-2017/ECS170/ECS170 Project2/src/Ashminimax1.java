/**
 * Created by Ash on 2017/2/26.
 */

import java.util.*;
import java.awt.Point;
import java.util.Random;
import java.lang.*;
public class Ashminimax1 extends AIModule
{
    private int maxdepth = 5;
    private final Random r = new Random(System.currentTimeMillis());
    private static int[][] Table =
            {{3, 4, 5, 7, 5, 4, 3},
            {4, 6, 8, 10, 8, 6, 4},
            {5, 8, 11, 13, 11, 8, 5},
            {5, 8, 11, 13, 11, 8, 5},
            {4, 6, 8, 10, 8, 6, 4},
            {3, 4, 5, 7, 5, 4, 3}};

    public void getNextMove(final GameStateModule state)
    {
        int move;
        if(!terminate)
        {
            move= ChooseMove(state,maxdepth,-Integer.MAX_VALUE,Integer.MAX_VALUE,true).column;
            if(!state.canMakeMove(move))System.out.println("illegal move: "+move);
            chosenMove=move;
        }


    }

    private mymove ChooseMove(final GameStateModule state, int depth,int high,int low,boolean maxmin)
    {
        int player = state.getActivePlayer();
        mymove bestmove = maxmin? new mymove(-Integer.MAX_VALUE,0):new mymove(Integer.MAX_VALUE,0);
        mymove currentmove;
        if(maxmin)
        {
            for (int move = 0;move<state.getWidth();move++)
            {
                if(state.canMakeMove(move))
                {
                    GameStateModule copy = state.copy();
                    copy.makeMove(move);
                     bestmove = new mymove(high,0);

                    //Terminal Test
                    if(copy.isGameOver()) //I terminate the game, so i will win with this move or making a draw move
                    {
                        int winner = copy.getWinner();
                        if(winner==0)//draw
                        {
                            return new mymove(0, move);
                        }
                        else if (maxmin)
                        {
                            return new mymove(Integer.MAX_VALUE, move);
                        }
                        else
                        {
                            return new mymove(-Integer.MAX_VALUE, move);
                        }
                    }

                    else if(depth>0)//it's not my turn, contrast minmax, decrease depth
                    {
                        currentmove = ChooseMove(copy,depth-1,high,low,false);
                        currentmove.column = move;
                    }
                    else//depth exhausted, using estimation
                    {
                        currentmove = new mymove(getscore(copy),move);
                    }
                    if(currentmove.value>bestmove.value)
                    {
                        bestmove = currentmove;
                    }
                    high = Math.max(bestmove.value,high);
                    if(low<=high)  return bestmove;

                    if(terminate)
                    {
                        System.out.println("Not Enough Time");
                        return bestmove;
                    }
                }
            }
            return bestmove;
        }
        else
        {
            for (int move = 0;move<state.getWidth();move++)
            {
                if(state.canMakeMove(move))
                {
                    GameStateModule copy = state.copy();
                    copy.makeMove(move);
                    bestmove = new mymove(low,0);
                    //Terminal Test
                    if(copy.isGameOver()) //I terminate the game, so i will win with this move or making a draw move
                    {
                        int winner = copy.getWinner();
                        if(winner==0)//draw
                        {
                            return new mymove(0, move);
                        }
                        else if (maxmin)
                        {
                            return new mymove(Integer.MAX_VALUE, move);
                        }
                        else
                        {
                            return new mymove(-Integer.MAX_VALUE, move);
                        }
                    }

                    else if(depth>0)//it's not my turn, contrast minmax, decrease depth
                    {
                        currentmove = ChooseMove(copy,depth-1,high,low,true);
                        currentmove.column = move;
                    }
                    else//depth exhausted, using estimation
                    {
                        currentmove = new mymove(getscore(copy),move);
                    }

                    if(currentmove.value<bestmove.value)
                    {
                        bestmove = currentmove;
                    }
                    low = Math.min(low,bestmove.value);
                    if(low<=high) return bestmove;
                    if(terminate)
                    {
                        System.out.println("Not Enough Time");
                        return bestmove;
                    }
                }

            }
            return bestmove;
        }
    }

    private int getscore(final GameStateModule state)
    {
        int player = state.getActivePlayer()%2 +1;//Maximize from states of MIN
       // int player = myplayer%2+1;
        int utility = 0;
        int boardscore = 0;
        int connectionscore = 0;
       // int a = state.getHeight();
        //int b= state.getWidth();
        for (int row = 0; row < state.getHeight(); row++)
        {
            for (int column = 0; column <state.getWidth(); column++)
            {
                if (state.getAt(column,row)== player)
                    boardscore += Table[row][column];
                else if (state.getAt(column,row) == (player %2 +1))
                    boardscore -=  Table[row][column];
            }
        }
        //if(boardscore<0)boardscore=0;
        utility += boardscore;


        //Connectionscore
        //player = state.getActivePlayer();

        /*int[][] s = {{1, 1, 0, -1}, {0, 1, 1, 1}};
        boolean[][] visited = new boolean[state.getHeight()][state.getWidth()];
        for (int row = 0; row < state.getHeight(); row++)
        {
            for (int column = 0; column <state.getWidth(); column++)
            {
                if (visited[row][column]) continue;
                int color= state.getAt(column,row);
                if (color==player)
                {
                    color = 1;
                    connectionscore+=getStrength(new intpair(row,column),color,visited,s,state);
                }
                else if (color==(player %2 +1))
                {
                    color = -1;
                    connectionscore+=getStrength(new intpair(row,column),color,visited,s,state);
                }
                visited[row][column]=true;
            }
        }*/
         return utility;
    }

    private final int empty = 0;
    private final int LEFT_BOTTOM_BORDER= 0;
    private final int RIGHT_BORDER = 6;
    private final int TOP_BORDER = 5;
    private int[] weight = {10, 100, 400};

    private int getStrength(intpair last, int color, boolean[][] visited, int[][] directions,final GameStateModule state)
    {
        int score = 0;

        for (int i = 0; i < 4; ++i)
        {
            intpair direction = new intpair(directions[0][i], directions[1][i]);
            intpair a = getLengthPair(last, direction, color, visited,state);

            direction = new intpair(-directions[0][i], -directions[1][i]);
            intpair b = getLengthPair(last, direction, color, visited,state);

            if ((a.v2 + b.v2) >= 3) {
                score += color * weight[a.v1 + b.v1];
            }
        }
        return score;
    }

    private intpair getLengthPair(intpair last, intpair direction, int color, boolean[][] visited,final GameStateModule state) {

        intpair position = new intpair(last.v1 + direction.v1,last.v2 + direction.v2);

        int playerLength = getLength(position, direction, color, visited, 0,state);

        int possibleLength = getLength(position, direction, empty, visited, playerLength,state);

        return new intpair(playerLength, possibleLength);
    }

    private int getLength(intpair position, intpair directions, int color, boolean[][] visited, int count,final GameStateModule state) {
        int row = position.v1 + count * directions.v1;
        int col = position.v2 + count * directions.v2;
        while (inbound(row, col, color,state))
        {
            visited[row][col] = true;
            count += 1;
            row += directions.v1;
            col += directions.v2;
        }
        return count;
    }

    private boolean inbound(int row, int col, int color,final GameStateModule state)
    {
        int curcolor = state.getAt(col, row);
        int player = state.getActivePlayer()%2+1;
        if(curcolor==player)curcolor=1;
        else if(curcolor==(player %2 +1)) curcolor=-1;
        return row >= LEFT_BOTTOM_BORDER
                && col >= LEFT_BOTTOM_BORDER
                && row <= TOP_BORDER
                && col <= RIGHT_BORDER
                && curcolor == color;
    }

    public class mymove
    {
        public mymove(int value, int column)
        {
            this.value = value;
            this.column = column;
        }
        private int value;
        private int column;
    }

    public class intpair
    {
        public intpair(int v1, int v2)
        {
            this.v1 = v1;
            this.v2 = v2;
        }
        private int v1;
        private int v2;
    }
}

