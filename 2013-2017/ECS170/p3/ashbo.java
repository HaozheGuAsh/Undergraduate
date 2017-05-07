/**
 * Created by Ash on 2017/3/14.
 */
import java.awt.*;
import java.nio.FloatBuffer;
import java.util.List;
import java.util.Random;
import java.util.*;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.nio.charset.*;
import java.nio.file.*;

public class bo {
    public static void main(String[] args)
    {
        bo ANN = new bo();
        if (args.length!=5)
        {System.out.println("Not Enough Arguments!  "+args.length+"Provided But need 5");}
        else
        {
            ANN.folder[1] = args[1];
            ANN.folder[0] = args[2];
            ANN.folder[2] = args[4];
        }
        ANN.Read_Data();
        ANN.Shuffle();
        ANN.five_fold();
        ANN.Train();

    }
    public int size = 960*16;
    public String[] folder = new String[3];
    public double [] weight  = new double [1+size];
    public double [][] Female = new double [55][size+1];
    public double [][] Male = new double[218][size+1];
    int Hidden_Node = 30;
    double[][] W1 = new double[Hidden_Node+1][size+1];
    double[][] W2 = new double[2][Hidden_Node+1];
    float accuracy;

    public double [][] Trainning = new double[273][size+1];
    public double [][] Test = new double [40][size+1];
    public double [] Test_Lable  = {1,1,1,1,1,          //Male=1. Female=0
            1,1,1,0,1,
            1,1,1,1,1,
            1,1,1,0,1,
            1,1,1,1,1,
            1,1,1,1,1,
            0,0,0,0,0,
            0,1,1,1,1};

    static String readFile(String path, Charset encoding)
            throws IOException
    {
        byte[] encoded = Files.readAllBytes(Paths.get(path));
        return new String(encoded, encoding);
    }

    public void Read_Data()
    {
        //String path = System.getProperty("user.dir");
        //System.out.println(path);
       // String[] folder = {"Female","Male","Test"};


        String tmppath = folder[0];
        File[] Femalefiles =  Arrays.copyOfRange(new File(tmppath).listFiles(), 0, 55);
        tmppath = folder[1];
        File[] Malefiles =  Arrays.copyOfRange(new File(tmppath).listFiles(), 0, 218);
        tmppath =folder[2];
        File[] Testfiles =  Arrays.copyOfRange(new File(tmppath).listFiles(), 0, 40);
        String tmp = "";
        for (int i = 0; i<55;i++)
        {
            try {
                tmp = readFile(Femalefiles[i].toString(), StandardCharsets.UTF_8);
            } catch (IOException e ){System.out.println("No Such File");}
            tmp = tmp.replace("\n"," ");
            String [] list = tmp.split(" ");
            Female[i][0] = 0;
            for (int j = 1;j<size+1;j++)
            {
                Female[i][j] = Double.parseDouble(list[j-1]);
            }
        }
        for (int i = 0; i<218;i++)
        {
            try {
                tmp = readFile(Malefiles[i].toString(), StandardCharsets.UTF_8);
            } catch (IOException e ){System.out.println("No Such File");}
            tmp = tmp.replace("\n"," ");
            String [] list = tmp.split(" ");
            Male[i][0] = 1;
            for (int j = 1;j<size+1;j++)
            {
                Male[i][j] = Double.parseDouble(list[j-1]);
            }
        }
        for (int i = 0; i<40;i++)
        {
            try {
                tmp = readFile(Malefiles[i].toString(), StandardCharsets.UTF_8);
            } catch (IOException e ){System.out.println("No Such File");}
            tmp = tmp.replace("\n"," ");
            String [] list = tmp.split(" ");
            Test[i][0] = Test_Lable[i];
            for (int j = 1;j<size+1;j++)
            {
                Test[i][j] = Double.parseDouble(list[j-1]);
            }
        }
    }

    public void Shuffle()
    {
        //double[][] a= {{1,1,1,1},{2,2,2,2},{3,3,3,3},{4,4,4,4}};
        List<double[]> tmp = new ArrayList<double[]>();
        tmp.addAll(Arrays.asList(Female));
        tmp.addAll(Arrays.asList(Male));
        Collections.shuffle(tmp);
        double[][] tmp1 = tmp.toArray(new double[273][size+1]);
        for(int i  = 0;i <273;i++)
        {
            Trainning[i] = tmp1[i];
        }
    }
    public void Trainning()
    {
       /* double[][] c = {{1,2,3}};
        double[][] d = {{4},{5},{6}};

        double [][]a = Matrix_Multiplication(c,d);
        double [][]x = Point_Multiplication(d,d);
        double [][]y = Point_Multiplication(c,c);*/
        int Iteration = 20;
        int Num_Layer = 3;
        double LearningRate = 0.01;
        double[] Output_Layer_Activation = new double[2];
        double[] Hidden_Layer_Activation = new double[Hidden_Node+1];
        double [] label = new double[273];
        double[] label_invert = new double[273];
        double[][] Train_Set = new double[273][size+1];
        int Correct = 0;
        double[][] Error = new double[2][1];

        for(int i = 0;i<273;i++) //Getting Label
        {
            label[i] = Trainning[i][0];
            label_invert[i] = label[i]==0?1:0;
        }

        for(int i = 0;i<273;i++)
        {
            for(int j = 0;j<size+1;j++)
            {
                if(j==0)
                {
                    Train_Set[i][j] = 1;
                    continue;
                }
                Train_Set[i][j] = Trainning[i][j];
            }
        }
        for(int i  = 0;i<Hidden_Node;i++)
        {
            for(int j = 0;j<size+1;j++)
            {
                W1[i][j] = 2*Math.random()-1;
            }
        }

        for(int i  = 0;i<2;i++)
        {
            for(int j = 0;j<Hidden_Node+1;j++)
            {
                W2[i][j] = 2*Math.random()-1;
            }
        }
        //------------------------ End of Initialization -------------------

        for (int iter = 0;iter<Iteration;iter++)//Iteration
        {

            for(int i = 0;i<Train_Set.length;i++)//Each Batch
            {
                //Forward calculate Activation
                for(int j = 1;j<Hidden_Node+1;j++)
                {

                    Hidden_Layer_Activation[j] = sigmoid(Train_Set[i],W1[j]);
                }
                Hidden_Layer_Activation[0] = 1;
                Output_Layer_Activation[0] = sigmoid(Hidden_Layer_Activation, W2[0]);//male
                Output_Layer_Activation[1] = sigmoid(Hidden_Layer_Activation, W2[1]);//female

                //Backward Propagation
                //Output ERROR
                Error[0][0] =  Output_Layer_Activation[0] - label[i];
                Error[1][0] =  Output_Layer_Activation[1] - label_invert[i];

                if(Output_Layer_Activation[0]<Output_Layer_Activation[1]&&label[i]==0)//is female
                {
                    Correct=Correct+1;
                }
                else if (Output_Layer_Activation[0]>Output_Layer_Activation[1] && label[i]==1)//is Male
                {
                    Correct=Correct+1;
                }


                //Hidden Layer Error
                double[][] A = Matrix_Multiplication(Tran(W2),Error);
                double []  B = new double [Hidden_Node+1];
                double []  C = new double [Hidden_Node+1];
                for (int x = 0;x<Hidden_Node+1;x++)
                {
                    B[x] = A[x][0];
                    C[x] = 1-Hidden_Layer_Activation[x];
                }
                //Updating
                double []  D = Point_Multiplication(B,Hidden_Layer_Activation);
                double []  New_Error = Point_Multiplication(D,C);

                for (int x = 0;x<2;x++)
                {
                    for(int y=0;y<Hidden_Node;y++)
                    {
                        W2[x][y] = W2[x][y] - Error[x][0]*Hidden_Layer_Activation[y];
                    }
                }
                //doing gradient descent update for  each value in one layer
                for (int x = 0;x<Hidden_Node;x++)
                {
                    for(int y=0;y<size+1;y++)
                    {
                        W1[x][y] = W1[x][y] - LearningRate*New_Error[x]*Train_Set[i][y];
                    }
                }

            }
            //System.out.print(Correct);
            //System.out.print('\n');
            Correct=0;


        }
        //System.out.println("as");
    }


    public int Testing(double[] M){
        //make copy of M
        double[] tmp = new double[M.length];
        for(int i = 0; i < M.length; i++){
            tmp[i] = M[i];
        }

        double[] Output_Layer_Activation = new double[2];
        double[] Hidden_Layer_Activation = new double[Hidden_Node+1];

        //set first entry to 1
        for(int j = 0;j<size+1;j++)
        {
            if(j==0)
            {
                tmp[j] = 1;
                continue;
            }
            tmp[j] = M[j];
        }

        //Forward calculate Activation
        for (int j = 1; j < Hidden_Node + 1; j++) {
            Hidden_Layer_Activation[j] = sigmoid(tmp, W1[j]);
        }
        Hidden_Layer_Activation[0] = 1;
        Output_Layer_Activation[0] = sigmoid(Hidden_Layer_Activation, W2[0]);//male
        Output_Layer_Activation[1] = sigmoid(Hidden_Layer_Activation, W2[1]);//female

        if(Output_Layer_Activation[0] < Output_Layer_Activation[1]) {
            accuracy = (float)Output_Layer_Activation[1];
            return 0;
        }
        else {
            accuracy = (float)Output_Layer_Activation[0];
            return 1;
        }
    }

    public void Training(double[][] M)
    {
        int Iteration = 20;
        int Num_Layer = 3;
        double LearningRate = 0.01;
        double[] Output_Layer_Activation = new double[2];
        double[] Hidden_Layer_Activation = new double[Hidden_Node+1];
        double [] label = new double[M.length];
        double[] label_invert = new double[M.length];
        double[][] Train_Set = new double[M.length][size+1];
        int Correct = 0;
        double[][] Error = new double[2][1];

        for(int i = 0;i<M.length;i++) //Getting Label
        {
            label[i] = M[i][0];
            label_invert[i] = label[i]==0?1:0;
        }

        for(int i = 0;i<M.length;i++)
        {
            for(int j = 0;j<size+1;j++)
            {
                if(j==0)
                {
                    Train_Set[i][j] = 1;
                    continue;
                }
                Train_Set[i][j] = M[i][j];
            }
        }
        for(int i  = 0;i<Hidden_Node;i++)
        {
            for(int j = 0;j<size+1;j++)
            {
                W1[i][j] = 2*Math.random()-1;
            }
        }

        for(int i  = 0;i<2;i++)
        {
            for(int j = 0;j<Hidden_Node+1;j++)
            {
                W2[i][j] = 2*Math.random()-1;
            }
        }
        //------------------------ End of Initialization -------------------

        for (int iter = 0;iter<Iteration;iter++)//Iteration
        {

            for(int i = 0;i<Train_Set.length;i++)//Each Batch
            {
                //Forward calculate Activation
                for(int j = 1;j<Hidden_Node+1;j++)
                {

                    Hidden_Layer_Activation[j] = sigmoid(Train_Set[i],W1[j]);
                }
                Hidden_Layer_Activation[0] = 1;
                Output_Layer_Activation[0] = sigmoid(Hidden_Layer_Activation, W2[0]);//male
                Output_Layer_Activation[1] = sigmoid(Hidden_Layer_Activation, W2[1]);//female

                //Backward Propagation
                //Output ERROR
                Error[0][0] =  Output_Layer_Activation[0] - label[i];
                Error[1][0] =  Output_Layer_Activation[1] - label_invert[i];

                if(Output_Layer_Activation[0]<Output_Layer_Activation[1]&&label[i]==0)//is female
                {
                    Correct=Correct+1;
                }
                else if (Output_Layer_Activation[0]>Output_Layer_Activation[1] && label[i]==1)//is Male
                {
                    Correct=Correct+1;
                }


                //Hidden Layer Error
                double[][] A = Matrix_Multiplication(Tran(W2),Error);
                double []  B = new double [Hidden_Node+1];
                double []  C = new double [Hidden_Node+1];
                for (int x = 0;x<Hidden_Node+1;x++)
                {
                    B[x] = A[x][0];
                    C[x] = 1-Hidden_Layer_Activation[x];
                }
                //Updating
                double []  D = Point_Multiplication(B,Hidden_Layer_Activation);
                double []  New_Error = Point_Multiplication(D,C);

                for (int x = 0;x<2;x++)
                {
                    for(int y=0;y<Hidden_Node;y++)
                    {
                        W2[x][y] = W2[x][y] - Error[x][0]*Hidden_Layer_Activation[y];
                    }
                }
                //doing gradient descent update for  each value in one layer
                for (int x = 0;x<Hidden_Node;x++)
                {
                    for(int y=0;y<size+1;y++)
                    {
                        W1[x][y] = W1[x][y] - LearningRate*New_Error[x]*Train_Set[i][y];
                    }
                }

            }
            //System.out.println(Correct);
            //System.out.print('\n');
            Correct=0;



        }
        //System.out.println("as");
    }



    public double[][] Tran(double[][] A)
    {
        int Acol=A.length;
        int Arow=A[0].length;
        double[][] T=new double[Arow][Acol];
        for(int i=0;i<Acol;i++)
        {
            for(int j=0;j<Arow;j++)
            {
                T[j][i]=A[i][j];
            }
        }
        return T;
    }
    public double sigmoid(double [] x,double[] w)
    {
        double XW = 0;
        for(int i =0;i<x.length;i++)
        {
            XW  = XW + x[i]*w[i];
        }
        return (1 / (1 + Math.exp(-XW)));
    }
    public double[][] Matrix_Multiplication(double[][]A,double[][]B)
    {
        int aRows = A.length;
        int aColumns = A[0].length;
        int bRows = B.length;
        int bColumns = B[0].length;

        if (aColumns != bRows) {
            throw new IllegalArgumentException("A:Column: " + aColumns + " did not match B:Rows " + bRows + ".");
        }

        double[][] C = new double[aRows][bColumns];

        for (int i = 0; i < aRows; i++) { // aRow
            for (int j = 0; j < bColumns; j++) { // bColumn
                for (int k = 0; k < aColumns; k++) { // aColumn
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        return C;
    }
    public double[] Point_Multiplication(double[]A,double[]B)
    {
        // int aRows = A.length;
        int aColumns = A.length;
        // int bRows = B.length;
        int bColumns = B.length;
        if ( aColumns!=bColumns) {
            throw new IllegalArgumentException("Point Multiplication dimension NOT AGREE");
        }
        double[] C = new double[bColumns];
        for (int i = 0; i < aColumns; i++) {
            C[i] = A[i]*B[i];
        }
        return C;
    }

    //TODO: add 1 more entry at the end of pixels(Female & Male); male = 1, female = 0
    public double[][] fold_Shuffle()
    {
        double [][] toFold = new double [273][size+1];

        List<double[]> tmp = new ArrayList<>();
        tmp.addAll(Arrays.asList(Trainning));

        Collections.shuffle(tmp);

        double[][] tmp2 = tmp.toArray(new double[273][size+1]);

        for(int i  = 0;i <273;i++)
        {
            toFold[i] = tmp2[i];
        }
        return toFold;
    }

    float getMean(List<Float> list)
    {
        float sum = 0;
        for(float a : list)
            sum += a;
        return sum/list.size();
    }
    float getSd(List<Float> list)
    {
        float mean = getMean(list);
        float temp = 0;
        for(float a :list)
            temp += (a - mean)*(a - mean);
        return (float)Math.sqrt(temp/list.size());
    }

    public void five_fold(){
        List<Float> train_std_dev = new ArrayList<>();
        List<Float> train_mean = new ArrayList<>();
        List<Float> test_std_dev = new ArrayList<>();
        List<Float> test_mean = new ArrayList<>();

        //run 10 times
        for(int i = 0; i < 10; i++){
            List<Float> train_accuracy = new ArrayList<>();
            List<Float> test_accuracy = new ArrayList<>();

            //run 5 fold
            for(int j = 0; j < 5; j++) {

                int train_count = 0;
                int test_count = 0;

                //shuffle input images
                double[][] test_data = fold_Shuffle();

                //1:4
                int cut_point = (int) Math.floor(test_data.length / 5);
                double[][] A = new double[cut_point][size + 1];
                double[][] B = new double[test_data.length - cut_point][size + 1];

                for (int k = 0; k < test_data.length; k++) {
                    if (k < cut_point)
                        A[k] = test_data[k];
                    else
                        B[k-cut_point] = test_data[k];
                }
                //TODO: train-> set of images;
                //TODO: test-> one image each time, output  1 -> male, 0 -> female
                Training(B);


                //get accuracies for :4 and :1
                for (int k = 0; k < cut_point; k++) {
                    int prediction = Testing(A[k]);
                    if (prediction == A[k][0]) {
                        test_count += 1;
                    }
                }
                for (int k = 0; k < test_data.length - cut_point; k++) {
                    int prediction = Testing(B[k]);
                    if (prediction == B[k][0])
                        train_count += 1;
                }

                train_accuracy.add((float)train_count/B.length);
                test_accuracy.add((float)test_count/A.length);
            }
            train_std_dev.add(getSd(train_accuracy));
            train_mean.add(getMean(train_accuracy));
            test_std_dev.add(getSd(test_accuracy));
            test_mean.add(getMean(test_accuracy));
            System.out.println("-------------------- Round: "+i+"--------------------");
            System.out.print("Training mean: "+getMean(train_accuracy));
            System.out.println("  Training std. dev.: "+getSd(train_accuracy));
            System.out.print("Testing mean: "+getMean(test_accuracy));
            System.out.println("  Testing std. dev.: "+getSd(test_accuracy));
            //System.out.print('\n');
        }
    }

    //
    public void Train(){
        float acc;
        System.out.print("\n");
        Training(Trainning);
        int count = 0;
        for(int i = 0; i < 40; i++){
            int prediction = Testing(Test[i]);
            if(prediction == 1)
                System.out.print("male  ");
            else
                System.out.print("female  ");

            if(prediction == Test_Lable[i])
                count += 1;
            System.out.print(accuracy);
            System.out.print('\n');
        }
        acc = (float)count/40;
        System.out.print("accuracy for 40 cases:");
        System.out.print(acc);
    }

}
