/**
 * Created by mengdaxu on 3/13/17.
 */
import java.lang.reflect.Array;
import java.util.*;
import java.awt.Point;
import java.lang.*;
import java.io.*;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;

public class ann {

    public static void main(String[] args)
    {
        double[][]female_feature=readdata("Female");
        double[][]male_feature=readdata("Male");
        double[][]feature=new double[55+218][128*120];
        double[][] Y=new double[55+218][2];
        for(int p=0;p<55;p++)
        {
            Y[p][1]=1;
            Y[p][0]=0;
        }
        for(int p=55;p<55+218;p++)
        {
            Y[p][1]=0;
            Y[p][0]=1;
        }
        for(int i=0;i<55+218;i++) {
            for (int j = 0; j < 2; j++)
            {
                if(i<55)
                {
                    feature[i][j]=female_feature[i][j];
                }
                else
                {
                    feature[i][j]=male_feature[i-55][j];
                }
            }
        }
        RandomData(feature,Y);
        double[][]trainfeature= Arrays.copyOfRange(feature,0,220);
        double[][]testfeature=Arrays.copyOfRange(feature,221,55+218-1);
        double[][]Ytrain=Arrays.copyOfRange(Y,0,220);
        double[][]Ytest=Arrays.copyOfRange(Y,221,55+218-1);
        if(args[0].equals("-train"))
            train(trainfeature,Ytrain);
        else
            test(testfeature,Ytest);
    }
    public static void test(double[][]feature,double[][]Y)
    {
        String B =System.getProperty("user.dir");
        File f = new File(B+"/"+"result.txt");
        BufferedReader reader = null;
        double[][] w1=new double[10][128*120];
        double[][] w2=new double[2][11];
        int counter=0;
        try {
            reader = new BufferedReader(new FileReader(f));
            String text = null;

            while ((text = reader.readLine()) != null) {
                StringTokenizer st = new StringTokenizer(text);
                int counter2=0;
                double[] list=new double[128*120];
                while (st.hasMoreTokens()) {
                    list[counter2]=Double.parseDouble(st.nextToken());
                    counter2++;
                }
                w1[counter]=list;
                counter++;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (reader != null) {
                    reader.close();
                }
            } catch (IOException e) {
            }
        }
        counter=0;

        f = new File(B+"/"+"result2.txt");
        try {
            reader = new BufferedReader(new FileReader(f));
            String text = null;

            while ((text = reader.readLine()) != null) {
                StringTokenizer st = new StringTokenizer(text);
                int counter2=0;
                double[] list=new double[11];
                while (st.hasMoreTokens()) {
                    list[counter2]=Double.parseDouble(st.nextToken());
                    counter2++;
                }
                w2[counter]=list;
                counter++;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (reader != null) {
                    reader.close();
                }
            } catch (IOException e) {
            }
        }
        double[] hidden_layer_output=new double[11];
        double[] output_layer=new double[2];
        double[][] fi=new double[2][1];
        int c=0;
        for(int i=0;i<feature.length;i++) {
            //forward
            //hidden layer
            for (int j = 0; j < 10; j++) {
                hidden_layer_output[j] = sigmoid(feature[i], w1[j]);
            }

            hidden_layer_output[10] = 1;//error


            output_layer[0] = sigmoid(hidden_layer_output, w2[0]);//male
            output_layer[1] = sigmoid(hidden_layer_output, w2[1]);//female


            //backward
            fi[0][0] = output_layer[0] - Y[i][0];
            fi[1][0] = output_layer[1] - Y[i][1];


            if (output_layer[1] > output_layer[0] && Y[i][1] == 1)
                c++;
            else if (output_layer[1] < output_layer[0] && Y[i][0] == 1)
                c++;
        }
        double accuracy=c/53.0;
        System.out.print("accuracy is ");
        System.out.print(accuracy);
        System.out.print('\n');
    }

    public static void train(double[][] X, double[][] Y)
    {
        int input_node=128*120;
        double[] output_layer = new double[2];
        int c=0;
        int hidden_node=10;
        double[][] w1=new double[hidden_node][input_node];
        double[][] w2 = new double[2][hidden_node + 1];
        double[][] fi = new double[2][1];
        for(int p=0;p<1;p++)
        {
            for(int q=0;q<hidden_node+1;q++)
            {
                w2[p][q]=Math.random();
            }
        }

        for(int p=0;p<hidden_node;p++)
        {
            for(int q=0;q<input_node;q++)
            {
                w1[p][q]=Math.random();
            }
        }
        double[]hidden_layer_output=new double[hidden_node+1];
        for(int iteration=0;iteration<10;iteration++)
        {
            for(int i=0;i<X.length;i++) {
                //forward
                //hidden layer
                for (int j = 0; j < hidden_node; j++) {
                    hidden_layer_output[j] = sigmoid(X[i], w1[j]);
                }

                hidden_layer_output[hidden_node] = 1;//error


                output_layer[0] = sigmoid(hidden_layer_output, w2[0]);//male
                output_layer[1] = sigmoid(hidden_layer_output, w2[1]);//female


                //backward
                fi[0][0] = output_layer[0] - Y[i][0];
                fi[1][0] = output_layer[1] - Y[i][1];


                if(output_layer[1]>output_layer[0]&&Y[i][1]==1)
                    c++;
                else if(output_layer[1]<output_layer[0]&&Y[i][0]==1)
                    c++;



                //update second layer
                double[][] tempt=matrix_prodcut(transpose(w2),fi);
                double[] tempt1=new double[hidden_node+1];
                double[] tempt3=new double[hidden_node+1];
                for(int k=0;k<hidden_node+1;k++)
                {
                    tempt1[k]=tempt[k][0];
                    tempt3[k]=1-hidden_layer_output[k];
                }
                double[] tempt2=row_prodcut(tempt1,hidden_layer_output);
                double[] fi_1=row_prodcut(tempt2,tempt3);
                for(int n=0;n<2;n++)
                {
                    for(int m=0;m<hidden_node;m++)
                    {
                        w2[n][m]=w2[n][m]-fi[n][0]*hidden_layer_output[m];
                    }
                }
                //update first layer;
                for(int n=0;n<hidden_node;n++)
                {
                    for(int m=0;m<input_node;m++)
                    {
                        w1[n][m]=w1[n][m]-fi_1[n]*X[i][m];
                    }
                }

            }
            System.out.print(c);
            System.out.print('\n');
            c=0;

        }
        File f = new File("result.txt");
        File f2=new File("result2.txt");
        BufferedWriter out=null;
        BufferedWriter out2=null;
        // tries to create new file in the system
        try {
            boolean bool = f.createNewFile();
            boolean bool2 = f2.createNewFile();
        }catch (Exception e)
        {
            e.printStackTrace();
        }
        try
        {
            FileWriter fstream = new FileWriter("result.txt", true);
            FileWriter fstream2 = new FileWriter("result2.txt", true);
            out = new BufferedWriter(fstream);
            out2 = new BufferedWriter(fstream2);
            //double[][] w1=new double[hidden_node][input_node];
            //double[][] w2 = new double[2][hidden_node + 1];
            for(int i=0;i<hidden_node;i++)
            {
                for(int j=0;j<input_node;j++)
                {
                    out.write(Double.toString(w1[i][j]));
                    out.write(" ");
                }
                out.write('\n');
            }
            for(int i=0;i<2;i++)
            {
                for(int j=0;j<hidden_node+1;j++)
                {
                    out2.write(Double.toString(w2[i][j]));
                    out2.write(" ");
                }
                out2.write('\n');
            }

        }
        catch (IOException e)
        {
            System.err.println("Error: " + e.getMessage());
        }
        finally
        {
            try {
                if (out != null) {
                    out.close();
                }
                if(out2!=null){
                    out2.close();
                }
            }
            catch (IOException ex) {

                ex.printStackTrace();

            }
        }

        //write to result.txt
        /*FileWriter fw = new FileWriter(result.txt);
        BufferedWriter bw = new BufferedWriter(fw);
        bw.write(content);
        double[][]test=readdata("Test");*/




    }
    public static double[][] matrix_prodcut(double[][] A, double[][] B) {
        int n=B[0].length;
        int m=A.length;
        int c=A[0].length;
        double[][] ans=new double[m][n];
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                ans[i][j]=0;
                for(int k=0;k<c;k++)
                {
                    ans[i][j]=ans[i][j]+A[i][k]*B[k][j];
                }
            }
        }
        return ans;
    }
    public static double[] row_prodcut(double[]A, double[]B)
    {
        int len=A.length;
        double[] ans=new double[len];
        for(int i=0;i<len;i++)
        {
            ans[i]=A[i]*B[i];
        }
        return ans;
    }


    public static double sigmoid(double[] x, double[] w)
    {
        double tempt=0;
        for(int i=0;i<x.length;i++){
            tempt=tempt+x[i]*w[i];
        }
        double y=1/(1+Math.exp(-1*tempt));
        return y;
    }

    public static double[][] transpose(double [][] A)
    {
        int col=A.length;
        int row=A[0].length;
        double[][] dup=new double[row][col];
        for(int i=0;i<col;i++)
        {
            for(int j=0;j<row;j++)
            {
                dup[j][i]=A[i][j];
            }
        }
        return dup;
    }

    public static void RandomData(double[][]X,double[][]Y)
    {
        Random rnd= ThreadLocalRandom.current();
        for(int i=0;i<X.length;i++)
        {
            int index=rnd.nextInt(55+218-1);
            double[]tempt=X[i];
            double[]tempt2=Y[i];
            X[i]=X[index];
            X[index]=tempt;
            Y[i]=Y[index];
            Y[index]=tempt2;
        }
    }


    public static double[][] readdata(String A)
    {
        String B =System.getProperty("user.dir");
        File folder = new File(B+"/"+A);
        File[] listOfFiles = folder.listFiles();
        int index=0;
        if(A.equals("Female"))
        {
            index=55;
        }
        else if(A.equals("Male"))
        {
            index=218;
        }
        else
        {
            index=40;
        }
        double[][] feature=new double[index][128*120];
        int counter=0;

        for (File file : listOfFiles) {
            if (file.isFile()) {
                //System.out.println(file.getName());
                // List<Integer> list = new ArrayList<Integer>();
                int counter2=0;
                double[] list=new double[128*120];
                String tempt=file.getName();
                File f=null;
                if(!tempt.contains("b")&&!tempt.contains("a")&&!tempt.contains("c")) {
                    f = new File(B+"/"+A +"/"+tempt);
                }
                else
                {
                    break;
                }
                BufferedReader reader = null;

                try {
                    reader = new BufferedReader(new FileReader(f));
                    String text = null;

                    while ((text = reader.readLine()) != null) {
                        StringTokenizer st = new StringTokenizer(text);
                        while (st.hasMoreTokens()) {
                            list[counter2]=Integer.parseInt(st.nextToken());
                            counter2++;
                        }
                    }
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                } finally {
                    try {
                        if (reader != null) {
                            reader.close();
                        }
                    } catch (IOException e) {
                    }
                }

//print out the list
                //System.out.println(list);
                //female_feature[counter]=list;
                for(int p=0;p<128*120;p++)
                {
                    feature[counter][p]=list[p];
                }
                if(counter==index-1)
                    break;
                counter++;
            }
        }
        return feature;
    }


}


