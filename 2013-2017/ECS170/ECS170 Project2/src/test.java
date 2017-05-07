import java.util.*;
import java.awt.Point;
import java.lang.*;

public class test extends AIModule {
    private int[] buildOneMoreLayer(final GameStateModule state) {
        int[] moves = new int[state.getWidth()];
        for (int i = 0; i < state.getWidth(); i++) {
            if (state.canMakeMove(i)) {
                moves[i] = 1;
            } else {
                moves[i] = 0;
            }
        }
        return moves;
    }

    public void getNextMove(final GameStateModule state) {
        double pick;
        if(state.getActivePlayer()==1)
            pick=max(state,2)[1];
        else
            pick=min(state,5)[1];
        chosenMove=(int)pick;
    }
    private double[] max(final GameStateModule state,int depth)
    {
        if(depth==0)
        {
            double[] sol={evaluation(state),0};
            return sol;
        }
        int[] moves = buildOneMoreLayer(state);
        int width = state.getWidth();
        double[] scores=new double[width];
        for(int i=0; i<width;i++)
        {
            if(moves[i]==1)
            {
                state.makeMove(i);
                System.out.print("i is : ");
                System.out.print((i));
                System.out.print('\n');
                scores[i] = min(state,depth-1)[0];
                state.unMakeMove();
            }
            else
            {
                scores[i]=-100000;
            }
        }
        return maxValueAndIndex(scores,width);

    }
    private double[] min(final GameStateModule state,int depth)
    {
        if(depth==0)
        {
            double[] sol={evaluation(state),0};
            return sol;
        }
        int[] moves = buildOneMoreLayer(state);
        int width = state.getWidth();
        double[] scores=new double[width];
        for(int i=0; i<width;i++)
        {
            if(moves[i]==1)
            {
                state.makeMove(i);
                scores[i] = max(state,depth-1)[0];
                state.unMakeMove();
            }
            else
            {
                scores[i]=100000;
            }
        }
        System.out.print("scores is :");
        System.out.print(' ');
        for(int i=0;i<7;i++)
        {
            System.out.print(scores[i]);
            System.out.print(' ');
        }
        System.out.print('\n');

        return minValueAndIndex(scores,width);

    }
    /* private int evaluation(final GameStateModule state)
     {
         int scores=0;
         int player=state.getActivePlayer();
          int[][] evaluationTable = {{3, 4, 5, 7, 5, 4, 3},
                 {4, 6, 8, 10, 8, 6, 4},
                 {5, 8, 11, 13, 11, 8, 5},
                 {5, 8, 11, 13, 11, 8, 5},
                 {4, 6, 8, 10, 8, 6, 4},
                 {3, 4, 5, 7, 5, 4, 3}};
          for(int i=0;i<7;i++)
          {
              for(int j=0;j<6;j++)
              {
                  if(state.getAt(j,i)==1)
                      scores=scores+evaluationTable[i][j];
                  if(state.getAt(j,i)==2)
                      scores=scores-evaluationTable[i][j];
              }
          }
         return 138+scores;
     }*/
    private double evaluation(final GameStateModule state)
    {
        int player=state.getActivePlayer();//always yourself
        //int player=state.getActivePlayer();//always oppe
        int opponent=0;
        double opp_score=0;
        double play_score = 0;
        int checker=0;
        if(player==1)
            opponent=2;
        else
            opponent=1;
        for(int row=0;row<6;row++)
        {
            opp_score=opp_score+readoffrow(row, state,opponent);
            play_score=play_score+readoffrow(row,state,player);
        }
        for(int col=0;col<7;col++)
        {
            opp_score=opp_score+readoffcol(col, state,opponent);
            play_score=play_score+readoffcol(col,state,player);
        }
        play_score=play_score+readoffdiag(0,3,4,state,player)+readoffdiag(0,4,5,state,player)+readoffdiag(0,5,6,state,player)+
                readoffdiag(1,5,5,state,player)+readoffdiag(2,5,4,state,player);
        opp_score=opp_score+readoffdiag(0,3,4,state,opponent)+readoffdiag(0,4,5,state,opponent)+readoffdiag(0,5,6,state,opponent)+
                readoffdiag(1,5,5,state,opponent)+readoffdiag(2,5,4,state,opponent);
        System.out.print("\nplayer score is :");
        System.out.print(play_score);
        System.out.print("\nopp score is :");
        System.out.print(opp_score);
        if(player==1)
            return play_score-0.8*opp_score;
        else
            return -play_score+1.3*opp_score;
    }

    private double readoffdiag(int x,int y,int length,final GameStateModule state, int player)
    {
        double[][] evaluationTable =
                        {{3, 4, 5, 7, 5, 4, 3},
                        {4, 6, 8, 10, 8, 6, 4},
                        {5, 8, 11, 13, 11, 8, 5},
                        {5, 8, 11, 13, 11, 8, 5},
                        {4, 6, 8, 10, 8, 6, 4},
                        {3, 4, 5, 7, 5, 4, 3}};
        double[] L=new double[7];
        int consecutive=0;
        double[] gap=new double[7];
        double count=0;
        int index=0;
        for(int i=0;i<length;i++)
        {
            if(state.getAt(x+i,y-i)==player)
            {
                count=count+evaluationTable[y-i][x+i];
                if(state.getAt(x+i-1,y-i+1)==player)
                    count=count*1.5;
                if(i==length-1)
                {
                    L[index]=consecutive;
                    gap[index]=count;
                }
            }
            else if(state.getAt(x+i,y-i)==0)
            {
                count=count+0.5*evaluationTable[y-i][x+i];
                consecutive++;
                if(i==length-1)
                {
                    gap[index]=count;
                    L[index]=consecutive;
                }
            }
            else
            {
                L[index]=consecutive;
                consecutive=0;
                gap[index]=count;
                index++;
                count=0;
            }
        }
        double score=0;
        for(int i=0;i<7;i++)
        {
            if(L[i]>3)
                score=score+gap[i];
        }

        return score;
    }
    private double readoffrow(int row,final GameStateModule state,int player)
    {
        int[][] evaluationTable =
                {{3, 4, 5, 7, 5, 4, 3},
                        {4, 6, 8, 10, 8, 6, 4},
                        {5, 8, 11, 13, 11, 8, 5},
                        {5, 8, 11, 13, 11, 8, 5},
                        {4, 6, 8, 10, 8, 6, 4},
                        {3, 4, 5, 7, 5, 4, 3}};
        double[] gap=new double[7];
        double[] length=new double[7];
        int consecutive=0;
        double count=0;
        int index=0;
        for(int i=0;i<7;i++)
        {
            if(state.getAt(i,row)==player)
            {
                consecutive++;
                count=count+evaluationTable[row][i];
                if(state.getAt(i-1,row)==player)
                    count=count*1.5;
                if(i==6)
                {
                    length[index]=consecutive;
                    gap[index]=count;
                }
            }
            else if(state.getAt(i,row)==0)
            {
                consecutive++;
                count=count+0.5*evaluationTable[row][i];
                if(i==6)
                {
                    gap[index]=count;
                    length[index]=consecutive;
                }
            }
            else
            {
                length[index]=consecutive;
                consecutive=0;
                gap[index]=count;
                index++;
                count=0;
            }
        }
        double score=0;
        for(int i=0;i<7;i++)
        {
            if(length[i]>3)
            {
                score=score+gap[i];
            }
        }

        return score;
    }

    private double readoffcol(int col,final GameStateModule state,int opponent)
    {
        double[][] evaluationTable =
                {{3, 4, 5, 7, 5, 4, 3},
                        {4, 6, 8, 10, 8, 6, 4},
                        {5, 8, 11, 13, 11, 8, 5},
                        {5, 8, 11, 13, 11, 8, 5},
                        {4, 6, 8, 10, 8, 6, 4},
                        {3, 4, 5, 7, 5, 4, 3}};
        double[] gap=new double[7];
        double[] length=new double[7];
        double count=0;
        int consecutive=0;
        int index=0;
        for(int i=0;i<6;i++)
        {
            if(state.getAt(col,i)==opponent)
            {
                consecutive++;
                count=count+evaluationTable[i][col];
                if(state.getAt(col,i)==opponent)
                    count=count*1.5;
                if(i==5)
                {
                    gap[index]=count;
                    length[index]=consecutive;
                }
            }
            else if(state.getAt(col,i)==0)
            {
                consecutive++;
                count=count+0.5*evaluationTable[i][col];
                if(i==5)
                {
                    gap[index]=count;
                    length[index]=consecutive;
                }
            }
            else
            {
                length[index]=consecutive;
                consecutive=0;
                gap[index]=count;
                index++;
                count=0;
            }
        }
        double score=0;
        for(int i=0;i<6;i++)
        {
            if(length[i]>3)
            {
                score=score+gap[i];
            }
        }
      /* System.out.print("col is :");
        System.out.print(col);
        System.out.print(' ');
        for(int i=0;i<6;i++)
        {
          System.out.print(length[i]);
            System.out.print(' ');
        }
        System.out.print('\n');*/
        return score;
    }

    private double[] maxValueAndIndex(double[] scores,int width)
    {
        double max=-1000000;
        int pick=0;
        for(int j=0; j<width;j++)
        {
            if(scores[j]>max)
            {
                max=scores[j];
                pick=j;
            }
        }
        double[] sol={max,pick};
        return sol;
    }

    private double[] minValueAndIndex(double[] scores,int width)
    {
        double min=1000000;
        int pick=0;
        for(int j=0; j<width;j++)
        {
            if(scores[j]<min)
            {
                min=scores[j];
                pick=j;
            }
        }
        double[] sol={min,pick};
        return sol;
    }
}
