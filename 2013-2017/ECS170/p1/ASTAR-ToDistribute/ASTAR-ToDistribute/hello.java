import java.awt.Point;
import java.util.List;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.HashMap;

public class hello implements AIModule
{
  public class Node
  {
    public Point point;
    public double g;
    public double f;
    public Node parent;

    public Node(final TerrainMap map, Point point, double g, Node parent)
    {
      this.point = point;
      this.parent = parent;
      this.g = g;
      this.f = g + getHeuristics(map, this.point, map.getEndPoint());
    }

    public boolean equals(Node n)
    {
      return point.equals(n.point);
    }
  }

  public List<Point> createPath(final TerrainMap map)
  {
    ArrayList<Point> total_path = new ArrayList<Point>();
    HashMap<Integer, Node> OpenSet = new HashMap<Integer, Node>();
    HashMap<Integer, Point> ClosedSet = new HashMap<Integer, Point>();
    Node start = new Node(map, map.getStartPoint(), 0.0, null);
    PriorityQueue<Node> Q = new PriorityQueue<Node>
    (
      new Comparator<Node>()
      {
        public int compare(Node n1, Node n2)
        {
          return n1.f > n2.f ? 1 : -1;
        }
      }
    );

    OpenSet.put(key(start), start);
    Q.add(start);

    while(!OpenSet.isEmpty())
    {
      Node current = Q.poll();

      if(current.point.equals(map.getEndPoint()))
      {
        for(Node n = current; n != null; n = n.parent)
          total_path.add(0, n.point);
          System.out.println("size: "+total_path.size());
        return total_path;
      }

      OpenSet.remove(key(current), current);
      ClosedSet.put(key(current), current.point);

      for (Point neighbor : map.getNeighbors(current.point))
      {
        int nKey = key(neighbor);

        if (!ClosedSet.containsKey(nKey))
        {
          double tentative_g = current.g + map.getCost(current.point, neighbor);

          if (!OpenSet.containsKey(nKey))
          {
            Node n = new Node(map, neighbor, tentative_g, current);
            OpenSet.put(nKey, n);
            Q.add(n);
          }
          else if (tentative_g < OpenSet.get(nKey).g)
          {
            OpenSet.get(nKey).parent = current;
            OpenSet.get(nKey).g = tentative_g;
            OpenSet.get(nKey).f = tentative_g + getHeuristics(map, OpenSet.get(nKey).point, map.getEndPoint());
          }
        }
      }
    }

    return null;
  }

  public int key(Point p)
  {
    return p.x * 10000 + p.y;
  }

  public int key(Node n)
  {
    return key(n.point);
  }

  private double getHeuristics(final TerrainMap map, final Point pt1, final Point pt2)
  {
    int d = Math.max(Math.abs(pt1.x - pt2.x), Math.abs(pt1.y - pt2.y));
	  double h = map.getTile(pt2) - map.getTile(pt1);
    double h1 = map.getTile(pt1);
    double h2 = map.getTile(pt2);
    double c = (h1+1)/h1;
    double result = 0;
    //double temp = h1;
    /*if ( h1 == h2 )
      return d*h2/(h1+1);
    else if (h2 > h1) {}

    if ( d > 1)
      return (d -1 )/1.1* Math.pow(h2/h1, 1/(d-1));
    else if (d== 1)
      return h2/(h1+1);
    */
    double temp = Math.floor(h/d);
    double temp2 = (h/d - temp) * d;
    return temp2 * Math.pow(2,(temp+1)) + (( d- temp2 ) * Math.pow (2,temp));
    //return 0;
  }
}
