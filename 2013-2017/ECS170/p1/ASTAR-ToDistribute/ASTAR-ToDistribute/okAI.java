import java.awt.Point;
import java.util.ArrayList;
import java.util.List;
import java.util.*;
import java.util.Collections;

public class okAI implements AIModule
{

  /// Creates the path to the goal.
  public static int width;
  public static int height;
  public List<Point> createPath(final TerrainMap map)
  {
    final ArrayList<Point> path = new ArrayList<Point>();
    final Point CurrentPoint = map.getStartPoint();
    //boolean flag = false;
    width = map.getWidth();
    height = map.getHeight();
    int mapsize = width*height;
    final double [] distance = new double[mapsize];
    final double [] heu = new double[mapsize];
    final int [] preceed = new int[mapsize];
    final boolean [] visited = new boolean [mapsize];
    for (int i  = 0; i<mapsize;i++)
    {
      distance[i] =0.5*Integer.MAX_VALUE ;
      preceed[i] = -1;
      heu[i] = 0.5*Integer.MAX_VALUE ;
    }
    distance[getindex(CurrentPoint)] = 0;
    heu[getindex(CurrentPoint)] = getHeuristic(map,CurrentPoint,map.getEndPoint());
    //System.out.println("start point: "+getindex(CurrentPoint));
    //FINISH INITIALIZING
    for(int i = 0;i<mapsize;i++)
    {

    //  if(i%10000==0){System.out.println("Iteration: "+i);}
      final int next = minnode(distance,visited,map,heu);
      if(next==getindex(map.getEndPoint())){break;}
    //  if(i<20){System.out.println("next is :"+next);}
      visited[next] = true;

      final Point [] n = map.getNeighbors(getpoint(next));
      for(int j = 0; j<n.length;j++)
      {
        final Point neighbor = n[j];
        if(visited[getindex(neighbor)]){continue;}
        final double tentative_g = distance[next]+ map.getCost(getpoint(next),neighbor);
        if(distance[getindex(neighbor)]>tentative_g)
        {
          distance[getindex(neighbor)] = tentative_g;
          preceed[getindex(neighbor)] = next;
          heu[getindex(neighbor)] = distance[getindex(neighbor)] +getHeuristic(map,getpoint(next),neighbor);
        }
      }
    }
    // Adding path

    int e = getindex(map.getEndPoint());
    int s = getindex(map.getStartPoint());
    int x = e;
  //  System.out.println("HERE S is : "+s);
  //  System.out.println("HERE x is : "+x);
  //  System.out.println("S : "+map.getStartPoint().x+map.getStartPoint().y);
  //  System.out.println("E : "+map.getEndPoint().x+map.getEndPoint().y);
    while(x!=s)
    {
      path.add(0,getpoint(x));
  //    System.out.println("x is : "+x);
      x = preceed[x];
    }
    path.add(0,CurrentPoint);
  //  System.out.println("HERE1: ");
    return path;
  }

public static int minnode(double [] distance,boolean [] visited,TerrainMap map,double [] heu)
{
  double x = Integer.MAX_VALUE;
  int y = -1;
  for(int i = 0; i<distance.length;i++)
  {
    double tmp = heu[i];//+distance[i];
    if(!visited[i] && tmp<=x)
    {
      y = i;
      x = tmp;
    }
  }
  //System.out.println("HERE");
  return y;
}
public  static int getindex(Point pt)
{
  return (pt.y)*width+(pt.x);
}
public  static Point getpoint(int ind)
{
    int x = ind % width;
    int y = ((ind-x)/width);
    return new Point(x,y);
}

  //Get A* Cost Function
  public  static double getHeuristic(final TerrainMap map, final Point pt1,final Point pt2)
  {
    //double gn = map.getCost(pt1,pt2);
    double hn = 0;
    double htdif = map.getTile(map.getEndPoint()) - map.getTile(pt2);
   if (htdif==0)
    {hn = ashdistance(map,pt2);}
    else if (htdif<0)
    {
      int dis = ashdistance(map,pt2);
      double tmp = htdif;
      hn = dis*Math.pow(2,tmp/dis);
    }
    else
    {
      int dis = ashdistance(map,pt2);
      double tmp = htdif;
      hn = dis*Math.pow(2,tmp/dis);

    //  htdif = Math.sqrt(Math.pow(map.getEndPoint().x-pt2.x,2)+Math.pow(map.getEndPoint().y-pt2.y,2));
    }

     //hn = 0.5*Math.sqrt(Math.pow(map.getEndPoint().x-pt2.x,2)+Math.pow(map.getEndPoint().y-pt2.y,2));

  //  double fn = gn+hn;
      return hn;
  }
  public static int ashdistance(TerrainMap map,Point pt)
  {
    int x2 = map.getEndPoint().x;
    int y2 = map.getEndPoint().y;
    int x1 = pt.x;
    int y1 = pt.y;
    int dis1 = Math.max(Math.abs(x1-x2),Math.abs(y1-y2));
    int dis2 = Math.abs(x1-x2)+Math.abs(y1-y2);
    return dis1;
  }
}
