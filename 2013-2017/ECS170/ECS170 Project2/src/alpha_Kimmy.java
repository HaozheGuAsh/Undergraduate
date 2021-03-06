import java.awt.Point;
import java.util.ArrayList;
import java.util.Random;
import java.util.*;


public class alpha_Kimmy extends AIModule {
	int[] rank1 = {3,2,4,1,5,0,6}; 
    int[] rank2 = {3,4,2,5,1,0,6}; 

	private static int ourPlayer;
	private static int opponent;
	private static boolean init= false;
	private static boolean control;

	int temp;
	int best = 0;
	int maxDepth;
	
	public class Line { //for all possible fours in graph
		Point[] points = new Point[4];
		
		public Line(Point p1, Point p2, Point p3, Point p4) {
			points[0] = p1;
			points[1] = p2;
			points[2] = p3;
			points[3] = p4;
		}
	}
	
	public class pair {
		Point[] points = new Point[2];
		
		public pair(Point p1, Point p2) {
			points[0] = p1;
			points[1] = p2;
		}
	}
	
	final ArrayList<Line> line = new ArrayList<Line>();

	public void getNextMove(final GameStateModule game) {
  
    	if(!init) {
    		ourPlayer = game.getActivePlayer();
        	if (ourPlayer==1) { //initial
        		opponent = 2;
        	} else {
        		opponent = 1;
        	}
			init = true;			
    	}
    	
		ArrayList<Point> player3 = check3(game, ourPlayer);
		ArrayList<Point> opp3 = check3(game, opponent);
		
		//if play first
    	if (ourPlayer == 1) { //Do i have control right now?
    		// no control
    		control = false;
    		//if has even threat
    		for (Point point:player3) {
    			if (point.y%2==0)
    		//get control
    				control = true;
    		}
    	} else {
    		// player p2
    		control = true;
    		//has even threat
    		for (Point point:opp3) {
    			if (point.y%2==0)
    			//lose control
    				control = false;
    		}
    	}
			maxDepth = 1;
    	
			while(!terminate && maxDepth < (42 - game.getCoins())) {
				alphaBetaPru(Integer.MIN_VALUE, Integer.MAX_VALUE, game, maxDepth, true);
    		
				if (!terminate) {
					chosenMove = temp;
				}
				maxDepth++;
			}  
		
    }
	
	public alpha_Kimmy() {

		//horizontal
		for (int row = 0; row < 6; row++) { 
			for (int col = 0;col < 4; col++) {
				line.add(new Line(new Point(row, col), new Point(row, col+1), new Point(row, col+2), new Point(row,col+3)));
			}
		}
		//vertical
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 7; col++) {
				line.add(new Line(new Point(row, col), new Point(row+1, col), new Point(row+2, col), new Point(row+3,col)));
		 	}
		 }
		 //diagonal +
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 4; col++) {
				line.add(new Line(new Point(row, col), new Point(row+1, col+1), new Point(row+2, col+2), new Point(row+3,col+3)));
			}
		}
		//diagonal -
		for (int row = 3; row < 6; row++) { 
			for (int col = 0; col < 4; col++) {
				line.add(new Line(new Point(row, col), new Point(row-1, col+1), new Point(row-2, col+2), new Point(row-3,col+3)));
			}
		}
	}
	
	private int alphaBetaPru(int alpha, int beta, final GameStateModule game, int depth, boolean turn) {
    	if (terminate || game.getCoins()==42) {
    		return 0;
    	}
    	//if terminate test return utility
        if (depth==0) {
        	return utility(game);
        }
        Random randomno = new Random();
        int ran = randomno.nextInt(10);
        int[] rank = rank1;
        if (ran > 4) {
        	rank = rank2;
        } 


       


    	
        for (int move : rank) {
            if (game.canMakeMove(move)) {
                game.makeMove(move);
                
                if (game.isGameOver()) {
                	int winner = game.getWinner();
                	best = winner==0 ? 0 : (winner==ourPlayer ? Integer.MAX_VALUE : Integer.MIN_VALUE);
                } else {
                	best = alphaBetaPru(alpha, beta, game, depth-1, !turn);
                }
                
                if (turn) {
                	if (alpha < best) {
                		alpha = best;
                		if (depth==maxDepth) //choose the best move.
                			temp = move;
                	}
                } else {
                	if (beta > best)
                		beta = best;
                }	
                game.unMakeMove();
                
                if (beta <= alpha)
                	break;
            }
        }
        return turn?alpha:beta;
    }

	public int utility(final GameStateModule game) {
		ArrayList<Point> player3 = check3(game, ourPlayer);
		ArrayList<Point> opp3 = check3(game, opponent);
		ArrayList<Point> player2 = check2(game, ourPlayer);
		ArrayList<Point> opp2 = check2(game, opponent);
		
		int result = 0;
		
		//our player p1
		if (ourPlayer==1) {
			//p1 odd p2 even
			for(Point p:player3) { 

				if (p.y % 2 == 1) {
					for (Point o: opp3) {
						if (o.y % 2 == 0) {

						    //p1 odd p2 even
							return +1000000;
						}
					}

				} else {
					for (Point o: opp3) {
						if (o.y % 2 == 0) {
							
						    //p1 even p2 even
							return -1000000;
						}
					}
				}
			}

			for (Point p:player3) { 
				if (p.y % 2 == 0) {
					result = 50000;
					for (Point o: opp3) {
						if (o.y % 2 == 1) {
						    //p1 even p2 odd
						    result -=10000;

							for (Point o2:opp2) {
								if (o2.y == o.y) {
									result -= 1000;

								}
							}

						}
					}
				} else {
					result = -50000;
					for (Point o: opp3) {
						if (o.y % 2 == 1) {
						    //p1 odd p2 odd
							result -= 10000;
							for (Point o2:opp2) {
								if (o2.y == o.y) {
									result -= 1000;

								}
							}
						}
					}
				}
				return result;

			}

			//our player p2
		} else {
			//p1 odd p2 even
			for(Point o:opp3) { 
				if (o.y % 2 == 1) {
					for (Point p: player3) {
						if (p.y % 2 == 0) {

						    //p1 odd p2 even
							return -1000000;
						}
					}
				} else {
					for (Point p: player3) {
						if (p.y % 2 == 0) {
							
						    //p1 even p2 even
							return +1000000;
						}
					}
				}
			}

			for(Point o:opp3) { 
				if (o.y % 2 == 0) {
					result = -50000;
					for (Point p: player3) {
						if (p.y % 2 == 1) {


						    //p1 even p2 odd
							result += 10000;
							for (Point p2:player2) {
								if (p2.y == o.y) {
									result +=1000;
								}
							}
						}
					}
				} else {
					result = 50000;
					for (Point p: player3) {
						if (p.y % 2 == 1) {
							
						    //p1 odd p2 odd
							result += 10000;
							for (Point p2:player2) {
								if (p2.y == o.y) {
									result +=1000;
								}
							}

						}
					}
				}
				return result;

			}

		}
		return result;
	}
	
    
    public ArrayList<Point> check3(final GameStateModule game, final int p) {
    	final ArrayList<Point> empty = new ArrayList<Point>();

    	final int[] buffer = new int[4];
    	
		for (int i=0;i < line.size();i++) {
			Line temp = line.get(i);
			buffer[0] = game.getAt(temp.points[0].x, temp.points[0].y);
			buffer[1] = game.getAt(temp.points[1].x, temp.points[1].y);
			buffer[2] = game.getAt(temp.points[2].x, temp.points[2].y);
			buffer[3] = game.getAt(temp.points[3].x, temp.points[3].y);
				
			if (buffer[0]==p && buffer[1]==p && buffer[2]==p && buffer[3]==0)
				empty.add(temp.points[3]);
			else if (buffer[0]==p && buffer[1]==p && buffer[2]==0 && buffer[3]==p)	
				empty.add(temp.points[2]);
			else if (buffer[0]==p && buffer[1]==0 && buffer[2]==p && buffer[3]==p)	
				empty.add(temp.points[1]);
			else if (buffer[0]==0 && buffer[1]==p && buffer[2]==p && buffer[3]==p)	
				empty.add(temp.points[0]);
		}
		
    	return empty;
    }

       public ArrayList<Point> check2(final GameStateModule game, final int p)
    {
    	ArrayList<Point> empty = new ArrayList<Point>();

    	final int[] buffer = new int[4];
    	
		for (int i=0;i<line.size();i++)
		{
			Line temp = line.get(i);
			buffer[0] = game.getAt(temp.points[0].x, temp.points[0].y);
			buffer[1] = game.getAt(temp.points[1].x, temp.points[1].y);
			buffer[2] = game.getAt(temp.points[2].x, temp.points[2].y);
			buffer[3] = game.getAt(temp.points[3].x, temp.points[3].y);
				
			if (buffer[0]==p && buffer[1]==p && buffer[2]==0 && buffer[3]==0){ //1100
				empty.add(temp.points[2]);
				empty.add(temp.points[3]);
			} else if (buffer[0]==p && buffer[1]==0 && buffer[2]==0 && buffer[3]==p){ //1001	
				empty.add(temp.points[1]);
				empty.add(temp.points[2]);
			} else if (buffer[0]==p && buffer[1]==0 && buffer[2]==p && buffer[3]==0){ //1010
				empty.add(temp.points[1]);
				empty.add(temp.points[3]);
			} else if (buffer[0]==0 && buffer[1]==0 && buffer[2]==p && buffer[3]==p){ //0011
				empty.add(temp.points[0]);
				empty.add(temp.points[1]);
			} else if (buffer[0]==0 && buffer[1]==p && buffer[2]==p && buffer[3]==0){	//0110
				empty.add(temp.points[0]);
				empty.add(temp.points[3]);
			} else if (buffer[0]==0 && buffer[1]==p && buffer[2]==0 && buffer[3]==p) {	//0101
				empty.add(temp.points[0]);
				empty.add(temp.points[2]);
			}
		}
		
    	return empty;
    }

}
