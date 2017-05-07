import java.awt.Point;
import java.util.*;

public class hello3 implements AIModule
{
 	private double getHeuristic(final TerrainMap map, final Point pt1, final Point pt2)
	{
    //return 0;
    int d = Math.max(Math.abs(pt1.x - pt2.x), Math.abs(pt1.y - pt2.y));
    double h = map.getTile(pt2) - map.getTile(pt1);
    return d*Math.exp(h/d);
	}

  public List<Point> createPath(final TerrainMap map)
	{
		final ArrayList<Point> path = new ArrayList<Point>();
		Point CurrentPoint = new Point(map.getStartPoint());

		HashMap<Point, Point> from = new HashMap<Point, Point>();
		HashMap<Point, Double> cost = new HashMap<Point, Double>();

		from.put(map.getStartPoint(), null);
		cost.put(map.getStartPoint(), 0.0);

    Queue<Point> frontier = new PriorityQueue<Point>
    (
    		new Comparator<Point>()
    		{
                public int compare(Point n1, Point n2)
                {
                	double cost1 = cost.get(n1) + getHeuristic(map, map.getEndPoint(), n1);
                	double cost2 = cost.get(n2) + getHeuristic(map, map.getEndPoint(), n2);
                    if (cost1 > cost2)
                        return 1;
                    else if (cost1 < cost2)
                        return -1;
                    else
                        return 0;
                }
    		}

    ); //frontier

		frontier.add(map.getStartPoint());

		while (!frontier.isEmpty())
		{
			CurrentPoint = frontier.remove();

			if ( CurrentPoint.equals(map.getEndPoint()))
					break;

			Point[] next = map.getNeighbors(CurrentPoint);

			for (int i=0; i < next.length; i++)
			{
				double newCost = cost.get(CurrentPoint) + map.getCost(CurrentPoint, next[i]);

				if (!cost.containsKey(next[i]) || newCost < cost.get(next[i]))
				{
					cost.put(next[i], newCost);
					frontier.add(next[i]);
					from.put(next[i], CurrentPoint);
				}

			}
		}

		CurrentPoint = map.getEndPoint();
		path.add(CurrentPoint);

		while (!CurrentPoint.equals(map.getStartPoint()))
		{
			CurrentPoint = from.get(CurrentPoint);
			path.add(0, CurrentPoint);
		}

		return path;
	}
}
